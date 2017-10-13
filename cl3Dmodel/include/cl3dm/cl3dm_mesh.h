#pragma once

#include "cl3dm\core\cl3dm_macro.h"
#include "cl\cl_types.h"

CL3DM_NAMESPACE_START
class cl3dmLoader;

class CL3DM_API cl3dmMesh{
public:
  cl3dmMesh(cluint meshIndexInModel);
  const cl::clf3* GetVertices()const{ return m_vertices; }
  const cl::clf3* GetNormals()const{ return m_normals; }
  const cl::clf3* GetTangents()const{ return m_tangents; }
  const cl::clf3* GetBitangents()const{ return m_biTangents; }
  const cluint* GetIndices()const{ return m_indices; }
  cluint GetNumVertices()const{ return m_uNumVertices; }
  cluint GetNumNormals()const{ return m_uNumVertices; }
  cluint GetNumTangents()const{ return m_uNumVertices; }
  cluint GetNumBitangents()const{ return m_uNumVertices; }
  cluint GetNumIndices()const{ return m_uNumIndices; }

private:
  friend class cl3dmLoader;
  ~cl3dmMesh();
  const cluint m_meshIndexInModel;
  cluint m_uNumVertices;
  cl::clf3* m_vertices;
  cl::clf3* m_tangents;
  cl::clf3* m_biTangents;
  cl::clf3* m_normals;
  cluint* m_indices;
  cluint m_uNumIndices;
  clstr m_sName;
};

CL3DM_NAMESPACE_END
