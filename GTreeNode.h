#ifndef GTREENODE_H
#define GTREENODE_H
#include "LinkList.h"
#include "TreeNode.h"
namespace SQHLib{
template <typename T>
class GTreeNode : public TreeNode<T>{
public:
LinkList<GTreeNode<T> *>   chid;
};

}

#endif // GTREENODE_H
