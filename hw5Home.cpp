

// ecs36b first program

#include <iostream>
#include "Network.h"
#include "IOT_Thing.h"
#include "ecs36b_Exception.h"

// JSON RPC part
#include "hw5home.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

using namespace jsonrpc;
using namespace std;

int
main()
{
  Thing *thing_ptr;
  GPS LittleRedHouse = GPS ("Red's and her Mother's House", "Village", 0.0);
  GPS meetingSpot = GPS ("entrance of the woods", "Forest");
  GPS grandmotherHouse = GPS("Grandma's house", "end of Woods", "three large oak", 0.5);

  Person LittleRedRidingHood = Person("Little Red Riding Hood", LittleRedHouse);
  LittleRedRidingHood.setLocation(LittleRedHouse, *getNowJvTime());
  Thing Cap = Thing("Cap", "a head covering");
  //Cap.setOwner(LittleRedRidingHood);
  //Thing Cap = Thing("Cap", LittleRedHouse);
  Cap.setLocation(LittleRedHouse, *getNowJvTime());
  Thing Cake = Thing("Cake", "a sweet dessert");
  Cake.setLocation(LittleRedHouse, *getNowJvTime());
  Thing Wine = Thing("Wine", "a drink");
  Wine.setLocation(LittleRedHouse, *getNowJvTime());
  //Json::Value result;


  // object mobility demo for 11/18/2022 and 11/21/2022
  HttpClient httpclient("http://127.0.0.1:7374");
  hw5Home myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value myv;

  // move
  try {
    std::cout << LittleRedRidingHood.dump2JSON().toStyledString() << std::endl;
    myv = myClient.move("move", "Person",
			//John.dump2JSON(),
      LittleRedRidingHood.dump2JSON(),
			//gps_TLC_UCDavis.dump2JSON(),
      meetingSpot.dump2JSON(),
			"000000001");
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;
  std::cout << LittleRedRidingHood.dump2JSON().toStyledString() << std::endl;
  
  try {
    std::cout << Cap.dump2JSON().toStyledString() << std::endl;
    myv = myClient.move("move", "Person",
			//John.dump2JSON(),
      Cap.dump2JSON(),
			//gps_TLC_UCDavis.dump2JSON(),
      meetingSpot.dump2JSON(),
			"000000002");
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;
  std::cout << Cap.dump2JSON().toStyledString() << std::endl;
  try {
    std::cout << Cake.dump2JSON().toStyledString() << std::endl;
    myv = myClient.move("move", "Thing",
			//John.dump2JSON(),
      Cake.dump2JSON(),
			//gps_TLC_UCDavis.dump2JSON(),
      meetingSpot.dump2JSON(),
			"987654321");
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;
  std::cout << Cake.dump2JSON().toStyledString() << std::endl;
    try {
    //thing_ptr = (Thing *) (&Wine);
    //result = thing_ptr->dump2JSON();
    //cout << result.toStyledString() << endl;
    std::cout << Wine.dump2JSON().toStyledString() << std::endl;
    myv = myClient.move("move", "Thing",
			//John.dump2JSON(),
      Wine.dump2JSON(),
			//gps_TLC_UCDavis.dump2JSON(),
      meetingSpot.dump2JSON(),
			"987654321");
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;
  cout << Wine.dump2JSON().toStyledString() << endl;
  //std::cout << Wine.dump2JSON().toStyledString() << std::endl;
  exit(-2);
  //Shadow_Thing st_1 { "http://127.0.0.1:7374", "Thing", "00000001" };
  
  // search
  /*try {
    myv = myClient.search("search", "Person",
			"987654321");
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;*/

  // demo on 10/27/2022 ecs36b for JSON2Object
  /*Json::Value xyz = gps_Home_Woodland.dump2JSON();
  GPS_DD yyy;
  bool status_j = yyy.JSON2Object(xyz);
  std::cout << (yyy.dump2JSON()).toStyledString() << std::endl;
  std::cout << (gps_Home_Woodland.dump2JSON()).toStyledString() << std::endl;
  
  // demo on 11/14/2022
  Json::Value abc = John.dump2JSON();
  Person John_Clone {};
  John_Clone.JSON2Object(abc);
  John_Clone.name = "John Clone";
  abc = John_Clone.dump2JSON();
  std::cout << abc.toStyledString() << std::endl;
  
  IP_Address meatball_IP { 2850883174 };
  IOT_Thing Irish_Coffee { John , meatball_IP };
  
  Irish_Coffee.model = "HUVUDROLL";
  Irish_Coffee.sequence_num = "123456-0000";
  Irish_Coffee.description = "frozen";
  Irish_Coffee.location = gps_Home_Woodland;
  Irish_Coffee.purchased = *getNowJvTime();
  Irish_Coffee.sold = *getNowJvTime();
  Irish_Coffee.owner = John;

  Json::Value result;

  thing_ptr = (Thing *) (&Irish_Coffee);
  result = thing_ptr->dump2JSON();
  cout << result.toStyledString() << endl;

  thing_ptr = (Thing *) (&st_1);
  result = thing_ptr->dump2JSON();
  cout << result.toStyledString() << endl;*/

  return 0;
}
