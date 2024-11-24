#ifndef IMAGE_SESSION_H
#define IMAGE_SESSION_H

#include "ImageRepository.h"
#include "Visitor.h"
#include "Visitable.h"
#include "../filters/ImageFilter.h"
#include "../filters/BatchFilter.h"

class SessionData : public QObject, public Visitable {
  Q_OBJECT
public:
    SessionData();

    void loadDirectory(const std::string path);
    void loadImage(const std::string path);
    void applyFilter(std::unique_ptr<ImageFilter> filter);
    void applyFilter(std::unique_ptr<ImageFilter> filter, std::vector<int> image_indices);

    bool undo();
    bool redo();

    std::vector<int> pixelIntensity(const std::vector<std::pair<int, int>> &points);
    cv::Mat heatMap();
    cv::Mat diffTwoImages(const cv::Mat &image2, const int threshold);

    ImageRepository& getImageRepo();
    Image* getSelectedImage();

    void accept(Visitor &v) const override;

signals:
    void loadActionList(QList<QString> actions);
    void updateActionList(QString action);
    void popActionList();

    void onBatchFilterStarted(int maxIterations);
    void onBatchFilterFinished();

private slots:
    void onBatchFilterApplied(std::vector<Image*> input, std::vector<cv::Mat> output, ImageStateSource stateSource);

private:
    ImageRepository _imageRepo;
    //UndoManager _undoManager;
    BatchFilter _batchFilter;
};

#endif // IMAGE_SESSION_H
