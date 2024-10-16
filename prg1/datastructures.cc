#include "datastructures.hh"
#include "customtypes.hh"

Datastructures::Datastructures()
{

}

Datastructures::~Datastructures()
{

}

unsigned int Datastructures::get_bite_count()
{
    return bites.size();
}

void Datastructures::clear_all()
{
    bites.clear();
    coordinates_map.clear();
    contours.clear();
}

std::vector<BiteID> Datastructures::all_bites()
{
    std::vector<BiteID> bite_ids;


    bite_ids.reserve(bites.size());


    for (auto it=bites.begin(); it!=bites.end(); ++it){
        bite_ids.push_back(it->first);
    }

    return bite_ids;
}

bool Datastructures::add_bite(BiteID id, const Name& name, Coord xy){


    if (coordinates_map.find(xy) != coordinates_map.end()) {
        return false;
    }


    if (bites.find(id) != bites.end()) {
        return false;
    }


    Bite new_bite;
    new_bite.name = name;
    new_bite.id = id;
    new_bite.coord = xy;


    bites[id] = new_bite;


    coordinates_map[xy] = new_bite;

    return true;
}


Name Datastructures::get_bite_name(BiteID id)
{
    auto it = bites.find(id);
    if (it != bites.end()) {
        return it->second.name;
    }
    return NO_NAME;
}

Coord Datastructures::get_bite_coord(BiteID id)
{
    auto it = bites.find(id);
    if (it != bites.end()) {
        return it->second.coord;
    }
    return NO_COORD;
}

// Optimising get bites function
std::vector<BiteID> Datastructures::get_bites_alphabetically()
{
    std::vector<std::pair<BiteID, std::string>> bites_sorted;

    for (const auto& pair : bites) {
        bites_sorted.push_back({pair.first, pair.second.name});
    }

    std::sort(bites_sorted.begin(), bites_sorted.end(), [&](auto left, auto right) {
        if (left.second != right.second) {
            return left.second < right.second;
        }
        return left.first < right.first;
    });

    std::vector<BiteID> result;
    for (const auto& pair : bites_sorted) {
        result.push_back(pair.first);
    }

    return result;
}



std::vector<BiteID> Datastructures::get_bites_distance_increasing()
{
    std::vector<std::pair<BiteID, Bite>> bites_sorted;


    for (const auto& pair : bites) {
        bites_sorted.push_back(pair);
    }


    std::sort(bites_sorted.begin(), bites_sorted.end(), [&](const auto& left, const auto& right) {
        const Bite& bite1 = left.second;
        const Bite& bite2 = right.second;


        if (manhattan_distance(bite1.coord) != manhattan_distance(bite2.coord)) {
            return manhattan_distance(bite1.coord) < manhattan_distance(bite2.coord);
        }


        if (bite1.coord.y != bite2.coord.y) {
            return bite1.coord.y < bite2.coord.y;
        }


        return left.first < right.first;
    });


    std::vector<BiteID> sorted_ids;
    for (const auto& pair : bites_sorted) {
        sorted_ids.push_back(pair.first);
    }

    return sorted_ids;

}

BiteID Datastructures::find_bite_with_coord(Coord xy)
{
    auto it = coordinates_map.find(xy);
    if (it != coordinates_map.end()) {
        return it->second.id;
    }
    return NO_BITE;
}


bool Datastructures::change_bite_coord(BiteID id, Coord newcoord)
{

    auto it = bites.find(id);
    if (it == bites.end()){
        return false;
    }


    if (find_bite_with_coord(newcoord) != NO_BITE){
        return false;
    }


    Bite& bite = bites.at(id);
    ContourID contour_id = bite.contour;


    if (contour_id != NO_CONTOUR){

        std::vector<Coord> c_coords = get_contour_coords(contour_id);
        auto it = std::find(c_coords.begin(), c_coords.end(), newcoord);


        if (it == c_coords.end()) {
            return false;
        }
    }


    Coord old_coord = bite.coord;
    coordinates_map[newcoord] = bite;
    bite.coord = newcoord;
    coordinates_map.erase(old_coord);

    return true;
}


