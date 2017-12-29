#pragma once

#include <string>
#include "core\cl_compile.h"

typedef size_t clsize;
typedef int clint;
typedef unsigned int cluint;
typedef float clfloat;
typedef double cldouble;
typedef bool clbool;
typedef char clchar;
typedef std::string clstr;

CL_NAMESPACE_START

template<typename T>
struct type_2T{
  T x,y;
  type_2T(){}
  type_2T(T xx,T yy):x(xx),y(yy){}

  void Set(T valuex,T valuey){
    x=valuex; y=valuey;
  }

  void Set(T value){
    x=y=value;
  }

  clbool operator!=(const type_2T& rhs){
    return !(x==rhs.x && y==rhs.y);
  }

  type_2T& operator=(const type_2T& rhs){
    x=rhs.x;
    y=rhs.y;
    return *this;
  }
};
typedef type_2T<clint> cli2;
typedef type_2T<cluint> clui2;
typedef type_2T<clfloat> clf2;
typedef type_2T<cldouble> cld2;

template<typename T>
struct type_3T{
  T x,y,z;
  type_3T(){}
  type_3T(T xx,T yy,T zz):x(xx),y(yy),z(zz){}
  void Set(T valuex,T valuey,T valuez){
    x=valuex; y=valuey; z=valuez;
  }

  void Set(T value){
    x=y=z=value;
  }

  clbool operator!=(const type_3T& rhs){
    return !(x==rhs.x && y==rhs.y && z==rhs.z);
  }

  type_3T& operator=(const type_3T& rhs){
    x=rhs.x;
    y=rhs.y;
    z=rhs.z;
    return *this;
  }
};
typedef type_3T<clint> cli3;
typedef type_3T<cluint> clui3;
typedef type_3T<clfloat> clf3;
typedef type_3T<cldouble> cld3;

template<typename T>
struct type_4T{
  T x,y,z,w;
  type_4T(){}
  type_4T(T xx,T yy,T zz,T ww):x(xx),y(yy),z(zz),w(ww){}

  void Set(T valuex,T valuey,T valuez,T valuew){
    x=valuex; y=valuey; z=valuez; w=valuew;
  }

  void Set(T value){
    x=y=z=w=value;
  }

  clbool operator!=(const type_4T& rhs){
    return !(x==rhs.x && y==rhs.y && z==rhs.z && w=rhs.w);
  }

  type_4T& operator=(const type_4T& rhs){
    x=rhs.x;
    y=rhs.y;
    z=rhs.z;
    w=rhs.w;
    return *this;
  }
};
typedef type_4T<clint> cli4;
typedef type_4T<cluint> clui4;
typedef type_4T<clfloat> clf4;
typedef type_4T<cldouble> cld4;

CL_API cluint GetUniqueUint();

CL_NAMESPACE_END
