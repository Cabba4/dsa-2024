#include "datastructures.hh"
#include "customtypes.hh"


Datastructures::Datastructures()
{
}


Datastructures::~Datastructures()
{
  clear_all();


}


unsigned int Datastructures::get_bite_count()
{
    return bite_map.size();
}


void Datastructures::clear_all()
{

    for (auto& pair : bite_map) {
        delete pair.second;
    }
    bite_map.clear();
    existing_coord.clear();
    bite_ids_alphabetically.clear();
    bite_ids_distance.clear();


    coord_to_bite_map.clear();


    for (auto& pair : contourMap) {
        delete pair.second;
    }
    contourMap.clear();
    contour_ids.clear();
    bite_contour_map.clear();
    distance_map.clear();
    cached_sorted_bites.clear();
}


std::vector<BiteID> Datastructures::all_bites()
{
   return bite_ids_alphabetically;
}


bool Datastructures::add_bite(BiteID id, const Name & name, Coord xy)
{
    if (bite_map.find(id) != bite_map.end()) {
        return false;
    }

    if (existing_coord.find(xy) != existing_coord.end()) {
        return false;
    }


    bite_map[id] = new Bite{name, xy};
    existing_coord.insert(xy);

    bite_ids_alphabetically.push_back(id);
    change_alphabeticall = false;
    bite_ids_distance.push_back(id);
    change_distance = false;

    coord_to_bite_map[xy] = id;

    double distance = std::hypot(xy.x, xy.y);
    distance_map.insert({distance, id});
    distance_sorted_dirty = true;

    return true;
}


Name Datastructures::get_bite_name(BiteID id)
{
    auto it = bite_map.find(id);
    if (it == bite_map.end()) {
        return NO_NAME;
    } else {
  return it->second->name;
}
}


Coord Datastructures::get_bite_coord(BiteID id)
{
    auto it = bite_map.find(id);
    if (it == bite_map.end()) {
        return NO_COORD;
    } else {
  return it->second->coord;
}
}



// This function retrieves all BiteIDs and sorts them alphabetically by their name only if there has been a change.
// Performance Analysis:
// 1. The `change_alphabeticall` flag prevents redundant sorting operations, improving efficiency by avoiding unnecessary re-sorting.
// 2. Sorting with `std::sort` on the `bite_ids_alphabetically` vector still incurs O(n log n) complexity, but it is only done once, making subsequent calls O(1).
// 3. Criticism: Accessing `bite_map.at()` within the lambda adds overhead due to the repeated lookups for each comparison. Caching names beforehand could improve efficiency.
// 4. Praiseworthy: The flag-based approach is a significant optimization for large datasets, reducing computation in scenarios with infrequent changes.
std::vector<BiteID> Datastructures::get_bites_alphabetically()
{
    if (!change_alphabeticall) {
        std::sort(bite_ids_alphabetically.begin(), bite_ids_alphabetically.end(), [&](BiteID id1, BiteID id2) {
            const std::string& name1 = bite_map.at(id1)->name;
            const std::string& name2 = bite_map.at(id2)->name;
            if (name1 == name2) {
                return id1 < id2;
            }
            return name1 < name2;
        });
        change_alphabeticall = true;
        return bite_ids_alphabetically;
    }
    else {
        return bite_ids_alphabetically;
    }

}

// This function retrieves all BiteIDs and sorts them by increasing Manhattan distance only if there has been a change.
// Performance Analysis:
// 1. The `change_distance` flag ensures sorting is only done when needed, greatly improving performance on repeated function calls by making subsequent calls O(1).
// 2. Sorting using Manhattan distance calculation has O(n log n) complexity, but caching the results would improve performance further.
// 3. Criticism: The repeated computation of Manhattan distances for every comparison in the sort could be optimized by precomputing and storing distances in an auxiliary data structure.
// 4. Praiseworthy: The sorting logic handles tie-breaking with y-coordinates and BiteID efficiently, and the use of the change flag significantly reduces redundant work.
std::vector<BiteID> Datastructures::get_bites_distance_increasing() {
    if (!change_distance) {
    std::sort(bite_ids_distance.begin(), bite_ids_distance.end(), [&](const BiteID id1, const BiteID id2) {
        const auto& coord1 = bite_map.at(id1)->coord;
        const auto& coord2 = bite_map.at(id2)->coord;
        int distance_a = std::abs(coord1.x) + std::abs(coord1.y);
        int distance_b = std::abs(coord2.x) + std::abs(coord2.y);

        if (distance_a == distance_b)
            {

            if (coord1.y == coord2.y)
            {
                return id1 < id2;
            }
            return coord1.y < coord2.y;
            }
        return distance_a < distance_b;
    });
    change_distance = true;
    return bite_ids_distance;
    }
    else {
        return bite_ids_distance;
    }
}




