//
// Created by martin on 01.05.19.
//

#ifndef OPENCV_CORE_FUNCTIONALITY_H
#define OPENCV_CORE_FUNCTIONALITY_H

#include <opencv2/opencv.hpp>

int color_reduction(int argc, char** argv);
int mask_operations(int argc, char** argv);
int basic_operations(int argc, char** argv);

cv::Mat* sharpen(cv::Mat& Input, cv::Mat& Output);



#endif //OPENCV_CORE_FUNCTIONALITY_H
