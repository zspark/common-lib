#ifndef QUATERNION_INL_INC
#define QUATERNION_INL_INC

namespace cl {
#ifdef __cplusplus
#include "clQuaternion.h"

#include <cmath>
	// ---------------------------------------------------------------------------
	template<typename TReal>
	bool Quaterniont<TReal>::operator== (const Quaterniont& o) const {
		return x==o.x && y==o.y && z==o.z && w==o.w;
	}

	// ---------------------------------------------------------------------------
	template<typename TReal>
	bool Quaterniont<TReal>::operator!= (const Quaterniont& o) const {
		return !(*this==o);
	}

	// ---------------------------------------------------------------------------
	template<typename TReal>
	inline bool Quaterniont<TReal>::Equal(const Quaterniont& o,TReal epsilon) const {
		return
			std::abs(x-o.x)<=epsilon &&
			std::abs(y-o.y)<=epsilon &&
			std::abs(z-o.z)<=epsilon &&
			std::abs(w-o.w)<=epsilon;
	}

	// ---------------------------------------------------------------------------
	template<typename TReal>
	inline Quaterniont<TReal>::Quaterniont(const Matrix3x3t<TReal> &pRotMatrix) {
		TReal t=pRotMatrix.a1+pRotMatrix.b2+pRotMatrix.c3;

		if(t>static_cast<TReal>(0)) {
			TReal s=std::sqrt(1+t) * static_cast<TReal>(2.0);
			x=(pRotMatrix.c2-pRotMatrix.b3)/s;
			y=(pRotMatrix.a3-pRotMatrix.c1)/s;
			z=(pRotMatrix.b1-pRotMatrix.a2)/s;
			w=static_cast<TReal>(0.25) * s;
		} else if(pRotMatrix.a1>pRotMatrix.b2 && pRotMatrix.a1>pRotMatrix.c3) {
			TReal s=std::sqrt(static_cast<TReal>(1.0)+pRotMatrix.a1-pRotMatrix.b2-pRotMatrix.c3) * static_cast<TReal>(2.0);
			x=static_cast<TReal>(0.25) * s;
			y=(pRotMatrix.b1+pRotMatrix.a2)/s;
			z=(pRotMatrix.a3+pRotMatrix.c1)/s;
			w=(pRotMatrix.c2-pRotMatrix.b3)/s;
		} else if(pRotMatrix.b2>pRotMatrix.c3) {
			TReal s=std::sqrt(static_cast<TReal>(1.0)+pRotMatrix.b2-pRotMatrix.a1-pRotMatrix.c3) * static_cast<TReal>(2.0);
			x=(pRotMatrix.b1+pRotMatrix.a2)/s;
			y=static_cast<TReal>(0.25) * s;
			z=(pRotMatrix.c2+pRotMatrix.b3)/s;
			w=(pRotMatrix.a3-pRotMatrix.c1)/s;
		} else {
			TReal s=std::sqrt(static_cast<TReal>(1.0)+pRotMatrix.c3-pRotMatrix.a1-pRotMatrix.b2) * static_cast<TReal>(2.0);
			x=(pRotMatrix.a3+pRotMatrix.c1)/s;
			y=(pRotMatrix.c2+pRotMatrix.b3)/s;
			z=static_cast<TReal>(0.25) * s;
			w=(pRotMatrix.b1-pRotMatrix.a2)/s;
		}
	}
	// ---------------------------------------------------------------------------
	template<typename TReal>
	inline void Quaterniont<TReal>::computeQuaterniont(const Matrix3x3t<TReal>& pRotMatrix) {
		TReal t=pRotMatrix.a1+pRotMatrix.b2+pRotMatrix.c3;

		if(t>static_cast<TReal>(0)) {
			TReal s=std::sqrt(1+t) * static_cast<TReal>(2.0);
			x=(pRotMatrix.c2-pRotMatrix.b3)/s;
			y=(pRotMatrix.a3-pRotMatrix.c1)/s;
			z=(pRotMatrix.b1-pRotMatrix.a2)/s;
			w=static_cast<TReal>(0.25) * s;
		} else if(pRotMatrix.a1>pRotMatrix.b2 && pRotMatrix.a1>pRotMatrix.c3) {
			TReal s=std::sqrt(static_cast<TReal>(1.0)+pRotMatrix.a1-pRotMatrix.b2-pRotMatrix.c3) * static_cast<TReal>(2.0);
			x=static_cast<TReal>(0.25) * s;
			y=(pRotMatrix.b1+pRotMatrix.a2)/s;
			z=(pRotMatrix.a3+pRotMatrix.c1)/s;
			w=(pRotMatrix.c2-pRotMatrix.b3)/s;
		} else if(pRotMatrix.b2>pRotMatrix.c3) {
			TReal s=std::sqrt(static_cast<TReal>(1.0)+pRotMatrix.b2-pRotMatrix.a1-pRotMatrix.c3) * static_cast<TReal>(2.0);
			x=(pRotMatrix.b1+pRotMatrix.a2)/s;
			y=static_cast<TReal>(0.25) * s;
			z=(pRotMatrix.c2+pRotMatrix.b3)/s;
			w=(pRotMatrix.a3-pRotMatrix.c1)/s;
		} else {
			TReal s=std::sqrt(static_cast<TReal>(1.0)+pRotMatrix.c3-pRotMatrix.a1-pRotMatrix.b2) * static_cast<TReal>(2.0);
			x=(pRotMatrix.a3+pRotMatrix.c1)/s;
			y=(pRotMatrix.c2+pRotMatrix.b3)/s;
			z=static_cast<TReal>(0.25) * s;
			w=(pRotMatrix.b1-pRotMatrix.a2)/s;
		}
	}
	// ---------------------------------------------------------------------------
	template<typename TReal>
	inline void Quaterniont<TReal>::computeQuaterniont(Vector3t<TReal> axis,TReal angle) {
		axis.Normalize();

		const TReal sin_a=std::sin(angle/2);
		const TReal cos_a=std::cos(angle/2);
		x=axis.x * sin_a;
		y=axis.y * sin_a;
		z=axis.z * sin_a;
		w=cos_a;
	}
	// ---------------------------------------------------------------------------
	template<typename TReal>
	inline Quaterniont<TReal>::Quaterniont(TReal fPitch,TReal fYaw,TReal fRoll) {
		const TReal fSinPitch(std::sin(fPitch*static_cast<TReal>(0.5)));
		const TReal fCosPitch(std::cos(fPitch*static_cast<TReal>(0.5)));
		const TReal fSinYaw(std::sin(fYaw*static_cast<TReal>(0.5)));
		const TReal fCosYaw(std::cos(fYaw*static_cast<TReal>(0.5)));
		const TReal fSinRoll(std::sin(fRoll*static_cast<TReal>(0.5)));
		const TReal fCosRoll(std::cos(fRoll*static_cast<TReal>(0.5)));
		const TReal fCosPitchCosYaw(fCosPitch*fCosYaw);
		const TReal fSinPitchSinYaw(fSinPitch*fSinYaw);
		x=fSinRoll * fCosPitchCosYaw-fCosRoll * fSinPitchSinYaw;
		y=fCosRoll * fSinPitch * fCosYaw+fSinRoll * fCosPitch * fSinYaw;
		z=fCosRoll * fCosPitch * fSinYaw-fSinRoll * fSinPitch * fCosYaw;
		w=fCosRoll * fCosPitchCosYaw+fSinRoll * fSinPitchSinYaw;
	}

