#include "transformations.h"

cv::Mat transformations::Transpose(const cv::Mat& inputImage)
{
	cv::Mat transposedImage(inputImage.cols, inputImage.rows, inputImage.depth());
	for (int x = 0; x < inputImage.cols; ++x)
	{
		for (int y = 0; y < inputImage.rows; ++y)
		{
			transposedImage.at<uchar>(x,y) = inputImage.at<uchar>(y,x);
		}
	}
	return transposedImage;
}
