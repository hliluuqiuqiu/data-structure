#ifndef DUALCIRECLELIST_H
#define DUALCIRECLELIST_H
#include "DualLinkList.h"
namespace  SQHLib {
template <typename T>
class DualCirecleList : public DualLinkList<T>{
 protected:
    typedef typename DualLinkList<T>::Node Node;
    Node* tail;
    void  last_to_head(){
       if(tail == NULL){
           return;
       }
       tail->next = this->m_header.next;
       this->m_header.next->pre = tail;
   }
 public:
    DualCirecleList(){
        tail = NULL;
    }
    bool insert(const T& e){
        bool ret = false;
         if(tail == NULL){
             Node* inList = this->create();
             if(inList == NULL){

             }else{
                 inList->value = e;
                 inList->next = NULL;
                 inList->pre = NULL;
                 this->m_header.next = inList;
                 tail = inList;
                 last_to_head();
                 this->m_length++;
                 ret = true;
             }
         }else{
             Node* inList = this->create();
             if(inList == NULL){

             }else{
                 inList->value = e;
                 inList->next = NULL;
                 inList->pre = NULL;
                 tail->next = inList;
                 inList->pre = tail;
                 tail = inList;
                 last_to_head();
                 this->m_length++;
                 ret = true;
             }
         }
         return ret;
    }
    bool insert(int i,const T& e){
        bool ret = false;
        int position = i % (this->m_length + 1);
        if(position == this->m_length){
              return insert(e);
        }else{
             if(position == 0){
                   Node* inList = this->create();
                   if(inList){
                       inList->value = e;
                       inList->next = NULL;
                       inList->pre = NULL;
                       inList->next = this->m_current->next;
                       this->m_current->next->pre  = inList;
                       this->m_current->next = inList;
                       last_to_head();
                       this->m_length++;
                       ret = true;
                   }else{

                   }
             }else{
                   return  DualLinkList<T>::insert(position,e);
             }
        }
        return ret;
    }
    bool remove(int i){
        bool ret = false;
        if(this->m_length == 0){
            \
        }
       int position = i % this->m_length;
       if(position == 0){
           Node* toDel = this->m_header.next;
           if(this->m_length == 1){
                 this->m_length--;
                 this->m_current = NULL;
                 this->destory(toDel);
           }else{
               this->m_length--;
               if(this->m_current == toDel){
                   this->m_current = toDel->next;
               }
               this->m_header.next = toDel->next;
               last_to_head();
               this->destory(toDel);
           }
           ret = true;
       }else if(position == this->m_length - 1){
            Node* toDel = tail;
            this->m_length--;
            if(this->m_current == toDel){
                this->m_current = toDel->next;
            }
            tail = toDel->pre;
            last_to_head();
            this->destory(toDel);
            ret = true;
       }else{
             ret =  DualLinkList<T>::remove(position);
       }
       return ret;
    }
    bool set(int i,const T& e){
       if(this->m_length == 0){

       }
       int position = i % this->m_length;
       return DualLinkList<T>::set(position,e);
   }
  bool get(int i, T& e){
      if(this->m_length == 0){

      }
      int position = i % this->m_length;
      return DualLinkList<T>::get(position,e);
  }


};
}
#endif // DUALCIRECLELIST_H
