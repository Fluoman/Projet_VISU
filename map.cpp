#include "map.h"
#include "point.h"
map::map()
{
	InitialPoints.push_back(Point(0,0));
	InitialPoints.push_back(Point(0,4));
	InitialPoints.push_back(Point(4,0));
	InitialPoints.push_back(Point(4,4));
	InitialPoints.push_back(Point(2,2));
	for (int i=0;i<5;i++) {
		InitialPoints[i].value.push_back(float(int(i/4)));
	}
}

float map::shepard(Point &P, unsigned int i) {
    float numerator = 0.0;
    float denominator = 0.0;
    std::vector<Point>::iterator it = this->InitialPoints.begin();
    while (it != this->InitialPoints.end()) {
        float dist = (*it).distanceEuclidienne(P);
        float value = (*it).getValue(i);
        if (dist == 0) {
				P.value.push_back(value);
                return value;
        }
        numerator += value/dist;
        denominator += 1/dist;
        it++;
    }
	P.value.push_back(numerator/denominator);
    return numerator/denominator;

}

float map::hardy(Point &P, unsigned int i) {
    // Hardy inverse multiquadrics
    float c = 1;
    float res = 0;
    std::vector<Point>::iterator it = this->InitialPoints.begin();
    while (it != this->InitialPoints.end()) {
        float dist = (*it).distanceEuclidienne(P);
        float value = (*it).getValue(i);
        res += value*sqrt(dist*dist + c*c);
        it++;
    }
	P.value.push_back(res);
    return res; }
map::~map()
{
    //dtor
}
