#ifndef __Matrix3_H__
#define __Matrix3_H__

namespace cl {
#ifdef __cplusplus
	template <typename T> class Matrix4x4t;

	template <typename TReal>
	class Matrix3x3t {
	public:
		Matrix3x3t():
			a1(static_cast<TReal>(1.0f)),a2(),a3(),
			b1(),b2(static_cast<TReal>(1.0f)),b3(),
			c1(),c2(),c3(static_cast<TReal>(1.0f)) {
		}

		Matrix3x3t(TReal _a1,TReal _a2,TReal _a3,
							 TReal _b1,TReal _b2,TReal _b3,
							 TReal _c1,TReal _c2,TReal _c3):
							 a1(_a1),a2(_a2),a3(_a3),
							 b1(_b1),b2(_b2),b3(_b3),
							 c1(_c1),c2(_c2),c3(_c3){
}

	Matrix3x3t(TReal* f);
public:

	Matrix3x3t& operator *= (const Matrix3x3t& m);
	Matrix3x3t  operator  * (const Matrix3x3t& m) const;
	Matrix3x3t operator + (const Matrix3x3t& m2) const;
	Matrix3x3t operator - (const Matrix3x3t& m2) const;

	TReal* operator[]       (unsigned int p_iIndex);
	const TReal* operator[] (unsigned int p_iIndex) const;

	bool operator== (const Matrix4x4t<TReal>& m) const;
	bool operator!= (const Matrix4x4t<TReal>& m) const;

	bool Equal(const Matrix4x4t<TReal>& m, TReal epsilon = 1e-6) const;

	template <typename TOther>
	operator Matrix3x3t<TOther>() const;

public:

	explicit Matrix3x3t(const Matrix4x4t<TReal>& pMatrix);

	Matrix3x3t& Transpose();

	Matrix3x3t& Inverse();
	TReal Determinant() const;

	void fromMatrix3ToArray(TReal* out);
public:
	/*static Matrix3x3t& RotationZ(TReal a, Matrix3x3t& out);

	static Matrix3x3t& Rotation(TReal a,
		const aiVector3t<TReal>& axis, Matrix3x3t& out);
	static Matrix3x3t& Translation(const aiVector2t<TReal>& v, Matrix3x3t& out);

	static aiMatrix3x3t& FromToMatrix(const aiVector3t<TReal>& from,
		const aiVector3t<TReal>& to, aiMatrix3x3t& out);*/

public:
	TReal a1, a2, a3;
	TReal b1, b2, b3;
	TReal c1, c2, c3;
};

typedef Matrix3x3t<float> Matrix3x3;

#endif
}
#endif
