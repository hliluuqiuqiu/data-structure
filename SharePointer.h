#ifndef SHAREPOINTER_H
#define SHAREPOINTER_H
#include "Pointer.h"
#include "Exception.h"
namespace  SQHLib {
template <typename  T>
class SharePointer : public Pointer<T>{
private:
    int* mRefCount;
    void clear()
    {
        T* toDel = this->mRef;
        int* tCount = this->mRefCount;
        this->mRef = NULL;
        this->mRefCount = NULL;
        if(tCount ){
            (*tCount)--;
            if(*tCount == 0){
                std::cout<<"smart point free"<<std::endl;
                delete toDel;
                delete tCount;
            }
        }
    }
public:
    SharePointer(T* p = NULL):Pointer<T>(NULL)
    {
         this->mRefCount = new int(1);
        if(this->mRefCount != NULL){
             this->mRef = p;
        }else{
            THROW_EXCEPTION("SharePointer:SharePointer()",NoEnoughMemoryException);
        }
    }
    SharePointer(const SharePointer<T>&  sp):Pointer<T>(sp.mRef){
        this->mRefCount = sp.mRefCount;
    }

    SharePointer<T>& operator =(const SharePointer<T>&  sp){
         if(this != &sp){
                clear();
                this->mRef = sp.mRef;
                this->mRefCount = sp.mRefCount;
                this->mRefCount++;
         }
         return *this;
    }
    ~SharePointer(){
         clear();
    }
};

 }
#endif // SHAREPOINTER_H
