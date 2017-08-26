#ifndef MATRIX4x4_INL_INC
#define MATRIX4x4_INL_INC

namespace cl {
#include "cldef.h"
#ifdef __cplusplus
#include "clMatrix3.h"
#include "clMatrix4.h"

#include <algorithm>
#include <limits>
#include <cmath>
#include "clVector3.inl"
#include "clVector4.inl"
	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	Matrix4x4t<TReal> ::Matrix4x4t():
		a1(1.0f),a2(),a3(),a4(),
		b1(),b2(1.0f),b3(),b4(),
		c1(),c2(),c3(1.0f),c4(),
		d1(),d2(),d3(),d4(1.0f) {
	}
	template <typename TReal>
	Matrix4x4t<TReal> ::Matrix4x4t(TReal f):
		a1(f),a2(),a3(),a4(),
		b1(),b2(f),b3(),b4(),
		c1(),c2(),c3(f),c4(),
		d1(),d2(),d3(),d4(f) {

	}
	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	Matrix4x4t<TReal> ::Matrix4x4t(TReal _a1,TReal _a2,TReal _a3,TReal _a4,
																 TReal _b1,TReal _b2,TReal _b3,TReal _b4,
																 TReal _c1,TReal _c2,TReal _c3,TReal _c4,
																 TReal _d1,TReal _d2,TReal _d3,TReal _d4):
																 a1(_a1),a2(_a2),a3(_a3),a4(_a4),
																 b1(_b1),b2(_b2),b3(_b3),b4(_b4),
																 c1(_c1),c2(_c2),c3(_c3),c4(_c4),
																 d1(_d1),d2(_d2),d3(_d3),d4(_d4) {

	}

	// ------------------------------------------------------------------------------------------------
	template <typename TReal>
	template <typename TOther>
	Matrix4x4t<TReal>::operator Matrix4x4t<TOther>() const {
		return Matrix4x4t<TOther>(static_cast<TOther>(a1),static_cast<TOther>(a2),static_cast<TOther>(a3),static_cast<TOther>(a4),
															static_cast<TOther>(b1),static_cast<TOther>(b2),static_cast<TOther>(b3),static_cast<TOther>(b4),
															static_cast<TOther>(c1),static_cast<TOther>(c2),static_cast<TOther>(c3),static_cast<TOther>(c4),
															static_cast<TOther>(d1),static_cast<TOther>(d2),static_cast<TOther>(d3),static_cast<TOther>(d4));
	}


	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix4x4t<TReal>::Matrix4x4t(const Matrix3x3t<TReal>& m) {
		a1=m.a1; a2=m.a2; a3=m.a3; a4=static_cast<TReal>(0.0);
		b1=m.b1; b2=m.b2; b3=m.b3; b4=static_cast<TReal>(0.0);
		c1=m.c1; c2=m.c2; c3=m.c3; c4=static_cast<TReal>(0.0);
		d1=static_cast<TReal>(0.0); d2=static_cast<TReal>(0.0); d3=static_cast<TReal>(0.0); d4=static_cast<TReal>(1.0);
	}
	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix4x4t<TReal>::Matrix4x4t(TReal* m) {
		a1=m[0]; a2=m[1]; a3=m[2]; a4=m[3];
		b1=m[4]; b2=m[5]; b3=m[6]; b4=m[7];
		c1=m[8]; c2=m[9]; c3=m[10]; c4=m[11];
		d1=m[12]; d2=m[13]; d3=m[14]; d4=m[15];
	}
	// ----------------------------------------------------------------------------------------

	template <typename TReal>
	inline Matrix4x4t<TReal>::Matrix4x4t(const Vector3t<TReal>& scaling,const  Vector3t<TReal>& euler,const  Vector3t<TReal>& distort,
																			 const Vector3t<TReal>& position) {
		Matrix3x3t<TReal> rotate=Matrix3x3t<TReal>(Matrix4x4t<TReal>().FromEulerAnglesXYZ(euler));

		float z_x=cos(distort.y);
		float z_y=cos(distort.z);
		float z_z=sqrt(1.0f-z_x*z_x-z_y*z_y);
		Vector3D x,y,z;

		x=Vector3D(rotate.a1,rotate.b1,rotate.c1);
		y=Vector3D(rotate.a2,rotate.b2,rotate.c2);
		z=Vector3D(rotate.a3,rotate.b3,rotate.c3);

		Vector3D newy=x*cos(distort.x)+y*sin(distort.x);

		z_x=z_x>0?z_z:-z_z;

		Vector3D newz=z_x*x+z_y*y+z_z*z;

		rotate.a2=newy.x;
		rotate.b2=newy.y;
		rotate.c2=newy.z;

		rotate.a3=newz.x;
		rotate.b3=newz.y;
		rotate.c3=newz.z;

		*this=Matrix4x4t<TReal>(scaling,rotate,position);
	}

