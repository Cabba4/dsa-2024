/**
 * @brief The Datastructures class
 * STUDENTS: Modify the code below to implement the functionality of the class.
 * Also remove comments from the parameter names when you implement an operation
 * (Commenting out parameter name prevents compiler from warning about unused
 * parameters on operations you haven't yet implemented.)
 */

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
//#include <QDebug>
#include <unordered_set>
#include <functional>
#include <queue>
#include <set>
#include <iostream>

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
    contour_map.clear();

    invalidate_cache();
    all_bites_cache_valid = false;

    cached_bite_ids_alphabetical.clear();
    cached_bite_ids_distance.clear();
    sorted_alphabetically = false;
    sorted_by_distance = false;

    connection_map.clear();
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

    Bite new_bite{id, name, xy, NO_CONTOUR, {}};
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

std::vector<ContourID> Datastructures::all_subcontours_of_contour(ContourID id) {
    auto contour_it = contour_map.find(id);
    if (contour_it == contour_map.end()) {
        return {NO_CONTOUR};
    }

    std::vector<ContourID> subcontours;
    std::function<void(ContourID)> collect_subcontours = [&](ContourID current_id) {
        auto current_it = contour_map.find(current_id);
        if (current_it != contour_map.end()) {
            for (const ContourID& subcontour_id : current_it->second.subcontours) {
                subcontours.push_back(subcontour_id);
                collect_subcontours(subcontour_id);
            }
        }
    };

    collect_subcontours(id);

    return subcontours;
}


std::vector<BiteID> Datastructures::get_bites_closest_to(Coord xy)
{
    std::vector<std::pair<BiteID, int>> bite_distances;

    for (const auto& entry : id_map) {
        BiteID id = entry.first;
        Coord bite_coord = entry.second.xy;

        int distance = std::abs(bite_coord.x - xy.x) + std::abs(bite_coord.y - xy.y);

        bite_distances.push_back({id, distance});
    }

    std::sort(bite_distances.begin(), bite_distances.end(),
              [this](const std::pair<BiteID, int>& bite1, const std::pair<BiteID, int>& bite2) {
                  if (bite1.second != bite2.second) {
                      return bite1.second < bite2.second;
                  }
                  Coord coord1 = id_map[bite1.first].xy;
                  Coord coord2 = id_map[bite2.first].xy;
                  if (coord1.y != coord2.y) {
                      return coord1.y < coord2.y;
                  }
                  return bite1.first < bite2.first;
              }
              );

    std::vector<BiteID> closest_bites;
    for (size_t i = 0; i < std::min(size_t(3), bite_distances.size()); ++i) {
        closest_bites.push_back(bite_distances[i].first);
    }

    return closest_bites;
}


bool Datastructures::remove_bite(BiteID id)
{
    auto it = id_map.find(id);
    if (it == id_map.end()) {
        return false;
    }

    for (const ConnectionID& connection_id : it->second.connections) {
        auto conn_it = connection_map.find(connection_id);
        if (conn_it != connection_map.end()) {

            BiteID bite1 = conn_it->second.bite1;
            BiteID bite2 = conn_it->second.bite2;

            if (bite1 != id) {
                auto& connections = id_map[bite1].connections;
                connections.erase(std::remove(connections.begin(), connections.end(), connection_id), connections.end());
            }

            if (bite2 != id) {
                auto& connections = id_map[bite2].connections;
                connections.erase(std::remove(connections.begin(), connections.end(), connection_id), connections.end());
            }

            connection_map.erase(conn_it);
        }
    }

    Coord coord = it->second.xy;
    coord_map.erase(coord);

    id_map.erase(it);

    invalidate_cache();

    return true;
}

ContourID Datastructures::get_closest_common_ancestor_of_contours(ContourID id1, ContourID id2) {
    // Check if both contours exist
    if (contour_map.find(id1) == contour_map.end() || contour_map.find(id2) == contour_map.end()) {
        return NO_CONTOUR;
    }

    // Function to collect all ancestors of a given contour (excluding itself)
    auto get_ancestors = [&](ContourID id) -> std::vector<ContourID> {
        std::vector<ContourID> ancestors;
        ContourID current_id = id;

        while (current_id != NO_CONTOUR) {
            auto it = contour_map.find(current_id);
            if (it == contour_map.end()) {
                break;  // Should not happen, but safety check
            }
            current_id = it->second.parent_contour;
            if (current_id != NO_CONTOUR) {
                ancestors.push_back(current_id);
            }
        }
        return ancestors;
    };

    // Get the ancestors of both contours
    std::vector<ContourID> ancestors1 = get_ancestors(id1);
    std::vector<ContourID> ancestors2 = get_ancestors(id2);

    // Create a set of ancestors from the first contour
    std::unordered_set<ContourID> ancestors_set(ancestors1.begin(), ancestors1.end());

    // Find the first common ancestor from the second contour's ancestors
    for (const auto& ancestor : ancestors2) {
        if (ancestors_set.find(ancestor) != ancestors_set.end()) {
            return ancestor;  // Return the first common ancestor
        }
    }

    return NO_CONTOUR;  // No common ancestor found
}




