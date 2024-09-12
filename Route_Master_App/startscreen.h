#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

class StartScreen : public QMainWindow
{
    Q_OBJECT

public:
    StartScreen(QWidget *parent = nullptr);

private slots:
    void openAlgorithmWindow();

private:
    QWidget *centralWidget;
    QVBoxLayout *layout;
    QPushButton *aStarButton;
    QPushButton *dijkstraButton;
    QPushButton *rrtButton;
    QPushButton *greedyButton;
    QPushButton *depthFirstButton;
    QPushButton *breadthFirstButton;
};

#endif // STARTSCREEN_H
