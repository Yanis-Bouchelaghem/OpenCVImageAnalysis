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

cv::Mat transformations::NearestNeighbor(const cv::Mat& inputImage, float scale)
{
	//Create a new image with the right size for the scaling.
	int newCols = int(inputImage.cols * scale);
	int newRows = int(inputImage.rows * scale);
	cv::Mat newImage(newRows, newCols, inputImage.depth());
	for (int x = 0; x < newCols; ++x)
	{
		for (int y = 0; y < newRows; ++y)
		{
			int originalX = (inputImage.cols * x) / newCols;
			int originalY = (inputImage.rows * y) / newRows;
			newImage.at<uchar>(y,x) = inputImage.at<uchar>(originalY, originalX);
		}
	}
	return newImage;
}