	template <typename TReal>
	inline Matrix4x4t<TReal>::Matrix4x4t(const Vector3t<TReal>& scaling,const Matrix3x3t<TReal>& m,const Vector3t<TReal>& position) {
		a1=m.a1 * scaling.x;
		b1=m.b1 * scaling.x;  //缩放*旋转
		c1=m.c1 * scaling.x;
		a4=position.x;

		a2=m.a2 * scaling.y;
		b2=m.b2 * scaling.y;
		c2=m.c2 * scaling.y;
		b4=position.y;

		a3=m.a3 * scaling.z;
		b3=m.b3 * scaling.z;
		c3=m.c3 * scaling.z;
		c4=position.z;

		d1=static_cast<TReal>(0.0);
		d2=static_cast<TReal>(0.0);
		d3=static_cast<TReal>(0.0);
		d4=static_cast<TReal>(1.0);

		//the wrong one
		//a1 = m.a1 * scaling.x;
		//a2 = m.a2 * scaling.x;  //缩放*旋转
		//a3 = m.a3 * scaling.x;
		//a4 = static_cast<TReal>(0.0);

		//b1 = m.b1 * scaling.y;
		//b2 = m.b2 * scaling.y;
		//b3 = m.b3 * scaling.y;
		//b4 = static_cast<TReal>(0.0);

		//c1 = m.c1 * scaling.z;
		//c2 = m.c2 * scaling.z;
		//c3 = m.c3 * scaling.z;
		//c4 = static_cast<TReal>(0.0);

		//d1 = position.x;
		//d2 = position.y;
		//d3 = position.z;
		//d4 = static_cast<TReal>(1.0);

	}
	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	void Matrix4x4t<TReal>::fromMatrixToArray(TReal* m) {
		m[0]=a1; m[1]=a2; m[2]=a3; m[3]=a4;
		m[4]=b1; m[5]=b2; m[6]=b3; m[7]=b4;
		m[8]=c1; m[9]=c2; m[10]=c3; m[11]=c4;
		m[12]=d1; m[13]=d2; m[14]=d3; m[15]=d4;
	}
	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix4x4t<TReal> Matrix4x4t<TReal>::operator - (const Matrix4x4t &m) const {
		Matrix4x4t<TReal> r;
		r.a1=a1-m.a1; r.a2=a2-m.a2; r.a3=a3-m.a3; r.a4=a4-m.a4;
		r.b1=b1-m.b1; r.b2=b2-m.b2; r.b3=b3-m.b3; r.b4=b4-m.b4;
		r.c1=c1-m.c1; r.c2=c2-m.c2; r.c3=c3-m.c3; r.c4=c4-m.c4;
		r.d1=0; r.d2=0; r.d3=0; r.d4=1;
		//r.d1 = d1 - m.d1; r.d2 = d2 - m.d2; r.d3 = d3 - m.d3; r.d4 = d4 - m.d4;
		return r;
	}
	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix4x4t<TReal> Matrix4x4t<TReal>::operator + (const Matrix4x4t &m) const {
		Matrix4x4t<TReal> r;
		r.a1=a1+m.a1; r.a2=a2+m.a2; r.a3=a3+m.a3; r.a4=a4+m.a4;
		r.b1=b1+m.b1; r.b2=b2+m.b2; r.b3=b3+m.b3; r.b4=b4+m.b4;
		r.c1=c1+m.c1; r.c2=c2+m.c2; r.c3=c3+m.c3; r.c4=c4+m.c4;
		r.d1=0; r.d2=0; r.d3=0; r.d4=1;
		//r.d1 = d1 + m.d1; r.d2 = d2 + m.d2; r.d3 = d3 + m.d3; r.d4 = d4 + m.d4;
		return r;
	}


	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix4x4t<TReal>& Matrix4x4t<TReal>::operator *= (const Matrix4x4t<TReal>& m) {
		*this=Matrix4x4t<TReal>(
			m.a1 * a1+m.b1 * a2+m.c1 * a3+m.d1 * a4,
			m.a2 * a1+m.b2 * a2+m.c2 * a3+m.d2 * a4,
			m.a3 * a1+m.b3 * a2+m.c3 * a3+m.d3 * a4,
			m.a4 * a1+m.b4 * a2+m.c4 * a3+m.d4 * a4,
			m.a1 * b1+m.b1 * b2+m.c1 * b3+m.d1 * b4,
			m.a2 * b1+m.b2 * b2+m.c2 * b3+m.d2 * b4,
			m.a3 * b1+m.b3 * b2+m.c3 * b3+m.d3 * b4,
			m.a4 * b1+m.b4 * b2+m.c4 * b3+m.d4 * b4,
			m.a1 * c1+m.b1 * c2+m.c1 * c3+m.d1 * c4,
			m.a2 * c1+m.b2 * c2+m.c2 * c3+m.d2 * c4,
			m.a3 * c1+m.b3 * c2+m.c3 * c3+m.d3 * c4,
			m.a4 * c1+m.b4 * c2+m.c4 * c3+m.d4 * c4,
			m.a1 * d1+m.b1 * d2+m.c1 * d3+m.d1 * d4,
			m.a2 * d1+m.b2 * d2+m.c2 * d3+m.d2 * d4,
			m.a3 * d1+m.b3 * d2+m.c3 * d3+m.d3 * d4,
			m.a4 * d1+m.b4 * d2+m.c4 * d3+m.d4 * d4);
		return *this;
	}
	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix4x4t<TReal> Matrix4x4t<TReal>::operator* (const Matrix4x4t<TReal>& m) const {
		Matrix4x4t<TReal> temp(*this);
		temp*=m;
		return temp;
	}

	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix4x4t<TReal>& Matrix4x4t<TReal>::Transpose() {
		std::swap((TReal&)b1,(TReal&)a2);
		std::swap((TReal&)c1,(TReal&)a3);
		std::swap((TReal&)c2,(TReal&)b3);
		std::swap((TReal&)d1,(TReal&)a4);
		std::swap((TReal&)d2,(TReal&)b4);
		std::swap((TReal&)d3,(TReal&)c4);
		return *this;
	}

