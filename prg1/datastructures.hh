// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include "customtypes.hh"
#include <unordered_map>
#include <vector>

// Add your own STL includes below this comment

template <typename Type>
Type random_in_range(Type start, Type end);

// This is the class you are supposed to implement

class Datastructures
{
public:
  Datastructures();
  ~Datastructures();

  // Estimate of performance: O(1)
  // Short rationale for estimate: The function simply returns the size of the `id_map`, which is a constant-time operation.
  unsigned int get_bite_count();

  // Estimate of performance: O(n)
  // Short rationale for estimate: Each call to `clear()` on an unordered_map takes linear time relative to the number of elements in the map. Since there are three maps, each of size n (assuming n is the largest map size), the overall complexity is O(n).
  void clear_all();

  // Estimate of performance: O(n)
  // Short rationale for estimate: The function iterates over all elements in `id_map` (which has n elements), and appends each key (BiteID) to a vector. This results in linear time complexity.
  std::vector<BiteID> all_bites();

  // Estimate of performance: O(log(n))
  // Short rationale for estimate: Both `id_map.find()` and `coord_map.find()` are lookup operations in an unordered_map, which typically take O(1) on average, but in the worst case (due to hash collisions), they can take O(log(n)). The insertions are also O(1) on average.
  bool add_bite(BiteID id, const Name & name, Coord xy);

  // Estimate of performance: O(1)
  // Short rationale for estimate: The `find()` operation in an unordered_map has an average time complexity of O(1). Retrieving the name from the iterator is also O(1).
  Name get_bite_name(BiteID id);

  // Estimate of performance:
  // Short rationale for estimate:
  Coord get_bite_coord(BiteID /*id*/);

  // We recommend you implement the operations below only after implementing the
  // ones above

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<BiteID> get_bites_alphabetically();

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<BiteID> get_bites_distance_increasing();

  // Estimate of performance:
  // Short rationale for estimate:
  BiteID find_bite_with_coord(Coord /*xy*/);

  // Estimate of performance:
  // Short rationale for estimate:
  bool change_bite_coord(BiteID /*id*/, Coord /*newcoord*/);

  // Estimate of performance:
  // Short rationale for estimate:
  bool add_contour(ContourID /*id*/, const Name & /*name*/, ContourHeight /*height*/,
                   std::vector<Coord> /*coords*/);

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<ContourID> all_contours();

  // Estimate of performance:
  // Short rationale for estimate:
  Name get_contour_name(ContourID /*id*/);

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<Coord> get_contour_coords(ContourID /*id*/);

  // Estimate of performance:
  // Short rationale for estimate:
  ContourHeight get_contour_height(ContourID /*id*/);

  // Estimate of performance:
  // Short rationale for estimate:
  bool add_subcontour_to_contour(ContourID /*id*/, ContourID /*parentid*/);

  // Estimate of performance:
  // Short rationale for estimate:
  bool add_bite_to_contour(BiteID biteid, ContourID /*parentid*/);

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<ContourID> get_bite_in_contours(BiteID /*id*/);

  // Non-compulsory operations

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<ContourID> all_subcontours_of_contour(ContourID /*id*/);

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<BiteID> get_bites_closest_to(Coord /*xy*/);

  // Estimate of performance:
  // Short rationale for estimate:
  bool remove_bite(BiteID /*id*/);

  // Estimate of performance:
  // Short rationale for estimate:
  ContourID get_closest_common_ancestor_of_contours(ContourID /*id1*/,
                                                    ContourID /*id2*/);

private:
  // Add stuff needed for your class implementation here
    struct Bite {
        BiteID id;
        Name name;
        Coord xy;
        ContourID contour_id = NO_CONTOUR;
    };
    std::unordered_map<BiteID, Bite> id_map;
    std::unordered_map<Coord, Bite> coord_map;

    struct Contour {
        ContourID id;
        Name name;
        ContourHeight height;
        std::vector<Coord> xy;
        ContourID parent_contour = NO_CONTOUR; // Optional parent contour ID (null if no parent)
        std::vector<ContourID> subcontours;
        std::vector<BiteID> bites;
    };
    std::unordered_map<ContourID, Contour> contour_map;
};



#endif // DATASTRUCTURES_HH
