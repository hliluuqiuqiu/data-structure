#ifndef TREENODE_H
#define TREENODE_H
#include "Object.h"
namespace SQHLib{
template <typename T>
class  TreeNode : public Object{
public:
    bool inHeap;
    T  value;
    TreeNode<T>* parrent;
    TreeNode():inHeap(false){
        parrent = NULL;
    }
    virtual ~TreeNode(){};
};
}

#endif // TREENODE_H
