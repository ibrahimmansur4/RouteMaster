#ifndef ROUTEMASTER_H
#define ROUTEMASTER_H

#include <QWidget>
#include <QPoint>

class RouteMaster : public QWidget
{
    Q_OBJECT

public:
    explicit RouteMaster(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QPoint startPoint;
    QPoint endPoint;
    bool hasStartPoint;
    bool hasEndPoint;

    void calculateDistance();
};

#endif // ROUTEMASTER_H
