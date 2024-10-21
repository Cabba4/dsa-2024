#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH 

#include "customtypes.hh"
#include <unordered_map>
#include <vector>
#include <map>
#include <algorithm>


template <typename Type>
Type random_in_range(Type start, Type end);



class Datastructures
{
public:
  Datastructures();
  ~Datastructures();



  unsigned int get_bite_count();



  void clear_all();



  std::vector<BiteID> all_bites();



  bool add_bite(BiteID id, const Name & name, Coord xy);



  Name get_bite_name(BiteID id);



  Coord get_bite_coord(BiteID id);






  std::vector<BiteID> get_bites_alphabetically();



  std::vector<BiteID> get_bites_distance_increasing();



  BiteID find_bite_with_coord(Coord xy);



  bool change_bite_coord(BiteID id, Coord newcoord);



  bool add_contour(ContourID id, const Name & name, ContourHeight height,
                   std::vector<Coord> coords);



  std::vector<ContourID> all_contours();



  Name get_contour_name(ContourID id);



  std::vector<Coord> get_contour_coords(ContourID id);



  ContourHeight get_contour_height(ContourID id);



  bool add_subcontour_to_contour(ContourID id, ContourID parentid);



  bool add_bite_to_contour(BiteID biteid, ContourID parentid);



  std::vector<ContourID> get_bite_in_contours(BiteID id);





  std::vector<ContourID> all_subcontours_of_contour(ContourID );



  std::vector<BiteID> get_bites_closest_to(Coord );



  bool remove_bite(BiteID );



  ContourID get_closest_common_ancestor_of_contours(ContourID ,
                                                    ContourID );

private:

    struct Bite {
        BiteID id;
        Name name;
        Coord xy;
        ContourID contour_id = NO_CONTOUR;
    };
    std::unordered_map<BiteID, Bite> id_map;
    std::unordered_map<Coord, Bite> coord_map;

    std::vector<BiteID> bite_ids_cache;
    bool all_bites_cache_valid = false;


    std::multimap<Name, BiteID> sorted_bites_multimap;

    std::vector<BiteID> cached_bite_ids_alphabetical;
    std::vector<BiteID> cached_bite_ids_distance;
    bool sorted_alphabetically = false;
    bool sorted_by_distance = false;


    void invalidate_cache() {
        sorted_alphabetically = false;
        sorted_by_distance = false;
        all_bites_cache_valid = false;
    }

    struct Contour {
        ContourID id;
        Name name;
        ContourHeight height;
        std::vector<Coord> xy;
        ContourID parent_contour = NO_CONTOUR;
        std::vector<ContourID> subcontours;
        std::vector<BiteID> bites;
    };
    std::unordered_map<ContourID, Contour> contour_map;
};



#endif
