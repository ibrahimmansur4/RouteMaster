#include "algorithmwindow.h"
#include "bfs.h"
#include <QPainter>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include <QThread>

AlgorithmWindow::AlgorithmWindow(const QString &algorithm, QWidget *parent)
    : QMainWindow(parent), algorithm(algorithm), hasStartPoint(false), hasEndPoint(false)
{
    setWindowTitle("Route Master - " + algorithm);
    setFixedSize(GRID_SIZE * CELL_SIZE, GRID_SIZE * CELL_SIZE + 30);

    statsWindow = new StatsWindow(this);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    statusLabel = new QLabel("Click to set start and end points", this);
    layout->addWidget(statusLabel);

    initializeGrid();

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &AlgorithmWindow::showNextPathStep);
}

void AlgorithmWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw grid
    painter.setPen(QPen(Qt::lightGray, 1));
    for (int i = 0; i <= GRID_SIZE; ++i) {
        painter.drawLine(i * CELL_SIZE, 0, i * CELL_SIZE, GRID_SIZE * CELL_SIZE);
        painter.drawLine(0, i * CELL_SIZE, GRID_SIZE * CELL_SIZE, i * CELL_SIZE);
    }

    // Draw visited cells
    painter.setBrush(QColor(200, 200, 255));
    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            if (visited[y][x]) {
                painter.drawRect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
            }
        }
    }

    // Draw path
    painter.setPen(QPen(Qt::blue, 2));
    for (int i = 1; i < currentPathIndex && i < path.size(); ++i) {
        QPoint p1 = gridToPixel(path[i-1]);
        QPoint p2 = gridToPixel(path[i]);
        painter.drawLine(p1, p2);
    }

    // Draw start point
    if (hasStartPoint) {
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::green);
        painter.drawEllipse(gridToPixel(startPoint), CELL_SIZE/3, CELL_SIZE/3);
    }

    // Draw end point
    if (hasEndPoint) {
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::red);
        painter.drawEllipse(gridToPixel(endPoint), CELL_SIZE/3, CELL_SIZE/3);
    }
}

void AlgorithmWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QPoint gridPoint = pixelToGrid(event->pos());

        if (!hasStartPoint) {
            startPoint = gridPoint;
            hasStartPoint = true;
            statusLabel->setText("Start point set. Click to set end point.");
        } else if (!hasEndPoint) {
            endPoint = gridPoint;
            hasEndPoint = true;
            statusLabel->setText("End point set. Running BFS...");
            runBFS();
        } else {
            resetGrid();
            hasStartPoint = hasEndPoint = false;
            statusLabel->setText("Grid reset. Click to set new start point.");
        }
        update();
    }
}

void AlgorithmWindow::initializeGrid()
{
    visited.resize(GRID_SIZE);
    for (int i = 0; i < GRID_SIZE; ++i) {
        visited[i].resize(GRID_SIZE);
    }
    resetGrid();
}

void AlgorithmWindow::resetGrid()
{
    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            visited[y][x] = false;
        }
    }
    path.clear();
    currentPathIndex = 0;
}

QPoint AlgorithmWindow::pixelToGrid(const QPoint& pixel)
{
    return QPoint(pixel.x() / CELL_SIZE, pixel.y() / CELL_SIZE);
}

QPoint AlgorithmWindow::gridToPixel(const QPoint& grid)
{
    return QPoint(grid.x() * CELL_SIZE + CELL_SIZE/2, grid.y() * CELL_SIZE + CELL_SIZE/2);
}

void AlgorithmWindow::runBFS()
{
    resetGrid();
    QElapsedTimer timer;
    timer.start();
    path = BFS::findPath(startPoint, endPoint, GRID_SIZE, GRID_SIZE,
        [this](const QPoint& p) {
            visited[p.y()][p.x()] = true;
            update();
            QApplication::processEvents();
            QThread::msleep(50);  // Slow down the algorithm
        }
    );
    double computationTime = timer.elapsed();
    double accuracy = path.isEmpty() ? 0.0 : 1.0;

    if (!path.isEmpty()) {
        statusLabel->setText("Path found! Animating...");
        statsWindow->updateStats(computationTime, accuracy);
        statsWindow->startPersonAnimation(path);
        statsWindow->show();
        animatePath();
    } else {
        statusLabel->setText("No path found. Click to reset.");
        statsWindow->updateStats(computationTime, accuracy);
        statsWindow->show();
    }
}

void AlgorithmWindow::animatePath()
{
    currentPathIndex = 0;
    animationTimer->start(100);  // Animate every 100 ms
}

void AlgorithmWindow::showNextPathStep()
{
    if (currentPathIndex < path.size()) {
        currentPathIndex++;
        update();
    } else {
        animationTimer->stop();
        statusLabel->setText("Animation complete. Click to reset.");
    }
}

