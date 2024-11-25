#include "noise_reduction_filter.h"
#include "../engines/logger.h"

NoiseReductionFilter::NoiseReductionFilter(double intensity)
{
    if (intensity < 0)
        _intensity = 0;
    else if (intensity > 100)
        _intensity = 100;
    else
        _intensity = intensity;
}

cv::Mat NoiseReductionFilter::applyFilter(const Image &inputImage) const
{
    cv::Mat image = inputImage.getImageMat();
    cv::Mat res;

    if (image.channels() == 1)
    {
        cv::fastNlMeansDenoising(cv::InputArray(image), cv::OutputArray(res), _intensity);
    }
    else
    {
        cv::fastNlMeansDenoisingColored(cv::InputArray(image), cv::OutputArray(res), _intensity, _intensity);
    }
    Logger::instance()->logMessage(
        Logger::MessageTypes::info, Logger::MessageID::images_loading_started,
        Logger::MessageOption::with_path,
        {"Noise Reduction"},
        "https://docs.opencv.org/4.x/d5/d69/tutorial_py_non_local_means.html");
    return res;
}

ImageStateSource NoiseReductionFilter::getImageSource() const
{
    return ImageStateSource::NoiseReductionFilter;
}

const double NoiseReductionFilter::getIntensity(void) const
{
    return _intensity;
}
