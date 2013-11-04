#ifndef __POINT__
#define __POINT__
#include <cmath>
#include <deque>

class Point {
    private:
float longitude;
float latitude;
    public:
std::deque<float> value;
float getLat();
float getLon();
float getValue(unsigned int indice);
float distance(Point & P);
Point(float longitude, float latitude);
};

#endif
