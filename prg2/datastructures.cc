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
#include "qdebug.h"
#include <algorithm>
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

bool Datastructures::add_connection(ConnectionID connectionid, BiteID id1, BiteID id2, std::vector<Coord> xy)
{
    if (connection_map.find(connectionid) != connection_map.end()) {
        return false;
    }

    auto bite1_it = id_map.find(id1);
    auto bite2_it = id_map.find(id2);
    if (bite1_it == id_map.end() || bite2_it == id_map.end()) {
        return false;
    }

    Coord prev = bite1_it->second.xy;
    for (const Coord& coord : xy) {
        if (prev.x != coord.x && prev.y != coord.y) {
            return false;
        }
        prev = coord;
    }

    Coord end = bite2_it->second.xy;
    if (prev.x != end.x && prev.y != end.y) {
        return false;
    }


    Connection new_connection{id1, id2, xy};
    connection_map[connectionid] = new_connection;

    bite1_it->second.connections.push_back(connectionid);
    bite2_it->second.connections.push_back(connectionid);

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
    if (id_map.find(id) == id_map.end()) {
        return {NO_BITE};
    }

    std::unordered_set<BiteID> unique_bites;

    for (const auto& conn_pair : connection_map) {
        const Connection& conn = conn_pair.second;

        if (conn.bite1 == id) {
            unique_bites.insert(conn.bite2);
        } else if (conn.bite2 == id) {
            unique_bites.insert(conn.bite1);
        }
    }

    return std::vector<BiteID>(unique_bites.begin(), unique_bites.end());
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


std::vector<Coord> Datastructures::get_connection_coords(BiteID biteid, ConnectionID connectionid)
{
    auto conn_it = connection_map.find(connectionid);
    if (conn_it == connection_map.end()) {
        return {NO_COORD};
    }

    const Connection& connection = conn_it->second;

    if (connection.bite1 != biteid && connection.bite2 != biteid) {
        return {NO_COORD};
    }

    std::vector<Coord> coords;

    if (connection.bite1 == biteid) {
        coords.push_back(id_map[connection.bite1].xy);
        coords.insert(coords.end(), connection.coords.begin(), connection.coords.end());
        coords.push_back(id_map[connection.bite2].xy);
    }

    else if (connection.bite2 == biteid) {
        coords.push_back(id_map[connection.bite2].xy);
        coords.insert(coords.end(), connection.coords.rbegin(), connection.coords.rend());
        coords.push_back(id_map[connection.bite1].xy);
    }

    return coords;
}

//--------------------------------


std::vector<std::pair<Coord, Distance>> Datastructures::path_any(BiteID fromid, BiteID toid) {
    std::vector<std::pair<Coord, Distance>> path;

    // Ensure the bites exist, return error indicator if not
    if (id_map.find(fromid) == id_map.end() || id_map.find(toid) == id_map.end()) {
        return {{NO_COORD, NO_DISTANCE}};
    }

    // Get the starting and ending coordinates
    Coord from_coord = get_bite_coord(fromid);

    // BFS queue: store bite ID, the path so far, and accumulated distance
    std::queue<std::tuple<BiteID, Coord, Distance, std::vector<std::pair<Coord, Distance>>>> q;
    q.push({fromid, from_coord, 0, {{from_coord, 0}}});

    // Unordered set to track visited bites
    std::unordered_set<BiteID> visited;
    visited.insert(fromid);

    while (!q.empty()) {
        auto [current_id, current_coord, total_distance, current_path] = q.front();
        q.pop();

        // Check if we reached the destination bite
        if (current_id == toid) {
            return current_path;
        }

        // Explore all connections from the current bite
        std::vector<ConnectionID> connections = get_connections(current_id);

        for (const auto& conn_id : connections) {
            Connection connection = connection_map[conn_id];
            BiteID next_bite = (connection.bite1 == current_id) ? connection.bite2 : connection.bite1;

            // Skip already visited bites to avoid loops
            if (visited.find(next_bite) != visited.end()) {
                continue;
            }

            // Traverse through each coordinate in the connection
            for (const auto& conn_coord : connection.coords) {
                Distance distance_to_next = std::abs(conn_coord.x - current_coord.x) + std::abs(conn_coord.y - current_coord.y);
                Distance new_total_distance = total_distance + distance_to_next;

                // Build the new path including this connection point
                std::vector<std::pair<Coord, Distance>> new_path = current_path;
                new_path.emplace_back(conn_coord, new_total_distance);

                // Check if we reached the next bite
                Coord next_bite_coord = get_bite_coord(next_bite);
                if (next_bite_coord != conn_coord) {
                    Distance distance_to_bite = std::abs(next_bite_coord.x - conn_coord.x) + std::abs(next_bite_coord.y - conn_coord.y);
                    new_total_distance += distance_to_bite;
                    new_path.emplace_back(next_bite_coord, new_total_distance);
                }

                // Enqueue the next bite for further exploration
                q.push({next_bite, next_bite_coord, new_total_distance, new_path});
                visited.insert(next_bite);
            }
        }
    }

    // If we exit the loop without finding a path, return error
    return path;
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
