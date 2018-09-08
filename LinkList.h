#ifndef LINKLIST_H
#define LINKLIST_H
#include <iostream>
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
        LinkList(){
            m_header.next = NULL;
            m_length = 0;
            m_current = NULL;
            m_step = 1;
        }
        virtual bool move(int i,int step = 1){
                if( i >= 0 && i < length() ){
                        m_current = position(i)->next;
                        this->m_step = step;
                        return true;
                }
                return false;
        }

      virtual  T& current(){
                if(m_current){
                        return m_current->value;
                }else{
                    THROW_EXCEPTION("TAG",IndexOutOfBoundsException);
                }
        }
     virtual   bool next(){
            int i = 0;
            for(;i < m_step;i++){
                    if(m_current == NULL){
                            break;
                    }
                    m_current = m_current->next;
            }
            return (i == m_step);
        }

       virtual bool end(){
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
                 if(this->m_current && this->m_current == toDel){
                     this->m_current = toDel->next;
                 }
                 m_length--;
                 destory(toDel);
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
              m_header.next = reverse(m_header.next);
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

    bool isBtt(){
        bool ret = false;
        if(m_length == 0){
            return ret;
        }

        Node* first = m_header.next;
        Node* slow = m_header.next;

        while(first->next){
            first = first->next;
            if(first->next == NULL){
                    break;
            }
            first = first->next;
            slow = slow->next;
        }



        bool isODD = ( (m_length % 2) == 1);

        Node* SendHead = NULL;
        Node* firstHead = NULL;
        Node* NodeFlag = NULL;
        if(isODD){
              SendHead = this->reverse(slow);
              NodeFlag = SendHead;
              firstHead =  m_header.next;

              while(SendHead){
                  if(firstHead->value != SendHead->value){
                         break;
                  }
                  SendHead = SendHead->next;
                  firstHead = firstHead->next;
              }

             if(SendHead == NULL){
                    ret = true;
             }else{
                    ret = false;
             }
             this->reverse(NodeFlag);
        }else{
            SendHead = this->reverse(slow->next);
            firstHead = m_header.next;
             NodeFlag = SendHead;
            cout << "..." <<SendHead->value<<endl;
            while(SendHead){
                if(firstHead->value != SendHead->value){
                       break;
                }
                SendHead = SendHead->next;
                firstHead = firstHead->next;
                // cout << "..." <<SendHead->value<<endl;
            }

           if(SendHead == NULL){
                  ret = true;
           }else{
                  ret = false;
           }
           this->reverse(NodeFlag);
        }
        return ret;
    }

    ~LinkList(){
        clear();
    }

private:
    Node*  reverse(Node*  head){
            Node* pre = NULL;
            Node* next = NULL;
            while(head){
                next = head->next;
                head->next = pre;
                pre = head;
                head = next;
            }
            return pre;
    }
};
}

#endif // LINKLIST_H
