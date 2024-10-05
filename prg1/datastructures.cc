/**
 * @brief The Datastructures class
 * STUDENTS: Modify the code below to implement the functionality of the class.
 * Also remove comments from the parameter names when you implement an operation
 * (Commenting out parameter name prevents compiler from warning about unused
 * parameters on operations you haven't yet implemented.)
 */

#include "datastructures.hh"
#include "customtypes.hh"
#include <algorithm>

Datastructures::Datastructures()
{
  // Write any initialization you need here
}

Datastructures::~Datastructures()
{
  // Write any cleanup you need here
}

unsigned int Datastructures::get_bite_count()
{
    return id_map.size();
}

void Datastructures::clear_all() {
    id_map.clear();
    coord_map.clear();

    invalidate_cache();
    all_bites_cache_valid = false;

    cached_bite_ids_alphabetical.clear();
    cached_bite_ids_distance.clear();
    sorted_alphabetically = false;
    sorted_by_distance = false;
}

std::vector<BiteID> Datastructures::all_bites() {
    if (!all_bites_cache_valid) {
        bite_ids_cache.clear();

        if (id_map.empty()) {
            all_bites_cache_valid = true;
            return {};
        }

        bite_ids_cache.reserve(id_map.size());
        for (const auto& pair : id_map) {
            bite_ids_cache.push_back(pair.first);
        }
        all_bites_cache_valid = true;
    }
    return bite_ids_cache;
}


bool Datastructures::add_bite(BiteID id, const Name & name, Coord xy)
{
    if (id_map.find(id) != id_map.end()) {
        return false;
    }
    if (coord_map.find(xy) != coord_map.end()) {
        return false;
    }

    Bite new_bite{id, name, xy};
    id_map[id] = new_bite;
    coord_map[xy] = new_bite;

    invalidate_cache();

    return true;
}

Name Datastructures::get_bite_name(BiteID id)
{
    auto it = id_map.find(id);
    if (it != id_map.end()) {
        return it->second.name;
    } else {
        return NO_NAME;
    }
}

Coord Datastructures::get_bite_coord(BiteID id)
{
    auto it = id_map.find(id);
    if (it != id_map.end()) {
        return it->second.xy;
    } else {
        return NO_COORD;
    }
}

std::vector<BiteID> Datastructures::get_bites_alphabetically() {
    if (!sorted_alphabetically) {
        cached_bite_ids_alphabetical.clear();
        cached_bite_ids_alphabetical.reserve(id_map.size());

        for (const auto& pair : id_map) {
            cached_bite_ids_alphabetical.push_back(pair.first);
        }

        std::sort(cached_bite_ids_alphabetical.begin(), cached_bite_ids_alphabetical.end(), [this](BiteID id1, BiteID id2) {
            const Name& name1 = id_map.at(id1).name;
            const Name& name2 = id_map.at(id2).name;

            if (name1 != name2) {
                return name1 < name2;
            }
            return id1 < id2;
        });

        sorted_alphabetically = true;
    }

    return cached_bite_ids_alphabetical;
}




std::vector<BiteID> Datastructures::get_bites_distance_increasing() {
    if (!sorted_by_distance) {
        cached_bite_ids_distance.clear();
        cached_bite_ids_distance.reserve(id_map.size());

        for (const auto& entry : id_map) {
            cached_bite_ids_distance.push_back(entry.first);
        }

        std::sort(cached_bite_ids_distance.begin(), cached_bite_ids_distance.end(), [this](BiteID id1, BiteID id2) {
            const Coord& c1 = id_map.at(id1).xy;
            const Coord& c2 = id_map.at(id2).xy;

            int dist1 = std::abs(c1.x) + std::abs(c1.y);
            int dist2 = std::abs(c2.x) + std::abs(c2.y);

            if (dist1 != dist2) {
                return dist1 < dist2;
            }

            if (c1.y != c2.y) {
                return c1.y < c2.y;
            }

            return id1 < id2;
        });

        sorted_by_distance = true;
    }

    return cached_bite_ids_distance;
}


BiteID Datastructures::find_bite_with_coord(Coord xy)
{
    auto it = coord_map.find(xy);

    if (it != coord_map.end()) {
        return it->second.id;
    } else {
        return NO_BITE;
    }
}

