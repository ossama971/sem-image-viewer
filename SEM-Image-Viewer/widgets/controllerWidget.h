#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include "../core/data/SessionData.h"
#include "../core/engines/Workspace.h"
#include "historywidget.h"
#include "grayscalewidget.h"
#include "noisereductionwidget.h"
class LoggerWidget;
class ImageWidget;
class ContourWidget;
class EdgeExtractionWidget;


class Controller : public QObject
{
    Q_OBJECT

public:
    static Controller &instance()
    {
        static Controller instance;
        return instance;
    }

    void setLoggerWidget(LoggerWidget *widget);
    void setImageWidget(ImageWidget *widget);
    void setContourWidget(ContourWidget *widget);
    void setEdgeExtractionWidget(EdgeExtractionWidget *widget);
    void setNoiseReductionWidget(NoiseReductionWidget *widget);
    void setHistoryWidget(HistoryWidget *widget);
    void setGraySacleWidget(GrayScaleWidget* widget);

private slots:

    void onEdgeWidgetFilterApplied();
    void onNoiseReductionFilterApplied();
    void onContourFilterApplied();
    void onGraySacleFilterApplied();
private:
    Controller();
    Controller(const Controller &) = delete;
    Controller &operator=(const Controller &) = delete;
    void printMat(const cv::Mat &mat);

    SessionData &SessionData_;

    LoggerWidget *loggerWidget = nullptr;
    HistoryWidget* historyWidget=nullptr;
    ImageWidget *imageWidget = nullptr;
    ContourWidget *contourWidget = nullptr;
    EdgeExtractionWidget *edgeExtractionWidget = nullptr;
    NoiseReductionWidget *noiseReductionWidget = nullptr;
    GrayScaleWidget *graySacleWidget = nullptr;

signals:
    void imageUpdated(const cv::Mat &newImage);

};

#endif // CONTROLLER_H
