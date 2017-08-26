#pragma once
#include <functional>
#include "clTypes.h"
#include "clguiEvent.h"

namespace clgui {

  using namespace cl;

	template<typename T>
	class ComponentVariable_T {
	public:
		//ComponentVariable_T(const ComponentVariable_T&)=delete;
		//ComponentVariable_T(const ComponentVariable_T*)=delete;
		//const ComponentVariable_T& operator=(const ComponentVariable_T& another) = delete;

	public:
		// reset old and new to same value;
		void ResetTo(T value) {
			m_oldValue=m_newValue=value;
		}

		T GetOldValue()const { return m_oldValue; };
		T GetNewValue()const { return m_newValue; };
		T* GetNewValueRef() { return &m_newValue; };

		//only set new to value;
		void SetNewValue(T value) { m_newValue=value; }

		// update old to new;
		void Update() { m_oldValue=m_newValue; };

		// if old and new are different return true;
		// others return false;
		bool CheckChange()const { return m_oldValue!=m_newValue; };

	private:
		T m_oldValue;
		T m_newValue;
  };
	typedef ComponentVariable_T<int> cvInt;
	typedef ComponentVariable_T<uint> cvUint;
	typedef ComponentVariable_T<float> cvFloat;
	typedef ComponentVariable_T<double> cvDouble;
	typedef ComponentVariable_T<bool> cvBool;

	typedef ComponentVariable_T<clInt3> cvInt3;
	typedef ComponentVariable_T<clUint3> cvUint3;
	typedef ComponentVariable_T<clFloat3> cvFloat3;
	typedef ComponentVariable_T<clDouble3> cvDouble3;

	enum UniformComponentVariableType {
	  UCV_INT=0,
	  UCV_UINT,
	  UCV_FLOAT,
	  UCV_DOUBLE,
	  UCV_BOOL,

	  UCV_INT3,
	  UCV_UINT3,
	  UCV_FLOAT3,
	  UCV_DOUBLE3,
	};

	struct UniformComponentVariable {
	  UniformComponentVariable() {};
	  ~UniformComponentVariable() {};

	  bool CheckChange() {
		 return intValue.CheckChange();
	  }

	  void Update() {
		 intValue.Update();
	  }

		UniformComponentVariableType type;
		union {
			cvInt intValue;
			cvUint uintValue;
			cvFloat floatValue;
			cvDouble doubleValue;
			cvBool boolValue;

			cvFloat3 float3Value;
			cvInt3 int3Value;
			cvUint3 uint3Value;
			cvDouble3 double3Value;
		};
	};


	typedef std::function<void()> CallBackFn;
	typedef std::function<void(bool)> CallBackBoolFn;
	typedef std::function<void(clguiEvent*)> EventCallBackFn;

}
