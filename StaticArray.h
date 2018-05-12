#ifndef STATICARRAY_H
#define STATICARRAY_H
#include "Array.h"
namespace SQHLib{
template <typename T,int N>
class StaticArray :public Array<T>{
        protected:
                T  m_space[N];
        public:
           StaticArray(){
               this->m_array = m_space;
           }
           int length()const{
               return N;
           }
};
}
#endif // STATICARRAY_H
