#include <opencv2/core.hpp>


namespace transformations
{
	//A function that transposes an image.
	cv::Mat Transpose(const cv::Mat& inputImage);
	//A function that grows or shrinks an image using nearest neighbor interpolation.
	cv::Mat NearestNeighbor(const cv::Mat& inputImage, float scale = 2);
}