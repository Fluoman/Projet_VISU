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
        map();
        virtual ~map();
    protected:
    private:
        std::deque<Point> Carte;
};

#endif // MAP_H
