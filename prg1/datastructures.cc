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

/*
Returns a vector of BiteIDs sorted alphabetically by name.

    Bites with the same name are sorted by their BiteIDs.
*/

std::vector<BiteID> Datastructures::get_bites_alphabetically()
{
    std::vector<BiteID> bite_ids;

    // Add all bite IDs to the vector
    for (const auto& bite : id_map) {
        bite_ids.push_back(bite.first);
    }

    // Sort the vector by name (which can contain emojis or other characters), and in case of tie, by BiteID
    std::sort(bite_ids.begin(), bite_ids.end(), [this](BiteID id1, BiteID id2) {
        const Name& name1 = id_map.at(id1).name;
        const Name& name2 = id_map.at(id2).name;

        // Use string comparison for sorting names (handles Unicode characters like emojis)
        if (name1 != name2) {
            return name1 < name2; // Unicode-based string comparison
        }
        // If names are the same, sort by BiteID
        return id1 < id2;
    });

    return bite_ids;
}

// Returns a vector of BiteIDs sorted by increasing Manhattan distance from the origin.
// If distances are equal, bites with smaller y-coordinates are sorted first.
// Bites with the same distance and y-coordinate are sorted by their BiteIDs.

std::vector<BiteID> Datastructures::get_bites_distance_increasing()
{
    std::vector<BiteID> bite_ids;

    // Fill the vector with all BiteIDs from id_map
    for (const auto& entry : id_map) {
        bite_ids.push_back(entry.first);
    }

    // Sort the bites by Manhattan distance from origin (0, 0)
    std::sort(bite_ids.begin(), bite_ids.end(), [this](BiteID id1, BiteID id2) {
        Coord c1 = id_map[id1].xy;
        Coord c2 = id_map[id2].xy;

        // Calculate Manhattan distances from the origin
        int dist1 = std::abs(c1.x) + std::abs(c1.y);
        int dist2 = std::abs(c2.x) + std::abs(c2.y);

        // Compare Manhattan distances
        if (dist1 != dist2) {
            return dist1 < dist2;
        }

        // If distances are equal, compare y-coordinates
        if (c1.y != c2.y) {
            return c1.y < c2.y;
        }

        // If y-coordinates are equal, compare BiteIDs
        return id1 < id2;
    });

    return bite_ids;
}


/*
Returns the BiteID at the given coordinates.

    If no bite exists at the coordinates, NO_BITE is returned.
*/

BiteID Datastructures::find_bite_with_coord(Coord xy)
{
    // Look for the coordinate in the coord_map
    auto it = coord_map.find(xy);

    // If the coordinate is found, return the corresponding BiteID
    if (it != coord_map.end()) {
        return it->second.id;
    } else {
        // If not found, return NO_BITE
        return NO_BITE;
    }
}

// Changes the coordinate of the bite with the given BiteID.
// Returns true if the coordinate is successfully changed.
// Returns false if:
// - No bite is found with the given id,
// - The new coordinate already contains a bite,
// - The new coordinate is invalid for the contour (if applicable).

bool Datastructures::change_bite_coord(BiteID id, Coord newcoord)
{
    auto bite_it = id_map.find(id);
    if (bite_it == id_map.end()) {
        return false;
    }

    if (coord_map.find(newcoord) != coord_map.end()) {
        return false;
    }

    // (Optional) Check if the new coordinate is valid for the contour
    // Add logic here if needed.

    Coord oldcoord = bite_it->second.xy;
    coord_map.erase(oldcoord);
    coord_map[newcoord].id = id;
    bite_it->second.xy = newcoord;

    return true;
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
