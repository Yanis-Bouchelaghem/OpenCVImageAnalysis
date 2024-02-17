#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <string>

namespace utils
{
	//Loads the specified image into a cv::Mat, throws cv::Exception if image is not found.
	cv::Mat LoadImage(std::string imagePath, cv::ImreadModes readMode);
}