/**
 * ============================
 * ============================
 * ========== PRG2 ============
 * ============================
 * ============================
 */


bool Datastructures::add_connection(ConnectionID connectionid, BiteID id1, BiteID id2,
                                    std::vector<Coord> xy)
{
    // Check if the connection ID is unique
    if (connection_map.find(connectionid) != connection_map.end()) {
        return false;  // Connection ID already exists
    }

    // Check if both bites exist
    if (id_map.find(id1) == id_map.end() || id_map.find(id2) == id_map.end()) {
        return false;  // Either bite not found
    }

    // Validate coordinates (straight line only)
    for (size_t i = 1; i < xy.size(); ++i) {
        if (xy[i - 1].x != xy[i].x && xy[i - 1].y != xy[i].y) {
            return false;  // Diagonal movement not allowed
        }
    }

    // Add the connection to the data structure
    connection_map.emplace(connectionid, Connection(id1, id2, xy));

    // Populate the bite_to_connections_ map for bite1 if
    bite_connections[id1].push_back(connectionid);

    // Populate the bite_to_connections_ map for bite2 if the bites are different
    if (id1 != id2) {
        bite_connections[id2].push_back(connectionid);
    }

    return true;
}

void Datastructures::clear_connections()
{
    connection_map.clear();

    for( auto& bite_entry : id_map) {
        bite_entry.second.connections.clear();
    }
}

std::vector<BiteID> Datastructures::get_next_bites_from(BiteID id)
{
    // Check if the bite exists
    auto it = id_map.find(id);
    if (it == id_map.end()) {
        return { NO_BITE };  // Bite not found
    }

    // Find all connections related to the bite
    auto conn_it = bite_connections.find(id);
    if (conn_it == bite_connections.end()) {
        return {};  // No connections found for the bite
    }

    // Extract the connection IDs
    const std::vector<ConnectionID>& connections = conn_it->second;

    // Find the next bites from the connections
    std::vector<BiteID> next_bites;
    for (const ConnectionID& conn_id : connections) {
        auto it = connection_map.find(conn_id);
        if (it == connection_map.end()) {
            continue;  // Connection not found
        }
        Connection connection = it->second;
        BiteID next_bite = connection.bite1 == id ? connection.bite2 : connection.bite1;
        // Check if the bite already exists in the vector
        if (std::find(next_bites.begin(), next_bites.end(), next_bite) == next_bites.end()) {
            next_bites.push_back(next_bite);
        }
    }

    return next_bites;
}

std::vector<ConnectionID> Datastructures::get_connections(BiteID id1, BiteID id2) {
    std::vector<ConnectionID> connections;

    if (id1 == NO_BITE && id2 == NO_BITE) {
        for (const auto& conn_pair : connection_map) {
            connections.push_back(conn_pair.first);
        }
        return connections;
    }

    if (id2 == NO_BITE) {
        for (const auto& conn_pair : connection_map) {
            const Connection& conn = conn_pair.second;

            if (conn.bite1 == id1 || conn.bite2 == id1) {
                connections.push_back(conn_pair.first);
            }
        }
        return connections.empty() ? std::vector<ConnectionID>{NO_CONNECTION} : connections;
    }

    bool bite1Exists = id_map.find(id1) != id_map.end();
    bool bite2Exists = id_map.find(id2) != id_map.end();


    if (!bite1Exists || !bite2Exists) {
        return {NO_CONNECTION};
    }

    for (const auto& conn_pair : connection_map) {
        const Connection& conn = conn_pair.second;

        if ((conn.bite1 == id1 && conn.bite2 == id2) ||
            (conn.bite1 == id2 && conn.bite2 == id1)) {
            connections.push_back(conn_pair.first);
        }
    }

    return connections;
}

std::vector<Coord> Datastructures::get_connection_coords(BiteID biteid,
                                                         ConnectionID connectionid)
{
    // Find the connection by ID
    auto conn_it = connection_map.find(connectionid);

    // If connection is not found, return a vector with NO_COORD
    if (conn_it == connection_map.end()) {
        return { NO_COORD };
    }

    // Extract the connection object
    const Connection& connection = conn_it->second;

    // Check if the provided biteid is part of the connection
    if (connection.bite1 != biteid && connection.bite2 != biteid) {
        return { NO_COORD };  // Return NO_COORD if bite_id is not part of the connection
    }

    // Find the start and end bites of the connection
    auto start_bite = id_map.find(connection.bite1);
    auto end_bite = id_map.find(connection.bite2);

    // Retrieve the coordinates of the connection (including start and end bites)
    std::vector<Coord> coords = connection.coords;

    // Add the start and end bite coordinates to the vector
    coords.insert(coords.begin(), start_bite->second.xy);
    coords.push_back(end_bite->second.xy);

    // If the provided bite_id is the end bite, reverse the coordinates
    if (connection.bite1 != biteid) {
        std::reverse(coords.begin(), coords.end());
    }

    return coords;  // Return the vector of coordinates
}

