#ifndef OBJECT_H
#define OBJECT_H
namespace  SQHLib {
//typedef unsigned int size_t;

class Object{
public:
    void *operator new ( size_t size) throw();
    void operator delete (void *p) throw();
    void *operator new []( size_t size) throw();
    void operator delete [](void *p) throw();
    virtual ~Object();
};
}
#endif // OBJECT_H
