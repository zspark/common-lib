
#include "cl3dm/cl3dm_loader.h"
#include <vector>
#include <map>
#include "assimp/postprocess.h"
#include <iostream>
#include "cl3dm/cl3dm_mesh.h"

using namespace std;

CL3DM_NAMESPACE_START
cl3dmLoader::cl3dmLoader(){}

cl3dmLoader::~cl3dmLoader(){
  hsn* node=m_hs.Traverse(nullptr,true);
  while(node){
    delete node->customObject;
    node=m_hs.Traverse(nullptr,false);
  }
}

clbool cl3dmLoader::Loader(clstr fileURL){
  Assimp::Importer importer;
  m_scene=importer.ReadFile(fileURL,aiProcess_Triangulate|aiProcess_FlipUVs);
  if(!m_scene||m_scene->mFlags==AI_SCENE_FLAGS_INCOMPLETE||!m_scene->mRootNode){
    cout<<"ERROR::ASSIMP::"<<importer.GetErrorString()<<endl;
    return false;
  }
  //directory=path.substr(0,path.find_last_of('/'));

  map<aiNode*,hsn*> tmpMap;

  vector<aiNode*> tmpVec;
  tmpVec.push_back(m_scene->mRootNode);
  aiNode* tmpNode=nullptr;
  aiNode* parentNode=nullptr;
  aiMesh* tmpMesh=nullptr;
  cluint index=0;
  while(tmpVec.size()>0){
    tmpNode=tmpVec.back();
    tmpVec.pop_back();
    //create root node;
    parentNode=tmpNode->mParent;
    hsn* parentNd=parentNode?tmpMap[parentNode]:nullptr;
    hsn* nd=m_hs.CreateNode();
    nd->customObject=nullptr;
    m_hs.InsertNode(parentNd,nd,hsr::R_LAST_CHILD);
    tmpMap[tmpNode]=nd;

    for(cluint i=0u;i<tmpNode->mNumChildren;i++){
      tmpVec.push_back(tmpNode->mChildren[i]);
    }
    for(cluint i=0u;i<tmpNode->mNumMeshes;i++){
      tmpMesh=m_scene->mMeshes[tmpNode->mMeshes[i]];
      nd=m_hs.CreateNode();
      nd->customObject=CreateMesh_(tmpMesh,index++);
      parentNode=tmpNode->mParent;
      parentNd=parentNode?tmpMap[parentNode]:nullptr;
      m_hs.InsertNode(parentNd,nd,hsr::R_LAST_CHILD);
      tmpMap[tmpNode]=nd;
    }
  }

#if __CL3DM_DEBUG__
  clint a=10;
  m_hs.Print();
#endif
}
const cl3dmMesh * cl3dmLoader::GetMesh(clbool begin){
  return m_hs.Traverse(nullptr,begin)->customObject;
}
cl3dmMesh * cl3dmLoader::CreateMesh_(aiMesh * aimesh,cluint index){
  cl3dmMesh* mesh=new cl3dmMesh(index);
  mesh->m_sName=aimesh->mName.C_Str();
  mesh->m_biTangents=(cl::clf3*)aimesh->mBitangents;
  mesh->m_normals=(cl::clf3*)aimesh->mNormals;
  mesh->m_tangents=(cl::clf3*)aimesh->mTangents;
  mesh->m_vertices=(cl::clf3*)aimesh->mVertices;
  mesh->m_uNumVertices=aimesh->mNumVertices;


  cluint N{aimesh->mNumFaces};
  cluint totalNumIndices=0;
  for(cluint i=0u;i<N;i++){
    aiFace& face=aimesh->mFaces[i];
    totalNumIndices+=face.mNumIndices;
  }
  mesh->m_uNumIndices=totalNumIndices;
  mesh->m_indices=new cluint[totalNumIndices];
  cluint index2=0;
  for(cluint i=0u;i<N;i++){
    aiFace& face=aimesh->mFaces[i];
    for(cluint j=0u;j<face.mNumIndices;j++){
      mesh->m_indices[index2++]=face.mIndices[j];
    }
  }
  return mesh;
}
CL3DM_NAMESPACE_END
