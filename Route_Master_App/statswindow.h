#ifndef STATSWINDOW_H
#define STATSWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>

class StatsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StatsWindow(QWidget *parent = nullptr);

    void updateStats(double computationTime, double accuracy);
    void startPersonAnimation(const QVector<QPoint>& path);

private:
    QLabel* computationTimeLabel;
    QLabel* accuracyLabel;
    QLabel* personLabel;
    QTimer* animationTimer;
    int currentPathIndex;
    QVector<QPoint> path;

private slots:
    void movePersonToNextStep();
};

#endif // STATSWINDOW_H
