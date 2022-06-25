#include "CoordinateTransformer.h"



/*void CoordinateTransformer::scrollCallback(GLFWwindow* window, double xoff, double yoff) {
	int sign = yoff / abs(yoff);

    for (int i = 0; i < (boundSTL->storageSize); i++) {
        boundSTL->coordinates[i].V1[1] = boundSTL->coordinates[i].V1[1] * pow(1.1, sign);
        boundSTL->coordinates[i].V1[2] = boundSTL->coordinates[i].V1[2] * pow(1.1, sign);
        boundSTL->coordinates[i].V1[3] = boundSTL->coordinates[i].V1[3] * pow(1.1, sign);

        boundSTL->coordinates[i].V2[1] = boundSTL->coordinates[i].V2[1] * pow(1.1, sign);
        boundSTL->coordinates[i].V2[2] = boundSTL->coordinates[i].V2[2] * pow(1.1, sign);
        boundSTL->coordinates[i].V2[3] = boundSTL->coordinates[i].V2[3] * pow(1.1, sign);

        boundSTL->coordinates[i].V3[1] = boundSTL->coordinates[i].V3[1] * pow(1.1, sign);
        boundSTL->coordinates[i].V3[2] = boundSTL->coordinates[i].V3[2] * pow(1.1, sign);
        boundSTL->coordinates[i].V3[3] = boundSTL->coordinates[i].V3[3] * pow(1.1, sign);
    }


}
*/


void CoordinateTransformer::bindSTL(FileReader* coordinates) {
	boundSTL = coordinates;
}