#ifndef __Matrix4_H__
#define __Matrix4_H__

namespace cl {
#include "clVector3.h"
#include "clVector4.h"
#include "cldef.h"
#ifdef __cplusplus

	template<typename TReal> class Matrix3x3t;
	//template<typename TReal> class aiQuaterniont;

	template<typename TReal>
	class Matrix4x4t {
	public:


		Matrix4x4t();
		Matrix4x4t(TReal f);
		Matrix4x4t(
			TReal _a1,TReal _a2,TReal _a3,TReal _a4,
			TReal _b1,TReal _b2,TReal _b3,TReal _b4,
			TReal _c1,TReal _c2,TReal _c3,TReal _c4,
			TReal _d1,TReal _d2,TReal _d3,TReal _d4
			);


		explicit Matrix4x4t(TReal* m);

		explicit Matrix4x4t(const Matrix3x3t<TReal>& m);

		Matrix4x4t(const Vector3t<TReal>& scaling,const Matrix3x3t<TReal>& rotation,
							 const Vector3t<TReal>& position);
		Matrix4x4t(const Vector3t<TReal>& scaling,const  Vector3t<TReal>& euler,const  Vector3t<TReal>& distort,
							 const Vector3t<TReal>& position);

	public:

		TReal* operator[]       (unsigned int p_iIndex);
		const TReal* operator[] (unsigned int p_iIndex) const;

		bool operator== (const Matrix4x4t& m) const;
		bool operator!= (const Matrix4x4t& m) const;

		bool Equal(const Matrix4x4t& m,TReal epsilon=1e-6) const;

		Matrix4x4t& operator *= (const Matrix4x4t& m);
		Matrix4x4t  operator *  (const Matrix4x4t& m) const;
		Matrix4x4t operator + (const Matrix4x4t &m2) const;
		Matrix4x4t operator - (const Matrix4x4t &m2) const;


		template <typename TOther>
		operator Matrix4x4t<TOther>() const;

		void fromMatrixToArray(TReal* m);

	public:

		Matrix4x4t& Transpose();
		Matrix4x4t& Transpose3x3();
		Matrix4x4t& Transpose4();

		Matrix4x4t& Inverse();
		TReal Determinant() const;

		Matrix4x4t& FromEulerAnglesXYZ(TReal x,TReal y,TReal z);
		Matrix4x4t& FromEulerAnglesXYZ(const Vector3t<TReal>& blubb);

		static Matrix4x4t& RotationX(TReal a,Matrix4x4t& out);

		static Matrix4x4t& RotationY(TReal a,Matrix4x4t& out);

		static Matrix4x4t& RotationZ(TReal a,Matrix4x4t& out);

		static Matrix4x4t& Rotation(TReal a,Vector3t<TReal>& axis,
																Matrix4x4t& out);

		static Matrix4x4t& Translation(const Vector3t<TReal>& v,Matrix4x4t& out);


		static Matrix4x4t& Scaling(const Vector3t<TReal>& v,Matrix4x4t& out);
		////self
		bool ToEulerAnglesXYZ(TReal& rfYAngle,TReal& rfPAngle,
													TReal& rfRAngle);

		void Decompose(Vector3t<TReal>& scaling,Matrix3x3t<TReal>& rotation,
									 Vector3t<TReal>& position) const;

		void Decompose(Vector3t<TReal>& scaling,Vector3t<TReal>& euler,Vector3t<TReal>& distort,
									 Vector3t<TReal>& position) const;

		void DecomposeByXYZ(Vector3t<TReal>& scaling,Matrix3x3t<TReal>& rotation,
												Vector3t<TReal>& position) const;

		void ComposeByXYZ(const Vector3t<TReal>& scaling,const Matrix3x3t<TReal>& m,
											const Vector3t<TReal>& position);
		void BuildByXYZPos(const Vector3t<TReal>& x,const Vector3t<TReal>& y,
											 const Vector3t<TReal>& z,const Vector3t<TReal>& position);


		void ToAxisAngle(TReal& x,TReal& y,TReal& z,TReal& rfRadians);

		static Matrix4x4t GetProjectionMatrix(TReal fov,TReal aspect,TReal zn,TReal zf);

		Matrix4x4t toMatrix4D(Matrix3x3t<TReal>& rotation);
		//static Ray GetRay();
	public:
		TReal a1,a2,a3,a4;
		TReal b1,b2,b3,b4;
		TReal c1,c2,c3,c4;
		TReal d1,d2,d3,d4;
	};
	typedef Matrix4x4t<float> Matrix4x4D;

#else
	struct Matrix4x4 {
		float a1, a2, a3, a4;
		float b1, b2, b3, b4;
		float c1, c2, c3, c4;
		float d1, d2, d3, d4;
	};

	//计算视图矩阵
	void calcViewMat(double eyex, double eyey, double eyez,
									 double centerx, double centery, double centerz,
									 double upx, double upy, double upz, float* out);
	//计算投影矩阵
	void calcProMat(m_FOV, m_Aspect, m_Near, m_Far, float* out);
	bool PickMesh(int iMouseX, int iMouseY, const int* pViewPort, const float* pPro,const float* pView, 
								Vector3D& nearClip, Vector3D& farClip);

#endif // __cplusplus
}
#endif