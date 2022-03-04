CONFIG += console c++11
#CONFIG -= app_bundle
#CONFIG -= qt

TARGET = cudaQTS

INCLUDEPATH += /usr/local/include/opencv4
INCLUDEPATH += /usr/local/include/opencv4/opencv2/
INCLUDEPATH += /usr/local/include/eigen3/
INCLUDEPATH += /usr/local/cuda/include

LIBS += -I/usr/local/include/opencv4/opencv -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_gapi -lopencv_stitching -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn_objdetect -lopencv_dpm -lopencv_face -lopencv_freetype -lopencv_fuzzy -lopencv_hfs -lopencv_img_hash -lopencv_line_descriptor -lopencv_quality -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_superres -lopencv_optflow -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_dnn -lopencv_plot -lopencv_videostab -lopencv_video -lopencv_xfeatures2d -lopencv_shape -lopencv_ml -lopencv_ximgproc -lopencv_xobjdetect -lopencv_objdetect -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_flann -lopencv_xphoto -lopencv_photo -lopencv_imgproc -lopencv_core -lopencv_cudacodec -lopencv_cudaarithm -lopencv_cudabgsegm -lopencv_cudalegacy -lopencv_cudastereo -lopencv_cudafilters -lopencv_cudaimgproc -lopencv_cudaoptflow -lopencv_cudawarping -lopencv_cudaobjdetect  -lopencv_cudafeatures2d

SOURCES += \
        Histogram.cpp \
        gpu-opencv.cpp \
        main.cpp \
        video.cpp

HEADERS += \
    init.h


## This makes the .cu files appear in your project
#OTHER_FILES +=  ./kernel.cu

## CUDA settings <-- may change depending on your system
#CUDA_SOURCES += ./kernel.cu
#CUDA_SDK = "/usr/local/cuda-11.1/"   # Path to cuda SDK install
#CUDA_DIR = "/usr/local/cuda-11.1/"            # Path to cuda toolkit install


## DO NOT EDIT BEYOND THIS UNLESS YOU KNOW WHAT YOU ARE DOING....

#SYSTEM_NAME = ubuntu         # Depending on your system either 'Win32', 'x64', or 'Win64'
#SYSTEM_TYPE = 64            # '32' or '64', depending on your system
#CUDA_ARCH = sm_61           # Type of CUDA architecture, for example 'compute_10', 'compute_11', 'sm_10'
#NVCC_OPTIONS = --use_fast_math

## include paths
#INCLUDEPATH += $$CUDA_DIR/include

## library directories
#QMAKE_LIBDIR += $$CUDA_DIR/lib64/

#CUDA_OBJECTS_DIR = ./

## Add the necessary libraries
#CUDA_LIBS = -lcuda -lcudart

## The following makes sure all path names (which often include spaces) are put between quotation marks
#CUDA_INC = $$join(INCLUDEPATH,'" -I"','-I"','"')
##LIBS += $$join(CUDA_LIBS,'.so ', '', '.so')
#LIBS += $$CUDA_LIBS

## Configuration of the Cuda compiler
#CONFIG(debug, debug|release) {
#    # Debug mode
#    cuda_d.input = CUDA_SOURCES
#    cuda_d.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
#    cuda_d.commands = $$CUDA_DIR/bin/nvcc -D_DEBUG $$NVCC_OPTIONS $$CUDA_INC $$NVCC_LIBS --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
#    cuda_d.dependency_type = TYPE_C
#    QMAKE_EXTRA_COMPILERS += cuda_d
#}
#else {
#    # Release mode
#    cuda.input = CUDA_SOURCES
#    cuda.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
#    cuda.commands = $$CUDA_DIR/bin/nvcc $$NVCC_OPTIONS $$CUDA_INC $$NVCC_LIBS --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
#    cuda.dependency_type = TYPE_C
#    QMAKE_EXTRA_COMPILERS += cuda
#}

#DISTFILES += \
#    Others files/kernel.cu \
#    Others files/kernel.cu \
#    Others files/kernel.cu \
#    Others files/kernel.cu

DISTFILES += \
    cuda.cu



