#ifndef IMAGE_H
#define IMAGE_H

#include "image_state.h"
#include "image_meta_data.h"
#include "Visitor.h"
#include "Visitable.h"

#include <memory>
#include <vector>
#include <filesystem>
#include <QObject>
#include <opencv2/opencv.hpp>

class Image : public QObject, public Visitable {
    Q_OBJECT

public:
    Image();
    Image(const std::filesystem::path path);
    Image(const Image& image);
    Image(Image&& image);
    Image& operator=(const Image& image);
    Image& operator=(Image&& image);
    ~Image();

    bool load(const std::filesystem::path path);
    bool setImage(const cv::Mat &image, ImageStateSource newState = ImageStateSource::Origin);

    void addRedo(const cv::Mat &image, ImageStateSource newState);

    bool isLoaded() const;
    const cv::Mat& getImageMat() const;
    ImageStateSource getImageState() const;
    std::filesystem::path getPath() const;
    ImageMetadata getMetadata() const;

    std::vector<std::unique_ptr<ImageState>>const & getStates() const;
    std::vector<std::unique_ptr<ImageState>>const & getUndo() const;

    void accept(Visitor &v) const override;

    const QString getCurrentAction() const;
    bool undo();
    bool redo();
    const QList<QString> getHistory();

signals:
    void onImageStateUpdated(std::vector<std::unique_ptr<ImageState>>& states);

private:
    bool _loaded;
    std::filesystem::path _path;
    ImageMetadata _metadata;
    std::vector<std::unique_ptr<ImageState>> _states;
    std::vector<std::unique_ptr<ImageState>> _redo;
};

#endif // IMAGE_H
