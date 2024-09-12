#ifndef BFS_H
#define BFS_H

#include <QPoint>
#include <QVector>
#include <QQueue>
#include <QSet>
#include <map>
#include <functional>

// Custom hash function for QPoint
inline uint qHash(const QPoint &key, uint seed = 0) noexcept
{
    return qHash(key.x(), seed) ^ qHash(key.y(), seed);
}

// Custom comparator for QPoint
struct QPointCompare {
    bool operator()(const QPoint &a, const QPoint &b) const {
        return a.x() < b.x() || (a.x() == b.x() && a.y() < b.y());
    }
};

class BFS {
public:
    static QVector<QPoint> findPath(const QPoint& start, const QPoint& goal, int gridWidth, int gridHeight,
                                    const std::function<void(const QPoint&)>& visitCallback);

private:
    static bool isValid(int x, int y, int gridWidth, int gridHeight);
    static QVector<QPoint> getNeighbors(const QPoint& p, int gridWidth, int gridHeight);
};

#endif // BFS_H
