////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_ALGORITHMS_HEADER
#define KF_ALGORITHMS_HEADER

#include <ostream>
#include "kf/kf_types.h"
#include "kf/kf_math.h"

namespace kf
{
	template<typename T=float, typename T2>
	void constrainDistFixed(T2 &pos1, T2 &pos2, float desiredDist, float compensate1 = 0.5, float compensate2 = 0.5)
	{
		T2 delta = pos2 - pos1;
		T deltalength = length(delta);
		if (deltalength > 0)
		{
			T diff = (deltalength - desiredDist) / deltalength;
			pos1 += delta * compensate1 * diff;
			pos2 -= delta * compensate2 * diff;
		}
	}

	template<typename T = float, typename T2>
	void constrainDistMin(T2 &pos1, T2 &pos2, float minDist, float compensate1 = 0.5, float compensate2 = 0.5)
	{
		T2 delta = pos2 - pos1;
		T deltalength = length(delta);
		if (deltalength > 0 && deltalength < minDist)
		{
			T diff = (deltalength - minDist) / deltalength;
			pos1 += delta * compensate1 * diff;
			pos2 -= delta * compensate2 * diff;
		}
	}

	template<typename T = float, typename T2>
	void constrainDistMax(T2 &pos1, T2 &pos2, float maxDist, float compensate1 = 0.5, float compensate2 = 0.5)
	{
		T2 delta = pos2 - pos1;
		T deltalength = length(delta);
		if (deltalength > 0 && deltalength > maxDist)
		{
			T diff = (deltalength - maxDist) / deltalength;
			pos1 += delta * compensate1 * diff;
			pos2 -= delta * compensate2 * diff;
		}
	}

	template<typename T = float, typename T2>
	void constrainDistRange(T2 &pos1, T2 &pos2, float minDist, float maxDist, float compensate1 = 0.5, float compensate2 = 0.5)
	{
		T2 delta = pos2 - pos1;
		T deltalength = length(delta);
		if (deltalength > 0 && (deltalength > maxDist || deltalength < minDist))
		{
			T diff = (deltalength - maxDist) / deltalength;
			pos1 += delta * compensate1 * diff;
			pos2 -= delta * compensate2 * diff;
		}
	}

	template<typename T = float, typename T2>
	void constrainBox(T2 &pos, const T2 &minCorner, const T2 &maxCorner)
	{
		pos = min(max(pos,minCorner), maxCorner);
	}

	template<typename T1, typename T2>
	inline T1 lerp(const T1 &val1, const T1 &val2, T2 t)
	{
		return (val2 - val1) * t + val1;
	}

	template<typename T>
	inline T remap(const T &src_range_start, const T &src_range_end, const T &dst_range_start, const T &dst_range_end, const T &value_to_remap)
	{
		return ((dst_range_end - dst_range_start) * (value_to_remap - src_range_start)) / (src_range_end - src_range_start) + dst_range_start;
	}

	template<typename T>
	inline T s_curve(const T &val)
	{
		return val*val*(T(3.0) - T(2.0)*val);
	}

	template<typename T>
	inline T expose(const T &val)
	{
		return 1.0 - exp(-val);
	}

	template<typename T>
	inline T cubic(const T &v0, const T &v1, const T &v2, const T &v3, float t)
	{
		return (v3 - v2 - v0 + v1) * t * t * t + (2.0f * v0 - 2.0f * v1 + v2 - v3) * t * t + (v2 - v0) * t + v1;
	}

	template<typename T>
	inline T hermite(const T &v0, const T &v1, const T &v2, const T &v3, float bias, float tension, float t)
	{
		T m0, m1;
		float a0, a1, a2, a3;
		m0 = (v1 - v0) * (1.0f + bias) * (1.0f - tension) / 2.0f;
		m0 += (v2 - v1) * (1.0f - bias) * (1.0f - tension) / 2.0f;
		m1 = (v2 - v1) * (1.0f + bias) * (1.0f - tension) / 2.0f;
		m1 += (v3 - v2) * (1.0f - bias) * (1.0f - tension) / 2.0f;
		a0 = 2.0f * t * t * t - 3.0f * t * t + 1.0f;
		a1 = t * t * t - 2.0f * t * t + t;
		a2 = t * t * t - t * t;
		a3 = -2.0f * t * t * t + 3.0f * t * t;
		return a0 * v1 + a1 * m0 + a2 * m1 + a3 * v2;
	}

}
#endif
