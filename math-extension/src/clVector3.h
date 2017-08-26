#ifndef __Vector3_H__
#define __Vector3_H__

namespace cl {

#ifdef __cplusplus
#include <cmath>
#else
#include <math.h>
#endif

#ifdef __cplusplus

	template<typename TReal> class Matrix3x3t;
	template<typename TReal> class Matrix4x4t;

	template <typename TReal>
	class Vector3t {
	public:
		Vector3t(): x(),y(),z() {}
		Vector3t(TReal _x,TReal _y,TReal _z): x(_x),y(_y),z(_z) {}
		explicit Vector3t(TReal* _p): x(_p[0]),y(_p[1]),z(_p[2]) {}
		explicit Vector3t(TReal _xyz): x(_xyz),y(_xyz),z(_xyz) {}
		Vector3t(const Vector3t& o): x(o.x),y(o.y),z(o.z) {}
	public:
		const Vector3t& operator += (const Vector3t& o);
		const Vector3t& operator -= (const Vector3t& o);
		const Vector3t& operator *= (TReal f);
		const Vector3t& operator /= (TReal f);
		const Vector3t operator * (TReal f);

		Vector3t& operator *= (const Matrix3x3t<TReal>& mat);
		Vector3t& operator *= (const Matrix4x4t<TReal>& mat);

		TReal operator[](unsigned int i) const;
		TReal& operator[](unsigned int i);

		bool operator== (const Vector3t& other) const;
		bool operator!= (const Vector3t& other) const;
		bool operator < (const Vector3t& other) const;

		bool Equal(const Vector3t& other,TReal epsilon=1e-6) const;

		template <typename TOther>
		operator Vector3t<TOther>() const;
	public:
		void Set(TReal pX,TReal pY,TReal pZ);
		TReal SquareLength() const;
		TReal Length() const;
		Vector3t& Normalize();
		const Vector3t SymMul(const Vector3t& o);
		TReal projection(Vector3t& n); //某向量上的投影距离
		Vector3t projectionVector(Vector3t& n);//某向量上的投影
		TReal angleBetween(Vector3t& dest);
		TReal cosBetween(Vector3t& dest);
		TReal dotProduct(const Vector3t& vec) const;
		const Vector3t crossProduct(const Vector3t& vec) const;

		TReal x,y,z;
	};
	typedef Vector3t<float> vec3f;
	typedef Vector3t<int> vec3i;
	typedef Vector3t<double> vec3d;
#else 
	struct Vector3D{
		float x,y,z;
	};
#endif // __cplusplus

#include "clVector3.inl"
}
#endif