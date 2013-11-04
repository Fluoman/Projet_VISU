#include "point.h"
#include <iostream>

Point::Point(float longitude, float latitude){
    this->longitude = longitude;
    this->latitude=latitude;
}

float Point::getLat(){ return this->latitude; }
float Point::getLon(){ return this->longitude; }

float Point::getValue(unsigned int indice){
    return this->value[indice];
}

float Point::distance(Point & P) {
     // return the distance in meters
     float toRad = 3.1415927/180;
     float R = 6371000; // m
     float dLat = (P.getLat()-this->getLat())*toRad;
     float dLon = (P.getLon()-this->getLon())*toRad;
     float lat1 = this->getLat()*toRad;
     float lat2 = P.getLat()*toRad;

     float a = sin(dLat/2) * sin(dLat/2) + sin(dLon/2) * sin(dLon/2) * cos(lat1) * cos(lat2);
     float c = 2 * atan2(sqrt(a), sqrt(1-a));
     float d = R * c;
     return d;
}

float Point::distanceEuclidienne(Point & P) {

	return sqrt(pow((self->latitude-P.latitude),2) + pow((self->longitude-P.longitude),2) ); 

}