	// ---------------------------------------------------------------------------
	template<typename TReal>
	inline Matrix3x3t<TReal> Quaterniont<TReal>::GetMatrix() const {
		Matrix3x3t<TReal> resMatrix;
		resMatrix.a1=static_cast<TReal>(1.0)-static_cast<TReal>(2.0) * (y * y+z * z);
		resMatrix.a2=static_cast<TReal>(2.0) * (x * y-z * w);
		resMatrix.a3=static_cast<TReal>(2.0) * (x * z+y * w);
		resMatrix.b1=static_cast<TReal>(2.0) * (x * y+z * w);
		resMatrix.b2=static_cast<TReal>(1.0)-static_cast<TReal>(2.0) * (x * x+z * z);
		resMatrix.b3=static_cast<TReal>(2.0) * (y * z-x * w);
		resMatrix.c1=static_cast<TReal>(2.0) * (x * z-y * w);
		resMatrix.c2=static_cast<TReal>(2.0) * (y * z+x * w);
		resMatrix.c3=static_cast<TReal>(1.0)-static_cast<TReal>(2.0) * (x * x+y * y);

		float L1=std::sqrt(resMatrix.a1 * resMatrix.a1+resMatrix.b1 * resMatrix.b1+resMatrix.c1 * resMatrix.c1);
		float L2=std::sqrt(resMatrix.a2 * resMatrix.a2+resMatrix.b2 * resMatrix.b2+resMatrix.c2 * resMatrix.c2);
		float L3=std::sqrt(resMatrix.a3 * resMatrix.a3+resMatrix.b3 * resMatrix.b3+resMatrix.c3 * resMatrix.c3);

		resMatrix.a1=resMatrix.a1/L1; resMatrix.b1=resMatrix.b1/L1; resMatrix.c1=resMatrix.c1/L1;
		resMatrix.a2=resMatrix.a2/L2; resMatrix.b2=resMatrix.b2/L2; resMatrix.c2=resMatrix.c2/L2;
		resMatrix.a3=resMatrix.a3/L3; resMatrix.b3=resMatrix.b3/L3; resMatrix.c3=resMatrix.c3/L3;
		return resMatrix;
	}

