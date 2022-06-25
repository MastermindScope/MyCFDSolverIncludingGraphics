#pragma once
#include <string>
#include <iostream>
#include <fstream> //I can read files with that
#include <intrin.h>
#include "BaseClass.h"
#include "glfwHandler.h"
#include <iostream>


class FileReader : public BaseClass
{
public:
	//public functions


	FileReader(std::string path) {
		filepath = path;

		file.open(path,std::ios::binary|std::ios::in|std::ios::ate); //loads the file to memory

		if (file.is_open()) {
			int filesize = file.tellg();
			std::cout << "Loaded file with size: " << filesize << std::endl;
		}

		file.seekg(80, std::ios::beg);//sets next character to be read to pos. 641 from BEGinning.
		//641 because the first 80 bytes of stl binaries are garbage
		char val0, val1, val2, val3;

		//read next 4 bytes. this gives the number of triangles
		file.read(&val0, 1); 
		file.read(&val1, 1);
		file.read(&val2, 1);
		file.read(&val3, 1);
		//std::cout << "first byte is: " << std::hex << val0 << std::endl;

		/*
		* this is only included for future reference
		* fstream only deals in chars and not bit. EVERY INTEGER YOU SEE CORRESPONDS TO BYTE *NOT* BIT
		std::cout << std::hex << "Singles: " << val0 << val1 << val2 << val3;

		storageSize = (val0 << 24) | (val1 << 16) | (val2 << 8) | (val3 << 0);
		std::cout << "Read raw: " << std::hex << storageSize << std::endl;
		*/
		std::cout << std::hex << val0 << val1 << val2 << val3 << std::endl;
		storageSize = _byteswap_ulong((val0 << 24) | (val1 << 16) | (val2 << 8) | (val3)); //do this to convert little endian to big endian
		std::cout << std::dec << "Read size: " << storageSize << std::endl;

		
		
		file.seekg(82, std::ios::beg); //set read position to first triangle

		coordReader(storageSize);
		
		

		file.close();
	}
	//float* loadData(std::string path);

	//public variables
	/*struct triangle {
		float V1[3];
		float V2[3];
		float V3[3];
		float normal[3];
	};*/
	triangle* coordinates;
	uint32_t storageSize = 1;

private:
	std::string filepath;
	std::ifstream file;
	float coordBuffer[3];

	void coordReader(int size);
	float readOne();



};

