#include <interactingcircle.h>
#include <utils.h>

#include <cmath>

InteractingCircle::InteractingCircle(double const x, double const y, double const radius) :
    Circle(x, y, radius),
    xF(0.0),
    yF(0.0),
    dxF(0.0),
    dyF(0.0),
    interacting(true),
    initNeeded(true) {}

InteractingCircle::~InteractingCircle() {}

double InteractingCircle::dx() const {
    return initNeeded ? 0.0 : xCenter - xPrev;
}

double InteractingCircle::dy() const {
    return initNeeded ? 0.0 : yCenter - yPrev;
}

bool InteractingCircle::isInteracting() const {
    return interacting;
}

void InteractingCircle::setPos(double const x, double const y) {
    Circle::setPos(x, y);
    initNeeded = true; // when changing position, prev position loose its meaning so we need to init again
}

void InteractingCircle::setInteracting(bool const new_flag) {
    interacting = new_flag;
}

void InteractingCircle::zeroForce() {
    xF = 0.0;
    yF = 0.0;
}

void InteractingCircle::accumulateForce(InteractingCircle & other, double const scale) {
    if (&other == this)
        return; // interaction is not self-acceptable
    double r_cen_x = other.xCenter - xCenter;
    double r_cen_y = other.yCenter - yCenter;
    double r_cen = std::sqrt(r_cen_x * r_cen_x + r_cen_y * r_cen_y);
    double r = (r_cen - radius - other.radius) * scale; // using scale for different force of interaction
    if (std::abs(r) < CircleUtils::distEps) {
        r = CircleUtils::distEps * (r < 0.0 ? -1.0 : 1.0) * scale;
    }
    double F = (r - 1.0) / (r * r);
    double F_x = F * (r_cen_x / r_cen);
    double F_y = F * (r_cen_y / r_cen);
    if (interacting) {
        dxF += F_x;
        dyF += F_y;
    }
    if (other.interacting) {
        other.dxF -= F_x;
        other.dyF -= F_y;
    }
}

void InteractingCircle::applyForce(double const dt, double const speed) {
    xF = dxF;
    yF = dyF;
    dxF = 0.0;
    dyF = 0.0;
    // using speed for different speed of position changing
    if (initNeeded) { // Euler
        xPrev = xCenter;
        yPrev = yCenter;
        xCenter += xF * dt * dt * speed;
        yCenter += yF * dt * dt * speed;
        initNeeded = false;
    }
    else { // Verlet
        double dx = xCenter - xPrev;
        double dy = yCenter - yPrev;
        xPrev = xCenter;
        yPrev = yCenter;
        xCenter += dx + xF * dt * dt * speed;
        yCenter += dy + yF * dt * dt * speed;
    }
}
