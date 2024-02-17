#pragma once
#include <opencv2/core.hpp>

namespace convolutions
{
	//Adds border padding to all sides of a 2D image.
	cv::Mat BorderPadding(const cv::Mat& inputImage, int paddingSize = 1);
	//Applies the mean filter on the given image, k is the size of the window for the convolution (calculated as 2k + 1).
	cv::Mat MeanFilter(const cv::Mat& inputImage, int k = 1);
}
