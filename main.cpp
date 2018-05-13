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

using namespace std;
using namespace SQHLib;

void josehus(){
    CircleList<int> cl;
    for(int i = 1 ;i < 42;i++){
        cl.insert(i);
     }
       cl.move(0,2);
      while(!cl.end()){
         cl.next();
         cout<<"value:"<<cl.current()<<endl;
         cl.remove(cl.find(cl.current()));
     }
}
int main(){
    josehus();
}

