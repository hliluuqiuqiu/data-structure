#ifndef TREENODE_H
#define TREENODE_H
namespace SQHLib{
template <typename T>
class  TreeNode{
public:
    T  value;
    TreeNode<T>* parrent;
    TreeNode(){
        parrent = NULL;
    }
};
}

#endif // TREENODE_H