	template <typename TReal>
	inline Matrix4x4t<TReal>& Matrix4x4t<TReal>::Transpose3x3() {
		std::swap((TReal&)b1,(TReal&)a2);
		std::swap((TReal&)c1,(TReal&)a3);
		std::swap((TReal&)c2,(TReal&)b3);
		return *this;
	}

	template <typename TReal>
	inline Matrix4x4t<TReal>& Matrix4x4t<TReal>::Transpose4() {
		std::swap((TReal&)d1,(TReal&)a4);
		std::swap((TReal&)d2,(TReal&)b4);
		std::swap((TReal&)d3,(TReal&)c4);
		return *this;
	}

	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline TReal Matrix4x4t<TReal>::Determinant() const {
		return a1*b2*c3*d4-a1*b2*c4*d3+a1*b3*c4*d2-a1*b3*c2*d4
			+a1*b4*c2*d3-a1*b4*c3*d2-a2*b3*c4*d1+a2*b3*c1*d4
			-a2*b4*c1*d3+a2*b4*c3*d1-a2*b1*c3*d4+a2*b1*c4*d3
			+a3*b4*c1*d2-a3*b4*c2*d1+a3*b1*c2*d4-a3*b1*c4*d2
			+a3*b2*c4*d1-a3*b2*c1*d4-a4*b1*c2*d3+a4*b1*c3*d2
			-a4*b2*c3*d1+a4*b2*c1*d3-a4*b3*c1*d2+a4*b3*c2*d1;
	}

	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix4x4t<TReal>& Matrix4x4t<TReal>::Inverse() {
		const TReal det=Determinant();
		if(det==static_cast<TReal>(0.0)) {
			const TReal nan=std::numeric_limits<TReal>::quiet_NaN();
			*this=Matrix4x4t<TReal>(
				nan,nan,nan,nan,
				nan,nan,nan,nan,
				nan,nan,nan,nan,
				nan,nan,nan,nan);

			return *this;
		}

		const TReal invdet=static_cast<TReal>(1.0)/det;

		Matrix4x4t<TReal> res;
		res.a1=invdet  * (b2 * (c3 * d4-c4 * d3)+b3 * (c4 * d2-c2 * d4)+b4 * (c2 * d3-c3 * d2));
		res.a2=-invdet * (a2 * (c3 * d4-c4 * d3)+a3 * (c4 * d2-c2 * d4)+a4 * (c2 * d3-c3 * d2));
		res.a3=invdet  * (a2 * (b3 * d4-b4 * d3)+a3 * (b4 * d2-b2 * d4)+a4 * (b2 * d3-b3 * d2));
		res.a4=-invdet * (a2 * (b3 * c4-b4 * c3)+a3 * (b4 * c2-b2 * c4)+a4 * (b2 * c3-b3 * c2));
		res.b1=-invdet * (b1 * (c3 * d4-c4 * d3)+b3 * (c4 * d1-c1 * d4)+b4 * (c1 * d3-c3 * d1));
		res.b2=invdet  * (a1 * (c3 * d4-c4 * d3)+a3 * (c4 * d1-c1 * d4)+a4 * (c1 * d3-c3 * d1));
		res.b3=-invdet * (a1 * (b3 * d4-b4 * d3)+a3 * (b4 * d1-b1 * d4)+a4 * (b1 * d3-b3 * d1));
		res.b4=invdet  * (a1 * (b3 * c4-b4 * c3)+a3 * (b4 * c1-b1 * c4)+a4 * (b1 * c3-b3 * c1));
		res.c1=invdet  * (b1 * (c2 * d4-c4 * d2)+b2 * (c4 * d1-c1 * d4)+b4 * (c1 * d2-c2 * d1));
		res.c2=-invdet * (a1 * (c2 * d4-c4 * d2)+a2 * (c4 * d1-c1 * d4)+a4 * (c1 * d2-c2 * d1));
		res.c3=invdet  * (a1 * (b2 * d4-b4 * d2)+a2 * (b4 * d1-b1 * d4)+a4 * (b1 * d2-b2 * d1));
		res.c4=-invdet * (a1 * (b2 * c4-b4 * c2)+a2 * (b4 * c1-b1 * c4)+a4 * (b1 * c2-b2 * c1));
		res.d1=-invdet * (b1 * (c2 * d3-c3 * d2)+b2 * (c3 * d1-c1 * d3)+b3 * (c1 * d2-c2 * d1));
		res.d2=invdet  * (a1 * (c2 * d3-c3 * d2)+a2 * (c3 * d1-c1 * d3)+a3 * (c1 * d2-c2 * d1));
		res.d3=-invdet * (a1 * (b2 * d3-b3 * d2)+a2 * (b3 * d1-b1 * d3)+a3 * (b1 * d2-b2 * d1));
		res.d4=invdet  * (a1 * (b2 * c3-b3 * c2)+a2 * (b3 * c1-b1 * c3)+a3 * (b1 * c2-b2 * c1));
		*this=res;

		return *this;
	}
	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline TReal* Matrix4x4t<TReal>::operator[](unsigned int p_iIndex) {
		return &this->a1+p_iIndex*4;
	}
	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline const TReal* Matrix4x4t<TReal>::operator[](unsigned int p_iIndex) const {
		return &this->a1+p_iIndex*4;
	}

	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline bool Matrix4x4t<TReal>::operator== (const Matrix4x4t<TReal>& m) const {
		return (a1==m.a1 && a2==m.a2 && a3==m.a3 && a4==m.a4 &&
						b1==m.b1 && b2==m.b2 && b3==m.b3 && b4==m.b4 &&
						c1==m.c1 && c2==m.c2 && c3==m.c3 && c4==m.c4 &&
						d1==m.d1 && d2==m.d2 && d3==m.d3 && d4==m.d4);
	}
	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline bool Matrix4x4t<TReal>::operator!= (const Matrix4x4t<TReal>& m) const {
		return !(*this==m);
	}

