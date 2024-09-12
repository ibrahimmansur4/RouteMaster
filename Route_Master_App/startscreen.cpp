#include "startscreen.h"
#include "algorithmwindow.h"
#include <QApplication>

StartScreen::StartScreen(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Route Master - Algorithm Selection");
    setMinimumSize(300, 400);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    layout = new QVBoxLayout(centralWidget);

    aStarButton = new QPushButton("A* Algorithm", this);
    dijkstraButton = new QPushButton("Dijkstra's Algorithm", this);
    rrtButton = new QPushButton("RRT Algorithm", this);
    greedyButton = new QPushButton("Greedy Search", this);
    depthFirstButton = new QPushButton("Depth-First Search", this);
    breadthFirstButton = new QPushButton("Breadth-First Search", this);

    layout->addWidget(aStarButton);
    layout->addWidget(dijkstraButton);
    layout->addWidget(rrtButton);
    layout->addWidget(greedyButton);
    layout->addWidget(depthFirstButton);
    layout->addWidget(breadthFirstButton);

    connect(aStarButton, &QPushButton::clicked, this, &StartScreen::openAlgorithmWindow);
    connect(dijkstraButton, &QPushButton::clicked, this, &StartScreen::openAlgorithmWindow);
    connect(rrtButton, &QPushButton::clicked, this, &StartScreen::openAlgorithmWindow);
    connect(greedyButton, &QPushButton::clicked, this, &StartScreen::openAlgorithmWindow);
    connect(depthFirstButton, &QPushButton::clicked, this, &StartScreen::openAlgorithmWindow);
    connect(breadthFirstButton, &QPushButton::clicked, this, &StartScreen::openAlgorithmWindow);
}

void StartScreen::openAlgorithmWindow()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        AlgorithmWindow *algorithmWindow = new AlgorithmWindow(button->text());
        algorithmWindow->show();
    }
}
