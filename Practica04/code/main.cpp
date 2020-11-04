#include <opencv2/highgui.hpp>

#include "octree_quantization.hpp"
using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {
  Mat input, output, out_palette;

  string file_name = argv[1];
  
	input = imread(file_name, IMREAD_COLOR);
	output = imread(file_name, IMREAD_COLOR);
	out_palette = imread(file_name, IMREAD_COLOR);

	OctreeQuantizer quantizer;

	quantizer.fill(output);
	quantizer.reduction();
	quantizer.reduction();
	quantizer.reduction();
	quantizer.reduction();
	quantizer.reduction();
	quantizer.reduction();
	quantizer.reconstruction(output);
	quantizer.palette(out_palette);

	namedWindow("Entrada", WINDOW_AUTOSIZE);
	imshow("Entrada", input);

	namedWindow("Resultado", WINDOW_AUTOSIZE);
	imshow("Resultado", output);

	namedWindow("Paleta de colores",WINDOW_AUTOSIZE);
	imshow("Paleta de colores", out_palette);

	waitKey(0);

	return 0;
}
