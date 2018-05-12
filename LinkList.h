#ifndef LINKLIST_H
#define LINKLIST_H
#include "Object.h"
#include "List.h"
#include "Exception.h"
namespace  SQHLib {
template<typename T>
class LinkList : public List<T>{
  protected:
      struct Node : public Object{
            T value;
            Node * next;
      };
       int m_length;
       mutable struct : public Object{
            char reserved[sizeof(T)];
             Node * next;
       }m_header;
    Node*  m_current;
    int m_step;
    Node * position(int i){
        Node * current = reinterpret_cast<Node*>(&m_header);
        for(int p = 0;p <  i ;p++){
            current = current->next;
        }
        return current;
    }
    public:
        LinkList(){
            m_header.next = NULL;
            m_length = 0;
            m_current = NULL;
            m_step = 1;
        }
        bool move(int i,int step = 1){
                if( i >= 0 && i < length() ){
                        m_current = position(i)->next;
                        return true;
                }
                return false;
        }

        T* current(){
                if(m_current){
                        return m_current->value;
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
                        Node * current = position(i);
                        node->next = current->next;
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
    ~LinkList(){
        clear();
    }
};
}

#endif // LINKLIST_H
