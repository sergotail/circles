#ifndef CIRCLE_H
#define CIRCLE_H

class Circle {
public:
    explicit Circle(double const x, double const y, double const radius);
    ~Circle();
    double x() const;
    double y() const;
    double getRadius() const;
    void setPos(double const x, double const y);
    void setRadius(double const radius);

protected:
    double xCenter;
    double yCenter;
    double radius;
};

#endif // CIRCLE_H
