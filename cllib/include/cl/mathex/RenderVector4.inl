#ifndef VECTOR4_INL_INC
#define VECTOR4_INL_INC

#ifdef __cplusplus
#include "RenderVector4.h"
#include <cmath>
#include <assert.h>

// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline void Vector4t<TReal>::swap(Vector4t<TReal>& other){
	std::swap(x, other.x);
	std::swap(y, other.y);
	std::swap(z, other.z);
	std::swap(w, other.w);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline TReal Vector4t<TReal>::dotProduct(const Vector4t<TReal>& vec) const{
	return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline TReal Vector4t<TReal>::operator[](const size_t i) const{
	return *(&x + i);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline TReal&  Vector4t<TReal>::operator [] (const size_t i){
	return *(&x + i);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline Vector4t<TReal>& Vector4t<TReal>::operator = (const Vector4t<TReal>& rkVector){
	x = rkVector.x;
	y = rkVector.y;
	z = rkVector.z;
	w = rkVector.w;

	return *this;
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline Vector4t<TReal>& Vector4t<TReal>::operator = (const TReal fScalar){
	x = fScalar;
	y = fScalar;
	z = fScalar;
	w = fScalar;
	return *this;
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline bool Vector4t<TReal>::operator == (const Vector4t<TReal>& rkVector) const{
	return (x == rkVector.x &&
		y == rkVector.y &&
		z == rkVector.z &&
		w == rkVector.w);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline bool Vector4t<TReal>::operator != (const Vector4t<TReal>& rkVector) const{
	return (x != rkVector.x ||
		y != rkVector.y ||
		z != rkVector.z ||
		w != rkVector.w);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline Vector4t<TReal>& Vector4t<TReal>::operator = (const Vector3t<TReal>& rhs){
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	w = 1.0f;
	return *this;
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline Vector4t<TReal> Vector4t<TReal>::operator + (const Vector4t<TReal>& rkVector) const{
	return Vector4t<TReal>(
		x + rkVector.x,
		y + rkVector.y,
		z + rkVector.z,
		w + rkVector.w);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline Vector4t<TReal> Vector4t<TReal>::operator - (const Vector4t<TReal>& rkVector) const{
	return Vector4t<TReal>(
		x - rkVector.x,
		y - rkVector.y,
		z - rkVector.z,
		w - rkVector.w);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline Vector4t<TReal> Vector4t<TReal>::operator * (const TReal fScalar) const{
	return Vector4t<TReal>(
		x * fScalar,
		y * fScalar,
		z * fScalar,
		w * fScalar);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline Vector4t<TReal> Vector4t<TReal>::operator * (const Vector4t<TReal>& rhs) const{
	return Vector4t<TReal>(
		rhs.x * x,
		rhs.y * y,
		rhs.z * z,
		rhs.w * w);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline Vector4t<TReal> Vector4t<TReal>::operator / (const TReal fScalar) const{
	assert(fScalar != 0.0);

	TReal fInv = 1.0f / fScalar;

	return Vector4t<TReal>(
		x * fInv,
		y * fInv,
		z * fInv,
		w * fInv);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline Vector4t<TReal> Vector4t<TReal>::operator / (const Vector4t<TReal>& rhs) const{
	return Vector4t<TReal>(
		x / rhs.x,
		y / rhs.y,
		z / rhs.z,
		w / rhs.w);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline Vector4t<TReal>& Vector4t<TReal>::operator += (const Vector4t<TReal>& rkVector){
	x += rkVector.x;
	y += rkVector.y;
	z += rkVector.z;
	w += rkVector.w;

	return *this;
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline Vector4t<TReal>& Vector4t<TReal>::operator -= (const Vector4t<TReal>& rkVector){
	x -= rkVector.x;
	y -= rkVector.y;
	z -= rkVector.z;
	w -= rkVector.w;

	return *this;
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline Vector4t<TReal>& Vector4t<TReal>::operator *= (const TReal fScalar){
	x *= fScalar;
	y *= fScalar;
	z *= fScalar;
	w *= fScalar;
	return *this;
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline Vector4t<TReal>& Vector4t<TReal>::operator += (const TReal fScalar){
	x += fScalar;
	y += fScalar;
	z += fScalar;
	w += fScalar;
	return *this;
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline Vector4t<TReal>& Vector4t<TReal>::operator -= (const TReal fScalar){
	x -= fScalar;
	y -= fScalar;
	z -= fScalar;
	w -= fScalar;
	return *this;
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline Vector4t<TReal>& Vector4t<TReal>::operator *= (const Vector4t<TReal>& rkVector){
	x *= rkVector.x;
	y *= rkVector.y;
	z *= rkVector.z;
	w *= rkVector.w;

	return *this;
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline Vector4t<TReal>& Vector4t<TReal>::operator /= (const TReal fScalar){
	assert(fScalar != 0.0);

	TReal fInv = 1.0f / fScalar;

	x *= fInv;
	y *= fInv;
	z *= fInv;
	w *= fInv;

	return *this;
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline Vector4t<TReal>& Vector4t<TReal>::operator /= (const Vector4t<TReal>& rkVector){
	x /= rkVector.x;
	y /= rkVector.y;
	z /= rkVector.z;
	w /= rkVector.w;

	return *this;
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE  Vector4t<TReal> operator * (const TReal fScalar, const Vector4t<TReal>& rkVector){
	return Vector4t<TReal>(
		fScalar * rkVector.x,
		fScalar * rkVector.y,
		fScalar * rkVector.z,
		fScalar * rkVector.w);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE Vector4t<TReal> operator / (const TReal fScalar, const Vector4t<TReal>& rkVector){
	return Vector4t<TReal>(
		fScalar / rkVector.x,
		fScalar / rkVector.y,
		fScalar / rkVector.z,
		fScalar / rkVector.w);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE Vector4t<TReal> operator + (const Vector4t<TReal>& lhs, const TReal rhs)
{
	return Vector4t<TReal>(
		lhs.x + rhs,
		lhs.y + rhs,
		lhs.z + rhs,
		lhs.w + rhs);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE Vector4t<TReal> operator + (const TReal lhs, const Vector4t<TReal>& rhs)
{
	return Vector4t<TReal>(
		lhs + rhs.x,
		lhs + rhs.y,
		lhs + rhs.z,
		lhs + rhs.w);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE Vector4t<TReal> operator - (const Vector4t<TReal>& lhs, TReal rhs)
{
	return Vector4t<TReal>(
		lhs.x - rhs,
		lhs.y - rhs,
		lhs.z - rhs,
		lhs.w - rhs);
}
// -----------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE Vector4t<TReal> operator - (const TReal lhs, const Vector4t<TReal>& rhs)
{
	return Vector4t<TReal>(
		lhs - rhs.x,
		lhs - rhs.y,
		lhs - rhs.z,
		lhs - rhs.w);
}
// -----------------------------------------------------------------------------------------------

#endif
#endif