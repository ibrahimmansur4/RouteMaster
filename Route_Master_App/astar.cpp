// astar.cpp

#include "astar.h"
#include <queue>
#include <cmath>

float heuristic(const Point &a, const Point &b) {
    return std::sqrt((a.x - b.x) * (a.y - b.y));
}

std::vector<Point> calculateRoute(const Point &start, const Point &end) {
    std::vector<Point> path;
    // Simple A* implementation with only heuristic (no obstacles)

    // Add start point
    path.push_back(start);

    // Add end point
    path.push_back(end);

    return path;
}
