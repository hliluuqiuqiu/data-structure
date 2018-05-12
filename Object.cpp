#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "Object.h"

using namespace std;
namespace SQHLib {
void *Object::operator new ( size_t size) throw(){
     cout<<"create object  size :" <<size<<endl;
    return malloc(size);
}
void Object::operator delete (void *p) throw(){
     cout<<"delete object"<<endl;
    free(p);
}
void *Object::operator new []( size_t size) throw(){
    return malloc(size);
}
void Object::operator delete [](void *p) throw(){
    free(p);
}
Object::~Object(){

}
}