BiteID Datastructures::find_bite_with_coord(Coord xy)
{
    auto it = coord_to_bite_map.find(xy);
    if (it != coord_to_bite_map.end()) {
        return it->second;
    }
    return NO_BITE;
}


bool Datastructures::change_bite_coord(BiteID id, Coord newcoord)
{
    auto it = bite_map.find(id);
    if (it == bite_map.end()) {
        return false;
    }


    if (existing_coord.find(newcoord) != existing_coord.end()) {
        return false;
    }
    existing_coord.erase(it->second->coord);
    it->second->coord = newcoord;
    existing_coord.insert(newcoord);
    coord_to_bite_map[newcoord] = id;
    change_distance = false;
    return true;
}






bool Datastructures::add_contour(ContourID id, const Name & name, ContourHeight height,
                                 std::vector<Coord> coords)
{
  if (contourMap.find(id) != contourMap.end()) {
      return false;
  }


  if (height > MAX_CONTOUR_HEIGHT || height < -MAX_CONTOUR_HEIGHT) {
      return false;
  }


  if (coords.empty()) {
      return false;
  }


  contourMap[id] = new Contour(id, name, height, coords);
  contour_ids.push_back(id);
  return true;


}


std::vector<ContourID> Datastructures::all_contours()
{
  return contour_ids;
}


Name Datastructures::get_contour_name(ContourID id)
{
    auto it = contourMap.find(id);
    if (it == contourMap.end()) {
        return NO_NAME;
    } else {
  return it->second->name;
}
}


std::vector<Coord> Datastructures::get_contour_coords(ContourID id)
{
  auto it = contourMap.find(id);
  if (it == contourMap.end()) {
      return {NO_COORD};
  }
  return it -> second -> coords;


}


ContourHeight Datastructures::get_contour_height(ContourID id)
{
  auto it = contourMap.find(id);
  if (it == contourMap.end()) {
      return NO_CONTOUR_HEIGHT;
  }
  return it -> second -> height;
}


bool Datastructures::add_subcontour_to_contour(ContourID id,
                                               ContourID parentid)
{
  auto parentIt = contourMap.find(parentid);
  auto childIt = contourMap.find(id);


  if (parentIt == contourMap.end() || childIt == contourMap.end()) {
      return false;
  }


  if (childIt->second->parent != nullptr) {
      return false;
  }


  ContourHeight parentHeight = parentIt->second->height;
  ContourHeight childHeight = childIt->second->height;


  if (childHeight < parentHeight) {
      return false;
  }


  if (std::abs(childHeight - parentHeight) != 1) {
      return false; }

  parentIt->second->children.push_back(childIt->second);
  childIt->second->parent = parentIt->second;


  return true;
}


bool Datastructures::add_bite_to_contour(BiteID biteid, ContourID contourid)
{
  auto bite_it = bite_map.find(biteid);
  auto contour_it = contourMap.find(contourid);


  if (bite_it != bite_map.end()) {
      return false;
  }


  if (contour_it != contourMap.end()) {
      return false;
  }


  if (bite_contour_map.find(biteid) != bite_contour_map.end()) {
      return false;
  }


  Coord coord_bite = bite_it->second->coord;
  const auto& coord_contour = contour_it->second->coords;
  if (std::find(coord_contour.begin(),coord_contour.end(), coord_bite) == coord_contour.end()) {
      return false;
  }


  bite_contour_map[biteid] = contourid;


  return true;


}


