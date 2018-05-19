#include <iostream>
#include "StaticList.h"
#include "Exception.h"
#include "StaticArray.h"
#include "DynamicArray.h"
#include "StaticLinkList.h"
#include "SmartPointer.h"
#include "SharePointer.h"
#include "test.h"
#include "CircleList.h"
#include "DualLinkList.h"
#include "DualCirecleList.h"
#include  "LinkStack.h"
#include "LinkQueue.h"

using namespace std;
using namespace SQHLib;

void test(){ 
    LinkQueue<int> lq;

    for(int i = 0;i<10;i++){
        lq.add(i);
    }
    int a = 0;
    cout<<" len :"<<lq.length()<<endl;
    for(int i = 0;i<10;i++){
      //  cout<<a<<" len :"<<lq.length()<<endl;
        lq.front(a);
        lq.remove();
        cout<<a<<" len :"<<lq.length()<<endl;
    }
  //
}
int main(){
    test();
}

