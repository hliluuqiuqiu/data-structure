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

using namespace std;
using namespace SQHLib;

void test(){
        DualLinkList<int>  dl;
        for(int i = 0;i < 10 ; i++){
            dl.insert(i);
        }

        dl.remove(0);
        dl.move(dl.length() - 1);
        while(!dl.end()){
            cout << dl.current() << endl;
            dl.pre();
        }
}
int main(){
    test();
}

