//
// Created by martin on 22.05.19.
//
#include <opencv2/opencv.hpp>
#include <vector>
#include <time.h>
#include "../include/random.h"


int drawRandomStuff(){

    cv::Mat bild = cv::Mat::zeros(WINDOWSIZEX,WINDOWSIZEY,CV_8UC3);
    cv::Mat bild2 = cv::Mat::zeros(WINDOWSIZEX,WINDOWSIZEY,CV_8UC3);
    std::time_t nowT;
    std::time(&nowT);




    cv::RNG rand(nowT);

    randLines(bild,rand);
    cv::imshow("Bild", bild);
    cv::waitKey();

    randRectangles(bild, rand);
    cv::imshow("Bild", bild);
    cv::waitKey();


    randCircles(bild2, rand);
    cv::imshow("Bild2", bild2);
    cv::waitKey();

    bild2 = cv::Mat::zeros(WINDOWSIZEX,WINDOWSIZEY,CV_8UC3);
    randEllipses(bild2, rand);
    cv::imshow("Bild2", bild2);
    cv::waitKey();

    bild2 = cv::Mat::zeros(WINDOWSIZEX,WINDOWSIZEY,CV_8UC3);
    randPolylines(bild2, rand,5);
    cv::imshow("Bild2", bild2);
    cv::waitKey();

    bild2 = cv::Mat::zeros(WINDOWSIZEX,WINDOWSIZEY,CV_8UC3);
    randPolygons(bild2, rand,5);
    cv::imshow("Bild2", bild2);
    cv::waitKey();


    return 0;
}




int randLines(cv::Mat bild, cv::RNG rng, int cnt){

    cv::Point pt1, pt2;
    for (int i = 0; i < cnt; ++i) {
        pt1.x = rng.uniform(1,WINDOWSIZEX);
        pt2.x = rng.uniform(1, WINDOWSIZEX);
        pt1.y = rng.uniform(1,WINDOWSIZEY);
        pt2.y = rng.uniform(1, WINDOWSIZEY);
        cv::line(bild, pt1, pt2, randColor(rng),rng.uniform(1,10));
    }

    return 0;

}


cv::Scalar randColor(cv::RNG rng){
    int icolor = rng;
    cv::Scalar color(icolor&255,(icolor>>8)&255,(icolor>>16)&255);
    return color;

}


int randRectangles(cv::Mat bild, cv::RNG rng, int cnt){
    for (int i = 0; i < cnt; ++i) {
        cv::Point pt1(rng.uniform(1,WINDOWSIZEX),rng.uniform(1,WINDOWSIZEY));
        cv::Point pt2(rng.uniform(1,WINDOWSIZEX), rng.uniform(1, WINDOWSIZEY));
        cv::rectangle(bild,pt1,pt2,randColor(rng),rng.uniform(1,10));


    }
	return 0;
}


int randCircles(cv::Mat bild, cv::RNG rng, int cnt){
    for (int i = 0; i < cnt; ++i) {

        cv::Point pt(rng.uniform(1,WINDOWSIZEX),rng.uniform(1,WINDOWSIZEY));

        cv::circle(bild, pt,rng.uniform(1,WINDOWSIZEX/5),randColor(rng),rng.uniform(1,10), rng.uniform(1,8));
    }
	return 0;
}


int randEllipses(cv::Mat bild, cv::RNG rng, int cnt){
    for (int i = 0; i < cnt; ++i) {

        cv::Point pt(rng.uniform(1,WINDOWSIZEX), rng.uniform(1,WINDOWSIZEY));
        cv::Size sz(rng.uniform(1,WINDOWSIZEX/4), rng.uniform(1,WINDOWSIZEY/4));


        cv::ellipse(bild,pt,sz,rng.gaussian(360),rng.gaussian(360),rng.gaussian(360),randColor(rng),rng.uniform(1,15));

    }
	return 0;
}


int randPolylines(cv::Mat bild, cv::RNG rng, int cnt){
    for (int i = 0; i < cnt; ++i) {

        std::vector<cv::Point> points;

        for (int j = 0; j < rng.uniform(1,10); ++j) {
            points.emplace_back(cv::Point(rng.uniform(1,WINDOWSIZEX), rng.uniform(1,WINDOWSIZEY)));
        }

        cv::polylines(bild,points,true,randColor(rng),rng.uniform(1,15));
    }
	return 0;
}


int randPolygons(cv::Mat bild, cv::RNG rng, int cnt){
    for (int i = 0; i < cnt; ++i) {

        std::vector<cv::Point> points;
        std::vector<std::vector<cv::Point>> pointss;

        for (int j = 0; j < rng.uniform(2,10); ++j) {
            points.emplace_back(cv::Point(rng.uniform(1,WINDOWSIZEX), rng.uniform(1,WINDOWSIZEY)));
        }

        pointss.push_back(points);

        cv::fillPoly(bild, pointss, randColor(rng));


    }
	return 0;
}


