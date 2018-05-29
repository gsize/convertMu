#include "muvoxel.h"

MuVoxel::MuVoxel():matrix_size0(0),matrix_size1(0),matrix_size2(0),pixel_size0(0.0f),pixel_size1(0.0f),pixel_size2(0.0f)
{
	MuMatrix.resize(0);
}

MuVoxel::MuVoxel(int matrix_s0,int matrix_s1,int matrix_s2,float pixel_s0,float pixel_s1,float pixel_s2)
	:matrix_size0(matrix_s0),matrix_size1(matrix_s1),matrix_size2(matrix_s2),pixel_size0(pixel_s0),pixel_size1(pixel_s1),pixel_size2(pixel_s2)
{
	MuMatrix.resize(matrix_size0*matrix_size1*matrix_size2);
}
bool MuVoxel::IsInVoxel(float x,float y,float z)
{
	if(fabs(x)<=(matrix_size0*pixel_size0/2.) &&fabs(y)<=(matrix_size1*pixel_size1/2.) && fabs(z)<=(matrix_size2*pixel_size2/2.))
		return true;
	else
		return false;
}

int MuVoxel::GetIndex(float x,float y,float z)
{
	if(IsInVoxel(x,y,z))
	{
		int i =(int)((x+matrix_size0*pixel_size0/2.0)/pixel_size0);
		int j =(int)((y+matrix_size1*pixel_size1/2.0)/pixel_size1);
		int k =(int)((z+matrix_size2*pixel_size2/2.0)/pixel_size2);
		return GetIndex(i,j,k);
	}else
		return -1;
}

int MuVoxel::ReadMuMatrix(const char *filepath)
{
	FILE *pf;
	pf=fopen(filepath,"rb");
	if(pf)
	{
		fread(&MuMatrix[0],sizeof(float),MuMatrix.size(),pf);
		fclose(pf);
		return 1;
	}
	else{
		printf("read Mu file failed!!\n");
		return 0;
	}
}
void MuVoxel::SaveMuMatrix(const char *filepath)
{
	FILE *pf;
	pf=fopen(filepath,"wb");
	if(pf)
	{
		fwrite(&MuMatrix[0],sizeof(float),MuMatrix.size(),pf);
		fclose(pf);
	}
	else{
		printf("read Mu file failed!!\n");
	}
}

int MuVoxel::GetPixelPosition(int i,int j,int k,float &cx,float &cy,float &cz)
{
	if(i>=0 &&j>=0&&k>=0 && i<matrix_size0 && j<matrix_size1 && k<matrix_size2)
	{
		cx =(float)(i*pixel_size0- matrix_size0*pixel_size0/2.0+pixel_size0/2.0);
		cy =(float)(j*pixel_size1- matrix_size1*pixel_size1/2.0+pixel_size1/2.0);
		cz =(float)(k*pixel_size2- matrix_size2*pixel_size2/2.0+pixel_size2/2.0);
		return GetIndex(i,j,k);
	}else 
		return -1;
}
void MuVoxel::convertMU(MuVoxel &dest)
{
	for(int k=0;k<dest.GetMatrixSize2()  ;k++)
		for(int j=0;j<dest.GetMatrixSize1()  ;j++)
			for(int i=0;i<dest.GetMatrixSize0()  ;i++)
			{
				float cx,cy,cz;
				int status = dest.GetPixelPosition(i,j,k,cx,cy,cz);

				if(status>-1)
				{
					int src_idx = this->GetIndex(cx,cy,cz);
					if(src_idx>-1)
						dest.SetMuByIndex(dest.GetIndex(i,j,k),this->GetMuByIndex(src_idx));
				}
			}
}

