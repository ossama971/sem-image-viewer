#ifndef CONTOURS_FILTER_H
#define CONTOURS_FILTER_H

#include "ImageFilter.h"

class EdgeDetectionFilter : public ImageFilter {
private:
    int threshold_low=50;
    int threshold_high=150;

    cv::Mat Denoise(const cv::Mat &image) const;
    cv::Mat ToGrayscale(const cv::Mat &image) const;
public:
    EdgeDetectionFilter();
    void setThresholdLow(int threshold);
    void setTHresholdHigh(int threshold);
    int get_threshold_low();
    int get_threshold_high();
    cv::Mat applyFilter(const cv::Mat &inputImage) const;

};

#endif // CONTOURS_FILTER_H
