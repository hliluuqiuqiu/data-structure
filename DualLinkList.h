#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H
#include "Object.h"
#include "List.h"
#include "Exception.h"
namespace  SQHLib {
template<typename T>
class DualLinkList : public List<T>{
  protected:
      struct Node : public Object{
            T value;
            Node * next;
            Node* pre;
      };
     int m_length;
     mutable struct : public Object{
            char reserved[sizeof(T)];
             Node * next;
             Node* pre;
     }m_header;
    Node * position(int i){
           Node * current = reinterpret_cast<Node*>(&m_header);
           for(int p = 0;p <  i ;p++){
               current = current->next;
           }
           return current;
       }
    Node*  m_current;
    int m_step;
    public:
        DualLinkList(){
            m_header.next = NULL;
            m_header.pre  = NULL;
            m_length = 0;
            m_current = NULL;
            m_step = 1;
        }
        bool move(int i,int step = 1){
                if( i >= 0 && i < length() ){
                        m_current = position(i)->next;
                        this->m_step = step;
                        return true;
                }
                return false;
        }

        T& current(){
                if(m_current){
                        return m_current->value;
                }else{
                    THROW_EXCEPTION("TAG",IndexOutOfBoundsException);
                }
        }
        bool next(){
            int i = 0;
            for(;i < m_step;i++){
                    if(m_current == NULL){
                            break;
                    }
                    m_current = m_current->next;
            }
            return (i == m_step);
        }

        bool pre(){
            int i = 0;
            for(;i < m_step;i++){
                    if(m_current == NULL){
                            break;
                    }
                    m_current = m_current->pre;
            }
            return (i == m_step);
        }

        bool end(){
            return m_current == NULL;
        }

        virtual  Node* create(){
            return new Node();
        }
        virtual void destory(Node*  e){
           delete e;
        }

       bool insert(const T& e){
          return  insert(m_length,e);
       }
       bool insert(int i,const T& e){
           bool ret = (i>=0) && (i<=m_length);
            if(ret){
                Node* node = create();
                if(node){
                        node->value = e;
                        node->next =NULL;
                        node->pre = NULL;
                        Node * current = position(i);
                        node->next = current->next;
                        if(i != 0){
                             node->pre = current;
                        }
                        if(current->next){
                            current->next->pre = node;
                         }
                         current->next = node;
                        m_length++;
                }else{
                    THROW_EXCEPTION("No mem",NoEnoughMemoryException);
                }
            }else{
                THROW_EXCEPTION("invalid para",InvalidParameterException);
            }
            return ret;
       }

      bool remove(int i){
              bool ret = (i>=0) && (i<m_length);
              if(ret){
                 Node * current = position(i);
                 Node *toDel  = current->next;
                 current->next = toDel->next;
                 if(i == 0 && toDel->next){
                      toDel->next->pre = NULL;
                 }
                 if(i != 0 && toDel->next){
                      toDel->next->pre = current;
                 }
                 if(this->m_current && this->m_current == toDel){
                     this->m_current = toDel->next;
                 }
                 destory(toDel);
                 m_length--;
              }else{
                       THROW_EXCEPTION("invalid para",InvalidParameterException);
              }
              return ret;
      }
     bool set(int i,const T& e){
         bool ret = ( i >= 0 ) && (i < m_length);
         if(ret){
             position(i)->next->value = e;
         }else{
                   THROW_EXCEPTION("invalid para",InvalidParameterException);
         }
         return ret;
     }

     bool get(int i, T& e){
         bool ret = ( i >= 0 ) && (i < m_length);
         if(ret){
              e =   position(i)->next->value;
         }else{
                   THROW_EXCEPTION("invalid para",InvalidParameterException);
         }
         return ret;
     }

     int find(const T& e){
         if(this->m_length > 0){
              Node* lHead  = m_header.next;
              int i = 0;
              for(;i < this->m_length;i++){
                  if(lHead->value == e){
                      break;
                  }
                  lHead = lHead->next;
              }
              if(i < this->m_length){
                  return i;
              }
         }
         return -1;
     }
     virtual int length() const{
         return m_length;
     }
    void clear(){
        if(m_length > 0){
            Node* current = m_header.next;
             Node* toDel = NULL;
            for(int i = 0;i < m_length ; i++){
                toDel = current;
                current = toDel->next;
                destory( toDel);
            }
             m_header.next = NULL;
            m_length = 0;
        }
     }
    void reverse(){
        if(m_length > 1){
               Node* current = m_header.next;
               Node* next1 = current->next;
               current->next = NULL;
               for(int i = 0 ; i < m_length -1; i++){
                     Node* next2 = next1->next;
                     next1->next = current;
                     current->pre = next1;
                     current = next1;
                     next1 = next2;
               }
               m_header.next = current;
        }
    }

    void print(){
        if(m_length > 0){
            T value;
            for(int i = 0 ; i < m_length; i++){
                    this->get(i,value);
                     std::cout<<value<<endl;
            }
        }
    }
    ~DualLinkList(){
        clear();
    }
};
}
#endif // DUALLINKLIST_H
