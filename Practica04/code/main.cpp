#include <opencv2/highgui.hpp>

#include "octree_quantizer.hpp"

int main(int argc, char *argv[]) {
  cv::Mat input, output, out_palette;

  std::string file_name = argv[1];

  input = cv::imread(file_name, cv::IMREAD_COLOR);
  output = cv::imread(file_name, cv::IMREAD_COLOR);
  out_palette = cv::imread(file_name, cv::IMREAD_COLOR);

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

  cv::namedWindow("Entrada", cv::WINDOW_AUTOSIZE);
  cv::imshow("Entrada", input);

  cv::namedWindow("Resultado", cv::WINDOW_AUTOSIZE);
  cv::imshow("Resultado", output);

  cv::namedWindow("Paleta de colores", cv::WINDOW_AUTOSIZE);
  cv::imshow("Paleta de colores", out_palette);

  cv::waitKey(0);

  return 0;
}
