#ifndef __Vector2_H__
#define __Vector2_H__

#ifdef __cplusplus
#include <cmath>
#else
#include <math.h>
#endif
#ifdef __cplusplus
template <typename TReal>
class Vector2t{
public:
	Vector2t() : x(), y() {}
	Vector2t(TReal _x, TReal _y) : x(_x), y(_y) {}
	explicit Vector2t(TReal _xyz) : x(_xyz), y(_xyz) {}
	Vector2t(const Vector2t& o) : x(o.x), y(o.y) {}

public:

	void Set(TReal pX, TReal pY);
	TReal SquareLength() const;
	TReal Length() const;
	Vector2t& Normalize();

public:

	const Vector2t& operator += (const Vector2t& o);
	const Vector2t& operator -= (const Vector2t& o);
	const Vector2t& operator + (const Vector2t& o);
	const Vector2t& operator - (const Vector2t& o);
	const Vector2t& operator * (const Vector2t& o);
	const Vector2t& operator / (const Vector2t& o);
	const Vector2t& operator * (TReal f);
	const Vector2t& operator / (TReal f);
	const Vector2t& operator *= (TReal f);
	const Vector2t& operator /= (TReal f);

	TReal operator[](unsigned int i) const;
	TReal& operator[](unsigned int i);

	bool operator== (const Vector2t& other) const;
	bool operator!= (const Vector2t& other) const;

	bool Equal(const Vector2t& other, TReal epsilon = 1e-6) const;
	TReal dotProduct(const Vector2t& vec) const;
	Vector2t& operator= (TReal f);

	template <typename TOther>
	operator Vector2t<TOther>() const;

	TReal x, y;

};
typedef Vector2t<float> Vector2D;

#else

struct aiVector2D {
	float x, y;
};
#endif
#endif