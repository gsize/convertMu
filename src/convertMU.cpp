
#include "muvoxel.h"
#include "CLI11.hpp"

#include <string>
#include <string>

using std::string;


int main(int argc, char **argv)
{
	string input;
	std::vector<float> inPixelSize;
	std::vector<float> outPixelSize;
	std::vector<int> outMatrixSize;
	std::vector<int> inMatrixSize;
	CLI::App app{"covert MuMap file to different pixel size and matrix size"};
	app.add_option("-i,--input",input,"input MuMap file")->required();
	app.add_option("--inPixelSize",inPixelSize,"input MuMap Pixel size")->required(3);
	app.add_option("--inMatrixSize",inMatrixSize,"input MuMap Matrix size")->required(3);
	app.add_option("--outPixelSize",outPixelSize,"output MuMap Pixel size")->required(3);
	app.add_option("--outMatrixSize",outMatrixSize,"output MuMap Matrix size")->required(3);

	try{
		CLI11_PARSE(app,argc,argv);
	}catch(const CLI::ParseError &e){
		return app.exit(e);
	}

	MuVoxel src,dest;

	src.SetPixelSize(inPixelSize[0],inPixelSize[1],inPixelSize[2]);
	src.SetMatrixSize(inMatrixSize[0],inMatrixSize[1],inMatrixSize[2]);

	if(! (src.ReadMuMatrix(input.c_str())))
	{
		printf("read input MuMap failed!\n");
		return -1;
	}

	dest.SetPixelSize(outPixelSize[0],outPixelSize[1],outPixelSize[2]);
	dest.SetMatrixSize(outMatrixSize[0],outMatrixSize[1],outMatrixSize[2]);

	string output(input);
	std::size_t pos=input.find_last_of(".");
	char str_tmp[256];
	sprintf(str_tmp,"_%d_%d_%d",outMatrixSize[0],outMatrixSize[1],outMatrixSize[2]);
	if(pos!=string::npos)
		output.insert(pos,str_tmp);
	else
		output+=str_tmp;

	src.convertMU(dest);
	printf("output file : %s\n",output.c_str());
	dest.SaveMuMatrix(output.c_str());

	return 0;
}

