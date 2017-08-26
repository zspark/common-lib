#ifndef MATRIX3x3_INL_INC
#define MATRIX3x3_INL_INC


namespace cl {
#ifdef __cplusplus
#include "clMatrix3.h"

#include "clMatrix4.h"
#include <algorithm>
#include <cmath>
#include <limits>

	template <typename TReal>
	inline Matrix3x3t<TReal>::Matrix3x3t(const Matrix4x4t<TReal>& pMatrix) {
		a1=pMatrix.a1; a2=pMatrix.a2; a3=pMatrix.a3;
		b1=pMatrix.b1; b2=pMatrix.b2; b3=pMatrix.b3;
		c1=pMatrix.c1; c2=pMatrix.c2; c3=pMatrix.c3;
	}

	template <typename TReal>
	inline Matrix3x3t<TReal>::Matrix3x3t(TReal* f) {
		a1=f[0]; a2=f[1]; a3=f[2];
		b1=f[4]; b2=f[5]; b3=f[6];
		c1=f[8]; c2=f[9]; c3=f[10];
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix3x3t<TReal>& Matrix3x3t<TReal>::operator *= (const Matrix3x3t<TReal>& m) {
		*this=Matrix3x3t<TReal>(m.a1 * a1+m.b1 * a2+m.c1 * a3,
														m.a2 * a1+m.b2 * a2+m.c2 * a3,
														m.a3 * a1+m.b3 * a2+m.c3 * a3,
														m.a1 * b1+m.b1 * b2+m.c1 * b3,
														m.a2 * b1+m.b2 * b2+m.c2 * b3,
														m.a3 * b1+m.b3 * b2+m.c3 * b3,
														m.a1 * c1+m.b1 * c2+m.c1 * c3,
														m.a2 * c1+m.b2 * c2+m.c2 * c3,
														m.a3 * c1+m.b3 * c2+m.c3 * c3);
		return *this;
	}

	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	template <typename TOther>
	Matrix3x3t<TReal>::operator Matrix3x3t<TOther>() const {
		return Matrix3x3t<TOther>(static_cast<TOther>(a1),static_cast<TOther>(a2),static_cast<TOther>(a3),
															static_cast<TOther>(b1),static_cast<TOther>(b2),static_cast<TOther>(b3),
															static_cast<TOther>(c1),static_cast<TOther>(c2),static_cast<TOther>(c3));
	}

	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix3x3t<TReal> Matrix3x3t<TReal>::operator* (const Matrix3x3t<TReal>& m) const {
		Matrix3x3t<TReal> temp(*this);
		temp*=m;
		return temp;
	}
	// ---------------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix3x3t<TReal> Matrix3x3t<TReal>::operator - (const Matrix3x3t<TReal>& m) const {
		Matrix3x3t<TReal> out;
		out.a1=a1-m.a1; out.a2=a2-m.a2; out.a3=a3-m.a3;
		out.b1=b1-m.b1; out.b2=b2-m.b2; out.b3=b3-m.b3;
		out.c1=c1-m.c1; out.c2=c2-m.c2; out.c3=c3-m.c3;
		return out;
	}
	// ---------------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix3x3t<TReal> Matrix3x3t<TReal>::operator + (const Matrix3x3t<TReal>& m) const {
		Matrix3x3t<TReal> out;
		out.a1=a1+m.a1; out.a2=a2+m.a2; out.a3=a3+m.a3;
		out.b1=b1+m.b1; out.b2=b2+m.b2; out.b3=b3+m.b3;
		out.c1=c1+m.c1; out.c2=c2+m.c2; out.c3=c3+m.c3;
		return out;
	}
	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	inline TReal* Matrix3x3t<TReal>::operator[] (unsigned int p_iIndex) {
		return &this->a1+p_iIndex*3;
	}

	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	inline const TReal* Matrix3x3t<TReal>::operator[] (unsigned int p_iIndex) const {
		return &this->a1+p_iIndex*3;
	}

	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	inline bool Matrix3x3t<TReal>::operator== (const Matrix4x4t<TReal>& m) const {
		return a1==m.a1 && a2==m.a2 && a3==m.a3 &&
			b1==m.b1 && b2==m.b2 && b3==m.b3 &&
			c1==m.c1 && c2==m.c2 && c3==m.c3;
	}

	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	inline bool Matrix3x3t<TReal>::operator!= (const Matrix4x4t<TReal>& m) const {
		return !(*this==m);
	}

	// ---------------------------------------------------------------------------
	template<typename TReal>
	inline bool Matrix3x3t<TReal>::Equal(const Matrix4x4t<TReal>& m,TReal epsilon) const {
		return
			std::abs(a1-m.a1)<=epsilon &&
			std::abs(a2-m.a2)<=epsilon &&
			std::abs(a3-m.a3)<=epsilon &&
			std::abs(b1-m.b1)<=epsilon &&
			std::abs(b2-m.b2)<=epsilon &&
			std::abs(b3-m.b3)<=epsilon &&
			std::abs(c1-m.c1)<=epsilon &&
			std::abs(c2-m.c2)<=epsilon &&
			std::abs(c3-m.c3)<=epsilon;
	}

	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix3x3t<TReal>& Matrix3x3t<TReal>::Transpose() {
		std::swap((TReal&)a2,(TReal&)b1);
		std::swap((TReal&)a3,(TReal&)c1);
		std::swap((TReal&)b3,(TReal&)c2);
		return *this;
	}

	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline TReal Matrix3x3t<TReal>::Determinant() const {
		return a1*b2*c3-a1*b3*c2+a2*b3*c1-a2*b1*c3+a3*b1*c2-a3*b2*c1;
	}

	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix3x3t<TReal>& Matrix3x3t<TReal>::Inverse() {
		TReal det=Determinant();
		if(det==static_cast<TReal>(0.0)) {
			const TReal nan=std::numeric_limits<TReal>::quiet_NaN();
			*this=aiMatrix3x3t<TReal>(nan,nan,nan,nan,nan,nan,nan,nan,nan);

			return *this;
		}

		TReal invdet=static_cast<TReal>(1.0)/det;

		aiMatrix3x3t<TReal> res;
		res.a1=invdet  * (b2 * c3-b3 * c2);
		res.a2=-invdet * (a2 * c3-a3 * c2);
		res.a3=invdet  * (a2 * b3-a3 * b2);
		res.b1=-invdet * (b1 * c3-b3 * c1);
		res.b2=invdet  * (a1 * c3-a3 * c1);
		res.b3=-invdet * (a1 * b3-a3 * b1);
		res.c1=invdet  * (b1 * c2-b2 * c1);
		res.c2=-invdet * (a1 * c2-a2 * c1);
		res.c3=invdet  * (a1 * b2-a2 * b1);
		*this=res;

		return *this;
	}
	template <typename TReal>
	void  Matrix3x3t<TReal>::fromMatrix3ToArray(TReal* out) {
		out[0]=a1; out[1]=a2; out[2]=a3; out[3]=0;
		out[4]=b1; out[5]=b2; out[6]=b3; out[7]=0;
		out[8]=c1; out[9]=c2; out[10]=c3; out[11]=0;
		out[12]=0; out[13]=0; out[14]=0; out[15]=1;
	}
#endif
}
#endif