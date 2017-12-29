#ifndef RENDERAABB_INL_INC
#define RENDERAABB_INL_INC

#ifdef __cplusplus
#include "RenderAABB.h"

#include <cmath>

// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE void  RenderAABB<TReal>::Include(TReal n){
	if (t_min.x > n.x)t_min.x = n.x;
	if (t_min.y > n.y)t_min.y = n.y;
	if (t_min.z > n.z)t_min.z = n.z;

	if (t_max.x < n.x)t_max.x = n.x;
	if (t_max.y < n.y)t_max.y = n.y;
	if (t_max.z < n.z)t_max.z = n.z;
}
template <typename TReal>
AI_FORCE_INLINE TReal RenderAABB<TReal>::GetCenter()
{
	TReal dir = t_max - t_min;
	dir.x *= 0.5f;
	dir.y *= 0.5f;
	dir.z *= 0.5f;
	TReal out = t_min + dir;
	return out;
}

template <typename TReal>
AI_FORCE_INLINE float RenderAABB<TReal>::GetLength()
{
	TReal dir = t_max - t_min;
	return dir.Length();
}
#endif//RENDERAABB_INL_INC
#endif//RENDERAABB_INL_INC