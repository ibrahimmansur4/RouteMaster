#include "statswindow.h"
#include <QPainter>
#include <QApplication>
#include <QThread>
#include <QVBoxLayout>
#include <QDebug>

StatsWindow::StatsWindow(QWidget *parent)
    : QMainWindow(parent), currentPathIndex(0)
{
    setWindowTitle("Algorithm Statistics");
    setFixedSize(400, 300);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    computationTimeLabel = new QLabel(this);
    accuracyLabel = new QLabel(this);
    personLabel = new QLabel(this);

    // Increase the size to ensure visibility
    personLabel->setScaledContents(true);
    personLabel->setFixedSize(50, 80);  // Increase size for visibility
    personLabel->setStyleSheet("background-color: rgba(255, 0, 0, 50); border: 2px solid black;");  // For debugging visibility

    layout->addWidget(computationTimeLabel);
    layout->addWidget(accuracyLabel);
    layout->addWidget(personLabel);

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &StatsWindow::movePersonToNextStep);

    // Create a pixelated graphic for the person
    QPixmap personPixmap(50, 80);  // Increased size
    personPixmap.fill(Qt::transparent);  // Transparent background

    QPainter painter(&personPixmap);
    painter.setBrush(Qt::black);

    // Draw a simple stick figure (resized for larger pixmap)
    painter.drawEllipse(20, 10, 20, 20);  // Head
    painter.drawLine(30, 30, 30, 60);     // Body
    painter.drawLine(30, 40, 10, 50);     // Left arm
    painter.drawLine(30, 40, 50, 50);     // Right arm
    painter.drawLine(30, 60, 10, 75);     // Left leg
    painter.drawLine(30, 60, 50, 75);     // Right leg

    painter.end();

    personLabel->setPixmap(personPixmap);  // Set the pixmap to the label
}

void StatsWindow::updateStats(double computationTime, double accuracy)
{
    computationTimeLabel->setText(QString("Computation Time: %1 ms").arg(computationTime));
    accuracyLabel->setText(QString("Accuracy: %1%").arg(accuracy * 100));
}

void StatsWindow::startPersonAnimation(const QVector<QPoint>& pathPoints)
{
    qDebug() << "Starting person animation...";
    path = pathPoints;
    currentPathIndex = 0;
    personLabel->move(path.first().x() - personLabel->width() / 2,
                     path.first().y() - personLabel->height());
    personLabel->show();
    animationTimer->start(100);  // Animate every 100 ms
}

void StatsWindow::movePersonToNextStep()
{
    if (currentPathIndex < path.size()) {
        qDebug() << "Moving person to" << path[currentPathIndex];
        personLabel->move(path[currentPathIndex].x() - personLabel->width() / 2,
                         path[currentPathIndex].y() - personLabel->height());
        currentPathIndex++;
    } else {
        qDebug() << "Person animation completed";
        animationTimer->stop();
        personLabel->hide();
    }
    QApplication::processEvents();
    QThread::msleep(50);  // Slow down the animation
}
