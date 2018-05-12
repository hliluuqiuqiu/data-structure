#ifndef SEQLIST_H
#define SEQLIST_H
#include "List.h"
#include "Exception.h"
#include "iostream"
using namespace std;
namespace  SQHLib {
template <typename T>
class SeqList : public List<T>{
 protected  :
    T * m_array;
    int m_length;
public:
    bool insert(const T& e){
        return insert(m_length,e);
    }
    bool insert(int i,const T& e){
        bool ret = (i >= 0) && (i <= m_length);
        ret = ret  &&  (m_length < capacity() ) ;
        if(ret){
            for(int p = m_length -1 ; p >=i;p--){
                m_array[p+1] = m_array[p];
            }
             m_array[i] = e;
             m_length++;
        }
        return ret;
    }
    bool remove(int i){
         bool ret = (i >= 0) && (i < m_length);
         if(ret){
             for(int p = i;p<m_length-1;p++){
                 m_array[p] = m_array[p+1];
             }
             m_length--;
         }
         return ret;
    }

    bool get(int i ,T& e){
        bool ret = (i >= 0) && (i < m_length);

        if(ret){
            cout<<"get"<<endl;
            e = m_array[i];
        }
        return ret;
    }
    bool set(int i ,const T& e){
        bool ret = (i >= 0) && (i < m_length);
        if(ret){
            m_array[i] = e;
        }
        return ret;
    }

    int  length()const{
        return m_length;
    }

    void clear(){
        m_length = 0;
    }
    T& operator[] (int i){
         bool ret = (i >= 0) && (i < m_length);
         if(ret){
             return m_array[i];
         }else{
                THROW_EXCEPTION("parameter is invalid..",InvalidParameterException);
         }
    }

    T& operator[] (int i) const{
        return (const_cast<SeqList<T> &>(*this))[i];
    }

    virtual int capacity() const= 0;
};
}

#endif // SEQLIST_H
