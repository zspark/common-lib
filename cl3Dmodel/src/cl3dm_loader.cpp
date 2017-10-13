
#include "cl3dm/cl3dm_loader.h"
#include <vector>
#include <map>
#include "assimp/postprocess.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "cl3dm/cl3dm_mesh.h"

using namespace std;

CL3DM_NAMESPACE_START

cl3dmLoader::cl3dmLoader(){}

cl3dmLoader::~cl3dmLoader(){
  m_hs.DeleteAllNodes(true);
}

clbool cl3dmLoader::Load(clstr fileURL){
  m_uNumMeshes=0;
  Assimp::Importer importer;
  const aiScene* scene=importer.ReadFile(fileURL,aiProcess_Triangulate|aiProcess_FlipUVs);
  if(!scene||scene->mFlags==AI_SCENE_FLAGS_INCOMPLETE||!scene->mRootNode){
    cout<<"ERROR::ASSIMP::"<<importer.GetErrorString()<<endl;
    return false;
  }
  //directory=path.substr(0,path.find_last_of('/'));

  map<aiNode*,hsn*> tmpMap;

  vector<aiNode*> tmpVec;
  tmpVec.push_back(scene->mRootNode);
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
    nd->custom=nullptr;
    m_hs.InsertNode(parentNd,nd,hsr::R_LAST_CHILD);
    tmpMap[tmpNode]=nd;

    for(cluint i=0u;i<tmpNode->mNumChildren;i++){
      tmpVec.push_back(tmpNode->mChildren[i]);
    }
    for(cluint i=0u;i<tmpNode->mNumMeshes;i++){
      tmpMesh=scene->mMeshes[tmpNode->mMeshes[i]];
      nd=m_hs.CreateNode();
      nd->custom=CreateMesh_(tmpMesh,index++);
      parentNode=tmpNode->mParent;
      parentNd=parentNode?tmpMap[parentNode]:nullptr;
      m_hs.InsertNode(parentNd,nd,hsr::R_LAST_CHILD);
      tmpMap[tmpNode]=nd;
    }
  }

#if __CL3DM_INTERNAL_DEBUG__
  clint a=10;
  m_hs.Print();
#endif
}
const hsn * cl3dmLoader::GetNode(clbool begin){
  void* c=m_hs.Traverse(nullptr,begin);
  return (hsn*)c;
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
  m_uNumMeshes++;
  return mesh;
}
CL3DM_NAMESPACE_END
