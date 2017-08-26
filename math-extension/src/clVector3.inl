#ifndef VECTOR3D_INL_INC
#define VECTOR3D_INL_INC

#ifdef __cplusplus
#include "clVector3.h"

#include <cmath>

#define AI_FORCE_INLINE __forceinline
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	inline Vector3t<TReal> operator * (const Matrix3x3t<TReal>& pMatrix,const Vector3t<TReal>& pVector) {
		Vector3t<TReal> res;
		res.x=pMatrix.a1 * pVector.x+pMatrix.a2 * pVector.y+pMatrix.a3 * pVector.z;
		res.y=pMatrix.b1 * pVector.x+pMatrix.b2 * pVector.y+pMatrix.b3 * pVector.z;
		res.z=pMatrix.c1 * pVector.x+pMatrix.c2 * pVector.y+pMatrix.c3 * pVector.z;
		return res;
	}

	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	inline Vector3t<TReal> operator * (const Matrix4x4t<TReal>& pMatrix,const Vector3t<TReal>& pVector) {
		Vector3t<TReal> res;
		res.x=pMatrix.a1 * pVector.x+pMatrix.a2 * pVector.y+pMatrix.a3 * pVector.z+pMatrix.a4;
		res.y=pMatrix.b1 * pVector.x+pMatrix.b2 * pVector.y+pMatrix.b3 * pVector.z+pMatrix.b4;
		res.z=pMatrix.c1 * pVector.x+pMatrix.c2 * pVector.y+pMatrix.c3 * pVector.z+pMatrix.c4;
		return res;
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	template <typename TOther>
	Vector3t<TReal>::operator Vector3t<TOther>() const {
		return Vector3t<TOther>(static_cast<TOther>(x),static_cast<TOther>(y),static_cast<TOther>(z));
	}

	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	inline TReal Vector3t<TReal>::SquareLength() const {
		return x*x+y*y+z*z;
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE TReal Vector3t<TReal>::Length() const {
		return std::sqrt(SquareLength());
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE Vector3t<TReal>& Vector3t<TReal>::Normalize() {
		*this/=Length(); return *this;
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE const Vector3t<TReal>& Vector3t<TReal>::operator += (const Vector3t<TReal>& o) {
		x+=o.x; y+=o.y; z+=o.z; return *this;
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE const Vector3t<TReal>& Vector3t<TReal>::operator -= (const Vector3t<TReal>& o) {
		x-=o.x; y-=o.y; z-=o.z; return *this;
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE const Vector3t<TReal>& Vector3t<TReal>::operator *= (TReal f) {
		x*=f; y*=f; z*=f; return *this;
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE const Vector3t<TReal>& Vector3t<TReal>::operator /= (TReal f) {
		x/=f; y/=f; z/=f; return *this;
	}
	template <typename TReal>
	AI_FORCE_INLINE const Vector3t<TReal> Vector3t<TReal>::operator * (TReal f) {
		Vector3t<TReal> v(x*f,y*f,z*f);
		return v;
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE Vector3t<TReal>& Vector3t<TReal>::operator *= (const Matrix3x3t<TReal>& mat) {
		return(*this=mat * (*this));
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE Vector3t<TReal>& Vector3t<TReal>::operator *= (const Matrix4x4t<TReal>& mat) {
		return(*this=mat * (*this));
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE TReal Vector3t<TReal>::operator[](unsigned int i) const {
		return *(&x+i);
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE TReal& Vector3t<TReal>::operator[](unsigned int i) {
		return *(&x+i);
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE bool Vector3t<TReal>::operator== (const Vector3t<TReal>& other) const {
		return x==other.x && y==other.y && z==other.z;
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE bool Vector3t<TReal>::operator!= (const Vector3t<TReal>& other) const {
		return x!=other.x||y!=other.y||z!=other.z;
	}
	// ---------------------------------------------------------------------------
	template<typename TReal>
	AI_FORCE_INLINE bool Vector3t<TReal>::Equal(const Vector3t<TReal>& other,TReal epsilon) const {
		return
			std::abs(x-other.x)<=epsilon &&
			std::abs(y-other.y)<=epsilon &&
			std::abs(z-other.z)<=epsilon;
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE void Vector3t<TReal>::Set(TReal pX,TReal pY,TReal pZ) {
		x=pX; y=pY; z=pZ;
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE bool Vector3t<TReal>::operator < (const Vector3t<TReal>& other) const {
		return x!=other.x?x<other.x:y!=other.y?y<other.y:z<other.z;
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE const Vector3t<TReal> Vector3t<TReal>::SymMul(const Vector3t<TReal>& o) {
		return Vector3t<TReal>(x*o.x,y*o.y,z*o.z);
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE Vector3t<TReal> operator + (const Vector3t<TReal>& v1,const Vector3t<TReal>& v2) {
		return Vector3t<TReal>(v1.x+v2.x,v1.y+v2.y,v1.z+v2.z);
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE Vector3t<TReal> operator - (const Vector3t<TReal>& v1,const Vector3t<TReal>& v2) {
		return Vector3t<TReal>(v1.x-v2.x,v1.y-v2.y,v1.z-v2.z);
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE TReal operator * (const Vector3t<TReal>& v1,const Vector3t<TReal>& v2) {
		return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE Vector3t<TReal> operator * (TReal f,const Vector3t<TReal>& v) {
		return Vector3t<TReal>(f*v.x,f*v.y,f*v.z);
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE  Vector3t<TReal> operator * (const Vector3t<TReal>& v,TReal f) {
		return Vector3t<TReal>(f*v.x,f*v.y,f*v.z);
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE  Vector3t<TReal> operator / (const Vector3t<TReal>& v,TReal f) {
		return v * (1/f);
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE  Vector3t<TReal> operator / (const Vector3t<TReal>& v,const Vector3t<TReal>& v2) {
		return Vector3t<TReal>(v.x/v2.x,v.y/v2.y,v.z/v2.z);
	}
	// ------------------------------------------------------------------------------------------------
	// cross product
	template <typename TReal>
	AI_FORCE_INLINE  Vector3t<TReal> operator ^ (const Vector3t<TReal>& v1,const Vector3t<TReal>& v2) {
		return Vector3t<TReal>(v1.y*v2.z-v1.z*v2.y,v1.z*v2.x-v1.x*v2.z,v1.x*v2.y-v1.y*v2.x);
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE  Vector3t<TReal> operator - (const Vector3t<TReal>& v) {
		return Vector3t<TReal>(-v.x,-v.y,-v.z);
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	inline TReal Vector3t<TReal>::projection(Vector3t<TReal>& n) {

		TReal value=0;;
		Vector3t<TReal> v=projectionVector(n);

		return v.Length();
	}

	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	inline Vector3t<TReal>  Vector3t<TReal>::projectionVector(Vector3t<TReal>& n) {
		Vector3t<TReal> out;
		Vector3t<TReal> V(x,y,z);
		TReal length=n.SquareLength();
		TReal dot=V*n;
		TReal mul=dot/length;
		out=n*mul;
		return out;
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	inline TReal Vector3t<TReal>::angleBetween(Vector3t<TReal>& dest) {
		TReal lenProduct=Length() * dest.Length();

		// Divide by zero check
		if(lenProduct<1e-6f)
			lenProduct=1e-6f;

		TReal f=dotProduct(dest)/lenProduct;
		f=std::max(std::min(f,static_cast<TReal>(1.0)),static_cast<TReal>(-1.0));

		return acos(f);
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	inline TReal Vector3t<TReal>::cosBetween(Vector3t<TReal>& dest) {
		TReal lenProduct=Length() * dest.Length();

		// Divide by zero check
		if(lenProduct<1e-6f)
			lenProduct=1e-6f;

		TReal f=dotProduct(dest)/lenProduct;
		f=std::max(std::min(f,static_cast<TReal>(1.0)),static_cast<TReal>(-1.0));
		return f;
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	TReal Vector3t<TReal>::dotProduct(const Vector3t<TReal>& vec) const {
		return x * vec.x+y * vec.y+z * vec.z;
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	const Vector3t<TReal> Vector3t<TReal>::crossProduct(const Vector3t<TReal>& vec) const {
		return Vector3t<TReal>(y*vec.z-vec.y*z,z*vec.x-vec.z*x,x*vec.y-y*vec.x);
	}

#endif
#endif