#include <Windows.h>
#include <iostream>
#include "cllib.h"
#include "clPrinter.h"
#include "clHierarchicalStructure.h"

using namespace std;
using namespace cl;

int main(){
  cl::Info("Hello World!");

  typedef hs::clHSNode_T<float> sh_node_int;
  typedef hs::clHS_T<float> sh_int;

  sh_int hs;
  sh_node_int* node=hs.CreateNode();
  node->customObject=10.0f;
  hs.InsertNode(nullptr,node,hs::clHSNodeRelation::R_FIRST_CHILD);

  sh_node_int* node2=hs.CreateNode();
  node2->customObject=1010;
  hs.InsertNode(node,node2,hs::clHSNodeRelation::R_FIRST_CHILD);

  //hs.DeleteAllNodes();
  cout<<hs.GetFirstChildNode(node)->customObject<<endl;

  node=hs.GetFirstChildNode();
  node=node->GetParentNode();

  hs.Print();



  system("pause");
  return 0;
}