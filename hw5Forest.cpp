
// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

// for JsonRPCCPP
#include <iostream>
#include "hw5forest.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include "hw5home.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <stdio.h>

// ecs36b
#include "IOT_Thing.h"
#include "Person.h"
#include "Thing.h"
#include <time.h>

using namespace jsonrpc;
using namespace std;

// std::map (key, value pairs)
std::map<std::string, Thing *> Thing_Map;
std::map<std::string, Person *> Person_Map;

// my location
GPS process_here;
GPS LittleRedHouse = GPS ("Red's and her Mother's House", "Village", 0.0);
GPS meetingSpot = GPS ("entrance of the woods", "Forest");
GPS grandmotherHouse = GPS("Grandma's house", "end of Woods", "three large oak", 0.5);
Person LittleRedRidingHood = Person("Little Red Riding Hood", meetingSpot);

class Myhw5Forest : public hw5Forest {
public:
  Myhw5Forest(AbstractServerConnector &connector, serverVersion_t type);
  virtual Json::Value move(const std::string& action,
			   const std::string& class_id,
			   const Json::Value& json_object,
			   const Json::Value& location,
			   const std::string& object_id);
  virtual Json::Value search(const std::string& action,
			     const std::string& class_id,
			     const std::string& object_id);
  virtual Json::Value dump2JSON(const std::string& action,
				const std::string& arguments,
				const std::string& class_id,
				const std::string& host_url,
				const std::string& object_id);
};

Myhw5Forest::Myhw5Forest(AbstractServerConnector &connector, serverVersion_t type)
  : hw5Forest(connector, type)
{
  std::cout << "Myhw5Forest Server Object created" << std::endl;
}

// member functions
HttpClient httpclient("http://127.0.0.1:7375");
hw5Home myClient(httpclient, JSONRPC_CLIENT_V2);
Json::Value myv;

Json::Value
Myhw5Forest::move
(const std::string& action, const std::string& class_id,
 const Json::Value& json_object, const Json::Value& location,
 const std::string& object_id)
{
  int error_code = 0;
  Json::Value result;
  std::string strJson;

  std::cout << "Move\n";
  if (class_id != "Person" && class_id != "Thing")
    {
      result["status"] = "failed";
      strJson = ( "class " + class_id + " unknown");
      result["reason"] = strJson;
      error_code = -1;
    }

  if (object_id.empty())
    {
      result["status"] = "failed";
      strJson = ( "object_id null ");
      result["reason"] = strJson;
      error_code = -2;
    }

  GPS incoming_location;
  if ((location.isNull() == true) ||
      (location.isObject() == false))
    {
      result["status"] = "failed";
      strJson = ( "location parsing error " );
      result["reason"] = strJson;
      error_code = -3;
    }

  if ((json_object.isNull() == true) ||
      (json_object.isObject() == false))
    {
      result["status"] = "failed";
      strJson = ( "person parsing error " );
      result["reason"] = strJson;
      error_code = -4;
    }

  if (error_code == 0)
    {
      incoming_location.JSON2Object(location);
      //std::cout << incoming_location.dump2JSON() << std::endl;
      //std::cout << process_here.dump2JSON() << std::endl;
      if (!(process_here==incoming_location))
       {
        result["status"] = "failed";
        strJson = ( "location mismatched" );
        result["reason"] = strJson;
        error_code = -5;
       }
      else
	{
	  Person * lv_person_ptr;
	  if (Person_Map.find(object_id) != Person_Map.end())
	    {
	      lv_person_ptr = Person_Map[object_id];
	    }
	  else
	    {
	      lv_person_ptr = new Person();
	      Person_Map[object_id] = lv_person_ptr;
	    }
    //std::cout << json_object.toStyledString() << std::endl;
	  lv_person_ptr->JSON2Object(json_object);

	  // originally from hw5Home.cpp
    GPS LittleRedHouse = GPS ("Red's and her Mother's House", "Village", 0.0);
    GPS meetingSpot = GPS ("entrance of the woods", "Woods");
    GPS grandmotherHouse = GPS("Grandma's house", "end of Woods", "three large oak", 0.5);
    Person LittleRedRidingHood = Person("Little Red Riding Hood", meetingSpot);
    LittleRedRidingHood.setLocation(meetingSpot, *getNowJvTime());
	  HttpClient httpclient("http://127.0.0.1:7375");
	  hw5Home myClient(httpclient, JSONRPC_CLIENT_V2);
	  Json::Value myv;

	  try {
	    //GPS_DD gps_Home_Woodland { 38.672215864622636, -121.72280111121437 };

      std::cout << lv_person_ptr->dump2JSON().toStyledString() << std::endl;
      //std::cout << LittleRedRidingHood.dump2JSON().toStyledString() << std::endl;
	    myv = myClient.move("move", "Person",
				//LittleRedRidingHood.dump2JSON(),
        lv_person_ptr->dump2JSON(),
				//gps_Home_Woodland.dump2JSON(),
        grandmotherHouse.dump2JSON(),
				"987654321");
	  } catch (JsonRpcException &e) {
	    cerr << e.what() << endl;
	  }
	  std::cout << myv.toStyledString() << std::endl;
    //std::cout << LittleRedRidingHood.dump2JSON().toStyledString() << std::endl;
    std::cout << lv_person_ptr->dump2JSON().toStyledString() << std::endl;
	  result["status"] = "successful";
	}
    }

  //std::cout << result.toStyledString() << std::endl;
  return result;
}

