#ifndef GTREE_H
#define GTREE_H
#include <iostream>
#include "LinkQueue.h"
#include "Exception.h"
#include "GTreeNode.h"
#include "Tree.h"

namespace SQHLib{
template <typename T>
class GTree : public Tree<T>{
private:
    //GTreeNode<T>* node;
protected:
    LinkQueue<GTreeNode<T>*>  queue;
    void free(GTreeNode<T> * node){
        if(node ==  NULL){
            return;
        }else{
            for(node->chid.move(0); !node->chid.end() ;node->chid.next()){
                free(node->chid.current());
            }
            if(node->inHeap){
                delete node;
             }else{
                cout<<"stack mem:"<<node->value<<endl;
            }
             node = NULL;
        }

    }
   int  height(GTreeNode<T> * node){
       if(node == NULL){
               return 0;
       }else{
                int h = 0,tempH = 0;
                for(node->chid.move(0);!node->chid.end();node->chid.next()){
                    tempH = height(node->chid.current());
                    if(tempH > h){
                            h = tempH;
                    }
                }

                return h + 1;
       }
   }

   int count(GTreeNode<T> * node){
        int ret = 0;
        if(node == NULL){
                return ret;
        }else{
            for(node->chid.move(0);!node->chid.end();node->chid.next()){
                ret += count(node->chid.current());
            }
        }
        return ret + 1;
   }

    int degree(GTreeNode<T> * node){

        int ret = 0,temp = 0;
        if(node == NULL){
            return ret;
        }else{
            for(node->chid.move(0);!node->chid.end();node->chid.next()){
                temp = degree(node->chid.current());

                if(temp > ret){
                        ret = temp;
                }
            }
        }

     //    cout<<"leng("<<node->value<<")"<<":"<<node->chid.length()<<endl;
        if(node->chid.length() > ret){
                ret = node->chid.length();

        }

        return ret;
    }
public:
    GTreeNode<T>*  createNode(){
           return  GTreeNode<T>::NewNode();
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
    SmartPointer< Tree<T> > remove(const T& value) {
        GTreeNode<T>* node = find(value);
        if(node == NULL){
            THROW_EXCEPTION("para error",InvalidParameterException);
        }else{
        //    TreeNode<T>* retNode = node;
            if(node == this->m_root){
                this->m_root = NULL;
            }else{
                 GTreeNode<T>* p =dynamic_cast< GTreeNode<T>*>(node->parrent);
                 p->chid.remove(p->chid.find(node));
            }
        }
        GTree<T>* ret = new GTree<T>();
        ret->m_root = NULL;
        return ret;
    }
    SmartPointer< Tree<T> >  remove(TreeNode<T>* node1){
        GTreeNode<T>* node = find(node1);
        if(node == NULL){
            THROW_EXCEPTION("para error",InvalidParameterException);
        }else{
        //    TreeNode<T>* retNode = node;
            if(node == this->m_root){
                this->m_root = NULL;
            }else{
                 GTreeNode<T>* p =dynamic_cast< GTreeNode<T>*>(node->parrent);
                 p->chid.remove(p->chid.find(node));
            }
        }
        GTree<T>* ret = new GTree<T>();
        ret->m_root = NULL;
        return ret;

    }

    GTreeNode<T>* find(const T& value){
        GTreeNode<T>* ret = NULL;
        GTreeNode<T>*  node = root();
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
        return  find(node,root());
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
    GTreeNode<T>* root(){
         return  dynamic_cast< GTreeNode<T>*>(this->m_root);
    }
    int degree(){
        return degree(root());
    }
    int count(){   
        return count(root());
    }
    int height(){
        return height(root()) ;
    }
    int clear(){
        free(root());
        this->m_root = NULL;
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
           this->printEdge(node);
       }else{
           for(node->chid.move(0);!node->chid.end();node->chid.next()){
                 printSubTree(node->chid.current());
           }
       }
   }
  /* void printEdge(TreeNode<T>* leaf){
        TreeNode<T>* parrent = leaf;
        while(parrent){
                cout << parrent->value;
                parrent = parrent->parrent;
        }
        cout<<endl;
   }*/

   void begin(){
       queue.clear();
       if(this->m_root){
           queue.add(root());
       }
   }

   bool end(){
       return (queue.length() == 0);
   }

   void next(){
       if(queue.length() > 0){

            GTreeNode<T>*  n = NULL;
            queue.front(n);
            queue.remove();

            for(n->chid.move(0);!n->chid.end();n->chid.next()){
                queue.add(n->chid.current());
            }
       }
   }

   GTreeNode<T>* current(){
        GTreeNode<T>* ret = NULL;

        queue.front(ret);

        return ret;
   }

    virtual ~GTree() {
       clear();
   }
};
}

#endif // GTREE_H
