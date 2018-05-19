#ifndef QUEUE_H
#define QUEUE_H
#include "Object.h"
namespace SQHLib {
template <typename T>
class Queue:public Object{
public:
    virtual void add(const T& e) = 0;
    virtual void  remove() = 0;
    virtual void front(T& e) = 0;
    virtual void clear() = 0;
    virtual int length() const = 0;
};
}

#endif // QUEUE_H
