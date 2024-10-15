#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH 


#include "customtypes.hh"
#include <utility>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>



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




  bool add_bite(BiteID , const Name & , Coord );




  Name get_bite_name(BiteID );




  Coord get_bite_coord(BiteID );
  std::vector<BiteID> get_bites_alphabetically();




  std::vector<BiteID> get_bites_distance_increasing();




  BiteID find_bite_with_coord(Coord );




  bool change_bite_coord(BiteID , Coord );




  bool add_contour(ContourID , const Name & , ContourHeight ,
                   std::vector<Coord> );




  std::vector<ContourID> all_contours();




  Name get_contour_name(ContourID );




  std::vector<Coord> get_contour_coords(ContourID );




  ContourHeight get_contour_height(ContourID );




  bool add_subcontour_to_contour(ContourID , ContourID );




  bool add_bite_to_contour(BiteID biteid, ContourID );





  std::vector<ContourID> get_bite_in_contours(BiteID );







  std::vector<ContourID> all_subcontours_of_contour(ContourID );




  std::vector<BiteID> get_bites_closest_to(Coord );




  bool remove_bite(BiteID );




  ContourID get_closest_common_ancestor_of_contours(ContourID ,
                                                    ContourID );


private:

  struct Bite {
      Name name;
      Coord coord;
  };


struct Contour {
    ContourID id;
    Name name;
    ContourHeight height;
    std::vector<Coord> coords;
    Contour* parent;
    std::vector<Contour*> children;



    Contour(ContourID contourId, const Name& contourName, ContourHeight contourHeight,
            const std::vector<Coord>& contourCoords, Contour* contourParent = nullptr)
        : id(contourId), name(contourName), height(contourHeight), coords(contourCoords),
          parent(contourParent), children() {}
};
  std::unordered_map<BiteID, Bite*> bite_map;
  std::unordered_set<Coord> existing_coord;
  std::vector<BiteID> bite_ids_alphabetically;
  bool change_alphabeticall = true;

  std::vector<BiteID> bite_ids_distance;
  bool change_distance = true;

  std::unordered_map<Coord, BiteID> coord_to_bite_map;


  std::unordered_map<ContourID, Contour*> contourMap;
  std::vector<ContourID> contour_ids;



  std::unordered_map<BiteID, ContourID> bite_contour_map;
  ContourID find_parent(ContourID contour_id);


  std::multimap<double, BiteID> distance_map;
  std::vector<BiteID> cached_sorted_bites;
  bool distance_sorted_dirty = true;


};


#endif
