#ifndef ALGORITHMWINDOW_H
#define ALGORITHMWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPoint>
#include <QTimer>
#include <QVector>
#include "statswindow.h"

class AlgorithmWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AlgorithmWindow(const QString &algorithm, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    StatsWindow* statsWindow;
    static const int GRID_SIZE = 20;
    static const int CELL_SIZE = 30;

    QString algorithm;
    QLabel *statusLabel;
    QPoint startPoint;
    QPoint endPoint;
    bool hasStartPoint;
    bool hasEndPoint;
    QVector<QVector<bool>> visited;
    QVector<QPoint> path;
    QTimer *animationTimer;
    int currentPathIndex;

    void initializeGrid();
    void resetGrid();
    QPoint pixelToGrid(const QPoint& pixel);
    QPoint gridToPixel(const QPoint& grid);
    void runBFS();
    void animatePath();
    QLabel* personLabel;

private slots:
    void showNextPathStep();
};

#endif // ALGORITHMWINDOW_H