bool Datastructures::change_bite_coord(BiteID id, Coord newcoord)
{
    auto bite_it = id_map.find(id);
    if (bite_it == id_map.end()) {
        return false;
    }

    if (coord_map.find(newcoord) != coord_map.end()) {
        return false;
    }

    ContourID contour_id = bite_it->second.contour_id;
    if (contour_id != NO_CONTOUR) {
        const Contour& contour = contour_map.at(contour_id);
        if (std::find(contour.xy.begin(), contour.xy.end(), newcoord) == contour.xy.end()) {
            return false;
        }
    }

    Coord oldcoord = bite_it->second.xy;
    coord_map.erase(oldcoord);
    coord_map[newcoord].id = id;
    bite_it->second.xy = newcoord;

    return true;
}

bool Datastructures::add_contour(ContourID id, const Name &name, ContourHeight height, std::vector<Coord> coords)
{
    if (contour_map.find(id) != contour_map.end()) {
        return false;
    }

    if (height > MAX_CONTOUR_HEIGHT || height < -MAX_CONTOUR_HEIGHT) {
        return false;
    }

    if (coords.empty()) {
        return false;
    }

    Contour new_contour;
    new_contour.id = id;
    new_contour.name = name;
    new_contour.height = height;
    new_contour.xy = coords;

    contour_map[id] = new_contour;

    return true;
}

std::vector<ContourID> Datastructures::all_contours()
{
    std::vector<ContourID> contourIDs;
    for (const auto &pair : contour_map) {
        contourIDs.push_back(pair.first);
    }
    return contourIDs;
}


Name Datastructures::get_contour_name(ContourID id)
{
    if (contour_map.find(id) != contour_map.end()) {
        return contour_map[id].name;
    } else {
        return NO_NAME;
    }
}

std::vector<Coord> Datastructures::get_contour_coords(ContourID id)
{
    if (contour_map.find(id) != contour_map.end()) {
        return contour_map[id].xy;
    } else {
        return { NO_COORD };
    }
}

ContourHeight Datastructures::get_contour_height(ContourID id)
{
    auto it = contour_map.find(id);
    if (it != contour_map.end()) {
        return it->second.height;
    } else {
        return NO_CONTOUR_HEIGHT;
    }
}

bool Datastructures::add_subcontour_to_contour(ContourID id, ContourID parentid) {
    if (contour_map.find(id) == contour_map.end() || contour_map.find(parentid) == contour_map.end()) {
        return false;
    }

    Contour& child_contour = contour_map[id];
    Contour& parent_contour = contour_map[parentid];

    if (child_contour.parent_contour != NO_CONTOUR || abs(child_contour.height - parent_contour.height) != 1) {
        return false;
    }

    if (abs(child_contour.height) < abs(parent_contour.height)) {
        return false;
    }

    child_contour.parent_contour = parentid;
    parent_contour.subcontours.push_back(id);

    return true;
}

bool Datastructures::add_bite_to_contour(BiteID biteid, ContourID contourid) {

    if (contour_map.find(contourid) == contour_map.end()) {
        return false;
    }

    if (id_map.find(biteid) == id_map.end()) {
        return false;
    }

    Contour& contour = contour_map[contourid];
    Bite& bite = id_map[biteid];

    if (bite.contour_id != NO_CONTOUR) {
        return false;
    }

    if (std::find(contour.xy.begin(), contour.xy.end(), bite.xy) == contour.xy.end()) {
        return false;
    }

    contour.bites.push_back(biteid);
    bite.contour_id = contourid;

    return true;
}

std::vector<ContourID> Datastructures::get_bite_in_contours(BiteID id) {
    std::vector<ContourID> contour_ids;

    auto bite_it = id_map.find(id);
    if (bite_it == id_map.end()) {
        return {NO_CONTOUR};
    }

    const Bite& bite = bite_it->second;

    ContourID current_contour_id = bite.contour_id;

    while (current_contour_id != NO_CONTOUR) {
        contour_ids.push_back(current_contour_id);
        auto contour_it = contour_map.find(current_contour_id);
        if (contour_it == contour_map.end()) {
            break;
        }
        const Contour& contour = contour_it->second;
        current_contour_id = contour.parent_contour;
    }

    return contour_ids;
}

// Not implemented yet

std::vector<ContourID>
Datastructures::all_subcontours_of_contour(ContourID /*id*/)
{
  throw NotImplemented("all_subcontours_of_contour");
}

ContourID
Datastructures::get_closest_common_ancestor_of_contours(ContourID /*id1*/,
                                                        ContourID /*id2*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("get_closest_common_ancestor_of_contours");
}

bool Datastructures::remove_bite(BiteID /*id*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("remove_bite");
}

std::vector<BiteID> Datastructures::get_bites_closest_to(Coord /*xy*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("get_bites_closest_to");
}
