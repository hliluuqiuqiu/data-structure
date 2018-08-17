#ifndef GTREENODE_H
#define GTREENODE_H
#include "LinkList.h"
#include "TreeNode.h"
namespace SQHLib{
template <typename T>
class GTreeNode : public TreeNode<T>{
protected:
    void * operator new ( size_t size) throw(){
            return Object::operator new(size);
    }
public:

LinkList<GTreeNode<T> *>   chid;
static GTreeNode<T>* NewNode(){
    GTreeNode<T>* ret = new GTreeNode<T>();
    if(ret){
        ret->inHeap = true;
    }
    return ret;
}
GTreeNode(){

}

};



}

#endif // GTREENODE_H
