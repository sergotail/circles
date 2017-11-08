#include <interactingcirclelist.h>


InteractingCircleList::InteractingCircleList() {
    circles.clear();
}

InteractingCircleList::~InteractingCircleList() {}

ic_vector InteractingCircleList::circlesVector() const {
    std::lock_guard<std::mutex>(this->circles_mutex);
    // caching current circles list state (must be "atomic")
    ic_vector vec;
    vec.reserve(circles.size());
    std::copy(std::begin(circles), std::end(circles), std::back_inserter(vec));
    return vec;
}

size_t InteractingCircleList::size() const {
    std::lock_guard<std::mutex>(this->circles_mutex);
    return circles.size();
}

void InteractingCircleList::setPos(ic_list::iterator const it, double const x, double const y) {
    std::lock_guard<std::mutex>(this->circles_mutex);
    it->setPos(x, y);
}

void InteractingCircleList::setInteracting(ic_list::iterator const it, const bool new_flag) {
    std::lock_guard<std::mutex>(this->circles_mutex);
    it->setInteracting(new_flag);
}

void InteractingCircleList::zeroForce(ic_list::iterator const it) {
    std::lock_guard<std::mutex>(this->circles_mutex);
    it->zeroForce();
}

ic_list::iterator InteractingCircleList::emplaceFront(InteractingCircle const & circle) {
    std::lock_guard<std::mutex>(this->circles_mutex);
    return circles.emplace(circles.begin(), circle);
}

ic_list::iterator InteractingCircleList::erase(ic_list::iterator it) {
    std::lock_guard<std::mutex>(this->circles_mutex);
    return circles.erase(it);
}

void InteractingCircleList::moveCircles(double const dt, double const scale, double const speed) {
    std::lock_guard<std::mutex>(this->circles_mutex);
    // lock mutex both for force accumulation and applying (move circles operation must be "atomic")
    for (auto it1 = circles.begin(); it1 != circles.end(); ++it1) {
        for (auto it2 = it1; it2 != circles.end(); ++it2) {
            it1->accumulateForce(*it2, scale);
        }
    }
    for (auto it = circles.begin(); it != circles.end(); ++it) {
        it->applyForce(dt, speed);
    }
}
