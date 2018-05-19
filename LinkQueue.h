#ifndef LINKQUEUE_H
#define LINKQUEUE_H
#include "Queue.h"
#include  "LinkList.h"
namespace SQHLib {
template <typename T>
class  LinkQueue : public Queue<T>
{
protected:
LinkList<T> mQueue;
public:
virtual void add(const T& e){
    mQueue.insert(e);
}
virtual void  remove(){
    mQueue.remove(0);
}
virtual void front(T& e) {
    mQueue.get(0,e);
}
virtual void clear() {
    mQueue.clear();
}
virtual int length() const {
   return  mQueue.length();
}
};
}

#endif // LINKQUEUE_H
