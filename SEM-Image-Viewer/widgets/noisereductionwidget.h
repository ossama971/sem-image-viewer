#ifndef NOISEREDUCTIONWIDGET_H
#define NOISEREDUCTIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QToolButton>

class NoiseReductionWidget:public QWidget
{
    Q_OBJECT
public:
    explicit NoiseReductionWidget(QWidget* parent=nullptr);
    int getIntensity() const;

private:
    QLabel *label;
    QToolButton *toggleButton;
    QSlider *IntensitySlider;
    QWidget *slidersWidget;
    QLabel *intensity;

signals:
    void intensityChanged(int value);
    void applyFilter();

private slots:
    void expandCollapseSliders(bool checked);
    void handleIntensityChange(int value);
    void handleApplyFilter();

};

#endif // NOISEREDUCTIONWIDGET_H
