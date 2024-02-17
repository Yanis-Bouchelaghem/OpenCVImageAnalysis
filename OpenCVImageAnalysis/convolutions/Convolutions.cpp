#include "Convolutions.h"
#include <cmath>
#include <opencv2/imgproc/imgproc.hpp>

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

convolutions::GaussianFilter::GaussianFilter(int k, double sigmaX, double sigmaY)
    :
    kernel(GenerateGaussianMatrix(k, sigmaX, sigmaY))
{
}

const cv::Mat& convolutions::GaussianFilter::GetKernel() const
{
    return kernel;
}

cv::Mat convolutions::GaussianFilter::GenerateGaussianMatrix(int k, double sigmaX, double sigmaY)
{
    //Implementation for generating a gaussian matrix of size k taken from :
    //https://codereview.stackexchange.com/a/169675
    auto gauss_x = cv::getGaussianKernel(k, sigmaX, CV_32F);
    auto gauss_y = cv::getGaussianKernel(k, sigmaY, CV_32F);
    return gauss_x * gauss_y.t();
}

