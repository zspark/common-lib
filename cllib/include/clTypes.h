#pragma once

#include <string>

namespace cl{
typedef int clI;
typedef unsigned int clUi;
typedef float clF;
typedef double clD;
typedef bool clB;
typedef const char* clCcs;
typedef char* clCs;
typedef std::string clString;

template<typename T>
struct type_2T{
  T x,y;
  void Set(T valuex,T valuey){
    x=valuex; y=valuey;
  }

  void Set(T value){
    x=y=value;
  }

  void Copy(const type_2T& another){
    x=another.x;
    y=another.y;
  }
};
typedef type_2T<clI> clI2;
typedef type_2T<clUi> clUi2;
typedef type_2T<clF> clF2;
typedef type_2T<clD> clD2;

template<typename T>
struct type_3T{
  T x,y,z;
  void Set(T valuex,T valuey,T valuez){
    x=valuex; y=valuey; z=valuez;
  }

  void Set(T value){
    x=y=z=value;
  }

  void Copy(const type_3T& another){
    x=another.x;
    y=another.y;
    z=another.z;
  }
};
typedef type_3T<clI> clI3;
typedef type_3T<clUi> clUi3;
typedef type_3T<clF> clF3;
typedef type_3T<clD> clD3;

template<typename T>
struct type_4T{
  T x,y,z,w;

  void Set(T valuex,T valuey,T valuez,T valuew){
    x=valuex; y=valuey; z=valuez; w=valuew;
  }

  void Set(T value){
    x=y=z=w=value;
  }

  void Copy(const type_4T& another){
    x=another.x;
    y=another.y;
    z=another.z;
    w=another.w;
  }
};
typedef type_4T<clI> clI4;
typedef type_4T<clUi> clUi4;
typedef type_4T<clF> clF4;
typedef type_4T<clD> clD4;

enum clUniformType{
  CL_INT=0,
  CL_UINT,
  CL_FLOAT,
  CL_DOUBLE,
  CL_BOOL,
  CL_CHARSTAR,

  CL_INT2,
  CL_UINT2,
  CL_FLOAT2,
  CL_DOUBLE2,

  CL_INT3,
  CL_UINT3,
  CL_FLOAT3,
  CL_DOUBLE3,

  CL_INT4,
  CL_UINT4,
  CL_FLOAT4,
  CL_DOUBLE4,
};

struct clUniform{
  clUniform(){}
  clUniformType type;
  union{
    clI intValue;
    clUi uintValue;
    float floatValue;
    double doubleValue;
    bool boolValue;
    clCcs charValue;

    clF2 float2Value;
    clI2 int2Value;
    clUi2 uint2Value;
    clD2 double2Value;

    clF3 float3Value;
    clI3 int3Value;
    clUi3 uint3Value;
    clD3 double3Value;

    clF4 float4Value;
    clI4 int4Value;
    clUi4 uint4Value;
    clD4 double4Value;
  };
};
}
