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
    //Calculate the area of the image over which the kernel will be applied
    const int topleftX = x - k;
    const int topleftY = y - k;
    const int bottomrightX = x + k;
    const int bottomrightY = y + k;
    //Calculate the mean of the surrounding pixels
    float sum = 0.f;
    for (int x = topleftX; x < bottomrightX; ++x)
    {
        for (int y = topleftY; y < bottomrightY; ++y)
        {
            sum += inputImage.at<uchar>(y, x);
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
    kernel(GenerateGaussianMatrix(2 * k + 1, sigmaX, sigmaY)),
    k(k),
    kernelSize(2 * k + 1)
{
}

int convolutions::GaussianFilter::GetK() const
{
    return k;
}

int convolutions::GaussianFilter::GetKernelSize() const
{
    return kernelSize;
}

const cv::Mat& convolutions::GaussianFilter::GetKernel() const
{
    return kernel;
}

uchar convolutions::GaussianFilter::operator()(const cv::Mat& inputImage, int y, int x)
{
    //Calculate the area of the image over which the kernel will be applied
    const int topleftX = x - k;
    const int topleftY = y - k;
    const int bottomrightX = x + k;
    const int bottomrightY = y + k;
    //Calculate the convolution with the gaussian filter
    float mean = 0.f;
    for (int imageX = topleftX; imageX <= bottomrightX; ++imageX)
    {
        for (int imageY = topleftY; imageY <= bottomrightY; ++imageY)
        {
            mean += inputImage.at<uchar>(imageY, imageX) * kernel.at<float>(imageY - topleftY, imageX - topleftX);
        }
    }
    return static_cast<uchar>(mean);
}

cv::Mat convolutions::GaussianFilter::GenerateGaussianMatrix(int k, double sigmaX, double sigmaY)
{
    //Implementation for generating a gaussian matrix of size k taken from :
    //https://codereview.stackexchange.com/a/169675
    auto gauss_x = cv::getGaussianKernel(k, sigmaX, CV_32F);
    auto gauss_y = cv::getGaussianKernel(k, sigmaY, CV_32F);
    return gauss_x * gauss_y.t();
}

