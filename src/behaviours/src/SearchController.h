#ifndef SEARCH_CONTROLLER
#define SEARCH_CONTROLLER

#include <geometry_msgs/Pose2D.h> //CNM added 3/7/18
#include <random_numbers/random_numbers.h>
#include "Controller.h"

/**
 * This class implements the search control algorithm for the rovers. The code
 * here should be modified and enhanced to improve search performance.
 */

extern bool cnmObstacleAvoided;
 
class SearchController : virtual Controller {

public:

  SearchController();

  void Reset() override;

  // performs search pattern
  Result DoWork() override;
  bool ShouldInterrupt() override;
  bool HasWork() override;

  // sets the value of the current location
  //void UpdateData(geometry_msgs::Pose2D currentLocation, geometry_msgs::Pose2D centerLocation);
  void SetCurrentLocation(Point currentLocation);
  void SetCenterLocation(Point centerLocation);
  void SetSuccesfullPickup();
  
  //Added CNM 3-7-2018
  void cnmSetCenterLocation(Point cnmCenterLocation);
  void cnmSetAvgCurrentLocation(Point cnmAVGCurrentLocation); 
  // {cnmCurrentLocation = cnmAVGCurrentLocation;}
  bool CNMCurrentLocationAVG();

  //sets the value for initial point in search pattern
  int SquareSearchStartPosition();
  
  //Added 3-5-2018
  //Finds the value for the initial point for the octagon search pattern
  int OctagonSearchStartPosition();
  
  //Added 3-5-2018
  //Finds the value for the initial point for the star search pattern
  int StarSearchStartPosition();
  
  //Added 3-6-2018
  //Finds the value for the initial point for the sector search pattern
  int SectorSearchStartPosition();
  
  //Added 3-5-2018
  //Creating point to move to
  Point SetDestination(Point centerLocation,
                       Point currentLocation, 
                       double xDelta,
                       double yDelta);
                       
  
  //Added 3-5-2018
  //Creates states to use to determine the correct search pattern.
  enum SearchState {
  SQUARE,
  OCTAGON,
  STAR,
  SECTOR,
  RANDOM
  }; 
  
  SearchState searchState; 
                       
  //Added 3-6-2018
  //Setting Search State
  void SetSearchState(SearchState searchState);
  
  //Added 3-6-2018
  void SetSectorRadius(double sectorRadius);
  
  //Added 3-6-2018
  void SetSquareHeight(double squareHeight);
  
  //Added 3-6-2018
  void SetSearchCounter(double searchCounter);
  
  //Added 3-10-18 For Obstacle Handling
  void cnmSetObstacleAvoidanceState();
  //extern bool cnmObstacleAvoided;

protected:

  void ProcessData();
  //void cnmSetObstacleAvoidanceState();

private:

  //Added CNM 3-7-2018
  //Averaged GPS center location
  Point cnmCenterLocation;
  //Averaged GPS current location
  Point cnmCurrentLocation;
  
  random_numbers::RandomNumberGenerator* rng;
  Point currentLocation;
  Point centerLocation;
  Point searchLocation;
  int attemptCount = 0;
  
  //incrememnt values for distance
  double searchCounter;
  double searchDist;
  //struct for returning data to ROS adapter
  Result result;

  // Search state
  // Flag to allow special behaviour for the first waypoint
  bool first_waypoint = true;
  bool succesfullPickup = false;
  
  //Added 3-6-18
  double squareHeight;
  double sectorRadius;
  
  //Added 3-10-18 for abstacle handling
  //bool obstacleAvoided;
  int obstacleAvoidanceCount;
  int totalObstacleAvoidanceCount;
  bool hasIncremented;
  
  //Added 3-10-18
  int searchStep;
  
};

#endif /* SEARCH_CONTROLLER */
