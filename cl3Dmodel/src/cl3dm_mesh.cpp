#include "cl3dm/cl3dm_mesh.h"

CL3DM_NAMESPACE_START
cl3dmMesh::cl3dmMesh(cluint meshIndexInModel)
:m_meshIndexInModel(meshIndexInModel){}

cl3dmMesh::~cl3dmMesh(){
  m_vertices=nullptr;
  m_tangents=nullptr;
  m_biTangents=nullptr;
  m_normals=nullptr;
  m_indices=nullptr;
}
CL3DM_NAMESPACE_END
