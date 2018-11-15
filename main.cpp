#include <iostream>
#include <typeinfo>
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
#include "SmartPointer.h"
#include "Graph.h"
#include "MatrixGraph.h"
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

     BTreeNode<int>*  node_3 = b->find(3);
     b->insert(6,node_3);
     b->insert(7,node_3);

     BTreeNode<int>*  node_4 = b->find(4);
     b->insert(8,node_4);
      b->insert(9,node_4);
     BTreeNode<int>*  node_5 = b->find(5);
     b->insert(10,node_5);
     b->insert(11,node_5);

     BTreeNode<int>*  node_6 = b->find(6);
     b->insert(12,node_6);
     b->insert(13,node_6);
     //b->remove(2);
     b->print();
   //  b->preTraversing();
     cout<<"..............."<<b->countCBT()<<endl;
   //  for(b->begin();!b->end();b->next()){
        //    cout<<b->current()->value<<endl;
 //    }
   // SmartPointer< BTree<int> > clo = b->clone();
   // clo->print();

   // SmartPointer< BTree<int> > sum = *b + *clo;
  //  sum->print();
//    cout<< (*b == *clo) << (*b == *sum) << endl;
//     SmartPointer< LinkQueue< BTreeNode<T>*  > >
    SmartPointer<  LinkQueue< BTreeNode<int>* > > q = b->travesal(POST_ORDER);
    BTreeNode<int>*  n = NULL;
    while(q->length() > 0){
        q->front(n);
        cout<<n->value<<" ";
        q->remove();
    }
}

void testMatricGraph(){
    MatricGraph<4,int,int>* g = new MatricGraph<4,int,int>();
    g->setVertext(0,0);
    g->setVertext(1,1);
    g->setVertext(2,2);
    g->setVertext(3,3);
    g->setEdge(0,1,1);
    g->setEdge(0,3,1);
    g->setEdge(1,0,1);
    g->setEdge(1,2,1);
    g->setEdge(2,1,1);
    g->setEdge(2,3,1);
    g->setEdge(3,0,1);
    g->setEdge(3,2,1);
    g->print();
   // testBtree();
    //testGTree();
    cout<<"ecout: "<<g->eCout();
     cout<<"vcout: "<<g->vCout();
     cout<<"od: "<<g->OD(0);
     cout<<"id:"<<g->ID(1);
     cout<<"TD"<<g->TD(2);
}
void testListReVerse(){
 //   cout<<"start";
   LinkList<int> list;
   int v[9] = {1,2,3,4,5,4,3,2,1};
    for(int i = 0 ; i < 9 ; i++){
        list.insert(v[i]);
    }
  //  cout<<list.length()<<endl;
   // list.reverse();
  //  list.print();
    //list.reverse();
   // list.print();
    cout<<list.isBtt()<<endl;
    list.print();
}

void printShareValue(){
LinkList<int> l;
LinkList<int> l1;
int  data[10] = {0,1,2,3,4,6,6,7,8,9};
int  data1[10] = {0,1,2,3,4,5,6,7,8,9};
for(int i = 0; i < 10 ; i++){
    l.insert(i,data[i]);
    l1.insert(i,data1[i]);
}
int curr1 = 0;
int curr2 = 0;
int v1 ,v2;
for(int i = 0 ; (curr1 < l.length()) && (curr2 < l1.length()) ; i++){
    l.get(curr1,v1);
    l1.get(curr2,v2);
    if(v1 > v2){
          curr2++;
          cout<<endl;
    }else if(v1 < v2){
        curr1++;
        cout<<endl;
    }else{
        curr1++;
        curr2++;
        cout<<v1<<" , ";
    }
}

}
void testExcption(){
    LinkList<int> l;
   // THROW_EXCEPTION("",InvalidParameterException);

}

int main(){
    //cout<<"start main";
    //testListReVerse();
  //  printShareValue();
  //  testExcption();
    testBtree();
}