	// ---------------------------------------------------------------------------
	template<typename TReal>
	inline Quaterniont<TReal>::Quaterniont(Vector3t<TReal> axis,TReal angle) {
		axis.Normalize();

		const TReal sin_a=std::sin(angle/2);
		const TReal cos_a=std::cos(angle/2);
		x=axis.x * sin_a;
		y=axis.y * sin_a;
		z=axis.z * sin_a;
		w=cos_a;
	}
	// ---------------------------------------------------------------------------
	template<typename TReal>
	inline Quaterniont<TReal>::Quaterniont(Vector3t<TReal> normalized) {
		x=normalized.x;
		y=normalized.y;
		z=normalized.z;

		const TReal t=static_cast<TReal>(1.0)-(x*x)-(y*y)-(z*z);

		if(t<static_cast<TReal>(0.0)) {
			w=static_cast<TReal>(0.0);
		} else w=std::sqrt(t);
	}

	// ---------------------------------------------------------------------------
	template<typename TReal>
	inline void Quaterniont<TReal>::Interpolate(Quaterniont& pOut,const Quaterniont& pStart,const Quaterniont& pEnd,TReal pFactor) {
		TReal cosom=pStart.x * pEnd.x+pStart.y * pEnd.y+pStart.z * pEnd.z+pStart.w * pEnd.w;

		Quaterniont end=pEnd;
		if(cosom < static_cast<TReal>(0.0)) {
			cosom=-cosom;
			end.x=-end.x;
			end.y=-end.y;
			end.z=-end.z;
			end.w=-end.w;
		}

		TReal sclp,sclq;
		if((static_cast<TReal>(1.0)-cosom) > static_cast<TReal>(0.0001)) {
			TReal omega,sinom;
			omega=std::acos(cosom);
			sinom=std::sin(omega);
			sclp=std::sin((static_cast<TReal>(1.0)-pFactor) * omega)/sinom;
			sclq=std::sin(pFactor * omega)/sinom;
		} else {
			sclp=static_cast<TReal>(1.0)-pFactor;
			sclq=pFactor;
		}

		pOut.x=sclp * pStart.x+sclq * end.x;
		pOut.y=sclp * pStart.y+sclq * end.y;
		pOut.z=sclp * pStart.z+sclq * end.z;
		pOut.w=sclp * pStart.w+sclq * end.w;
	}

	// ---------------------------------------------------------------------------
	template<typename TReal>
	inline Quaterniont<TReal>& Quaterniont<TReal>::Normalize() {
		const TReal mag=std::sqrt(x*x+y*y+z*z+w*w);
		if(mag) {
			const TReal invMag=static_cast<TReal>(1.0)/mag;
			x*=invMag;
			y*=invMag;
			z*=invMag;
			w*=invMag;
		}
		return *this;
	}

	// ---------------------------------------------------------------------------
	template<typename TReal>
	inline Quaterniont<TReal> Quaterniont<TReal>::operator* (const Quaterniont& t) const {
		return Quaterniont(w*t.w-x*t.x-y*t.y-z*t.z,
											 w*t.x+x*t.w+y*t.z-z*t.y,
											 w*t.y+y*t.w+z*t.x-x*t.z,
											 w*t.z+z*t.w+x*t.y-y*t.x);
	}

	// ---------------------------------------------------------------------------
	template<typename TReal>
	inline Quaterniont<TReal>& Quaterniont<TReal>::Conjugate() {
		x=-x;
		y=-y;
		z=-z;
		return *this;
	}

	// ---------------------------------------------------------------------------
	template<typename TReal>
	inline Vector3t<TReal> Quaterniont<TReal>::Rotate(const Vector3t<TReal>& v) {
		Quaterniont q2(0.f,v.x,v.y,v.z),q=*this,qinv=q;
		qinv.Conjugate();

		q=q*q2*qinv;
		return Vector3t<TReal>(q.x,q.y,q.z);
	}
#endif
}
#endif