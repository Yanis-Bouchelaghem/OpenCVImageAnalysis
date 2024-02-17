#include "Convolutions.h"
#include <assert.h>

cv::Mat convolutions::BorderPadding(const cv::Mat& inputImage, int paddingSize)
{
    assert(inputImage.dims == 2); //If assertion triggers : Input is not a 2D image.
    cv::Mat imagePadded(inputImage.rows + 2*paddingSize, inputImage.cols + 2*paddingSize, inputImage.depth());
    // form a border in-place
    cv::copyMakeBorder(inputImage, imagePadded, paddingSize, paddingSize,
                       paddingSize, paddingSize, cv::BORDER_REPLICATE);
    return imagePadded;
}

cv::Mat convolutions::MeanFilter(const cv::Mat& inputImage, int k)
{
    assert(inputImage.dims == 2); //If assertion triggers : Input is not a 2D image.
    cv::Mat imageCopy = inputImage.clone();
    const int kernelSize = 2*k + 1;
    //todo


    return cv::Mat();
}
