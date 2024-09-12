// astar.h

#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <utility>

struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

std::vector<Point> calculateRoute(const Point &start, const Point &end);

#endif // ASTAR_H