	// ---------------------------------------------------------------------------
	template<typename TReal>
	inline bool Matrix4x4t<TReal>::Equal(const Matrix4x4t<TReal>& m,TReal epsilon) const {
		return
			std::abs(a1-m.a1)<=epsilon &&
			std::abs(a2-m.a2)<=epsilon &&
			std::abs(a3-m.a3)<=epsilon &&
			std::abs(a4-m.a4)<=epsilon &&
			std::abs(b1-m.b1)<=epsilon &&
			std::abs(b2-m.b2)<=epsilon &&
			std::abs(b3-m.b3)<=epsilon &&
			std::abs(b4-m.b4)<=epsilon &&
			std::abs(c1-m.c1)<=epsilon &&
			std::abs(c2-m.c2)<=epsilon &&
			std::abs(c3-m.c3)<=epsilon &&
			std::abs(c4-m.c4)<=epsilon &&
			std::abs(d1-m.d1)<=epsilon &&
			std::abs(d2-m.d2)<=epsilon &&
			std::abs(d3-m.d3)<=epsilon &&
			std::abs(d4-m.d4)<=epsilon;
	}

	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix4x4t<TReal>& Matrix4x4t<TReal>::FromEulerAnglesXYZ(const Vector3t<TReal>& blubb) {
		return FromEulerAnglesXYZ(blubb.x,blubb.y,blubb.z);
	}

	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix4x4t<TReal>& Matrix4x4t<TReal>::FromEulerAnglesXYZ(TReal x,TReal y,TReal z) {
		Matrix4x4t<TReal>& _this=*this;
		x=AngleToRad(x);
		y=AngleToRad(y);
		z=AngleToRad(z);

		TReal cr=std::cos(x);

		TReal sr=std::sin(x);
		TReal cp=std::cos(y);
		TReal sp=std::sin(y);
		TReal cy=std::cos(z);
		TReal sy=std::sin(z);

		_this.a1=cp*cy;
		_this.a2=cp*sy;
		_this.a3=-sp;

		TReal srsp=sr*sp;
		TReal crsp=cr*sp;

		_this.b1=srsp*cy-cr*sy;
		_this.b2=srsp*sy+cr*cy;
		_this.b3=sr*cp;

		_this.c1=crsp*cy+sr*sy;
		_this.c2=crsp*sy-sr*cy;
		_this.c3=cr*cp;

		return *this;
	}

	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix4x4t<TReal>& Matrix4x4t<TReal>::RotationX(TReal a,Matrix4x4t<TReal>& out) {
		/*
			|  1  0       0       0 |
			M = |  0  cos(A) -sin(A)  0 |
			|  0  sin(A)  cos(A)  0 |
			|  0  0       0       1 |
			*/
		a=AngleToRad(a);
		out=Matrix4x4t<TReal>();
		out.b2=out.c3=std::cos(a);
		out.b3=-(out.c2=std::sin(a));
		return out;
	}

	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix4x4t<TReal>& Matrix4x4t<TReal>::RotationY(TReal a,Matrix4x4t<TReal>& out) {
		/*
			|  cos(A)  0   sin(A)  0 |
			M = |  0       1   0       0 |
			| -sin(A)  0   cos(A)  0 |
			|  0       0   0       1 |
			*/
		a=AngleToRad(a);
		out=Matrix4x4t<TReal>();
		out.a1=out.c3=std::cos(a);
		out.c1=-(out.a3=std::sin(a));
		return out;
	}

	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix4x4t<TReal>& Matrix4x4t<TReal>::RotationZ(TReal a,Matrix4x4t<TReal>& out) {
		/*
			|  cos(A)  -sin(A)   0   0 |
			M = |  sin(A)   cos(A)   0   0 |
			|  0        0        1   0 |
			|  0        0        0   1 |
			*/
		a=AngleToRad(a);
		out=Matrix4x4t<TReal>();
		out.a1=out.b2=std::cos(a);
		out.a2=-(out.b1=std::sin(a));
		return out;
	}

	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix4x4t<TReal>& Matrix4x4t<TReal>::Rotation(TReal a,Vector3t<TReal>& axis,Matrix4x4t<TReal>& out) {
		axis.Normalize();
		a=AngleToRad(a);
		TReal c=std::cos(a),s=std::sin(a),t=1-c;
		TReal x=axis.x,y=axis.y,z=axis.z;

		out.a1=t*x*x+c;   out.a2=t*x*y-s*z; out.a3=t*x*z+s*y;
		out.b1=t*x*y+s*z; out.b2=t*y*y+c;   out.b3=t*y*z-s*x;
		out.c1=t*x*z-s*y; out.c2=t*y*z+s*x; out.c3=t*z*z+c;
		out.a4=out.b4=out.c4=static_cast<TReal>(0.0);
		out.d1=out.d2=out.d3=static_cast<TReal>(0.0);
		out.d4=static_cast<TReal>(1.0);

		float L1=std::sqrt(out.a1 * out.a1+out.b1 * out.b1+out.c1 * out.c1);
		float L2=std::sqrt(out.a2 * out.a2+out.b2 * out.b2+out.c2 * out.c2);
		float L3=std::sqrt(out.a3 * out.a3+out.b3 * out.b3+out.c3 * out.c3);


		out.a1=out.a1/L1; out.b1=out.b1/L1; out.c1=out.c1/L1;
		out.a2=out.a2/L2; out.b2=out.b2/L2; out.c2=out.c2/L2;
		out.a3=out.a3/L3; out.b3=out.b3/L3; out.c3=out.c3/L3;
		return out;
	}
	// ----------------------------------------------------------------------------------------
	//template <typename TReal>
	//static Matrix4x4t<TReal> Matrix4x4t<TReal>::GetProjectionMatrix(TReal fov, TReal aspect, TReal zn, TReal zf){
	//	for (int i = 0; i < 16; i++)
	//	{
	//		pPro[i] = 0.0f;
	//	}
	//
	//}


	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix4x4t<TReal>& Matrix4x4t<TReal>::Translation(const Vector3t<TReal>& v,Matrix4x4t<TReal>& out) {
		out.a4=v.x;
		out.b4=v.y;
		out.c4=v.z;

		//the wrong one
		//out.d1 = v.x;
		//out.d2 = v.y;
		//out.d3 = v.z;
		return out;
	}

	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix4x4t<TReal>& Matrix4x4t<TReal>::Scaling(const Vector3t<TReal>& v,Matrix4x4t<TReal>& out) {
		Vector3D pSalaing;
		Vector3D pPos;
		Matrix3x3 pRotation;
		out.Decompose(pSalaing,pRotation,pPos);
		pSalaing.x=v.x;
		pSalaing.y=v.y;
		pSalaing.z=v.z;

		Matrix4x4D temp(pSalaing,pRotation,pPos);
		out=temp;
		return out;
	}
	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline bool Matrix4x4t<TReal>::ToEulerAnglesXYZ(TReal& rfYAngle,TReal& rfPAngle,
																									TReal& rfRAngle) {
		// rot =  cy*cz          -cy*sz           sy
		//        cz*sx*sy+cx*sz  cx*cz-sx*sy*sz -cy*sx
		//       -cx*cz*sy+sx*sz  cz*sx+cx*sy*sz  cx*cy

		rfPAngle=asin(-a3);
		if(rfPAngle < kPi/2) {
			if(rfPAngle > -kPi/2) {
				rfYAngle=atan2(b3,c3);
				rfRAngle=atan2(a2,a1);
				rfYAngle=RadToAngle(rfYAngle);
				rfPAngle=RadToAngle(rfPAngle);
				rfRAngle=RadToAngle(rfRAngle);
				return true;
			} else {
				// WARNING.  Not a unique solution.
				TReal fRmY=atan2(b1,b2);
				rfRAngle=0.0;  // any angle works
				rfYAngle=rfRAngle-fRmY;
				rfYAngle=RadToAngle(rfYAngle);
				rfPAngle=RadToAngle(rfPAngle);
				rfRAngle=RadToAngle(rfRAngle);
				return false;
			}
		} else {
			// WARNING.  Not a unique solution.
			TReal fRpY=atan2(b1,b2);
			rfRAngle=0.0;  // any angle works
			rfYAngle=fRpY-rfRAngle;
			rfYAngle=RadToAngle(rfYAngle);
			rfPAngle=RadToAngle(rfPAngle);
			rfRAngle=RadToAngle(rfRAngle);
			return false;
		}
	}
	// ----------------------------------------------------------------------------------------

