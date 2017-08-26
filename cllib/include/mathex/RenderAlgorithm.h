#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

//#include "RenderVector3.h"
//#include "RenderVector3.inl"


//计算三角形相交检测，并且可以返回相交点
inline bool IntersectTriangle(const float* pVer, int pIndex1, int pIndex2, int pIndex3, float* rayNearxyz, float* rayFarxyz, float* pIntersect)
{
	float edge1[3];
	float edge2[3];
	float V0[3], V1[3], V2[3];
	float V_Temp[3] = { 0.0, 0.0, 0.0 };

	//initialize three vertex
	V0[0] = pVer[3 * pIndex1];
	V0[1] = pVer[3 * pIndex1 + 1];
	V0[2] = pVer[3 * pIndex1 + 2];

	V1[0] = pVer[3 * pIndex2];
	V1[1] = pVer[3 * pIndex2 + 1];
	V1[2] = pVer[3 * pIndex2 + 2];

	V2[0] = pVer[3 * pIndex3];
	V2[1] = pVer[3 * pIndex3 + 1];
	V2[2] = pVer[3 * pIndex3 + 2];


	//get world vertex
	//Vector3D vertex[3];

	// vertex[0] = GetAxesWorldVec3(V0[0], V0[1], V0[2]);
	// vertex[1] = GetAxesWorldVec3(V1[0], V1[1], V1[2]);
	// vertex[2] = GetAxesWorldVec3(V2[0], V2[1], V2[2]);

	//multi 3. to detect the object easier
	//for (int i = 0; i < 3; i++)
	//{
	//	V0[i] = vertex[0][i];
	//	V1[i] = vertex[1][i];
	//	V2[i] = vertex[2][i];
	//}

	edge1[0] = V1[0] - V0[0];
	edge1[1] = V1[1] - V0[1];
	edge1[2] = V1[2] - V0[2];

	edge2[0] = V2[0] - V0[0];
	edge2[1] = V2[1] - V0[1];
	edge2[2] = V2[2] - V0[2];

	float dir[3];
	dir[0] = rayFarxyz[0] - rayNearxyz[0];
	dir[1] = rayFarxyz[1] - rayNearxyz[1];
	dir[2] = rayFarxyz[2] - rayNearxyz[2];

	float w = (float)sqrt((double)pow(dir[0], 2.0f) + (double)pow(dir[1], 2.0f) + (double)pow(dir[2], 2.0f));
	dir[0] /= w;
	dir[1] /= w;
	dir[2] /= w;

	float pvec[3];
	pvec[0] = dir[1] * edge2[2] - dir[2] * edge2[1];
	pvec[1] = dir[2] * edge2[0] - dir[0] * edge2[2];
	pvec[2] = dir[0] * edge2[1] - dir[1] * edge2[0];

	float det;
	det = edge1[0] * pvec[0] + edge1[1] * pvec[1] + edge1[2] * pvec[2];

	float tvec[3];
	if (det > 0)
	{
		tvec[0] = rayNearxyz[0] - V0[0];
		tvec[1] = rayNearxyz[1] - V0[1];
		tvec[2] = rayNearxyz[2] - V0[2];
	}
	else
	{
		tvec[0] = V0[0] - rayNearxyz[0];
		tvec[1] = V0[1] - rayNearxyz[1];
		tvec[2] = V0[2] - rayNearxyz[2];
		det = -det;
	}

	if (det < 0.0001f)  return false;

	float u;
	u = tvec[0] * pvec[0] + tvec[1] * pvec[1] + tvec[2] * pvec[2];

	if (u < 0.0f || u > det)  return false;

	float qvec[3];
	qvec[0] = tvec[1] * edge1[2] - tvec[2] * edge1[1];
	qvec[1] = tvec[2] * edge1[0] - tvec[0] * edge1[2];
	qvec[2] = tvec[0] * edge1[1] - tvec[1] * edge1[0];


	float v;
	v = dir[0] * qvec[0] + dir[1] * qvec[1] + dir[2] * qvec[2];
	if (v < 0.0f || u + v > det)  return false;

	float t = edge2[0] * qvec[0] + edge2[1] * qvec[1] + edge2[2] * qvec[2];
	float fInvDet = 1.0f / det;
	t *= fInvDet;
	u *= fInvDet;
	v *= fInvDet;

	//vertex info
	V_Temp[0] = (1 - u - v) * V0[0] + u * V1[0] + v * V2[0];
	V_Temp[1] = (1 - u - v) * V0[1] + u * V1[1] + v * V2[1];
	V_Temp[2] = (1 - u - v) * V0[2] + u * V1[2] + v * V2[2];

	//相交点，目前的话在旋转操纵过程中计算坐标中的切线的时候用到
	if (nullptr != pIntersect)
	{
		memcpy(pIntersect, V_Temp, 3 * sizeof(float));
	}
	Vector3D vIntersect = { V_Temp[0], V_Temp[1], V_Temp[2] };
	//cout << "After convert: (" << V_Temp[0] << "," << V_Temp[1] << "," << V_Temp[2] << ")" << endl;
	return true;
}

inline void ScalingPicture(unsigned int inWidth, unsigned int inHeight, unsigned char* inBuffer
	, unsigned int outWidth, unsigned int outHeight, unsigned char* outBuffer)
{
	float xRate, yRate;
	float u, v;
	for (int i = 0; i < outHeight; ++i)
	{
		for (int j = 0; j < outWidth; ++j)
		{
			xRate = float(j) / (outWidth - 1);
			yRate = float(i) / (outHeight - 1);
			u = xRate*(inWidth - 1);
			v = yRate*(inHeight - 1);
			unsigned int ui, vi;
			float uRate, vRate;
			ui = int(u);
			vi = int(v);
			uRate = u - ui;
			vRate = v - vi;

			unsigned char* outPix;
			unsigned char* inPix[4];
			outPix = outBuffer + (i*outWidth + j) * 4;

			unsigned int x1, x2, y1, y2;
			x1 = ui;
			x2 = ui + 1;
			y1 = vi;
			y2 = vi + 1;
			if (x1 < 0)x1 = 0;
			if (x1>inWidth - 1)x1 = inWidth - 1;

			if (x2 < 0)x2 = 0;
			if (x2>inWidth - 1)x2 = inWidth - 1;

			if (y1 < 0)y1 = 0;
			if (y1>inHeight - 1)y1 = inHeight - 1;

			if (y2 < 0)y2 = 0;
			if (y2>inHeight - 1)y2 = inHeight - 1;

			inPix[0] = inBuffer+ (y1*inWidth + x1) * 4;
			inPix[1] = inBuffer + (y1*inWidth + x2) * 4;
			inPix[2] = inBuffer + (y2*inWidth + x1) * 4;
			inPix[3] = inBuffer + (y2*inWidth + x2) * 4;
			for (int k = 0; k < 4; ++k)
			{
				float out, in[4];
				
				for (int n = 0; n < 4; ++n)
				{
					in[n] = inPix[n][k];
				}
				out = (1.0f - uRate)* (1.0f - vRate)*in[0]
					+ uRate* (1.0f - vRate)*in[1]
					+ (1.0f - uRate)* vRate*in[2]
					+ uRate* vRate*in[3];
				outPix[k] = out;
			}
		}
	}	
}


#endif