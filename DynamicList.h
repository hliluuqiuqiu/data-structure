#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H
#include "SeqList.h"
#include "Exception.h"
namespace SQHLib{
template <typename T>
class DynamicList : public SeqList<T>{
protected:
       int  m_capacity;
public:
       DynamicList(int capacity){
            this->m_array= new T[capacity];
            if(this->m_array != NULL){
                    m_capacity = capacity;
                    this->m_length = 0;
            }else{
                    THROW_EXCEPTION("create DynamicList failed",NoEnoughMemoryException);
            }
       }

       int capacity()const{
           return m_capacity;
       }

     void resize(int capacity){
           if(capacity < 0){
                THROW_EXCEPTION("DynamicList resize failed",InvalidParameterException);
           }

           if(capacity != m_capacity){
                T * array  = new T[capacity];
                if(array == NULL){
                     THROW_EXCEPTION("resize DynamicList failed",NoEnoughMemoryException);
                }

                int len = this->length() > capacity?capacity:this->length();
                for(int i = 0;i<len;i++){
                    array[i] = this->m_array[i];
                }

                T * t = this->m_array;
                this->m_array = array;
                this->m_length = len;
                this->capacity() = capacity;
                delete[] t;
           }
     }

    ~DynamicList(){
            delete[] this->m_array;
     }

};
}

#endif // DYNAMICLIST_H
