#ifndef GTREE_H
#define GTREE_H
#include <iostream>
#include "GTreeNode.h"
#include "Tree.h"

namespace SQHLib{
template <typename T>
class GTree : public Tree<T>{
private:
    //GTreeNode<T>* node;
public:
    GTreeNode<T>*  createNode(){
           return  new   GTreeNode<T>();
    }
    bool insert(TreeNode<T>*  node,TreeNode<T>*  parrent){
        bool ret = false;
        if(node == NULL){
               return ret;
        }

        if(isEmpty()){
            this->m_root = node;
             ret = true;
        }else{
            if(parrent == NULL){
                    parrent =   this->m_root;
            }

            GTreeNode<T>* p= find(parrent);
            if(p){
                if(p->chid.find((GTreeNode<T>*)node) < 0){
                       p->chid.insert((GTreeNode<T>*)node)  ;
                       node->parrent = p;
                }
                ret = true;
            }
        }
        return ret;
    }
    bool insert(const T& value,TreeNode<T>*  parrent) {
           bool ret = false;

           GTreeNode<T>*  node  = createNode();
           if(node == NULL){
                return ret;
           }

           node->value = value;
           if(isEmpty()){
                    this->m_root = node;
                    ret = true;
           }else{
               if(parrent ==NULL){
                       ((GTreeNode<T>*) (this->m_root))->chid.insert(node);
                       node->parrent = this->m_root;
                       ret = true;
               }else{
                     GTreeNode<T>* p= find(parrent);
                     if(p){
                         p->chid.insert(node) ;
                          node->parrent =p;
                         ret = true;
                     }else{
                         cout<<"not found parrent"<<endl;
                     }
               }
           }

           return ret;
    }
    SmartPointer< TreeNode<T> >  remove(const T& value) {
          return NULL;
    }
    SmartPointer< TreeNode<T> >  remove(TreeNode<T>* node){
          return NULL;

    }

    GTreeNode<T>* find(const T& value){
        GTreeNode<T>* ret = NULL;
        GTreeNode<T>*  node = (GTreeNode<T>*) root();
        if(node ){
            ret =   find(value,node);
        }
        return ret;
    }

    GTreeNode<T>* find(const T& value,GTreeNode<T>* parrent){
        GTreeNode<T>* ret = NULL;
        if(parrent == NULL ){
                return NULL;
        }

        if(parrent->value == value){
                return parrent;
        }else{
            if(parrent->chid.length() > 0){
                for(parrent->chid.move(0);!parrent->chid.end();parrent->chid.next()){
                     ret = find(value,parrent->chid.current());
                     if(ret){
                        break;
                     }
                }
            }

        }
        return ret;
    }
    GTreeNode<T>* find(TreeNode<T>* node){
        return  find(node,(GTreeNode<T>*)root());
    }

    GTreeNode<T>* find(const TreeNode<T>* node,GTreeNode<T>* parrent){
        GTreeNode<T>* ret = NULL;
        if(parrent == NULL ){
                return NULL;
        }

        if(parrent == node){
                return parrent;
        }else{
            if(parrent->chid.length() > 0){
                for(parrent->chid.move(0);!parrent->chid.end();parrent->chid.next()){
                     ret = find(node,parrent->chid.current());
                     if(ret){
                        break;
                     }
                }
            }

        }
        return ret;
    }
    TreeNode<T>* root(){
         return  (this->m_root);
    }
    int degree(){
        return 0;
    }
    int count(){
        return 0;
    }
    int height(){
        return 0;
    }
    int clear(){
        return 0;
    }
   bool isEmpty(){
        return   this->m_root == NULL;
   }

   void print(){
       if(!isEmpty()){
           GTreeNode<T>* r = ( GTreeNode<T>*)root();
           //cout<<r->value;
           printSubTree(r);
       }
   }

   void printSubTree( GTreeNode<T>* node){
       if(node->chid.length() == 0){
           printEdge(node);
       }else{
           for(node->chid.move(0);!node->chid.end();node->chid.next()){
                 printSubTree(node->chid.current());
           }
       }
   }
   void printEdge(TreeNode<T>* leaf){
        TreeNode<T>* parrent = leaf;
        while(parrent){
                cout << parrent->value;
                parrent = parrent->parrent;
        }
        cout<<endl;
   }
};
}

#endif // GTREE_H
