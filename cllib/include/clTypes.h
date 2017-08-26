#pragma once

namespace cl {
	typedef int clInt;
	typedef unsigned int clUint;
	typedef float clFloat;
	typedef double clDouble;
	typedef bool clBool;
	typedef unsigned int uint;
	typedef const char* ccharstar;
	typedef char* charstar;

	template<typename T>
	struct type_2T {
		T x,y;
		void Set(T valuex,T valuey) {
			x=valuex; y=valuey;
		}

		void Set(T value) {
			x=y=value;
		}

		void Copy(const type_2T& another) {
			x=another.x;
			y=another.y;
		}
	};
	typedef type_2T<int> clInt2;
	typedef type_2T<uint> clUint2;
	typedef type_2T<float> clFloat2;
	typedef type_2T<double> clDouble2;

	template<typename T>
	struct type_3T {
		T x,y,z;
		void Set(T valuex,T valuey,T valuez) {
			x=valuex; y=valuey; z=valuez;
		}

		void Set(T value) {
			x=y=z=value;
		}

		void Copy(const type_3T& another) {
			x=another.x;
			y=another.y;
			z=another.z;
		}
	};
	typedef type_3T<int> clInt3;
	typedef type_3T<uint> clUint3;
	typedef type_3T<float> clFloat3;
	typedef type_3T<double> clDouble3;

	template<typename T>
	struct type_4T {
		T x,y,z,w;

		void Set(T valuex,T valuey,T valuez,T valuew) {
			x=valuex; y=valuey; z=valuez; w=valuew;
		}

		void Set(T value) {
			x=y=z=w=value;
		}

		void Copy(const type_4T& another) {
			x=another.x;
			y=another.y;
			z=another.z;
			w=another.w;
		}
	};
	typedef type_4T<int> clInt4;
	typedef type_4T<uint> clUint4;
	typedef type_4T<float> clFloat4;
	typedef type_4T<double> clDouble4;

	enum clUniformType {
		CL_INT=0,
		CL_UINT,
		CL_FLOAT,
		CL_DOUBLE,
		CL_BOOL,
		CL_CHARSTAR,

		CL_INT2,
		CL_UINT2,
		CL_FLOAT2,
		CL_DOUBLE2,

		CL_INT3,
		CL_UINT3,
		CL_FLOAT3,
		CL_DOUBLE3,

		CL_INT4,
		CL_UINT4,
		CL_FLOAT4,
		CL_DOUBLE4,
	};

	struct clUniform {
		clUniform() {}
		clUniformType type;
		union {
			int intValue;
			uint uintValue;
			float floatValue;
			double doubleValue;
			bool boolValue;
			ccharstar charValue;

			clFloat2 float2Value;
			clInt2 int2Value;
			clUint2 uint2Value;
			clDouble2 double2Value;

			clFloat3 float3Value;
			clInt3 int3Value;
			clUint3 uint3Value;
			clDouble3 double3Value;

			clFloat4 float4Value;
			clInt4 int4Value;
			clUint4 uint4Value;
			clDouble4 double4Value;
		};
	};
}
