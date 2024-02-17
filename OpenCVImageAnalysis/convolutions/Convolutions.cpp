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
    cv::Mat paddedImage = BorderPadding(inputImage, k);
    const int kernelSize = 2*k + 1;
    //go through every pixel of the image
    for(int x = k; x < paddedImage.cols - k; ++x)
    {
        for (int y = k; y < paddedImage.rows - k; ++y)
        {
            //Calculate the mean of the k nearest pixels
            const int topleftX = x - k;
            const int topleftY = y - k;
            const int bottomrightX = x + k;
            const int bottomrightY = y + k;
            float sum = 0.f;
            for (int kernelX = topleftX; kernelX <= bottomrightX; ++kernelX)
            {
                for (int kernelY = topleftY; kernelY <= bottomrightY; ++kernelY)
                {
                    sum += paddedImage.at<uchar>(kernelY, kernelX);
                }
            }
            float mean = sum / (kernelSize * kernelSize);
            paddedImage.at<uchar>(y,x) = mean;
        }
    }

    return paddedImage;
}

//Keep in mind that it is the job of the Convolution function (not the functor) to deal with the padding.
//The convolution function will need to call the functor on the right pixels. (meaning not on the borders)
