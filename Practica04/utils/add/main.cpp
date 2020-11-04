#include "QuantizationOctree.hpp"
#include <opencv2/highgui.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
    cv::Mat image;
    std::string file_name = argv[1];
    //image = cv::imread(file_name, CV_LOAD_IMAGE_COLOR);
    image = cv::imread(file_name, cv::IMREAD_COLOR);

    if (!image.data)
    {
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    QuantizationOctree quantization;

    quantization.fill(image);

    quantization.reduction();
    quantization.reduction();
    quantization.reduction();
    quantization.reduction();
    quantization.reduction();
    quantization.reduction();


    quantization.reconstruction(image);

    cv::namedWindow("Color Quantization", cv::WINDOW_AUTOSIZE);
    cv::imshow("Color Quantization", image);

    cv::Mat original;
    //original = cv::imread(file_name, CV_LOAD_IMAGE_COLOR);
    original = cv::imread(file_name, cv::IMREAD_COLOR);

    cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
    cv::imshow("Original", original);

    cv::Mat paleta;
    paleta = cv::imread(file_name, cv::IMREAD_COLOR);

    quantization.palette(paleta);

    cv::namedWindow("Paleta", cv::WINDOW_AUTOSIZE);
    cv::imshow("Paleta", paleta);

    cv::waitKey(0);

    return 0;
}
