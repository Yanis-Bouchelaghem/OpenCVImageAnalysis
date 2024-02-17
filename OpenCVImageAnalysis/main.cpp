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

	// Display the image
	cv::imshow("Grayscale cat", imageGrayscale);
	cv::imshow("Bordered image", utils::BorderPadding(imageGrayscale, 50));

	// Apply a mean filter on the grayscale cat image.
	convolutions::MeanFilter meanFilter(5);
	cv::imshow("mean filter applied on cat", convolutions::SlideWindow(imageGrayscale, meanFilter));

	convolutions::GaussianFilter gaussianFilter(3, 1, 1);
	cv::Mat kernel = gaussianFilter.GetKernel();
	cv::imshow("Gaussian filter applied on cat", convolutions::SlideWindow(imageGrayscale, gaussianFilter));
	for (int x = 0; x < kernel.cols; ++x)
	{
		for (int y = 0; y < kernel.rows; ++y)
		{
			std::cout << kernel.at<float>(y, x) << "   ";
		}
		std::cout << "\n";
	}
	std::cout << "Sum : " << cv::sum(kernel);
	int key = cv::waitKey(0);

	return 0;
}