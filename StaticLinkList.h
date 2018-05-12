#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H
#include "LinkList.h"
namespace  SQHLib{
template <typename T , int N>
class  StaticLinkList : public LinkList<T>{
protected:
   typedef  typename LinkList<T>::Node Node;
    struct SNode : Node{
        void * operator new(size_t  size, void * loc){
               (void)size;
                return loc;
        }

        ~SNode(){
        }
    };
   //unsigned char m_space[sizeof(Node)  * N];
   Node  m_space[N];
   int m_used[N];
public:
   StaticLinkList(){
       for(int i  = 0; i < N ; i++){
           m_used[i] = 0;
       }
   }
 Node * create(){
     int  unuse_item;
     Node * ret = NULL;
     for(unuse_item = 0; unuse_item < N ; unuse_item++){
            if(m_used[unuse_item] == 0){
                  cout <<" unuse_item : "<<unuse_item<<endl;
                 ret = dynamic_cast<Node *>(new( m_space + unuse_item) SNode());
                   cout <<" unuse_item 30 "<<endl;
                 m_used[unuse_item]  = 1;
                 break;
            }
     }
     return ret;
 }
 void destory(Node*  e){
    for(int i = 0 ; i < N ; i++){
        if(m_space + i == e){
             m_used[i] = 0;

        }
    }
 }
};
}
#endif // STATICLINKLIST_H
