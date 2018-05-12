#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H
#include "Pointer.h"
namespace SQHLib{
template <typename T>
class SmartPointer : public Pointer<T>{
public:
    SmartPointer(T* p = NULL):Pointer<T>(NULL){
            if(p){
                this->mRef = p;
            }
    }
     SmartPointer(const SmartPointer<T>& sp):Pointer<T>(sp.mRef){
        std:cout<<"SmartPointer(const SmartPointer<T>& sp)"<<endl;
       const_cast<SmartPointer<T>&>(sp).mRef = NULL;
     }

     SmartPointer<T>& operator =(const SmartPointer<T>& sp){
         std:cout<<"operator =(const SmartPointer<T>& sp)"<<endl;
         if(this != &sp){
             delete this->mRef;
             this->mRef = sp.mRef;
             const_cast<SmartPointer<T>&>(sp).mRef = NULL;
         }
         return *this;
     }
     ~SmartPointer(){
         delete this->mRef;
     }
};
}
#endif // SMARTPOINTER_H
