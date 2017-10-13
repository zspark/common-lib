#pragma once

#include "cl3dm\core\cl3dm_macro.h"
#include "cl\cl_types.h"
#include "cl\cl_hierarchical_structure.h"

struct aiMesh;

CL3DM_NAMESPACE_START

enum class cl3dmloaderNodeType{
  TYPE_EMPTY=0,
  TYPE_CAMERA,
  TYPE_MESH,
  TYPE_EVN,
};
/*
class cl3dmNodedata{
public:
  cl3dmloaderNodeType type;
  cl3dmMesh* mesh=nullptr;
  ~cl3dmNodedata(){
    delete mesh;
  }

};
*/

typedef cl::hs::clHS hs;
typedef cl::hs::clHSNode hsn;
typedef cl::hs::clHSNodeRelation hsr;

class cl3dmMesh;

class CL3DM_API cl3dmLoader{
public:
  cl3dmLoader();
  ~cl3dmLoader();
  clbool Load(clstr fileURL);
  const hsn* GetNode(clbool begin=false);
  cluint GetNumMeshes()const{ return m_uNumMeshes; }

private:
  cl3dmMesh* CreateMesh_(aiMesh* aimesh,cluint index);
  cluint m_uNumMeshes=0;
  hs m_hs;
  cluint m_uNextMeshIndex=0;

};
CL3DM_NAMESPACE_END
