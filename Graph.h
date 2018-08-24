#ifndef GRAPH_H
#define GRAPH_H
#include "Object.h"
#include "SharePointer.h"
#include  "Array.h"
 namespace SQHLib{
template <typename V, typename E>
 class Graph : public Object{
 public:
     virtual bool getVertex(int i,V& value) = 0;
     virtual bool setVertext(int i,const V& value) = 0;
     virtual SharePointer< Array<int> > getAdjacent(int i) = 0;
     virtual bool getEdge(int i, int j ,E& value) = 0;
     virtual bool setEdge(int i, int j ,const E& value) = 0;
     virtual bool remove(int i,int j) = 0;
     virtual int vCout() = 0;
     virtual int eCout() = 0;
     virtual int OD(int i) = 0;
     virtual int ID(int i ) = 0;
     virtual int TD(int i) {
         return OD(i) + ID(i);
     }

      virtual void print(){};
 };

}

#endif // GRAPH_H
