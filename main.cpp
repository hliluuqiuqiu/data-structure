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
#include  "BTree.h"
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
   // cout<<ret<<endl;
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
   //   tree->insert('M',hnode);
       //tree->print();
      GTreeNode<char> insert;
      insert.value = 'M';
      tree->insert(&insert,hnode);
      tree->print();
      GTree<char>*  gtree =  dynamic_cast<GTree<char>*> (tree);
      cout<<"result:...1................."<<endl;
      for(gtree->begin();!gtree->end();gtree->next()){
            cout<<" "<<gtree->current()->value;
      }
}
void testBtree(){
    BTree<int>* b = new BTree<int>();
   // TreeNode<int> a;
     bool ret = b->insert(1,NULL);
   //  cout<<ret<<endl;
     BTreeNode<int>*  node_1 = b->find(1);
     b->insert(2,node_1);
     b->insert(3,node_1);

     BTreeNode<int>*  node_2 = b->find(2);
     b->insert(4,node_2);
     b->insert(5,node_2);

     BTreeNode<int>*  node_4 = b->find(4);
     b->insert(8,node_4);
     b->insert(9,node_4);

     BTreeNode<int>*  node_5 = b->find(5);
     b->insert(10,node_5);

     BTreeNode<int>*  node_3 = b->find(3);
     b->insert(6,node_3);
     b->insert(7,node_3);

     BTreeNode<int>*  node_6 = b->find(6);
     b->insert(11,node_6);
     //b->remove(2);
     b->print();
     cout<<"..............."<<endl;
     cout<<b->count()<<endl;
      cout<<b->degree()<<endl;
       cout<<b->height()<<endl;
}
int main(){
    testBtree();
    //testGTree();
}

