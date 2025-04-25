#ifndef ASTAR_H
#define ASTAR_H

#include <QPoint>
#include <QVector>
#include <functional>
#include <queue>
#include <map>

class AStar {
public:
    struct Node {
        QPoint pos;
        double g;  // Cost from start to current node
        double h;  // Heuristic (estimated cost from current node to goal)
        double f;  // Total cost (g + h)

        Node(const QPoint& p, double g_cost = 0, double h_cost = 0)
            : pos(p), g(g_cost), h(h_cost), f(g_cost + h_cost) {}
    };

    struct NodeCompare {
        bool operator()(const Node& a, const Node& b) const {
            return a.f > b.f;  // Priority queue will sort by lowest f cost
        }
    };

    static QVector<QPoint> findPath(
        const QPoint& start,
        const QPoint& goal,
        int gridWidth,
        int gridHeight,
        const std::function<void(const QPoint&)>& visitCallback
    );

private:
    static bool isValid(int x, int y, int gridWidth, int gridHeight);
    static QVector<QPoint> getNeighbors(const QPoint& p, int gridWidth, int gridHeight);
    static double heuristic(const QPoint& a, const QPoint& b);
    static double calculateGCost(const QPoint& from, const QPoint& to);
    static QVector<QPoint> reconstructPath(
        const std::map<QPoint, QPoint>& cameFrom,
        const QPoint& current,
        const QPoint& start
    );
};

// Custom hash function for QPoint to use in maps and sets
inline uint qHash(const QPoint &key, uint seed = 0) noexcept
{
    return qHash(key.x(), seed) ^ qHash(key.y(), seed);
}

#endif // ASTAR_H
