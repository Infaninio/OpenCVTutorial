//
// Created by martin on 22.05.19.
//

#ifndef OPENCV_RANDOM_H
#define OPENCV_RANDOM_H
#define WINDOWSIZEX 1000
#define WINDOWSIZEY 1000

#include <opencv2/opencv.hpp>


int drawRandomStuff();

int randLines(cv::Mat image,cv::RNG rng, int cnt = 100);
int randRectangles(cv::Mat image,cv::RNG rng, int cnt = 100);
int randEllipses(cv::Mat image,cv::RNG rng, int cnt = 100);
int randPolylines(cv::Mat image,cv::RNG rng, int cnt = 100);
int randPolygons(cv::Mat image,cv::RNG rng, int cnt = 100);
int randCircles(cv::Mat image,cv::RNG rng, int cnt = 100);
//int randText(cv::Mat image,cv::RNG rng, int cnt = 20);
static cv::Scalar randColor(cv::RNG rng);








#endif //OPENCV_RANDOM_H
