#include "FileReader.h"
#include <intrin.h>



void FileReader::coordReader(int size) {

	file.seekg(2, std::ios::cur);
	/*
	*
	* STL file structure
	* UINT8[80]    – Header						- 80 bytes
	* UINT32       – Number of triangles		- 4	 bytes
	* foreach triangle							- 50 bytes:
	* 	REAL32[3] – Normal vector				- 12 bytes
	*	REAL32[3] – Vertex 1					- 12 bytes
	*	REAL32[3] – Vertex 2					- 12 bytes
	*	REAL32[3] – Vertex 3					- 12 bytes
	*	UINT16    – Attribute byte count		-  2 bytes
	* end
	*/

	coordinates = new triangle[size];
	


	for (int entry = 0; entry < size; entry++) {
		

		coordinates[entry].normal[0] = readOne();
		coordinates[entry].normal[1] = readOne();
		coordinates[entry].normal[2] = readOne();



		coordinates[entry].V1[0] = readOne();
		coordinates[entry].V1[1] = readOne();
		coordinates[entry].V1[2] = readOne();


		coordinates[entry].V2[0] = readOne();
		coordinates[entry].V2[1] = readOne();
		coordinates[entry].V2[2] = readOne();


		coordinates[entry].V3[0] = readOne();
		coordinates[entry].V3[1] = readOne();
		coordinates[entry].V3[2] = readOne();

		file.seekg(2, std::ios::cur);

	}


	
}

float FileReader::readOne() {
	//shit reads 4 byte
	// 
	// 
	// 
	char val0;
	char val1;
	char val2;
	char val3;

	file.read(&val0, 1);
	file.read(&val1, 1);
	file.read(&val2, 1);
	file.read(&val3, 1);
	char vals[4] = { val0, val1, val2, val3 };
	float value = (*(float*)vals);
	return value;
}