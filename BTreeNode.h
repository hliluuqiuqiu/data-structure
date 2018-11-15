#ifndef BTREENODE_H
#define BTREENODE_H
#include "Object.h"
#include "TreeNode.h"
namespace SQHLib{
    enum BTreeNodePos{ANY,LEFT,RIGHT};
template  <typename T>
class BTreeNode : public TreeNode<T>{
protected:
     void*  operator new(size_t size){
         return Object::operator new(size);
     }
public:

    static BTreeNode<T>*   NewNode(){
        BTreeNode<T>* ret = new   BTreeNode<T>();
        if(ret){
            ret->inHeap = true;
        }
        return ret;
    }

    BTreeNode<T>*  left;
    BTreeNode<T>*  right;
    BTreeNode():left(NULL),right(NULL){}
};
}

#endif // BTREENODE_H
