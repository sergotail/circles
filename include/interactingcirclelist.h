#ifndef INTERACTINGCIRCLELIST_H
#define INTERACTINGCIRCLELIST_H

#include <typedefs.h>
#include <interactingcircle.h>

class InteractingCircleList {
public:
    explicit InteractingCircleList();
    ~InteractingCircleList();
    ic_vector circlesVector() const;
    size_t size() const;
    void setPos(ic_list::iterator const it, double const x, double const y);
    void setInteracting(ic_list::iterator const it, bool const new_flag);
    void zeroForce(ic_list::iterator const it);
    ic_list::iterator emplaceFront(InteractingCircle const & circle);
    ic_list::iterator erase(ic_list::iterator it);
    void moveCircles(double const dt, double const scale, double const speed);

private:
    ic_list circles;
    mutable std::mutex circles_mutex; // mutex for circles list
};

#endif // INTERACTINGCIRCLELIST_H
