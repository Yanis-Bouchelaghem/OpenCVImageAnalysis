#include "utils.h"

cv::Mat utils::LoadImage(std::string imagePath, cv::ImreadModes readMode)
{
	std::string absolutePath = cv::samples::findFile(imagePath, true);
	return cv::imread(absolutePath, readMode);
}
