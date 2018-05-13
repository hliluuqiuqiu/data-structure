#ifndef CIRCLELIST_H
#define CIRCLELIST_H
#include "LinkList.h"
#include "Exception.h"
namespace SQHLib{
template <typename T>
class CircleList:public LinkList<T>
{
protected:
    //typedef  LinkList<T>::Node Node;
    typedef  typename LinkList<T>::Node Node;
    Node* tail;
    void last_to_first(void)
    {
        if(tail){
            Node* lHead = this->m_header.next;
            tail->next = lHead;
        }
    }
public:
    CircleList():tail(NULL){}
    bool insert(const T& e){
        if(tail){
           Node* newNode = LinkList<T>::create();
           if(newNode){
               newNode->value = e;
               newNode->next = NULL;
               tail->next = newNode;
               tail = newNode;
               last_to_first();
           }else{
               THROW_EXCEPTION("TAG",NoEnoughMemoryException);
           }

        }else{
            Node* lCurrent = this->m_header.next;
            if(lCurrent ==  NULL){
                  Node* newNode = LinkList<T>::create();
                  if(newNode){
                      newNode->value = e;
                      newNode->next = NULL;
                      this->m_header.next  = newNode;
                      tail = newNode;
                      last_to_first();
                  }else{
                       THROW_EXCEPTION("TAG",NoEnoughMemoryException);
                  }
            }else{
                 THROW_EXCEPTION("TAG",InvalidParameterException);
            }
        }
        this->m_length++;
       return true;
    }
    bool insert(int i,const T& e){
         bool ret = false;
         i =(i % this->m_length + 1);
         if(i == 0){
                Node* firstNode = this->m_header.next;
                if(firstNode){
                     Node* newNode = LinkList<T>::create();
                     if(newNode){
                         newNode->value = e;
                         newNode->next = firstNode;
                         this->m_header.next = newNode;
                         last_to_first();
                         this->m_length++;
                         ret = true;
                     }else{
                         THROW_EXCEPTION("No mem",NoEnoughMemoryException);
                     }
                }else{
                     ret = insert(e);
                }
         }else if(i == this->m_length){
                     ret = insert(e);
         }
        else if(i > 0 && i <  this->m_length){
              Node* node = LinkList<T>::create();
              if(node){
                      node->value = e;
                      node->next =NULL;
                      Node * current = LinkList<T>::position(i);
                      node->next = current->next;
                      current->next = node;
                      this->m_length++;
                      ret = true;
              }else{
                  THROW_EXCEPTION("No mem",NoEnoughMemoryException);
              }
          }else{
              THROW_EXCEPTION("invalid para",InvalidParameterException);
          }
          return ret;
       }
    bool remove(int i){
   //   std::cout<<"remove:"<<i<<std::endl;
    //   std::cout<<"remove step:"<<this->m_step<<std::endl;
        bool ret = false;
        i = (i % this->m_length);
        if(i == 0){
             Node* toDel = this->m_header.next;
             Node* mCurrentHead = toDel->next;
             this->m_header.next = mCurrentHead;
             last_to_first();
             this->m_length--;
             if(this->m_length == 0){
                  this->m_header.next = NULL;
                  this->m_current = NULL;
             }
             if(this->m_current &&this->m_current == toDel){
                  this->m_current = toDel->next;
             }
             ret = true;
             LinkList<T>::destory(toDel);

        }else if(i ==this->m_length -1){
            Node* toDel = tail;
            Node* mCurrentTail = LinkList<T>::position(this->m_length -1);
            if(this->m_current &&this->m_current == toDel){
                 this->m_current = toDel->next;
            }
            tail = mCurrentTail;
            last_to_first();
            LinkList<T>::destory(toDel);
            this->m_length--;
            ret = true;
        }else if(i > 0 && i < this->m_length - 1){
            Node * current = LinkList<T>::position(i);
            Node *toDel  = current->next;

            current->next = toDel->next;
            if(this->m_current && this->m_current == toDel){
               //  std::cout<<"change m_current pre:"<<this->m_current->value<<std::endl;
                 this->m_current = toDel->next;
                 //  std::cout<<"change m_current after:"<<this->m_current->value<<std::endl;
            }
            this->m_length--;
            ret = true;
            LinkList<T>::destory(toDel); 
        }
    //    std::cout<<"138  remove step:"<<this->m_step<<std::endl;
        return ret;
    }

    bool next(){
        int i = 0;
        if(this->m_current)
        {
            for(;i < this->m_step;i++){
                    this->m_current = this->m_current->next;
            }
         //   std::cout<<"next"<<this->m_current->value<<" step : "<<this->m_step<<std::endl;
         }
        return (i == this->m_step);
    }
    bool set(int i,const T& e){
        return LinkList<T>::set((i % this->m_length),e);
    }
    bool get(int i, T& e){
        return LinkList<T>::get((i % this->m_length),e);
    }
    bool move(int i,int step){
            return LinkList<T>::move((i % this->m_length) ,step);
    }
};

}
#endif // CIRCLELIST_H
