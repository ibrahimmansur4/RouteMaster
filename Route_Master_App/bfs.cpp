#include "bfs.h"

QVector<QPoint> BFS::findPath(const QPoint& start, const QPoint& goal, int gridWidth, int gridHeight,
                              const std::function<void(const QPoint&)>& visitCallback)
{
    QQueue<QPoint> queue;
    QSet<QPoint> visited;
    std::map<QPoint, QPoint, QPointCompare> cameFrom;

    queue.enqueue(start);
    visited.insert(start);

    while (!queue.isEmpty()) {
        QPoint current = queue.dequeue();
        visitCallback(current);

        if (current == goal) {
            // Reconstruct the path
            QVector<QPoint> path;
            while (current != start) {
                path.prepend(current);
                current = cameFrom[current];
            }
            path.prepend(start);
            return path;
        }

        for (const QPoint& neighbor : getNeighbors(current, gridWidth, gridHeight)) {
            if (!visited.contains(neighbor)) {
                queue.enqueue(neighbor);
                visited.insert(neighbor);
                cameFrom[neighbor] = current;
            }
        }
    }

    return QVector<QPoint>(); // No path found
}

bool BFS::isValid(int x, int y, int gridWidth, int gridHeight)
{
    return x >= 0 && x < gridWidth && y >= 0 && y < gridHeight;
}

QVector<QPoint> BFS::getNeighbors(const QPoint& p, int gridWidth, int gridHeight)
{
    QVector<QPoint> neighbors;
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    for (int i = 0; i < 4; ++i) {
        int newX = p.x() + dx[i];
        int newY = p.y() + dy[i];
        if (isValid(newX, newY, gridWidth, gridHeight)) {
            neighbors.append(QPoint(newX, newY));
        }
    }

    return neighbors;
}
