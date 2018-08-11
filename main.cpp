#include <iostream>
#include "StaticList.h"
#include "Exception.h"
#include "StaticArray.h"
#include "DynamicArray.h"
#include "StaticLinkList.h"
#include "SmartPointer.h"
#include "SharePointer.h"
#include "CircleList.h"
#include "DualLinkList.h"
#include "DualCirecleList.h"
#include  "LinkStack.h"
#include "LinkQueue.h"
#include "Tree.h"
#include "GTree.h"
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
void testGTree(){
    Tree<char>*  tree  = new GTree<char>();
    tree->insert('A',NULL);
    TreeNode<char>* anode = tree->find('A');
    bool ret = tree->insert('B',anode);
  //  cout<<ret<<endl;
   // cout<<anode->chid.length();
    tree->insert('C',anode);
    tree->insert('D',anode);

     TreeNode<char>* bnode = tree->find('B');
     tree->insert('E',bnode);
     tree->insert('F',bnode);

     TreeNode<char>* cnode = tree->find('C');
     tree->insert('G',cnode);

     TreeNode<char>* dnode = tree->find('D');
     tree->insert('H',dnode);
     tree->insert('I',dnode);
     tree->insert('J',dnode);

     TreeNode<char>* enode = tree->find('E');
     tree->insert('K',enode);
     tree->insert('L',enode);

     TreeNode<char>* gnode = tree->find('G');
      tree->insert('N',gnode);

      TreeNode<char>* hnode = tree->find('H');
       tree->insert('M',hnode);
       tree->print();
}
int main(){
    testGTree();
}