Json::Value
Myhw5Forest::search
(const std::string& action, const std::string& class_id,
 const std::string& object_id)
{
  int error_code = 0;
  int rc;
  Json::Value result;
  std::string strJson;

  if (class_id != "Person")
    {
      result["status"] = "failed";
      strJson = ( "class " + class_id + " unknown");
      result["reason"] = strJson;
      error_code = -1;
    }

  if (object_id.empty())
    {
      result["status"] = "failed";
      strJson = ( "object_id null ");
      result["reason"] = strJson;
      error_code = -2;
    }

  Person * lv_person_ptr;
  if (Person_Map.find(object_id) != Person_Map.end())
    {
      lv_person_ptr = Person_Map[object_id];
      Json::Value json_object = lv_person_ptr->dump2JSON();
      json_object["current location"] = process_here.dump2JSON();
      result["object"] = json_object;
      result["status"] = "successful";
    }
  else
    {
      result["status"] = "failed";
      strJson = ( "object_id not found ");
      result["reason"] = strJson;
    }

  return result;
}

Json::Value
Myhw5Forest::dump2JSON
(const std::string& action, const std::string& arguments,
 const std::string& class_id, const std::string& host_url,
 const std::string& object_id)
{
  // a pointer to Thing
  Thing *thing_ptr; // now a local variable

  Json::Value result;
  std::cout << action << " " << arguments << std::endl;
  std::string strJson;

  if (class_id != "Thing")
    {
      result["status"] = "failed";
      strJson = ( "class " + class_id + " unknown");
      result["reason"] = strJson;
    }
  else
    {
      if (Thing_Map.find(object_id) != Thing_Map.end())
	{
	  thing_ptr = Thing_Map[object_id];
	  result = thing_ptr->dump2JSON();
	  result["status"] = "successful";
	}
      else
	{
	  result["status"] = "failed";
	  strJson = ( "object " + object_id + " unknown");
	  result["reason"] = strJson;
	}
  }
  return result;
}

int main()
{
  /*GPS LittleRedHouse = GPS ("Red's and her Mother's House", "Village", 0.0);
  GPS meetingSpot = GPS ("entrance of the woods", "Forest");
  GPS grandmotherHouse = GPS("Grandma's house", "end of Woods", "three large oak", 0.5);
  Person LittleRedRidingHood = Person("Little Red Riding Hood", meetingSpot);*/
  LittleRedRidingHood.setLocation(meetingSpot, *getNowJvTime());
  // set location here
  //process_here = gps_TLC_UCDavis; // server, forrest
  process_here = meetingSpot;
  
#define _GPS_STUFF_
#ifdef _GPS_STUFF_

#endif /* _GPS_STUFF_ */
  
  HttpServer httpserver(7374);
  Myhw5Forest s(httpserver,
		JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the server" << endl;
  getchar();

  s.StopListening();
  return 0;
}
