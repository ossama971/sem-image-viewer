QT       += core gui
QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    widgets/image_widget.cpp

HEADERS += \
    mainwindow.h \
    widgets/image_widget.h

FORMS += \
    mainwindow.ui \
    widgets/image_widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


# Include OpenCV libraries and directories
INCLUDEPATH += /opt/homebrew/Cellar/opencv/4.10.0_11/include/opencv4
# LIBS += -L/opt/homebrew/lib/ -lopencv_world
LIBS += -L/opt/homebrew/lib/ \
    -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs \
    -lopencv_calib3d -lopencv_dnn -lopencv_features2d -lopencv_flann -lopencv_gapi \
    -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_video \
    -lopencv_videoio -lopencv_alphamat -lopencv_aruco -lopencv_bgsegm \
    -lopencv_bioinspired -lopencv_ccalib -lopencv_datasets -lopencv_dnn_objdetect \
    -lopencv_dnn_superres -lopencv_dpm -lopencv_face -lopencv_freetype -lopencv_fuzzy \
    -lopencv_hfs -lopencv_img_hash -lopencv_intensity_transform -lopencv_line_descriptor \
    -lopencv_mcc -lopencv_optflow -lopencv_phase_unwrapping -lopencv_plot \
    -lopencv_quality -lopencv_rapid -lopencv_reg -lopencv_rgbd -lopencv_saliency \
    -lopencv_sfm -lopencv_shape -lopencv_signal -lopencv_stereo -lopencv_structured_light \
    -lopencv_superres -lopencv_surface_matching -lopencv_text -lopencv_tracking \
    -lopencv_videostab -lopencv_viz -lopencv_wechat_qrcode -lopencv_xfeatures2d \
    -lopencv_ximgproc -lopencv_xobjdetect -lopencv_xphoto

# Include Boost libraries and directories
INCLUDEPATH += /opt/homebrew/opt/boost/include
LIBS += -L/opt/homebrew/opt/boost/lib -lboost_system -lboost_filesystem


LIBS += -framework OpenGL
