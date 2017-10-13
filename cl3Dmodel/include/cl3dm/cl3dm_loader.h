#pragma once

#include "cl3dm\core\cl3dm_macro.h"
#include "cl\cl_types.h"
#include "cl\cl_hierarchical_structure.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"

CL3DM_NAMESPACE_START
class cl3dmMesh;

typedef cl::hs::clHSNode_T<cl3dmMesh*> hsn;
typedef cl::hs::clHS_T<cl3dmMesh*> hs;
typedef cl::hs::clHSNodeRelation hsr;

class CL3DM_API cl3dmLoader{
public:
  cl3dmLoader();
  ~cl3dmLoader();
  clbool Loader(clstr fileURL);
  const cl3dmMesh* GetMesh(clbool begin=false);
  cluint GetNumMeshes()const{ return m_uNumMeshes; }

private:
  cl3dmMesh* CreateMesh_(aiMesh* aimesh,cluint index);
  const aiScene* m_scene=nullptr;
  cluint m_uNumMeshes=0;
  hs m_hs;
  cluint m_uNextMeshIndex=0;

};
CL3DM_NAMESPACE_END