	template <typename TReal>
	inline void Matrix4x4t<TReal>::Decompose(Vector3t<TReal>& scaling,Vector3t<TReal>& euler,Vector3t<TReal>& distort,
																					 Vector3t<TReal>& position) const {
		Matrix3x3t<TReal> rotate;
		Decompose(scaling,rotate,position);
		Vector3t<TReal> x(rotate.a1,rotate.b1,rotate.c1);
		Vector3t<TReal> y(rotate.a2,rotate.b2,rotate.c2);
		Vector3t<TReal> z(rotate.a3,rotate.b3,rotate.c3);

		x.Normalize();
		y.Normalize();
		z.Normalize();
		Vector3t<TReal> newx=x;
		Vector3t<TReal> newz=(x^y).Normalize();
		Vector3t<TReal> newy=(z^x).Normalize();



		distort.x=newx.dotProduct(y);
		distort.y=newx.dotProduct(z);
		distort.z=newy.dotProduct(z);

		distort.x=acos(distort.x);
		if(newz.dotProduct(z)>0.0f) {
			distort.y=acos(distort.y);
			distort.z=acos(distort.z);
		} else if(newz.dotProduct(z)<0.0f) {
			distort.y=-acos(distort.y);
			distort.z=-acos(distort.z);
		} else {
			return;
		}

		Matrix3x3t<TReal> rotateMat;
		rotateMat.a1=newx.x;
		rotateMat.b1=newx.y;
		rotateMat.c1=newx.z;

		rotateMat.a2=newy.x;
		rotateMat.b2=newy.y;
		rotateMat.c2=newy.z;

		rotateMat.a3=newz.x;
		rotateMat.b3=newz.y;
		rotateMat.c3=newz.z;

		Matrix4x4t<TReal>(rotateMat).ToEulerAnglesXYZ(euler.x,euler.y,euler.z);
	}
	template <typename TReal>
	inline void Matrix4x4t<TReal>::Decompose(Vector3t<TReal>& scaling,Matrix3x3t<TReal>& rotation,
																					 Vector3t<TReal>& position) const {
		const Matrix4x4t<TReal>& _this=*this;

		// extract translation
		position.x=_this[0][3];
		position.y=_this[1][3];
		position.z=_this[2][3];

		//the wrong one
		//position.x = _this[3][0];
		//position.y = _this[3][1];
		//position.z = _this[3][2];

		// extract the rows of the matrix
		Vector3t<TReal> vRows[3]={
			Vector3t<TReal>(_this[0][0],_this[1][0],_this[2][0]),
			Vector3t<TReal>(_this[0][1],_this[1][1],_this[2][1]),
			Vector3t<TReal>(_this[0][2],_this[1][2],_this[2][2])
		};

		//the wrong one
		//Vector3t<TReal> vRows[3] = {
		//	Vector3t<TReal>(_this[0][0], _this[0][1], _this[0][2]),
		//	Vector3t<TReal>(_this[1][0], _this[1][1], _this[1][2]),
		//	Vector3t<TReal>(_this[2][0], _this[2][1], _this[2][2])
		//};

		// extract the scaling factors
		scaling.x=vRows[0].Length();
		scaling.y=vRows[1].Length();
		scaling.z=vRows[2].Length();

		// and the sign of the scaling
		//if (_this.Determinant() < 0) {
		//	scaling.x = -scaling.x;
		//	scaling.y = -scaling.y;
		//	scaling.z = -scaling.z;
		//}

		// and remove all scaling from the matrix
		if(scaling.x) {
			vRows[0]/=scaling.x;
		}
		if(scaling.y) {
			vRows[1]/=scaling.y;
		}
		if(scaling.z) {
			vRows[2]/=scaling.z;
		}

		// build a 3x3 rotation matrix
		Matrix3x3t<TReal> m(vRows[0].x,vRows[1].x,vRows[2].x,
												vRows[0].y,vRows[1].y,vRows[2].y,
												vRows[0].z,vRows[1].z,vRows[2].z);


		//the wrong one
		//Matrix3x3t<TReal> m(vRows[0].x, vRows[0].y, vRows[0].z,
		//	vRows[1].x, vRows[1].y, vRows[1].z,
		//	vRows[2].x, vRows[2].y, vRows[2].z);

		// and generate the rotation quaternion from it
		rotation=m;
	}

