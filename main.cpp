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

using namespace std;
using namespace SQHLib;

void test(){
        DualCirecleList<int>  dl;
        for(int i = 0;i < 10 ; i++){
            dl.insert(i);
        }
        dl.insert(10,10);
        dl.move(0);
        while(!dl.end()){
            cout << dl.current() << endl;
         //   dl.pre();
            dl.remove(dl.find(dl.current()));
        }
         //   cout << dl.current() << endl;
       //     dl.pre();

}
int main(){
    test();
}

