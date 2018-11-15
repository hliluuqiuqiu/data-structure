#ifndef AVLTREE_H
#define AVLTREE_H
#include "Tree.h"
#include "BTreeNode.h"
namespace SQHLib{
template <typename T>
class AVLTree : public Tree<T>{
protected:
    int  height(BTreeNode<T>*  node){
        int ret = 0,h = 0;
        if(node == NULL){
                return 0;
        }

        h =  height(node->left);
        if(ret < h){
                ret = h;
        }

        h =  height(node->right);
        if(ret < h){
                ret = h;
        }

        return ret + 1;
    }
 virtual  BTreeNode<T>* insert(const BTreeNode<T>*  v,const BTreeNode<T>* p ){
        if(p == NULL){
               v->parrent = NULL;
               v->left = NULL;
               v->right = NULL;
                return v;
        }else{
            if(v->value < p->value){
                p->left = insert(v,p->left);
                p->left->parrent = p;
                if(height(p->left) - height(p->right) == 2){
                    if(v->value < p->left->value){
                       p =  singleRotate(p,true);
                    }else{
                        p = doubleRotate(p,true);
                    }
                }
            }else{
                p->right = insert(v,p->right);
                 p->right->parrent = p;
                if(height(p->right) - height(p->left) == 2){
                    if(v->value > p->right->value){
                       p =  singleRotate(p,false);
                    }else{
                       p = doubleRotate(p,false);
                    }
                }
            }

        }
        return p;
}

    BTreeNode<T>*  singleRotate( BTreeNode<T>*  node,bool left){
        if(node == NULL){
            return;
        }
        if(left == true){
            BTreeNode<T>* l =  node->left;
            node->left = l->right;
            l->right->parrent = node;
            l->right = node;
            node->parrent = l;
            return l;
        }else{
            BTreeNode<T>* r = node->right;
            node->right = r->left;
            r->left->parrent = node;
            r->left = node;
            node->parrent = r;
            return  r;
        }
    }

    BTreeNode<T>* doubleRotate(BTreeNode<T>*  node,bool left){
        BTreeNode<T>* p = NULL;
        if(left == true){
            p = singleRotate(node->left ,false);
            node->left = p;
            p->parrent = node;
           p =  singleRotate(node,true);
        }else{
            p = singleRotate(node->left ,true);
            node->right = p;
            p->parrent = node;
            p = singleRotate(node,false);
         }
        return p;
    }


public:
    AVLTree(){}


    virtual insert(const T& value){

    }

    BTreeNode<T>* root(){
        return dynamic_cast<BTreeNode<T>*> (this->m_root);
    }
};
}

#endif // AVLTREE_H
