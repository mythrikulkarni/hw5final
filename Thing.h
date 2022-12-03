//
// Created by Teni on 10/9/2022.
//


#ifndef _THING_H_
#define _THING_H_

    #include <strings.h>
    #include <string>
    #include <iostream>
    #include <stdio.h>
    #include <iomanip>
    #include <cstdlib>
    #include <sstream>
    #include <ctime>
    #include <exception>
    #include <cstring>


    // for Json::value
    #include <json/json.h>
    #include <json/reader.h>
    #include <json/writer.h>
    #include <json/value.h>

    using namespace std;
    #include "Person.h"

    class Thing {
    private:
        std::string name;
        std::string description;
        Person owner;
        GPS location;
        JvTime since_when;

    public:
        explicit Thing();
        explicit Thing(std::string);
        explicit Thing(std::string, std::string);
        explicit Thing(Person);

        std::string getName();
        void setName(std::string newName);
        std::string getDescription();
        void setDescription(std::string newDescription);
        Person getOwner();
        void setOwner(Person newOwner);
        GPS getLocation();
        void setLocation(GPS newLocation);
        void setLocation(GPS arg_location, JvTime arg_time);
        JvTime getLocationTime();

        bool isBlankThing();
        virtual Json::Value dump2JSON();
        virtual bool JSON2Object(Json::Value input);
    };
#endif