	// ----------------------------------------------------------------------------------------
	//decompose the scale by x,y,z(Xx, Yx, Zx as one row), not the x axes, y axes, z axes
	template <typename TReal>
	inline void Matrix4x4t<TReal>::DecomposeByXYZ(Vector3t<TReal>& scaling,Matrix3x3t<TReal>& rotation,
																								Vector3t<TReal>& position) const {
		const Matrix4x4t<TReal>& _this=*this;

		// extract translation
		position.x=_this[0][3];
		position.y=_this[1][3];
		position.z=_this[2][3];

		//the wrong one
		//position.x = _this[3][0];
		//position.y = _this[3][1];
		//position.z = _this[3][2];

		// extract the rows of the matrix
		//Vector3t<TReal> vRows[3] = {
		//	Vector3t<TReal>(_this[0][0], _this[1][0], _this[2][0]),
		//	Vector3t<TReal>(_this[0][1], _this[1][1], _this[2][1]),
		//	Vector3t<TReal>(_this[0][2], _this[1][2], _this[2][2])
		//};

		//the wrong one
		Vector3t<TReal> vRows[3]={
			Vector3t<TReal>(_this[0][0],_this[0][1],_this[0][2]),
			Vector3t<TReal>(_this[1][0],_this[1][1],_this[1][2]),
			Vector3t<TReal>(_this[2][0],_this[2][1],_this[2][2])
		};

		// extract the scaling factors
		scaling.x=vRows[0].Length();
		scaling.y=vRows[1].Length();
		scaling.z=vRows[2].Length();

		// and the sign of the scaling
		if(_this.Determinant()<0) {
			scaling.x=-scaling.x;
			scaling.y=-scaling.y;
			scaling.z=-scaling.z;
		}

		// and remove all scaling from the matrix
		if(scaling.x) {
			vRows[0]/=scaling.x;
		}
		if(scaling.y) {
			vRows[1]/=scaling.y;
		}
		if(scaling.z) {
			vRows[2]/=scaling.z;
		}

		// build a 3x3 rotation matrix
		//Matrix3x3t<TReal> m(vRows[0].x, vRows[1].x, vRows[2].x,
		//	vRows[0].y, vRows[1].y, vRows[2].y,
		//	vRows[0].z, vRows[1].z, vRows[2].z);


		//the wrong one
		Matrix3x3t<TReal> m(vRows[0].x,vRows[0].y,vRows[0].z,
												vRows[1].x,vRows[1].y,vRows[1].z,
												vRows[2].x,vRows[2].y,vRows[2].z);

		// and generate the rotation quaternion from it
		rotation=m;
	}

	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline void Matrix4x4t<TReal>::ComposeByXYZ(const Vector3t<TReal>& scaling,
																							const Matrix3x3t<TReal>& m,const Vector3t<TReal>& position) {
		Matrix4x4t<TReal>& _this=*this;

		_this.a1=m.a1 * scaling.x;
		_this.b1=m.b1 * scaling.y;  //缩放*旋转
		_this.c1=m.c1 * scaling.z;
		_this.a4=position.x;

		_this.a2=m.a2 * scaling.x;
		_this.b2=m.b2 * scaling.y;
		_this.c2=m.c2 * scaling.z;
		_this.b4=position.y;

		_this.a3=m.a3 * scaling.x;
		_this.b3=m.b3 * scaling.y;
		_this.c3=m.c3 * scaling.z;
		_this.c4=position.z;

		_this.d1=static_cast<TReal>(0.0);
		_this.d2=static_cast<TReal>(0.0);
		_this.d3=static_cast<TReal>(0.0);
		_this.d4=static_cast<TReal>(1.0);

		//the wrong one
		//a1 = m.a1 * scaling.x;
		//a2 = m.a2 * scaling.x;  //缩放*旋转
		//a3 = m.a3 * scaling.x;
		//a4 = static_cast<TReal>(0.0);

		//b1 = m.b1 * scaling.y;
		//b2 = m.b2 * scaling.y;
		//b3 = m.b3 * scaling.y;
		//b4 = static_cast<TReal>(0.0);

		//c1 = m.c1 * scaling.z;
		//c2 = m.c2 * scaling.z;
		//c3 = m.c3 * scaling.z;
		//c4 = static_cast<TReal>(0.0);

		//d1 = position.x;
		//d2 = position.y;
		//d3 = position.z;
		//d4 = static_cast<TReal>(1.0);

	}
	template <typename TReal>
	inline void Matrix4x4t<TReal>::BuildByXYZPos(const Vector3t<TReal>& x,const Vector3t<TReal>& y,
																							 const Vector3t<TReal>& z,const Vector3t<TReal>& position) {
		a1=x.x;
		b1=x.y;
		c1=x.z;
		d1=0.f;

		a2=y.x;
		b2=y.y;
		c2=y.z;
		d2=0.f;

		a3=z.x;
		b3=z.y;
		c3=z.z;
		d3=0.f;

		a4=position.x;
		b4=position.y;
		c4=position.z;
		d4=1.f;
	}
	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline void Matrix4x4t<TReal>::ToAxisAngle(TReal& x,TReal& y,TReal& z,TReal& rfRadians) {
		TReal fTrace=a1+b2+c3;
		TReal fCos=0.5f*(fTrace-1.0f);
		rfRadians=acos(fCos);  // in [0,PI]

		if(rfRadians>0) {
			if(rfRadians<kPi) {
				x=c2-b3;
				y=a3-c1;
				z=b1-a2;

				Vector3D vector(x,y,z);
				vector=vector.Normalize();
				x=vector.x;
				y=vector.y;
				z=vector.z;
			} else {
				// angle is PI
				float fHalfInverse;
				if(a1>=b2) {
					// r00 >= r11
					if(a1>=c3) {
						// r00 is maximum diagonal term
						x=0.5f*std::sqrt(a1-
														 b2-c3+1.0f);
						fHalfInverse=0.5f/x;
						y=fHalfInverse*a2;
						z=fHalfInverse*a3;
					} else {
						// r22 is maximum diagonal term
						z=0.5f*std::sqrt(c3-
														 a1-b2+1.0f);
						fHalfInverse=0.5f/z;
						x=fHalfInverse*a3;
						y=fHalfInverse*b3;
					}
				} else {
					// r11 > r00
					if(b2>=c3) {
						// r11 is maximum diagonal term
						y=0.5f*std::sqrt(b2-
														 a1-c3+1.0f);
						fHalfInverse=0.5f/y;
						x=fHalfInverse*a2;
						z=fHalfInverse*b3;
					} else {
						// r22 is maximum diagonal term
						z=0.5f*std::sqrt(c3-
														 a1-b2+1.0f);
						fHalfInverse=0.5f/z;
						x=fHalfInverse*a3;
						y=fHalfInverse*b3;
					}
				}
			}
		} else {
			// The angle is 0 and the matrix is the identity.  Any axis will
			// work, so just use the x-axis.
			x=1.0;
			y=0.0;
			z=0.0;
		}
		rfRadians=RadToAngle(rfRadians);
	}
	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	AI_FORCE_INLINE Vector4t<TReal> operator * (const Matrix4x4t<TReal>& mat,const Vector4t<TReal>& v) {
		return Vector4t<TReal>(
			mat.a1 * v.x+mat.a2 * v.y+mat.a3 * v.z+mat.a4 * v.w,
			mat.b1 * v.x+mat.b2 * v.y+mat.b3 * v.z+mat.b4 * v.w,
			mat.c1 * v.x+mat.c2 * v.y+mat.c3 * v.z+mat.c4 * v.w,
			mat.d1 * v.x+mat.d2 * v.y+mat.d3 * v.z+mat.d4 * v.w
			);
	}
	// ----------------------------------------------------------------------------------------
	template <typename TReal>
	inline Matrix4x4t<TReal> Matrix4x4t<TReal>::toMatrix4D(Matrix3x3t<TReal>& m) {
		Matrix4x4t<TReal> out;
		out.a1=m.a1; out.a2=m.a2; out.a3=m.a3; out.a4=static_cast<TReal>(0.0);
		out.b1=m.b1; out.b2=m.b2; out.b3=m.b3; out.b4=static_cast<TReal>(0.0);
		out.c1=m.c1; out.c2=m.c2; out.c3=m.c3; out.c4=static_cast<TReal>(0.0);
		out.d1=static_cast<TReal>(0.0); out.d2=static_cast<TReal>(0.0); out.d3=static_cast<TReal>(0.0); out.d4=static_cast<TReal>(1.0);
		return out;
	}

