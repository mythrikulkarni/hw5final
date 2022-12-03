//
// Created by Fatima Shaik on 10/9/22.
// Header file for Person

#ifndef UHW_2_PERSON_H
#define UHW_2_PERSON_H

#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <cstdlib>

// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>

#include "GPS.h"
#include "JvTime.h"


class Person {
private:
    std::string name;
    //is creature, girl, boy, adult, elderly, ect.
    std::string type;
    GPS home;
    GPS location;
    JvTime since_when;
public:
    //Constructors:
    Person(std::string, GPS);
    Person(std::string);
    Person();

    //Setter Methods (Members)
    void setHome(GPS);
//    void setLocation(GPS, JvTime);
    void setHealth(bool);

    //Getter Methods (Members)
    std::string getName(void);
    std::string getType();
    GPS getHome();
    GPS getLocation();
    JvTime getLocationTime();
    void setLocation(GPS , JvTime);
    bool isBlankPerson();

    //Dump Method
    virtual Json::Value dump2JSON();
    virtual bool JSON2Object(Json::Value arg_jv);
};


#endif //UHW_2_PERSON_H
