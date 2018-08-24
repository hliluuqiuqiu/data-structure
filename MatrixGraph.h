#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H
#include "DynamicArray.h"
#include "Graph.h"
#include "Exception.h"
namespace SQHLib{

template <int  N, typename V , typename E>

class MatricGraph : public Graph<V,E>
{
protected:
    V*  m_vertexes[N];
    E*  m_edge[N][N];
    int getAdjacentCount(int i ){
        int retCount = 0;
        for(int j = 0; j < N ; j++){
            if(m_edge[i][j]){
                   retCount++;
            }
        }
        return retCount;
    }
public:
    MatricGraph(){
        for(int i = 0 ; i < N ; i++){
            m_vertexes[i]   = NULL;
            for(int j = 0; j < N ; j++){
                m_edge[i][j] = NULL;
            }
        }
    }

    bool getVertex(int i,V& value){
        bool ret = (i >= 0 && i < N);
        if(ret){
            if(m_vertexes[i]){
                   value = *m_vertexes[i];
            }else{
                THROW_EXCEPTION("in valid para",InvalidParameterException);
            }
        }
        return ret;
    }
    virtual bool setVertext(int i,const V& value) {
        bool ret = (i >= 0 && i < N);
         if(ret){
             if(m_vertexes[i] ==NULL){
                 V*  ver = new V();
                 if(ver){
                     *ver = value;
                 }else{
                      THROW_EXCEPTION("no mem",NoEnoughMemoryException);
                 }

                 m_vertexes[i] = ver;
             }else{
                 *m_vertexes[i]  = value;
             }
         }else{
            THROW_EXCEPTION("in valid para",InvalidParameterException);
         }
         return true;
    }
    virtual SharePointer< Array<int> > getAdjacent(int i){
       bool valid = (i >= 0 && i < N);
       if(!valid){
            THROW_EXCEPTION("in valid para",InvalidParameterException);
        }
        int retCount =  getAdjacentCount(i);

        DynamicArray<int>*  ret = new DynamicArray<int>(retCount);
        retCount = 0;
        for(int j = 0; j < N ; j++){
            if(m_edge[i][j]){
                (*ret)[retCount++]   =  j;
            }
        }
        return ret;
    }
    virtual bool getEdge(int i, int j ,E& value){
        bool  ret = (i >= 0 && i < N) && (j>= 0 && j < N);
        if(ret){
            if(m_edge[i][j]){
                value = * m_edge[i][j];
            }else{
                  THROW_EXCEPTION("in valid para",InvalidParameterException);
            }
        }
        return ret;
    }

    virtual bool setEdge(int i, int j ,const E& value){
        bool  ret = (i >= 0 && i < N) && (j>= 0 && j < N)    &&  (i != j) ;
      //  cout<<"setEdge : "<<ret;
        if(ret){
            if(m_edge[i][j]){
                 *m_edge[i][j] = value;
            }else{
                E* e = new E();
                if(e){
                    *e = value;
                     m_edge[i][j] = e;
                }else{
                    THROW_EXCEPTION("no mem",NoEnoughMemoryException);
                }
            }
        }
        return ret;
    }
    virtual bool remove(int i,int j) {
        bool  ret = (i >= 0 && i < N) && (j>= 0 && j < N);
        if(ret){
            if(m_edge[i][j]){
                 delete m_edge[i][j];
                 m_edge[i][j] = NULL;
            }else{
                 THROW_EXCEPTION("",InvalidParameterException);
            }
        }
        return ret;
    }
    virtual int vCout() {
        return N;
    }
    virtual int eCout() {
        int ret = 0;
        for(int i = 0 ; i < N ;i++){
            ret+= getAdjacentCount(i);
        }
        return ret;
    }
    virtual int OD(int i) {
        bool  valid = (i >= 0 && i < N) ;
        int ret = 0;
        if(valid){
            ret = getAdjacentCount(i);
        }else{
             THROW_EXCEPTION("in valid para",InvalidParameterException);
        }
        return ret;
    }
    virtual int ID(int i ){
        bool  valid = (i >= 0 && i < N) ;
        int ret = 0;
        if(valid){
            for(int j = 0 ; j < N ;j++){
                if(m_edge[j][i]){
                        ret++;
                }
            }
        }else{
             THROW_EXCEPTION("in valid para",InvalidParameterException);
        }
        return ret;
    }
    virtual int TD(int i) {
        return OD(i) + ID(i);
    }

    void print(){
        for(int i = 0; i < N ; i++){
            for(int j = 0; j < N ;j++ ){
                if(m_edge[i][j]){
                    cout<<" 1 ";
                }else{
                    cout<<" 0 ";
                }
            }
            cout<<endl;
        }

        for(int i = 0; i < N ;i++ ){
            if(m_vertexes[i]){
                cout<< *m_vertexes[i];
            }else{
                cout<<" 0 ";
            }
            cout<<endl;
        }
    }
};

}

#endif // MATRIXGRAPH_H
