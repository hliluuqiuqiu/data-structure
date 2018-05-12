#ifndef STATICLIST_H
#define STATICLIST_H
#include "SeqList.h"
namespace SQHLib{
template <typename T,int N>
class StaticList : public SeqList<T>{
protected:
        T  m_space[N];
public:
        StaticList(){
            this->m_length = 0;
            this->m_array = m_space;
        }
        int capacity() const{
           return N;
        }
};
}
#endif // STATICLIST_H