//--------------------------------

Distance Datastructures::manhattan_distance(const Coord& coord1, const Coord& coord2) {
    return std::abs(coord1.x - coord2.x) + std::abs(coord1.y - coord2.y);
}

std::vector<std::pair<Coord, Distance>> Datastructures::path_any(BiteID fromid, BiteID toid)
{
    // Check if the start and end bites exist in the bites_ map
    auto from_it = id_map.find(fromid);
    auto to_it = id_map.find(toid);

    // Return {NO_COORD, NO_DISTANCE} if either bite does not exist
    if (from_it == id_map.end() || to_it == id_map.end()) {
        return { { NO_COORD, NO_DISTANCE } };
    }

    // If the starting and ending bites are the same, return an empty vector
    if (fromid == toid) {
        return {};
    }

    // BFS or DFS to find any path (since we're not optimizing for shortest path)
    std::unordered_map<BiteID, BiteID> came_from; // To track the path
    std::queue<BiteID> to_visit;  // Queue for BFS

    to_visit.push(fromid);
    came_from[fromid] = NO_BITE;  // Mark the start point

    while (!to_visit.empty()) {
        BiteID current = to_visit.front();
        to_visit.pop();

        // If we reached the destination, build the path
        if (current == toid) {
            std::vector<std::pair<Coord, Distance>> path;

            // Start with the source point and trace forward to the destination
            BiteID step = toid;
            Coord prev_coord = to_it->second.xy; // Start at the destination bite

            // We'll store the path coordinates in reverse and then fix it later
            std::vector<std::pair<Coord, Distance>> reversed_path;

            // Add the destination bite's coordinate
            reversed_path.emplace_back(prev_coord, 0);

            while (step != fromid) {
                BiteID previous_bite_id = came_from[step];

                // Get the connection between step and previous_bite
                std::vector<ConnectionID> connections = get_connections(step, previous_bite_id);
                if (connections.empty()) {
                    return {}; // No valid connection found, return an empty path
                }

                // Use the first connection for simplicity
                auto connection_it = connection_map.find(connections[0]);
                if (connection_it == connection_map.end()) {
                    return {}; // Connection not found, return an empty path
                }
                auto& connection = connection_it->second;
                const std::vector<Coord>& intermediate_coords = connection.coords;

                // Determine if we need to reverse the intermediate coordinates
                bool reverse_intermediates = (connection.bite1 != step);

                if (reverse_intermediates) {
                    for (auto it = intermediate_coords.rbegin(); it != intermediate_coords.rend(); ++it) {
                        Distance dist = manhattan_distance(prev_coord, *it);
                        reversed_path.emplace_back(*it, dist);
                        prev_coord = *it;
                    }
                } else {
                    for (const auto& coord : intermediate_coords) {
                        Distance dist = manhattan_distance(prev_coord, coord);
                        reversed_path.emplace_back(coord, dist);
                        prev_coord = coord;
                    }
                }

                // Add the previous bite's coordinate and update the total distance
                Coord previous_coord = get_bite_coord(previous_bite_id);
                Distance dist = manhattan_distance(prev_coord, previous_coord);
                reversed_path.emplace_back(previous_coord, dist);

                // Move to the previous bite
                step = previous_bite_id;
                prev_coord = previous_coord;
            }

            // Now reverse the reversed_path to make it start from 'fromid' to 'toid'
            Distance total_distance = 0;
            for (auto it = reversed_path.rbegin(); it != reversed_path.rend(); ++it) {
                path.push_back({ it->first, total_distance });
                total_distance += it->second;
            }

            return path;
        }

        // Explore all connected bites from the current bite
        for (const auto& next_bite : get_next_bites_from(current)) {
            if (came_from.find(next_bite) == came_from.end()) { // Unvisited bite
                came_from[next_bite] = current;
                to_visit.push(next_bite);
            }
        }
    }

    // If no path is found, return an empty vector
    return {};
}
//--------------------------------

// Non-compulsory operations
std::vector<std::pair<Coord, Distance>> Datastructures::path_shortest(BiteID /*fromid*/,
                                                                      BiteID /*toid*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("path_shortest");
}
std::vector<std::pair<Coord, Distance>> Datastructures::path_least_bites(BiteID /*fromid*/,
                                                                         BiteID /*toid*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("path_least_bites");
}
std::vector<std::pair<Coord, Distance>> Datastructures::path_least_uphill(BiteID /*fromid*/,
                                                                          BiteID /*toid*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("path_least_uphill");
}