std::vector<ContourID> Datastructures::get_bite_in_contours(BiteID id)
{
    std::vector<ContourID> contour_chain;


    auto biteIt = bite_map.find(id);
    if (biteIt == bite_map.end()) {
        return { NO_CONTOUR };
    }


    auto contourIt = bite_contour_map.find(id);
    if (contourIt == bite_contour_map.end()) {
        return {};
    }


    ContourID current_contour = contourIt->second;
    while (true) {
        contour_chain.push_back(current_contour);


        auto parent_contour_it = contourMap.find(current_contour);
        if (parent_contour_it != contourMap.end() && parent_contour_it->second->parent != nullptr) {
            current_contour = parent_contour_it->second->parent->id;
        } else {
            break;
        }
    }


    return contour_chain;
}


std::vector<ContourID>
Datastructures::all_subcontours_of_contour(ContourID id)
{
    std::vector<ContourID> sub_contours;


    auto contourIt = contourMap.find(id);
    if (contourIt == contourMap.end()) {
        return { NO_CONTOUR };
    }


    for (const auto& pair : contourMap) {
        if (pair.second->parent && pair.second->parent->id == id) {
            sub_contours.push_back(pair.first);
        }
    }


    return sub_contours;
}


ContourID Datastructures::find_parent(ContourID contour_id) {
    auto contourIt = contourMap.find(contour_id);
    return (contourIt != contourMap.end() && contourIt->second->parent) ? contourIt->second->parent->id : NO_CONTOUR;
}


ContourID
Datastructures::get_closest_common_ancestor_of_contours(ContourID id1,
                                                        ContourID id2)
{
    std::unordered_set<ContourID> ancestors1;


    ContourID current = id1;
    while (current != NO_CONTOUR) {
        ancestors1.insert(current);
        current = find_parent(current);
    }


    current = id2;
    while (current != NO_CONTOUR) {
        if (ancestors1.find(current) != ancestors1.end()) {
            return current;
        }
        current = find_parent(current);
    }


    return NO_CONTOUR;
}


bool Datastructures::remove_bite(BiteID id)
{


    auto biteIt = bite_map.find(id);
    if (biteIt == bite_map.end()) {
        return false;
    }

    Coord coord = biteIt->second->coord;
    double distance = std::hypot(coord.x, coord.y);

    existing_coord.erase(biteIt->second->coord);
    bite_contour_map.erase(id);
    coord_to_bite_map.erase(biteIt->second->coord);
    delete biteIt->second;
    bite_map.erase(id);
    bite_ids_alphabetically.erase(std::find(bite_ids_alphabetically.begin(),bite_ids_alphabetically.end(),id));
    change_alphabeticall = false;
    bite_ids_distance.erase(std::find(bite_ids_distance.begin(),bite_ids_distance.end(),id));
    change_distance = false;

    auto range = distance_map.equal_range(distance);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second == id) {
            distance_map.erase(it);
            break;
        }
    }


    distance_sorted_dirty = true;
    return true;
}


std::vector<BiteID> Datastructures::get_bites_closest_to(Coord xy)
{
    std::vector<std::pair<double, BiteID>> distances;




    for (const auto& pair : bite_map) {
        const auto& bite_coord = pair.second->coord;
        double distance = std::hypot(bite_coord.x - xy.x, bite_coord.y - xy.y);
        distances.emplace_back(distance, pair.first);
    }




    std::sort(distances.begin(), distances.end(), [&](const auto &a, const auto &b) {
        if (a.first != b.first) return a.first < b.first;
        const auto& coordA = bite_map[a.second]->coord;
        const auto& coordB = bite_map[b.second]->coord;


        if (coordA.y != coordB.y) return coordA.y < coordB.y;
        return a.second < b.second;
    });


    std::vector<BiteID> closest_bites;
    for (size_t i = 0; i < std::min<size_t>(3, distances.size()); ++i) {
        closest_bites.push_back(distances[i].second);
    }


    return closest_bites;
}
