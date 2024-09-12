#include "routemaster.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <cmath>

RouteMaster::RouteMaster(QWidget *parent)
    : QWidget(parent), hasStartPoint(false), hasEndPoint(false)
{
}

void RouteMaster::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw start point
    if (hasStartPoint)
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::green);
        painter.drawEllipse(startPoint, 5, 5);
    }

    // Draw end point
    if (hasEndPoint)
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::red);
        painter.drawEllipse(endPoint, 5, 5);
    }

    // Draw line between points
    if (hasStartPoint && hasEndPoint)
    {
        painter.setPen(QPen(Qt::black, 2));
        painter.drawLine(startPoint, endPoint);
    }
}

void RouteMaster::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (!hasStartPoint)
        {
            startPoint = event->pos();
            hasStartPoint = true;
        }
        else if (!hasEndPoint)
        {
            endPoint = event->pos();
            hasEndPoint = true;
            calculateDistance();
        }
        else
        {
            // Reset points
            hasStartPoint = false;
            hasEndPoint = false;
        }
        update();
    }
}

void RouteMaster::calculateDistance()
{
    double dx = endPoint.x() - startPoint.x();
    double dy = endPoint.y() - startPoint.y();
    double distance = std::sqrt(dx*dx + dy*dy);

    QMessageBox::information(this, "Distance", QString("Distance between points: %1 pixels").arg(distance));
}
