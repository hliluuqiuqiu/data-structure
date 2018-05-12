#include <iostream>
#include "StaticList.h"
#include "Exception.h"
#include "StaticArray.h"
#include "DynamicArray.h"
#include "StaticLinkList.h"
#include "SmartPointer.h"
#include "SharePointer.h"
#include "test.h"

using namespace std;
using namespace SQHLib;

int main(){
      SharePointer<int>   sp = new int(5);
      int t = sp.get();
      SharePointer<int> sp1 = sp;
      std::cout<<"t"<<t<<std::endl;
}

