#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <iostream>
#include "utils.h"
#include "convolutions/Convolutions.h"
#include "transformations/transformations.h"

int main()
{
	cv::Mat imageGrayscale;
	cv::Mat imageBGR;
	// load a cat image in grayscale
	try
	{
		imageGrayscale = utils::LoadImage("images/cat.jpg", cv::IMREAD_GRAYSCALE);
	}
	catch (cv::Exception)
	{
		std::cout << "\nCould not read the cat image ! Please ensure that cat.jpg is present in the 'images' folder.";
		return -1;
	}

	// Display the image
	cv::imshow("Grayscale cat", imageGrayscale);
	cv::imshow("Bordered image", utils::BorderPadding(imageGrayscale, 50));

	// Apply a mean filter on the grayscale cat image.
	convolutions::MeanFilter meanFilter(5);
	cv::imshow("mean filter applied on cat", convolutions::SlideWindow(imageGrayscale, meanFilter));

	//Apply a gaussian filter on the grayscale cat image.
	convolutions::GaussianFilter gaussianFilter3x3(1, 1, 1);
	convolutions::GaussianFilter gaussianFilter5x5(2, 1, 1);
	cv::imshow("3x3 Gaussian filter applied on cat", convolutions::SlideWindow(imageGrayscale, gaussianFilter3x3));
	cv::imshow("5x5 Gaussian filter applied on cat", convolutions::SlideWindow(imageGrayscale, gaussianFilter5x5));

	//Apply the median filter on the grayscale cat image.
	convolutions::MedianFilter medianFilter3x3{1};
	convolutions::MedianFilter medianFilter5x5{2};
	cv::imshow("3x3 Median filterapplied on cat", convolutions::SlideWindow(imageGrayscale, medianFilter3x3));
	cv::imshow("5x5 Median filterapplied on cat", convolutions::SlideWindow(imageGrayscale, medianFilter5x5));

	///////////////////// Transformations  /////////////////////
	cv::imshow("Transposed image of a cat", transformations::Transpose(imageGrayscale));
	cv::imshow("0.7 scale nearest neighbor on cat", transformations::NearestNeighbor(imageGrayscale, 0.7f));
	cv::imshow("2 scale nearest neighbor on cat", transformations::NearestNeighbor(imageGrayscale, 2.0f));
	int key = cv::waitKey(0);
	return 0;
}