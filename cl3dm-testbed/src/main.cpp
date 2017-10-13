#include <iostream>
#include "cl3dm\cl3dm_loader.h"
#include "cl3dm\cl3dm_mesh.h"

using namespace std;
using namespace cl;
using namespace cl3dm;

int main(){
  cout<<"Hello World!"<<endl;


  cl3dmLoader loader;
  loader.Load("obuma.obj");
  //loader.Load("obuma.fbx");
  cluint N=loader.GetNumMeshes();
  const hsn* node=loader.GetNode(true);

  while(node){
    cl3dmMesh* mesh=(cl3dmMesh*)node->custom;
    if(mesh)
      cout<<mesh->GetName()<<endl;
    node=loader.GetNode(false);
  }







  system("pause");
  return 0;
}