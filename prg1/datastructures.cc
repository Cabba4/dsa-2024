/**
 * @brief The Datastructures class
 * STUDENTS: Modify the code below to implement the functionality of the class.
 * Also remove comments from the parameter names when you implement an operation
 * (Commenting out parameter name prevents compiler from warning about unused
 * parameters on operations you haven't yet implemented.)
 */

#include "datastructures.hh"
#include "customtypes.hh"

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

/*
Clears the data structures (all bites, contours, etc.).
For example, the all_bites and all_contours functions should return an empty vector after this command.
*/

void Datastructures::clear_all()
{
    id_map.clear();
    coord_map.clear();
}

/*
Returns all bites in the data structure. The order of the returned bites does not matter; the main program will sort them by id before printing.
*/

std::vector<BiteID> Datastructures::all_bites()
{
    std::vector<BiteID> bite_ids;
    bite_ids.reserve(id_map.size());
    for(const auto& pair : id_map) {
        bite_ids.push_back(pair.first);
    }
    return bite_ids;
}

/*
Adds a new bite to the data structure with the given id, name, and location, and returns true. Adding fails and false is returned if:

    a bite with the given id already exists in the data structure
    a bite already exists at the given coordinate
*/

bool Datastructures::add_bite(BiteID id, const Name & name, Coord xy)
{
    if (id_map.find(id) != id_map.end()){
        return false;
    }
    if (coord_map.find(xy) != coord_map.end()) {
        return false;
    }

    Bite new_bite{id, name, xy};
    id_map[id] = new_bite;
    coord_map[xy] = new_bite;

    return true;
}

/*
Returns the name of the bite.

    If no bite is found with the given id, the constant NO_NAME (defined in the customtypes.hh file) is returned.
*/

Name Datastructures::get_bite_name(BiteID id)
{
    auto it = id_map.find(id);
    if (it != id_map.end()) {
        return it->second.name;
    } else {
        return NO_NAME;
    }
}

/*
Returns the coordinates of the bite.

    If no bite is found with the given id, the constant NO_COORD (defined in the customtypes.hh file) is returned.
*/

Coord Datastructures::get_bite_coord(BiteID id)
{
    auto it = id_map.find(id);
    if (it != id_map.end()) {
        return it->second.xy;
    } else {
        return NO_COORD;
    }
}

std::vector<BiteID> Datastructures::get_bites_alphabetically()
{
  // Replace the line below with your implementation
  throw NotImplemented("get_bites_alphabetically");
}

std::vector<BiteID> Datastructures::get_bites_distance_increasing()
{
  // Replace the line below with your implementation
  throw NotImplemented("get_bites_distance_increasing");
}

BiteID Datastructures::find_bite_with_coord(Coord /*xy*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("find_bite_with_coord");
}

bool Datastructures::change_bite_coord(BiteID /*id*/, Coord /*newcoord*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("change_bite_coord");
}

bool Datastructures::add_contour(ContourID /*id*/, const Name & /*name*/, ContourHeight /*height*/,
                                 std::vector<Coord> /*coords*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("add_contour");
}

std::vector<ContourID> Datastructures::all_contours()
{
  // Replace the line below with your implementation
  throw NotImplemented("all_contours");
}

Name Datastructures::get_contour_name(ContourID /*id*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("get_contour_name");
}

std::vector<Coord> Datastructures::get_contour_coords(ContourID /*id*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("get_contour_coords");
}

ContourHeight Datastructures::get_contour_height(ContourID /*id*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("get_contour_height");
}

bool Datastructures::add_subcontour_to_contour(ContourID /*id*/,
                                               ContourID /*parentid*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("add_subcontour_to_contour");
}

bool Datastructures::add_bite_to_contour(BiteID /*biteid*/, ContourID /*contourid*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("add_bite_to_contour");
}

std::vector<ContourID> Datastructures::get_bite_in_contours(BiteID /*id*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("get_bite_in_contours");
}

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
