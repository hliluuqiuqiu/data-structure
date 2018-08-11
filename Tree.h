#ifndef TREE_H
#define TREE_H
#include "SmartPointer.h"
#include "TreeNode.h"
namespace SQHLib{
template <typename T>
class Tree{
protected:
 TreeNode<T> *  m_root;
public:
 Tree(){
        m_root = NULL;
 }

 virtual bool insert(TreeNode<T>*  node,TreeNode<T>*  parrent) = 0;
 virtual bool insert(const T& value,TreeNode<T>*  parrent) = 0;
 virtual SmartPointer< TreeNode<T> >  remove(const T& value) = 0;
 virtual SmartPointer< TreeNode<T> >  remove(TreeNode<T>* node) = 0;
 virtual TreeNode<T>* find(const T& value) = 0;
 virtual TreeNode<T>* find(TreeNode<T>* node) = 0;
 virtual TreeNode<T>* root() = 0;
 virtual int degree() = 0;
 virtual int count() = 0;
 virtual int height() = 0;
 virtual int clear() = 0;
 virtual bool isEmpty() = 0;
 virtual void print() = 0;
};
}

#endif // TREE_H
