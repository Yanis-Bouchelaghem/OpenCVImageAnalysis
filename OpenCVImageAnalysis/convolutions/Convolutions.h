#pragma once
#include <opencv2/core.hpp>
#include <assert.h>
#include "../utils.h"

namespace convolutions
{
	// A generic function that can apply any given filter on a grayscale image.
	// The filter must implement 'GetK()', 'GetKernelSize()', and the () operator.
	template<class Filter>
	cv::Mat SlideWindow(const cv::Mat& inputImage, Filter filter)
	{
        assert(inputImage.dims == 2); //If assertion triggers : Input is not a 2D image.
		const int k = filter.GetK();
        const int kernelSize = filter.GetKernelSize();
		//Add the necessary padding to the image.
        cv::Mat paddedImage = utils::BorderPadding(inputImage, k); 
        //Go through every pixel of the image (ignoring the padding).
        for (int x = k; x < paddedImage.cols - k; ++x)
        {
            for (int y = k; y < paddedImage.rows - k; ++y)
            {
				//Apply the filter on the pixel.
                paddedImage.at<uchar>(y, x) = filter(paddedImage, y, x);
            }
        }
		//Remove the padding from the image
        return utils::RemoveBorder(paddedImage, k);
	}


	class MeanFilter
	{
	public:
		MeanFilter(int k);
		uchar operator()(const cv::Mat& inputImage, int y, int x);
		int GetK() const;
		int GetKernelSize() const;
	private:
		const int k;
		const int kernelSize;
	};

	class GaussianFilter
	{
	public:
		GaussianFilter(int k, double sigmaX = 1, double sigmaY = 1);
		int GetK() const;
		int GetKernelSize() const;
		const cv::Mat& GetKernel() const;
		uchar operator()(const cv::Mat& inputImage, int y, int x);
		static cv::Mat GenerateGaussianMatrix(int k, double sigmaX, double sigmaY);
	
	private:
		const cv::Mat kernel;
		const int k;
		const int kernelSize;
	};
}
