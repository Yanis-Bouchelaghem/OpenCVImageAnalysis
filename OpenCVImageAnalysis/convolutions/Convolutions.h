#pragma once
#include <opencv2/core.hpp>
#include <assert.h>
#include "../utils.h"

namespace convolutions
{
	// A generic function that can convolve any given filter on a grayscale image.
	// The filter must implement 'GetK()', 'GetKernelSize()', and the () operator.
	template<class Filter>
	cv::Mat Convolve(const cv::Mat& inputImage, Filter filter)
	{
        assert(inputImage.dims == 2); //If assertion triggers : Input is not a 2D image.
		int k = filter.GetK();
        cv::Mat paddedImage = utils::BorderPadding(inputImage, k);
        const int kernelSize = filter.GetKernelSize();
        //go through every pixel of the image
        for (int x = k; x < paddedImage.cols - k; ++x)
        {
            for (int y = k; y < paddedImage.rows - k; ++y)
            {
				//Apply the filter on the pixel
                paddedImage.at<uchar>(y, x) = filter(paddedImage, y, x);
            }
        }
        return paddedImage;
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
}
