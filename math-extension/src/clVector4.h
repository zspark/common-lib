#ifndef __Vector4_H__
#define __Vector4_H__

namespace cl {

#ifdef __cplusplus
#include <cmath>
#else
#include <math.h>
#endif
#include "clVector3.h"
#include "cldef.h"
#ifdef __cplusplus


	template <typename TReal>
	class Vector4t {
	public:
		Vector4t(): x(),y(),z(),w() {}
		Vector4t(TReal _x): x(_x),y(_x),z(_x),w(_x) {}
		Vector4t(TReal _x,TReal _y,TReal _z,TReal _w): x(_x),y(_y),z(_z),w(_w) {}
		Vector4t(const Vector4t& o): x(o.x),y(o.y),z(o.z),w(o.w) {}
		explicit Vector4t(TReal* const r)
			: x(r[0]),y(r[1]),z(r[2]),w(r[3]) {}
		explicit Vector4t(const Vector3t<TReal>& rhs)
			: x(rhs.x),y(rhs.y),z(rhs.z),w(static_cast<TReal>(1.0f)) {}
	public:
		void swap(Vector4t& other);
		TReal operator [] (const size_t i) const;
		TReal& operator [] (const size_t i);
		Vector4t& operator = (const Vector4t& rkVector);
		Vector4t& operator = (const TReal fScalar);
		bool operator == (const Vector4t& rkVector) const;
		bool operator != (const Vector4t& rkVector) const;
		Vector4t& operator = (const Vector3t<TReal>& rhs);
		Vector4t operator + (const Vector4t& rkVector) const;
		Vector4t operator - (const Vector4t& rkVector) const;
		Vector4t operator * (const TReal fScalar) const;
		Vector4t operator * (const Vector4t& rhs) const;
		Vector4t operator / (const TReal fScalar) const;
		Vector4t operator / (const Vector4t& rhs) const;
		Vector4t& operator += (const Vector4t& rkVector);
		Vector4t& operator -= (const Vector4t& rkVector);
		Vector4t& operator *= (const TReal fScalar);
		Vector4t& operator += (const TReal fScalar);
		Vector4t& operator -= (const TReal fScalar);
		Vector4t& operator *= (const Vector4t& rkVector);
		Vector4t& operator /= (const TReal fScalar);
		Vector4t& operator /= (const Vector4t& rkVector);

	public:
		TReal dotProduct(const Vector4t& vec) const;
	public:
		TReal x,y,z,w;
	};
	typedef Vector4t<float> Vector4D;
#else 
struct Vector4D{
	float x, y, z,w;
};
#endif
}
#endif