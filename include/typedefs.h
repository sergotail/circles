#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <memory>
#include <mutex>
#include <list>
#include <vector>
#include <chrono>

class InteractingCircle;
class InteractingCircleList;

typedef std::shared_ptr<InteractingCircle> ic_ptr;
typedef std::list<InteractingCircle> ic_list;
typedef std::vector<InteractingCircle> ic_vector;
typedef std::shared_ptr<InteractingCircleList> ic_list_ptr;

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;

#endif // TYPEDEFS_H
