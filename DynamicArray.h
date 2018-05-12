#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
#include "Array.h"
#include "Exception.h"
namespace SQHLib {
template <typename T>
class DynamicArray : public Array<T>{
protected:
    int m_length;
public :
    DynamicArray(int size){
            this->m_array = new T[size];
            if(this->m_array){
                m_length = size;
            }else{

                 THROW_EXCEPTION("can not create  DynamicArray",NoEnoughMemoryException);
            }
    }

    void resize(int size){
        if(m_length != size){
                int copy_len = size > m_length ? m_length:size;
                T *array = new T[size];
                if(array){
                    for(int i = 0;i<copy_len;i++){
                            array[i] = this->m_array[i];
                    }
                    T* temp = this->m_array;
                    this->m_array = array;
                    this->m_length = size;
                    delete[] temp;
                }else{
                   THROW_EXCEPTION("can not create  DynamicArray",NoEnoughMemoryException);
                }
        }
    }

    int length() const{
        return m_length;
    }
};
}
#endif // DYNAMICARRAY_H