	//计算视图矩阵
	inline	void calcViewMat(double eyex,double eyey,double eyez,
													 double centerx,double centery,double centerz,
													 double upx,double upy,double upz,float* m) {
		float x[3],y[3],z[3],mag;

		// Difference eye and center vectors to make Z vector. 
		z[0]=eyex-centerx;
		z[1]=eyey-centery;
		z[2]=eyez-centerz;
		// Normalize Z. 
		mag=sqrt(z[0]*z[0]+z[1]*z[1]+z[2]*z[2]);
		if(mag) {
			z[0]/=mag;
			z[1]/=mag;
			z[2]/=mag;
		}

		// Up vector makes Y vector. 
		y[0]=upx;
		y[1]=upy;
		y[2]=upz;

		// X vector = Y cross Z. 
		x[0]=y[1]*z[2]-y[2]*z[1];
		x[1]=-y[0]*z[2]+y[2]*z[0];
		x[2]=y[0]*z[1]-y[1]*z[0];

		// Recompute Y = Z cross X. 
		y[0]=z[1]*x[2]-z[2]*x[1];
		y[1]=-z[0]*x[2]+z[2]*x[0];
		y[2]=z[0]*x[1]-z[1]*x[0];

		// Normalize X. 
		mag=sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);
		if(mag) {
			x[0]/=mag;
			x[1]/=mag;
			x[2]/=mag;
		}

