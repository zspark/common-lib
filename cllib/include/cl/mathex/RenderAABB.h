#ifndef _RenderAABB_H_
#define _RenderAABB_H_
#include "RenderVector3.h"
#ifdef __cplusplus
#include <cmath>
#else
#include <math.h>
#endif


#ifdef __cplusplus
#   define AI_FORCE_INLINE __forceinline

template <typename TReal>
class RenderAABB
{
public:
	RenderAABB() :t_min(), t_max(){}
	RenderAABB(TReal _min, TReal _max) : t_min(_min), t_max(_max) {}
	RenderAABB(const RenderAABB& o) : t_min(o.t_min), t_max(o.t_max){}
	void Include(TReal pos);
	TReal GetCenter();
	float GetLength();
public:
	TReal t_min,t_max;
};
typedef RenderAABB<Vector3D> RenderAABBV3;
#endif // __cplusplus
#endif//_RenderAABB_H_