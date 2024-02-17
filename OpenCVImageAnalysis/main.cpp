#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <iostream>
#include "utils.h"
#include "Convolutions.h"

int main()
{
	cv::Mat imageGrayscale;
	cv::Mat imageBGR;
	// load a cat image in grayscale
	try
	{
		imageGrayscale = utils::LoadImage("images/cat.jpg", cv::IMREAD_GRAYSCALE);
		imageBGR = utils::LoadImage("images/cat.jpg", cv::IMREAD_COLOR);
	}
	catch (cv::Exception)
	{
		std::cout << "\nCould not read the cat image ! Please ensure that cat.jpg is present in the 'images' folder.";
		return -1;
	}

	// Display the image
	cv::imshow("Grayscale cat", imageGrayscale);
	cv::imshow("BGR cat", imageBGR);
	cv::imshow("Bordered image", convolutions::BorderPadding(imageGrayscale, 50));
	cv::imshow("mean filter applied on cat", convolutions::MeanFilter(imageGrayscale, 4));
	int key = cv::waitKey(0);
}