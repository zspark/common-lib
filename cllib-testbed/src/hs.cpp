#include <Windows.h>
#include <iostream>
#include "cl/cl_hierarchical_structure.h"

using namespace std;
using namespace cl;


struct DATA{
  int a;
  float b;
  bool c;
};

int main(){

  typedef hs::clHSNode sh_node_int;
  typedef hs::clHS sh_int;

  sh_int hs;
  cluint N{5};
  sh_node_int* node=nullptr;
  sh_node_int* node2=nullptr;
  for(cluint i=0;i<N;i++){
    node=hs.CreateNode();
    node->custom=new DATA();
    hs.InsertNode(nullptr,node,hs::clHSNodeRelation::R_FIRST_CHILD);
    if(i==2){
      for(cluint j=0;j<N;j++){
        sh_node_int* node3=hs.CreateNode();
        hs.InsertNode(node,node3,hs::clHSNodeRelation::R_LAST_CHILD);
        if(j==2){
          for(cluint k=0;k<N;k++){
            sh_node_int* node4=hs.CreateNode();
            hs.InsertNode(node3,node4,hs::clHSNodeRelation::R_LAST_CHILD);
          }
        }
      }
    }
  }

  node2=hs.CreateNode();
  node=hs.GetFirstChildNode();
  hs.InsertNode(node,node2,hs::clHSNodeRelation::R_FIRST_CHILD);


#if 1
  //test traverse;
  hs.Print();
  //system("pause");
  cout<<"======================"<<endl;
  node=hs.Traverse(nullptr,true);
  while(node){
    cout<<node->GetId()<<endl;
    node=hs.Traverse();
  }
#endif

  system("pause");
  hs.DeleteAllNodes();

  return 0;
}