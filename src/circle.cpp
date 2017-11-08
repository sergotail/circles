#include <circle.h>

Circle::Circle(const double x, const double y, double const radius) :
    xCenter(x),
    yCenter(y),
    radius(radius < 0.0 ? 0.0 : radius) {}

Circle::~Circle() {}

double Circle::x() const {
    return xCenter;
}

double Circle::y() const {
    return yCenter;
}

double Circle::getRadius() const {
    return radius;
}

void Circle::setPos(double const x, double const y) {
    xCenter = x;
    yCenter = y;
}

void Circle::setRadius(double const radius) {
    this->radius = radius < 0.0 ? 0.0 : radius;
}