bool Datastructures::add_contour(ContourID id, const Name & name, ContourHeight height,
                                 std::vector<Coord> coords)
{

    if (contours.find(id) != contours.end() || coords.empty()) {
        return false;
    }


    if (height > MAX_CONTOUR_HEIGHT || height < -MAX_CONTOUR_HEIGHT) {
        return false;
    }


    Contour new_contour;
    new_contour.id = id;
    new_contour.name = name;
    new_contour.height = height;
    new_contour.c_coordinates = coords;

    contours[id]=new_contour;
    return true;
}

std::vector<ContourID> Datastructures::all_contours()
{
    std::vector<BiteID> contour_ids;

    for (auto it=contours.begin(); it!=contours.end(); ++it){
        contour_ids.push_back(it->first);
    }

    return contour_ids;
}

Name Datastructures::get_contour_name(ContourID id)
{
    auto it = contours.find(id);
    if (it != contours.end()) {
        return it->second.name;
    }
    return NO_NAME;
}

std::vector<Coord> Datastructures::get_contour_coords(ContourID id)
{
    auto it = contours.find(id);
    if (it != contours.end()) {
        Contour& contour = contours.at(id);
        std::vector<Coord> contour_coords = contour.c_coordinates;
        return contour_coords;
    }
    return std::vector<Coord>{NO_COORD};
}

ContourHeight Datastructures::get_contour_height(ContourID id)
{
    auto it = contours.find(id);
    if (it != contours.end()) {
        return it->second.height;
    }
    return NO_CONTOUR_HEIGHT;
}

bool Datastructures::add_subcontour_to_contour(ContourID childID, ContourID parentID)
{
    auto it_child = contours.find(childID);
    auto it_parent = contours.find(parentID);


    if (it_child == contours.end() || it_parent == contours.end()){
        return false;
    }

    Contour& parent = contours.at(parentID);
    Contour& child = contours.at(childID);


    if (child.parent != nullptr) {
        return false;
    }


    if (std::abs(child.height) < std::abs(parent.height)) {
        return false;
    }


    if (std::abs((child.height)-(parent.height)) != 1) {
        return false;
    }



    parent.children.push_back(&child);

    child.parent = &parent;
    return true;
}

bool Datastructures::add_bite_to_contour(BiteID biteid, ContourID contourid)
{

    auto bite_iter = bites.find(biteid);
    if (bite_iter == bites.end()) {
        return false;
    }


    auto contour_iter = contours.find(contourid);
    if (contour_iter == contours.end()) {
        return false;
    }

    Bite& bite = bites.at(biteid);
    Contour& contour = contours.at(contourid);


    if (bite.contour != NO_CONTOUR){
        return false;
    }


    std::vector<Coord>& c_coordinates = contour.c_coordinates;
    Coord& bite_coord = bite.coord;
    auto it = find(c_coordinates.begin(),c_coordinates.end(),bite_coord);
    if (it == c_coordinates.end()){
        return false;
    }

    contour.biteIDs.push_back(biteid);
    bite.contour = contourid;

    return true;
}

std::vector<ContourID> Datastructures::get_bite_in_contours(BiteID id)
{

    auto bite_iter = bites.find(id);
    if (bite_iter == bites.end()) {
        return std::vector<ContourID>{NO_CONTOUR};
    }

    Bite& bite = bites.at(id);

    if (bite.contour == NO_CONTOUR){
        return std::vector<ContourID>{};
    }

    std::vector<ContourID> contours_vector = {bite.contour};
    Contour& contour = contours.at(bite.contour);
    Contour* contour_ptr_to_parent = contour.parent;

    while (contour_ptr_to_parent != nullptr){
        contours_vector.push_back(contour_ptr_to_parent->id);
        contour_ptr_to_parent = contour_ptr_to_parent->parent;
    }

    return contours_vector;
}


std::vector<ContourID>
Datastructures::all_subcontours_of_contour(ContourID )
{
    throw NotImplemented("all_subcontours_of_contour");
}

ContourID
Datastructures::get_closest_common_ancestor_of_contours(ContourID ,
                                                        ContourID )
{

    throw NotImplemented("get_closest_common_ancestor_of_contours");
}

bool Datastructures::remove_bite(BiteID )
{

    throw NotImplemented("remove_bite");
}

std::vector<BiteID> Datastructures::get_bites_closest_to(Coord )
{

    throw NotImplemented("get_bites_closest_to");
}
