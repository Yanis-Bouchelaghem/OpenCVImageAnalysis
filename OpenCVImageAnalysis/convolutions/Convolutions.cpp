#include "Convolutions.h"

convolutions::MeanFilter::MeanFilter(int k)
	:
	k(k),
    kernelSize(2*k + 1)
{
}

uchar convolutions::MeanFilter::operator()(const cv::Mat& inputImage, int y, int x)
{
    //Calculate the mean of the surrounding pixels
    const int topleftX = x - k;
    const int topleftY = y - k;
    const int bottomrightX = x + k;
    const int bottomrightY = y + k;
    float sum = 0.f;
    for (int kernelX = topleftX; kernelX <= bottomrightX; ++kernelX)
    {
        for (int kernelY = topleftY; kernelY <= bottomrightY; ++kernelY)
        {
            sum += inputImage.at<uchar>(kernelY, kernelX);
        }
    }
    float mean = sum / (kernelSize * kernelSize);
    return static_cast<uchar>(mean);
}

int convolutions::MeanFilter::GetK() const
{
    return k;
}

int convolutions::MeanFilter::GetKernelSize() const
{
    return kernelSize;
}