		// Normalize Y. 
		mag=sqrt(y[0]*y[0]+y[1]*y[1]+y[2]*y[2]);
		if(mag) {
			y[0]/=mag;
			y[1]/=mag;
			y[2]/=mag;
		}

		// Build resulting view matrix. 
		m[0*4+0]=x[0];  m[0*4+1]=x[1];
		m[0*4+2]=x[2];  m[0*4+3]=-x[0]*eyex+-x[1]*eyey+-x[2]*eyez;

		m[1*4+0]=y[0];  m[1*4+1]=y[1];
		m[1*4+2]=y[2];  m[1*4+3]=-y[0]*eyex+-y[1]*eyey+-y[2]*eyez;

		m[2*4+0]=z[0];  m[2*4+1]=z[1];
		m[2*4+2]=z[2];  m[2*4+3]=-z[0]*eyex+-z[1]*eyey+-z[2]*eyez;

		m[3*4+0]=0.0;   m[3*4+1]=0.0;  m[3*4+2]=0.0;  m[3*4+3]=1.0;
	}

	//计算投影矩阵
	inline  void calcProMat(float m_FOV,float m_Aspect,float m_Near,float m_Far,float* pPro) {
		for(int i=0; i<16; i++) {
			pPro[i]=0.f;
		}
		const double D2R=clPi/180.0;
		pPro[5]=1/tan(D2R * m_FOV/2);
		pPro[0]=pPro[5]/m_Aspect;
		pPro[10]=(m_Near+m_Far)/(m_Near-m_Far);
		pPro[11]=2*(m_Near * m_Far)/(m_Near-m_Far);
		pPro[14]=-1.0;
	}

	inline	bool PickMesh(int iMouseX,int iMouseY,const int* pViewPort,const float* pPro,const float* pView,
												Vector3D& nearClip,Vector3D& farClip) {
		int wx,wy,wz;
		Matrix4x4D mPro,mView;
		Vector4D Vertex,vTemp;

		//set matrix
		memcpy(mPro[0],pPro,sizeof(float)*16);
		memcpy(mView[0],pView,sizeof(float)*16);

		//set near ray
		//gluUnProject function
		wx=iMouseX;
		wy=pViewPort[3]-iMouseY;
		wz=0;
		Vertex={(wx-(float)pViewPort[0])/(float)pViewPort[2]*2.0f-1.0f,(wy-(float)pViewPort[1])/(float)pViewPort[3]*2.0f-1.0f,2*wz-1.0f,1};
		vTemp=(mPro * mView).Inverse() * Vertex;
		vTemp[0]/=vTemp[3];
		vTemp[1]/=vTemp[3];
		vTemp[2]/=vTemp[3];

		nearClip={vTemp[0],vTemp[1],vTemp[2]};
		//cout << vTemp << endl;


		//set far ray
		//gluUnProject function
		wx=iMouseX;
		wy=pViewPort[3]-iMouseY;
		wz=1;
		Vertex={(wx-(float)pViewPort[0])/(float)pViewPort[2]*2.0f-1.0f,(wy-(float)pViewPort[1])/(float)pViewPort[3]*2.0f-1.0f,2*wz-1.0f,1};
		vTemp=(mPro * mView).Inverse() * Vertex;
		//vTemp = (mPro * mView).inverse() * Vertex;

		vTemp[0]/=vTemp[3];
		vTemp[1]/=vTemp[3];
		vTemp[2]/=vTemp[3];

		farClip={vTemp[0],vTemp[1],vTemp[2]};

		return true;
	}
#endif
}
#endif