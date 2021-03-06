#ifndef DEF_H
#define DEF_H
#include <cmath>
#ifndef _NOSTDSTRING
using namespace std;
#endif //std
const float kPi = 4 * atan(1.0);
const float k2Pi = kPi * 2.0f;
const float kPiOver2 = kPi / 2.0f;
const float k1OverPi = 1.0f / kPi;
const float k1Over2Pi = 1.0f / k2Pi;
const float kPiOver180 = kPi / 180.0f;
const float k180OverPi = 180.0f / kPi;

inline double AngleToRad(double a){
	return a*kPi / 180;
}

inline double RadToAngle(double rad){
	return rad * 180 / kPi;
}

inline void MatrixMultiplications(float *m1, float *m2, float *m3, int m, int n, int k){
	for (int i = 0; i<m; i++)
	{
		for (int j = 0; j<k; j++)
		{
			float sum = 0.0;
			for (int jj = 0; jj<n; jj++)
			{
				sum += *(m1 + i*n + jj)*(*(m2 + jj*k + j));
			}
			*(m3 + i*k + j) = sum;
		}
	}
}

#endif