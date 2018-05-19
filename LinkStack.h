#ifndef LINKSTACK_H
#define LINKSTACK_H
#include "Stack.h"
#include "LinkList.h"
namespace SQHLib {
template <typename T>
class LinkStack : public Stack<T>{
protected:
  LinkList<T> mStack;
public:
  void push(const T& e) {
      mStack.insert(e);
  }
  void pop(){
      mStack.remove(mStack.length() -1);
  }
  void top(T& e){
        mStack.get(mStack.length() -1,e);
  }
  void clear(){
      mStack.clear();
  }
  int size(){
      return mStack.length();
  }
};
}

#endif // LINKSTACK_H
