#pragma once
#include "clVector2.h"
#include "clVector3.h"

namespace cl {
	//���ܳ��ȷ�Χ�ڣ�ʹ��simpson�㷨�ķָ���  
#define TOTAL_SIMPSON_STEP  (10000)  
	//�����귽��
	namespace Bezier {
		//�����ٶȷ���

		inline double beze_speed_axis(double t,double axis0,double axis1,double axis2,double axis3) {

			double it=1-t;

			return -3*axis0*it*it+3*axis1*it*it-6*axis1*it*t+6*axis2*it*t-3*axis2*t*t+3*axis3*t*t;

		}

		inline double beze_speed(double t,Vector2D P0,Vector2D P1,Vector2D P2,Vector2D P3) {

			double sx=beze_speed_axis(t,P0.x,P1.x,P2.x,P3.x);

			double sy=beze_speed_axis(t,P0.y,P1.y,P2.y,P3.y);

			return sqrt(sx*sx+sy*sy);

		}

		inline double beze_speed(double t,Vector3D P0,Vector3D P1,Vector3D P2,Vector3D P3) {

			double sx=beze_speed_axis(t,P0.x,P1.x,P2.x,P3.x);

			double sy=beze_speed_axis(t,P0.y,P1.y,P2.y,P3.y);

			double sz=beze_speed_axis(t,P0.z,P1.z,P2.z,P3.z);

			return sqrt(sx*sx+sy*sy+sz*sz);
		}

		inline double beze_speed_x(double t,Vector2D P0,Vector2D P1,Vector2D P2,Vector2D P3) {

			double sx=beze_speed_axis(t,P0.x,P1.x,P2.x,P3.x);

			return sx;

		}

		//-------------------------------------------------------------------------------------  

		//���ȷ���,ʹ��Simpson�����㷨  
		inline double beze_length(double t,Vector2D P0,Vector2D P1,Vector2D P2,Vector2D P3) {

			//�ָ����  

			int stepCounts=(int)(TOTAL_SIMPSON_STEP*t);

			if(stepCounts&1) stepCounts++;    //ż��  

			if(stepCounts==0) return 0.0;



			int halfCounts=stepCounts/2;

			double sum1=0.0,sum2=0.0;

			double dStep=t/stepCounts;



			for(int i=0; i<halfCounts; i++) {

				sum1+=beze_speed((2*i+1)*dStep,P0,P1,P2,P3);

			}

			for(int i=1; i<halfCounts; i++)

			{

				sum2+=beze_speed((2*i)*dStep,P0,P1,P2,P3);

			}

			return (beze_speed(0.0,P0,P1,P2,P3)+beze_speed(1.0,P0,P1,P2,P3)+2*sum2+4*sum1)*dStep/3.0;

		}

		inline double beze_length(double t,Vector3D P0,Vector3D P1,Vector3D P2,Vector3D P3) {

			//�ָ����  

			int stepCounts=(int)(TOTAL_SIMPSON_STEP*t);

			if(stepCounts&1) stepCounts++;    //ż��  

			if(stepCounts==0) return 0.0;



			int halfCounts=stepCounts/2;

			double sum1=0.0,sum2=0.0;

			double dStep=t/stepCounts;



			for(int i=0; i<halfCounts; i++) {

				sum1+=beze_speed((2*i+1)*dStep,P0,P1,P2,P3);

			}

			for(int i=1; i<halfCounts; i++)

			{

				sum2+=beze_speed((2*i)*dStep,P0,P1,P2,P3);

			}

			return (beze_speed(0.0,P0,P1,P2,P3)+beze_speed(1.0,P0,P1,P2,P3)+2*sum2+4*sum1)*dStep/3.0;

		}
		inline double beze_length_x(double t,Vector2D P0,Vector2D P1,Vector2D P2,Vector2D P3) {

			//�ָ����  

			int stepCounts=(int)(TOTAL_SIMPSON_STEP*t);

			if(stepCounts&1) stepCounts++;    //ż��  

			if(stepCounts==0) return 0.0;



			int halfCounts=stepCounts/2;

			double sum1=0.0,sum2=0.0;

			double dStep=t/stepCounts;



			for(int i=0; i<halfCounts; i++) {

				sum1+=beze_speed_x((2*i+1)*dStep,P0,P1,P2,P3);

			}

			for(int i=1; i<halfCounts; i++)

			{

				sum2+=beze_speed_x((2*i)*dStep,P0,P1,P2,P3);

			}



			return (beze_speed_x(0.0,P0,P1,P2,P3)+beze_speed_x(1.0,P0,P1,P2,P3)+2*sum2+4*sum1)*dStep/3.0;

		}
		//-------------------------------------------------------------------------------------  

