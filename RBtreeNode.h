#ifndef RBTREE_NODE_H_SQH
#define RBTREE_NODE_H_SQH
#include "Object.h"
namespace SQHLib{
enum class COLOR {RED , BLACK};    
template <typename T>
struct RBreeNode : public Object{
T  m_value;
COLOR  m_color;
RBreeNode<T>* m_left;
RBreeNode<T>* m_right;
RBreeNode<T>* m_parrent;
RBreeNode()
:m_color(COLOR::RED),m_left(NULL),m_right(NULL),m_parrent(NULL)
{}
};
}

#endif