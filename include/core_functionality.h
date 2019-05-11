//
// Created by martin on 01.05.19.
//

#ifndef OPENCV_CORE_FUNCTIONALITY_H
#define OPENCV_CORE_FUNCTIONALITY_H

#include <opencv2/opencv.hpp>

int color_reduction(int argc, char** argv);
int mask_operations(int argc, char** argv);
int basic_operations(int argc, char** argv);
int image_transformation(int argc, char** argv);
int drawing();

cv::Mat blend2images(std::string src1, std::string src2, float alpha);
cv::Mat* sharpen(cv::Mat& Input, cv::Mat& Output);
cv::Mat linearTransformation(cv::Mat& src, cv::Mat& dst, float alpha, float beta);
cv::Mat gammaTransformation(cv::Mat& src, cv::Mat& dst, float gamma);


#endif //OPENCV_CORE_FUNCTIONALITY_H
