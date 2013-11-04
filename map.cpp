#include "map.h"

map::map()
{
    //ctor
}

float map::shepard(Point &P, unsigned int i) {
    float numerator = 0.0;
    float denominator = 0.0;
    std::vector<Point>::iterator it = this->InitialPoints.begin();
    while (it != this->InitialPoints.end()) {
        float dist = (*it).distance(P);
        float value = (*it).getValue(i);
        if (dist == 0) {
                return value;
        }
        numerator += value/dist;
        denominator += 1/dist;
        it++;
    }
    return numerator/denominator;

}

float map::hardy(Point &P, unsigned int i) {
    // Hardy inverse multiquadrics
    float c = 1;
    float res = 0;
    std::vector<Point>::iterator it = this->InitialPoints.begin();
    while (it != this->InitialPoints.end()) {
        float dist = (*it).distance(P);
        float value = (*it).getValue(i);
        res += value*sqrt(dist*dist + c*c);
        it++;
    }
    return res; }
map::~map()
{
    //dtor
}
