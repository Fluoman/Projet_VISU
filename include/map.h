#ifndef MAP_H
#define MAP_H
#include <vector>
#include <deque>
#include "point.h"

class map
{
    public:
        float shepard(Point &P, unsigned int i = 0);
        float hardy(Point &P, unsigned int i = 0);
        std::vector<Point> InitialPoints;
		std::vector<std::vector<float> > coeffHardy;
		map();
        virtual ~map();
		void computeHardy();
        std::deque<Point> Carte;
    protected:
    private:
};

#endif // MAP_H
