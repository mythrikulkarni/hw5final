//
// Created by Teni on 10/9/2022.
//
#include "Thing.h"

//Default constructor
Thing::Thing() {
    this->name = "";
    this->description = "";
    this->owner = Person();
    this->location = GPS();
}

//Constructor that takes a string as an argument; sets the name of the thing
Thing::Thing(std::string name) {
    this->name = name;
    this->description = "";
    this->owner = Person();
    this->location = GPS();
}

//Constructor that sets both the name and the description of the thing
Thing::Thing(std::string name, std::string description) {
    this->name = name;
    this->description = description;
    this->owner = Person();
    this->location = GPS();
}

//Constructor that only sets the owner of the object
Thing::Thing(Person arg_owner) {
    this->name = "";
    this->description = "";
    this->owner = arg_owner;
    this->location = GPS();
}

//If available, writes the name, description, owner, and location of the thing
Json::Value Thing::dump2JSON() {
    Json::Value result { };

    if (this->name != "")
    {
        result["name"] = this->name;
    }

    if (this->description != "")
    {
        result["description"] = this->description;
    }

    Json::Value jv_result;

    if (!((this->owner).isBlankPerson()))
    {
        jv_result = (this->owner).dump2JSON();
        result["owner"] = jv_result;
    }

    if ((this->location).getName() != "")
    {
        jv_result = (this->location).dump2JSON();
        result["location"] = jv_result;
    }
    jv_result = (this->since_when).dump2JSON();
    result["since_when"] = jv_result;

    return result;
}
bool Thing::JSON2Object(Json::Value input){
    if ((input.isNull() == true) ||
        (input.isObject() != true))
    {
        return false;
    }
    if (((input["name"]).isNull() == true) ||
        ((input["name"]).isString() != true))
    {
        return false;
    }
    this->name = (input["name"]).asString();
    if (((input["description"]).isNull() == true) ||
        ((input["description"]).isString() != true))
    {
        return false;
    }
    this->description = (input["description"]).asString();
    if ((input["owner"].isNull() == true) ||
        (input["owner"].isObject() != true))
    {
        return false;
    }
    this->owner.JSON2Object(input["owner"]);
    if ((input["location"].isNull() == true) ||
        (input["location"].isObject() != true))
    {
        return false;
    }
    this->location.JSON2Object(input["location"]);
    return true;
}

//Returns the name of the object
std::string Thing::getName() {
    return this->name;
}

//Sets the object's name
void Thing::setName(std::string newName) {
    this->name = newName;
}

//Returns the description of the object
std::string Thing::getDescription() {
    return this->description;
}

//Sets the object's description
void Thing::setDescription(std::string newDescription) {
    this->description = newDescription;
}

//Returns the owner of the object
Person Thing::getOwner() {
    return this->owner;
}

//Sets the object's owner
void Thing::setOwner(Person newOwner) {
    this->owner =  newOwner;
}

//Sets the object's location
void Thing::setLocation(GPS newLocation) {
    this->location = newLocation;
}

void Thing::setLocation(GPS arg_location, JvTime arg_time){
    this->location = arg_location;
    this->since_when = arg_time;
}

JvTime Thing::getLocationTime(){
    return this-> since_when;
}

//Returns the location of the object
GPS Thing::getLocation() {
    return this->location;
}

//Checks if a thing object is blank
bool Thing::isBlankThing() {
    return (this->name == "");
}
