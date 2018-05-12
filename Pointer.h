#ifndef POINTER_H
#define POINTER_H
#include "Object.h"
namespace  SQHLib {
template <typename T>
class Pointer : public Object{
protected:
    T* mRef;
 public:

    Pointer(T* p = NULL){
        mRef = p;
    }
    T* operator ->(){
        return mRef;
    }

    T&  operator *(){
         return *mRef;
    }

    T&  get (){
         return *mRef;
    }
    bool isNull(){
        return mRef == NULL;
    }
    virtual ~Pointer(){
        std::cout<<"free pointer"<<std::endl;
     //   delete mRef;
   }
};
}
#endif // POINTER_H
