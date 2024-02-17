#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <iostream>

int main()
{
	cv::Mat image;
	// load a cat image in grayscale
	try
	{
		std::string imagePath = cv::samples::findFile("images/cat.jpg", true);
		image = cv::imread( imagePath, cv::IMREAD_GRAYSCALE);
	}
	catch (cv::Exception)
	{
		std::cout << "\nCould not read the cat image ! Please ensure that cat.jpg is present in the 'images' folder.";
		return -1;
	}

	// Display the image
	cv::imshow("Grayscale cat", image);
	int key = cv::waitKey(0);
}