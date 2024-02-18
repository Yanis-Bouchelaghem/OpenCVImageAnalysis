#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <iostream>
#include "utils.h"
#include "convolutions/Convolutions.h"

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
	short kernelXData[9] = { -1, 0, 1,
					-2, 0, 2,
					-1, 0, 1 };
	short kernelYData[9] = { 1,  2,  1,
							 0,  0,  0,
							-1, -2, -1 };
	cv::Mat kernelX = cv::Mat(3, 3, CV_16SC1, kernelXData);
	cv::Mat kernelY = cv::Mat(3, 3, CV_16SC1, kernelYData);
	std::cout << kernelX << "\n";
	std::cout << kernelX.at<short>(0,0) << "\n";
	// Display the image
	cv::imshow("Grayscale cat", imageGrayscale);
	cv::imshow("Bordered image", utils::BorderPadding(imageGrayscale, 50));

	// Apply a mean filter on the grayscale cat image.
	convolutions::MeanFilter meanFilter(5);
	cv::imshow("mean filter applied on cat", convolutions::SlideWindow(imageGrayscale, meanFilter));

	convolutions::GaussianFilter gaussianFilter3x3(1, 1, 1);
	convolutions::GaussianFilter gaussianFilter5x5(2, 1, 1);
	cv::imshow("3x3 Gaussian filter applied on cat", convolutions::SlideWindow(imageGrayscale, gaussianFilter3x3));
	cv::imshow("5x5 Gaussian filter applied on cat", convolutions::SlideWindow(imageGrayscale, gaussianFilter5x5));


	//Apply the sobel edge detection 
	convolutions::MedianFilter medianFilter3x3{1};
	convolutions::MedianFilter medianFilter5x5{2};
	cv::imshow("3x3 Median filterapplied on cat", convolutions::SlideWindow(imageGrayscale, medianFilter3x3));
	cv::imshow("5x5 Median filterapplied on cat", convolutions::SlideWindow(imageGrayscale, medianFilter5x5));



	int key = cv::waitKey(0);
	return 0;
}