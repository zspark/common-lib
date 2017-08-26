#ifndef _clAABB_H_
#define _clAABB_H_

namespace cl {
#include "clVector3.h"
#ifdef __cplusplus
#include <cmath>
#else
#include <math.h>
#endif


#ifdef __cplusplus
#define AI_FORCE_INLINE __forceinline

	template <typename TReal>
	class clAABB {
	public:
		clAABB():t_min(),t_max() {}
		clAABB(TReal _min,TReal _max): t_min(_min),t_max(_max) {}
		clAABB(const clAABB& o): t_min(o.t_min),t_max(o.t_max) {}
		void Include(TReal pos);
		TReal GetCenter();
		float GetLength();
	public:
		TReal t_min,t_max;
	};
	typedef clAABB<Vector3D> clAABBV3;
#endif 
}
#endif//_clAABB_H_