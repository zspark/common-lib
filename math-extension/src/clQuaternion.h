#ifndef QUATERNION_H_INC
#define QUATERNION_H_INC

#ifdef __cplusplus
namespace cl {
	template <typename TReal> class Vector3t;
	template <typename TReal> class Matrix3x3t;

	template <typename TReal>
	class Quaterniont {
	public:
		Quaterniont(): w(1.0),x(),y(),z() {}
		Quaterniont(TReal pw,TReal px,TReal py,TReal pz)
			: w(pw),x(px),y(py),z(pz) {}

		//通过旋转矩阵获得四元数
		explicit Quaterniont(const Matrix3x3t<TReal>& pRotMatrix);

		//通过欧拉角获取四元数
		Quaterniont(TReal rotx,TReal roty,TReal rotz);

		//通过坐标轴和角度获取四元数
		Quaterniont(Vector3t<TReal> axis,TReal angle);
		//根据已存在四元数构造新四元数
		explicit Quaterniont(Vector3t<TReal> normalized);

		//根据四元数获取矩阵
		Matrix3x3t<TReal> GetMatrix() const;

	public:

		bool operator== (const Quaterniont& o) const;
		bool operator!= (const Quaterniont& o) const;

		bool Equal(const Quaterniont& o,TReal epsilon=1e-6) const;

	public:

		//单位化四元数
		Quaterniont& Normalize();

		//(计算四元数共轭)
		Quaterniont& Conjugate();

		//通过四元数对顶点就进行旋转操作
		Vector3t<TReal> Rotate(const Vector3t<TReal>& in);

		//四元数乘法
		Quaterniont operator* (const Quaterniont& two) const;



	public:

		//四元数插值
		static void Interpolate(Quaterniont& pOut,const Quaterniont& pStart,
														const Quaterniont& pEnd,TReal pFactor);

		void computeQuaterniont(const Matrix3x3t<TReal>& pRotMatrix);

		void computeQuaterniont(Vector3t<TReal> axis,TReal angle);

	public:

		TReal w,x,y,z;
	};

	typedef Quaterniont<float> QuaternionD;

#else

struct Quaternion {
	float w, x, y, z;
};

#endif
}
#endif
