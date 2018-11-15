#ifndef REBTREE_H_SQH
#define REBTREE_H_SQH
#include "Object.h"
#include "RBtreeNode.h"
#include "Exception.h"
namespace SQHLib{
template <typename T>
class RBTree : public Object{
private:
RBreeNode<T>* m_root;

public:
RBTree():m_root(NULL){}
RBreeNode<T>* root(){
    return m_root;
}

bool insert(T& val){
    if(m_root == NULL){
         RBreeNode<T>* node = createNode(val,COLOR::BLACK);
         m_root =  node;
         return true;
    }

    RBreeNode<T>* node = m_root;
    RBreeNode<T>* target = NULL;

    while(node != NULL){
        target = node;
        if(node->m_value > val){
            node = node->m_left;
        }else if(node->m_value < val){
            node = node->m_right;
        }else{
            return false;
        }
    }

    if(target != NULL){
        node = createNode(val,COLOR::RED);
        if(target->m_value > val){
            target->m_left = node;
            node->m_parrent = target;
        }else{
            target->m_right = node;
            node->m_parrent = target;
        }
    }

    insertFixUp(node);
       
}

protected:
RBreeNode<T>* createNode(T& val, COLOR color){
    RBreeNode<T>*  ret = new RBreeNode<T>();
    if(ret == NULL){
             THROW_EXCEPTION("RBreeNode<T>",NoEnoughMemoryException);
    }

    ret->m_color = color;
    ret->m_value = val;
    return ret;   
}

void insertFixUp(RBreeNode<T>* node){

    while(node->m_parrent && node->m_parrent->m_color == COLOR::RED){
        RBreeNode<T>* p = node->m_parrent;
      
        RBreeNode<T>* pp = p->m_parrent;
        if(pp && isLeftChild(p,pp)){
            RBreeNode<T>* uncle = pp->m_right;
            if(uncle && uncle->m_color == COLOR::RED){
                p->m_color = COLOR::BLACK;
                uncle->m_color = COLOR::BLACK;
                pp->m_color = COLOR::RED;
                node = pp;
                continue;
            }

            if(!isLeftChild(node,p)){
                RBreeNode<T>* tempP =  rotateWithLeft(p);
                node = p;
                p = tempP;
                p->m_parrent = pp;
            }

            p->m_color = COLOR::BLACK;
            pp->m_color = COLOR::RED;
            RBreeNode<T>* ppp = pp->m_parrent;
            pp = rotateWithRight(pp);
            pp->m_parrent = ppp;
            break;

        }else if(pp &&(!isLeftChild(p,pp))){
            RBreeNode<T>* uncle  = pp->m_left;
            if(uncle && uncle->m_color == COLOR::RED){
                p->m_color = COLOR::BLACK;
                uncle->m_color = COLOR::BLACK;
                pp->m_color = COLOR::RED;
                node = pp;
                continue;
            }

            if(isLeftChild(node,p)){
                RBreeNode<T>* tempP  = rotateWithRight(p);
                node = p;
                p = tempP;
                p->m_parrent = pp;
            }

            p->m_color = COLOR::BLACK;
            pp->m_color = COLOR::RED;
            RBreeNode<T>* ppp = pp->m_parrent;
            pp = rotateWithLeft(pp);
            pp->m_parrent = ppp;
            break;
        }
               
    }

     m_root->m_color = COLOR::BLACK;  
        
}

RBreeNode<T>* rotateWithLeft(RBreeNode<T>* node){
    RBreeNode<T>* right = node->m_right;
    node->m_right = right->m_left;
    right->m_left = node;
    node->m_parrent = right;
    return right;
}

RBreeNode<T>* rotateWithRight(RBreeNode<T>* node){
    RBreeNode<T>* left = node->m_left;
    node->m_left = left->m_right;
    left->m_right = node;
    node->m_parrent = left;
    return left;
}

bool isLeftChild(RBreeNode<T>* n,RBreeNode<T>* p){
    if(n == NULL || p == NULL || n->m_parrent != p  ){
        THROW_EXCEPTION("",InvalidParameterException);
    }

    return (n == p->m_left);
}
};
}

#endif