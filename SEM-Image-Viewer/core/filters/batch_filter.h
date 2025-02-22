#ifndef BATCH_FILTER_H
#define BATCH_FILTER_H

#include "image_filter.h"
#include <QWidget>
#include <memory>
#include <vector>
#include <QDateTime>


class BatchFilter : public QObject
{
    Q_OBJECT

public:
    BatchFilter() = default;
    ~BatchFilter() = default;

    void apply(std::unique_ptr<ImageFilter> filter, const std::vector<Image*> &input);

signals:
    void onImageProcessed(Image* image);
    void onFinish(const std::vector<Image*> &input, const std::vector<std::pair<cv::Mat, bool>> &output, ImageStateSource stateSource);

private:
    QDateTime startTime;
};

#endif // BATCH_FILTER_H
