#ifndef MUVOXEL_H
#define MUVOXEL_H
//
//
//  g++ convertMU.C -o convertMU
//
#include <stdio.h>
#include <math.h>
#include <string>
#include <vector>
using std::vector;

class MuVoxel
{
	public:
		MuVoxel();
		MuVoxel(int matrix_s0,int matrix_s1,int matrix_s2,float pixel_s0,float pixel_s1,float pixel_s2);
		void SetMatrixSize(int i,int j,int k){
			matrix_size0=i;matrix_size1=j;matrix_size2=k;
			MuMatrix.resize(matrix_size0*matrix_size1*matrix_size2);};
		void SetPixelSize(float i,float j,float k){pixel_size0=i;pixel_size1=j;pixel_size2=k;};
		bool IsInVoxel(float x,float y,float z);
		int GetIndex(float x,float y,float z);
		int GetIndex(int i,int j,int k){return k*matrix_size0*matrix_size1+j*matrix_size0+i;};
		int GetPixelPosition(int i,int j,int k,float &x,float &y,float &z);
		float GetMuByIndex(int i){return MuMatrix[i];};
		void SetMuByIndex(int i,float mu){MuMatrix[i]=mu;};
		int ReadMuMatrix(const char *filepath);
		void SaveMuMatrix(const char *filepath);
		int GetMatrixSize(){return MuMatrix.size();};
		int GetMatrixSize0(){return matrix_size0;};
		int GetMatrixSize1(){return matrix_size1;};
		int GetMatrixSize2(){return matrix_size2;};
		void convertMU(MuVoxel &dest);

	private:
		int matrix_size0;
		int matrix_size1;
		int matrix_size2;
		float pixel_size0;
		float pixel_size1;
		float pixel_size2;
		vector<float> MuMatrix;
};
#endif
