#include "astar.h"
#include <QSet>
#include <cmath>

QVector<QPoint> AStar::findPath(
    const QPoint& start,
    const QPoint& goal,
    int gridWidth,
    int gridHeight,
    const std::function<void(const QPoint&)>& visitCallback
) {
    std::priority_queue<Node, std::vector<Node>, NodeCompare> openSet;
    QSet<QPoint> closedSet;
    std::map<QPoint, QPoint> cameFrom;
    std::map<QPoint, double> gScore;

    // Initialize starting node
    openSet.push(Node(start, 0, heuristic(start, goal)));
    gScore[start] = 0;

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        // Call the callback function to visualize the search
        visitCallback(current.pos);

        // If we've reached the goal, reconstruct and return the path
        if (current.pos == goal) {
            return reconstructPath(cameFrom, current.pos, start);
        }

        // Skip if we've already processed this node
        if (closedSet.contains(current.pos)) {
            continue;
        }

        closedSet.insert(current.pos);

        // Check all neighbors
        for (const QPoint& neighbor : getNeighbors(current.pos, gridWidth, gridHeight)) {
            // Skip if we've already processed this neighbor
            if (closedSet.contains(neighbor)) {
                continue;
            }

            // Calculate tentative g score
            double tentativeGScore = gScore[current.pos] + calculateGCost(current.pos, neighbor);

            // If we haven't seen this neighbor before or if this path is better
            if (!gScore.contains(neighbor) || tentativeGScore < gScore[neighbor]) {
                cameFrom[neighbor] = current.pos;
                gScore[neighbor] = tentativeGScore;
                double h = heuristic(neighbor, goal);
                openSet.push(Node(neighbor, tentativeGScore, h));
            }
        }
    }

    // No path found
    return QVector<QPoint>();
}

bool AStar::isValid(int x, int y, int gridWidth, int gridHeight) {
    return x >= 0 && x < gridWidth && y >= 0 && y < gridHeight;
}

QVector<QPoint> AStar::getNeighbors(const QPoint& p, int gridWidth, int gridHeight) {
    QVector<QPoint> neighbors;

    // Define possible movements (8 directions)
    const int dx[] = {-1, -1, -1,  0,  0,  1, 1, 1};
    const int dy[] = {-1,  0,  1, -1,  1, -1, 0, 1};

    for (int i = 0; i < 8; ++i) {
        int newX = p.x() + dx[i];
        int newY = p.y() + dy[i];

        if (isValid(newX, newY, gridWidth, gridHeight)) {
            neighbors.append(QPoint(newX, newY));
        }
    }

    return neighbors;
}

double AStar::heuristic(const QPoint& a, const QPoint& b) {
    // Using Euclidean distance as heuristic
    double dx = a.x() - b.x();
    double dy = a.y() - b.y();
    return std::sqrt(dx * dx + dy * dy);
}

double AStar::calculateGCost(const QPoint& from, const QPoint& to) {
    // Calculate actual cost between two adjacent points
    // Diagonal movement costs sqrt(2), orthogonal movement costs 1
    double dx = std::abs(from.x() - to.x());
    double dy = std::abs(from.y() - to.y());

    if (dx + dy > 1) {
        return std::sqrt(2);  // Diagonal movement
    }
    return 1.0;  // Orthogonal movement
}

QVector<QPoint> AStar::reconstructPath(
    const std::map<QPoint, QPoint>& cameFrom,
    const QPoint& current,
    const QPoint& start
) {
    QVector<QPoint> path;
    QPoint currentPos = current;

    while (currentPos != start) {
        path.prepend(currentPos);
        auto it = cameFrom.find(currentPos);
        if (it == cameFrom.end()) {
            break;
        }
        currentPos = it->second;
    }

    path.prepend(start);
    return path;
}
