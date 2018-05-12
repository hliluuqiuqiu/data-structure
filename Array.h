#ifndef ARRAY_H
#define ARRAY_H
#include "Object.h"
#include "Exception.h"
namespace SQHLib{
template <typename T>
class Array : public Object{
    protected:
            T* m_array;
           Array(const Array & e);
            Array& operator=(const Array & e);
     public:
        Array(){}
        virtual   bool set(int i,const T& e){
                bool ret = (i>=0) && (i<length());
                if(ret){
                        m_array[i] = e;
                }
                return ret;
         }

         virtual   bool get(int i, T& e){
                    bool ret = (i>=0) && (i<length());
                    if(ret){
                             e = m_array[i];
                    }
                    return ret;
           }

          T& operator[](int i){
                    if((i>=0) && (i<length())){
                            return m_array[i];
                    }else{
                           THROW_EXCEPTION("out of bouds",IndexOutOfBoundsException);
                    }
          }

          T  operator [](int i)const{
               return (const_cast<Array<T> &>(*this))[i];
          }
         virtual  int length() const= 0;
};
}
#endif // ARRAY_H
