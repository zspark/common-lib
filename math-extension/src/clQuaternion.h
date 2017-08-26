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

		//ͨ����ת��������Ԫ��
		explicit Quaterniont(const Matrix3x3t<TReal>& pRotMatrix);

		//ͨ��ŷ���ǻ�ȡ��Ԫ��
		Quaterniont(TReal rotx,TReal roty,TReal rotz);

		//ͨ��������ͽǶȻ�ȡ��Ԫ��
		Quaterniont(Vector3t<TReal> axis,TReal angle);
		//�����Ѵ�����Ԫ����������Ԫ��
		explicit Quaterniont(Vector3t<TReal> normalized);

		//������Ԫ����ȡ����
		Matrix3x3t<TReal> GetMatrix() const;

	public:

		bool operator== (const Quaterniont& o) const;
		bool operator!= (const Quaterniont& o) const;

		bool Equal(const Quaterniont& o,TReal epsilon=1e-6) const;

	public:

		//��λ����Ԫ��
		Quaterniont& Normalize();

		//(������Ԫ������)
		Quaterniont& Conjugate();

		//ͨ����Ԫ���Զ���ͽ�����ת����
		Vector3t<TReal> Rotate(const Vector3t<TReal>& in);

		//��Ԫ���˷�
		Quaterniont operator* (const Quaterniont& two) const;



	public:

		//��Ԫ����ֵ
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
