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
    return true;  
}

bool remove(T& val){
    RBreeNode<T>* target = find(val);
    if(target == NULL){
         THROW_EXCEPTION("RBreeNode<T>",InvalidParameterException);
    }
    RBreeNode<T>* replace = target;
    if(target->m_left && target->m_right){
        replace = target->m_right;
        while(replace->m_left != NULL){
            replace = replace->m_left;
        }
       target->m_value = replace->m_value;

    }

    RBreeNode<T>* child = NULL;

    if(replace->m_left){
        child = replace->m_left;
    }else{
        child = replace->m_right;
    }

    if(child){
        child->m_parrent = replace->m_parrent;
    }

    if(replace->m_parrent && isLeftChild(replace,replace->m_parrent)){
        replace->m_parrent->m_left = child;
    }else if(replace->m_parrent && (!isLeftChild(replace,replace->m_parrent))){
        replace->m_parrent->m_right = child;
    }

    if(replace->m_parrent == NULL){
        m_root == child;
    }

    if(replace->m_color = COLOR::BLACK){
        fixRemoveUp(child,replace->m_parrent);
    }

    destroyNode(replace);
    return true;
}

RBreeNode<T>* find(T& val){
    RBreeNode<T>* ret = m_root;

    while(ret){
        if(ret->m_value == val){
            break;
        }else if(ret->m_value > val){
            ret = ret->m_left;
        }else{
            ret = ret->m_right;
        }
    }

    return ret;

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

void destroyNode(RBreeNode<T>*  ret){
    delete ret;
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

void fixRemoveUp(RBreeNode<T>* node, RBreeNode<T>* parrent){

    while((!node || isBlack(node)) && (node != m_root)){
       if(isLeftChild(node, parrent)){
           RBreeNode<T>* brother  =  parrent->m_right;
           if(isRed(brother)){
               brother->m_color = COLOR::BLACK;
               parrent->m_color = COLOR::RED;
               RBreeNode<T>* temp = parrent->m_parrent;
               RBreeNode<T>*  tempN = NULL;

               tempN = rotateWithLeft(parrent);
               tempN->m_parrent = temp;
               if(temp == NULL){
                   m_root = temp;
               } 
               brother = parrent->m_right;
               
           }

           if( ((!brother->m_left) || isBlack(brother->m_left))
                && ((!brother->m_right) || isBlack(brother->m_right))
           ){

               brother->m_color = COLOR::RED;
               node = parrent;
               parrent = parrent->m_parrent;
               if(parrent == NULL){   
                   m_root = node;              
                   break;
               }
           }else{
               if(!brother->m_right || isBlack(brother->m_right)){
                   brother->m_left->m_color =  COLOR::BLACK;
                   brother->m_color = COLOR::RED;
                   RBreeNode<T>* temp = brother->m_parrent;
                   brother = rotateWithRight(brother);
                   brother->m_parrent = temp;
               }

               brother->m_color = brother->m_parrent->m_color;
               brother->m_parrent->m_color = COLOR::BLACK;
               brother->m_right->m_color = COLOR::BLACK;
               RBreeNode<T>* temp = brother->m_parrent->m_parrent;
               RBreeNode<T>* tempN = NULL;
               tempN = rotateWithLeft(brother->m_parrent);
               tempN->m_parrent = temp;
               if(temp == NULL){
                   m_root = tempN;
               }
               
               break;
           }
       }else{
            RBreeNode<T>* brother  =  parrent->m_left;
            if(isRed(brother)){
                brother->m_color = COLOR::BLACK;
                parrent->m_color = COLOR::RED;
                RBreeNode<T>* temp = parrent->m_parrent;
                RBreeNode<T>*  tempN = NULL;
                tempN = rotateWithRight(parrent);
                tempN->m_parrent = temp;
                if(temp ==  NULL){
                    m_root = tempN;
                }

                brother = parrent->m_left;
            }

            if( ((!(brother->m_left)) || isBlack(brother->m_left))
            && ((!(brother->m_right)) || isBlack(brother->m_right))
            ){
                brother->m_color = COLOR::RED;
                node = parrent;
                parrent = parrent->m_parrent;
                if(parrent =  NULL ){
                    m_root = node;
                    break;
                }

            }else{
                if((!(brother->m_left)) || isBlack(brother->m_left)){
                    brother->m_right->m_color = COLOR::BLACK;
                    brother->m_color = COLOR::RED;
                    RBreeNode<T>* temp = brother->m_parrent;
                    brother = rotateWithLeft(brother);
                    brother->m_parrent = temp;
                }

                brother->m_color = brother->m_parrent->m_color;
                brother->m_left->m_color =  COLOR::BLACK;
                RBreeNode<T>* temp = brother->m_parrent->m_parrent;
                RBreeNode<T>* tempN = NULL;
                tempN = rotateWithRight(brother->m_parrent);
                tempN->m_parrent = temp;
                if(temp == NULL){
                   m_root = tempN;
                }              
                break;
            }
       }
    }

    if(node){
        node->m_color = COLOR::BLACK;
    }

}

bool isRed(RBreeNode<T>* node){
    bool ret = false;
    if(ret){
        ret = (node->m_color == COLOR::RED);
    }

    return ret;
}

bool isBlack(RBreeNode<T>* node){
    bool ret = false;
    if(ret){
        ret = (node->m_color == COLOR::BLACK);
    }

    return ret;
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