		//����t�Ƶ��������˶��Ա���t'�ķ���(ʹ��ţ�����߷�)  

		inline double beze_even(double t,Vector2D P0,Vector2D P1,Vector2D P2,Vector2D P3) {

			double len=t*beze_length(1.0,P0,P1,P2,P3); //���������������,��ʱ��Ӧ�����߳���  

			double t1=t,t2;

			do {

				t2=t1-(beze_length(t1,P0,P1,P2,P3)-len)/beze_speed(t1,P0,P1,P2,P3);

				if(abs(t1-t2)<0.0000001) break;

				t1=t2;

			} while(true);

			return t2;

		}

		inline double beze_even(double t,Vector3D P0,Vector3D P1,Vector3D P2,Vector3D P3) {

			double len=t*beze_length(1.0,P0,P1,P2,P3); //���������������,��ʱ��Ӧ�����߳���  

			double t1=t,t2;

			do {

				t2=t1-(beze_length(t1,P0,P1,P2,P3)-len)/beze_speed(t1,P0,P1,P2,P3);

				if(abs(t1-t2)<0.0000001) break;

				t1=t2;

			} while(true);

			return t2;

		}

		inline double beze_even_x(double t,Vector2D P0,Vector2D P1,Vector2D P2,Vector2D P3) {

			double len=t*beze_length_x(1.0,P0,P1,P2,P3); //���������������,��ʱ��Ӧ�����߳���  

			double t1=t,t2;

			do {

				t2=t1-(beze_length_x(t1,P0,P1,P2,P3)-len)/beze_speed_x(t1,P0,P1,P2,P3);

				if(abs(t1-t2)<0.0000001) break;

				t1=t2;

			} while(true);

			return t2;

		}
	};
	//ͨ������t��x,y,(z)ֵ
	inline bool get_beze_value_by_t(double t,Vector2D P0,Vector2D P1,Vector2D P2,Vector2D P3,Vector2D& ret) {
		if(t < 0||t>1) {
			return false;
		}
		double it=1-t;
		ret.x=it*it*it*P0.x+3*it*it*t*P1.x+3*it*t*t*P2.x+t*t*t*P3.x;
		ret.y=it*it*it*P0.y+3*it*it*t*P1.y+3*it*t*t*P2.y+t*t*t*P3.y;
		return true;
	}

	inline bool get_beze_value_by_t(double t,Vector3D P0,Vector3D P1,Vector3D P2,Vector3D P3,Vector3D& ret) {
		if(t < 0||t>1) {
			return false;
		}
		double it=1-t;
		ret.x=it*it*it*P0.x+3*it*it*t*P1.x+3*it*t*t*P2.x+t*t*t*P3.x;
		ret.y=it*it*it*P0.y+3*it*it*t*P1.y+3*it*t*t*P2.y+t*t*t*P3.y;
		ret.z=it*it*it*P0.z+3*it*it*t*P1.z+3*it*t*t*P2.z+t*t*t*P3.z;
		return true;
	}

	//�߶ξ��� 
	inline bool get_beze_value(unsigned int index,unsigned int Step,Vector2D P0,Vector2D P1,Vector2D P2,Vector2D P3,Vector2D& ret) {
		if(Step<index) {
			return false;
		}
		double t=(double)index/Step;

		//��������˶���Ӧ��tֵ  

		t=Bezier::beze_even(t,P0,P1,P2,P3);

		//���ݱ��������ߺ��������ȡ�ô�ʱ��x,y����  

		get_beze_value_by_t(t,P0,P1,P2,P3,ret);
		return true;
	}

	inline bool get_beze_value(unsigned int index,unsigned int Step,Vector3D P0,Vector3D P1,Vector3D P2,Vector3D P3,Vector3D& ret) {
		if(Step<index) {
			return false;
		}
		double t=(double)index/Step;

		//��������˶���Ӧ��tֵ  

		t=Bezier::beze_even(t,P0,P1,P2,P3);

		//���ݱ��������ߺ��������ȡ�ô�ʱ��x,y����  

		get_beze_value_by_t(t,P0,P1,P2,P3,ret);
		return true;
	}
	//x�����
	inline bool get_beze_value_x(unsigned int index,unsigned int Step,Vector2D P0,Vector2D P1,Vector2D P2,Vector2D P3,Vector2D& ret) {
		if(Step<index) {
			return false;
		}
		double t=(double)index/Step;

		//��������˶���Ӧ��tֵ  

		t=Bezier::beze_even_x(t,P0,P1,P2,P3);



		//���ݱ��������ߺ��������ȡ�ô�ʱ��x,y����  

		get_beze_value_by_t(t,P0,P1,P2,P3,ret);

		return true;
	}
}