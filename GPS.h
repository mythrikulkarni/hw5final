//
// Created by Fatima Shaik on 10/9/22.
// Header File for GPS

#ifndef UHW_2_GPS_H
#define UHW_2_GPS_H

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


class GPS {
private:
    std::string name;
    //woods, village
    std::string locatedIn;
    std::string landmarks;
    double leagues;

public:
    explicit GPS();
    explicit GPS(std::string, std::string, std::string, double);
    explicit GPS(std::string, std::string);
    explicit GPS(std::string, std::string , double);
    std::string getName();
    std::string getLocatedIn();
    std::string getLandmarks();
    double getLeagues();
    double distance(GPS);
    bool operator==(GPS&);
    Json::Value dump2JSON();
    bool JSON2Object(Json::Value);
};


#endif //UHW_2_GPS_H
