#ifndef BTREE_H
#define BTREE_H
#include "Tree.h"
#include "BTreeNode.h"
#include "Exception.h"
namespace SQHLib{
template <typename  T>
class BTree : public Tree<T>{
protected:
    BTreeNode<T>*  find(BTreeNode<T>* obj, BTreeNode<T>* node){
            BTreeNode<T>* ret = NULL;
            if(obj == NULL || node == NULL){
                THROW_EXCEPTION("invalid para..",InvalidParameterException);
            }

            if(node->value == obj->value){
                   ret = node;
            }else{
                if(node->left){
                   ret =  find(obj,node->left);
                }else if((ret == NULL ) && node->right){
                     ret =  find(obj,node->right);
                }
          }
          return ret;
    }

    BTreeNode<T>*  find(const T& obj, BTreeNode<T>* node){
            BTreeNode<T>* ret = NULL;
            //  cout<<"find value"<<node->value<<endl;
            if(node == NULL){
                THROW_EXCEPTION("invalid para..",InvalidParameterException);
            }

            if(node->value == obj){
                   ret = node;
            }else{
                if(node->left){
                   ret =  find(obj,node->left);
                }

                if((ret == NULL ) && node->right){
                    //cout<<"(ret == NULL ) && node->right"<<endl;
                     ret =  find(obj,node->right);
                }
          }
          return ret;
    }

    bool insert(BTreeNode<T>*  node,BTreeNode<T>*  parrent,BTreeNodePos pos){
            bool ret = false;
           if(node == NULL || parrent == NULL){
                     THROW_EXCEPTION("invalid para..",InvalidParameterException);
           }else{
          //     BTreeNode<T>*  bParrent = dynamic_cast<BTreeNode<T>* > (parrent);
               BTreeNode<T>*  bParrent = parrent;
               if(pos == ANY){
                   if(bParrent->left == NULL){
                          bParrent->left = node;
                          node->parrent = parrent;
                          ret = true;
                   }else if(bParrent->right == NULL){
                        bParrent->right = node;
                        node->parrent = parrent;
                        ret = true;
                   }
               }else if(pos == LEFT){
                   if(bParrent->left == NULL){
                          bParrent->left = node;
                          node->parrent = parrent;
                          ret = true;
                   }
               }else if(pos == RIGHT){
                   if(bParrent->right == NULL){
                                           bParrent->right =node;
                                           node->parrent = parrent;
                                           ret = true;
                    }
               }
           }
           return ret;
    }

    void print(BTreeNode<T>* node){
        if(node->left == NULL && node->right == NULL){
                this->printEdge(node);
        }else{
            if(node->left){
                print(node->left);
            }

            if(node->right){
                     print(node->right);
            }

        }
    }

    bool remove(BTreeNode<T>*  node,BTree<int>* & tree){
        if(node == root()){
                this->m_root = NULL;
        }else{
            BTreeNode<T>* p =dynamic_cast<BTreeNode<T>*>  ( node->parrent);
            if(p->left == node){
                    p->left = NULL;

            }else if(p->right == node){
                    p->right = NULL;
            }

            node->parrent = NULL;
        }

        BTree<T>* ret = new BTree<T>();
        ret->m_root = node;

        tree = ret;
        return true;
    }
    void clear(BTreeNode<T>*  node){
        if(node == NULL){
            return;
        }else{
            clear(node->left);
            clear(node->right);

            if(node->inHeap){
                delete node;
                node =NULL;
            }
        }
    }

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

    int count(BTreeNode<T>*  node){
        if(node ==NULL){
                return 0;
        }
        int ret = 0;
        ret += count(node->left);
        ret+= count(node->right);
       return ret + 1;
    }

    int degree(BTreeNode<T>*  node){
        int ret = 0;
        int d = 0;
        if(node ==NULL){
                return 0;
        }
        ret = !!node->left + !! node->right;
        if(ret == 2){
                return 2;
        }

        d = degree(node->left);

        if(d == 2){
            return 2;
        }

        if(ret < d){
            ret = d;
        }

        d = degree(node->right);
        if(d == 2){
            return 2;
        }

        if(ret < d){
            ret = d;
        }

        return ret;

    }
public:
     bool insert(TreeNode<T>*  node,TreeNode<T>*  parrent ){
             if(node == NULL){
                 THROW_EXCEPTION("invalid para..",InvalidParameterException);
             }

             if(parrent == NULL){
                    this->m_root = node;
                    node->parrent = NULL;
                    return true;
             }

            return  insert(dynamic_cast<  BTreeNode<T>* >(node),dynamic_cast<  BTreeNode<T>* >(parrent),ANY);
     }
     bool insert(const T& value,TreeNode<T>*  parrent) {
         BTreeNode<T>* node  = createNode();
         if(node == NULL){
                return false;
         }

         node->value = value;

         if(parrent == NULL){
                this->m_root = node;
                return true;
         }

          return insert(node,dynamic_cast<  BTreeNode<T>* >(parrent),ANY);
     }

     BTreeNode<T>* createNode(){
         return BTreeNode<T>::NewNode();
     }
     SmartPointer< Tree<T> >  remove(const T& value) {
               BTreeNode<T>* retNode =  find(value);
               if(retNode == NULL){
                        THROW_EXCEPTION("invalid para..",InvalidParameterException);
               }
               BTree<int>* ret  = NULL;
               remove(retNode,ret);
               return ret;
     }
     SmartPointer< Tree<T> >  remove(TreeNode<T>* node) {
         BTreeNode<T>* retNode =  find(node);
         if(retNode == NULL){
                  THROW_EXCEPTION("invalid para..",InvalidParameterException);
         }
         BTree<int>* ret  = NULL;
         remove(retNode,ret);
         return ret;
     }
     BTreeNode<T>* find(const T& value){
          return root() == NULL ? NULL:find(value,root());
     }
     BTreeNode<T>* find(TreeNode<T>* node) {
             return root() == NULL ? NULL:find(dynamic_cast<  BTreeNode<T>* >(node),root());
     }
     BTreeNode<T>* root() {
         return dynamic_cast<  BTreeNode<T>* > (this->m_root);
     }

     int degree() {
         return degree(root());
     }
     int count(){
         return count(root());
     }
     int height() {
         return height(root());
     }

     int clear() {
         clear(root());
     }
     bool isEmpty() {
          return 0;
     }
     void print() {
         if(this->m_root){
             print(root());
         }
     }
     ~BTree(){};
};

}

#endif // BTREE_H
