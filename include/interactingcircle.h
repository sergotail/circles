#ifndef INTERACTINGCIRCLE_H
#define INTERACTINGCIRCLE_H

#include <circle.h>

class InteractingCircle : public Circle {
public:
    explicit InteractingCircle(double const x, double const y, double const radius);
    ~InteractingCircle();
    double dx() const;
    double dy() const;
    bool isInteracting() const;
    void setPos(double const x, double const y);
    void setInteracting(bool const new_flag);
    void zeroForce();
    void accumulateForce(InteractingCircle & other, double const scale);
    void applyForce(double const dt, double const speed);

private:
    // members for using Verlet position-based approach for calculating circles interactions
    double xF;
    double yF;
    double dxF;
    double dyF;
    double xPrev;
    double yPrev;
    bool interacting; // is circle can be affected by other circles
    bool initNeeded; // true when prev pos is not set yet (using Euler method instead of Verlet)
};

#endif // INTERACTINGCIRCLE_H
