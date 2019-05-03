//
// Created by martin on 01.05.19.
//

#include "../include/core_functionality.h"
#include <opencv2/opencv.hpp>
#include <stdio.h>


int color_reduction(int argc, char** argv){

    if(argc < 3){
        std::cout << "Zu wenige Argumente übergeben, \"Name Bild Reduzierung\", Beispiel\n" << argv[0] << "test.jpg 10\n" << std::endl;
        return -1;
    }

    int devide = 0;
    std::stringstream s;
    s << argv[2];
    s >> devide;

    cv::Mat orginal;
    cv::Mat copy;
    orginal = cv::imread(argv[1], 1);

    if(orginal.empty()){
        std::cout << "Fehler beim Lesen der Datei" << std::endl;
        return -1;
    }

    orginal.copyTo(copy);

    //cv::namedWindow("Original bild",cv::WINDOW_AUTOSIZE);
    //cv::imshow("Original Bild", orginal);


    uchar lookuptable[255];
    for (int i = 0; i < 255; ++i) {
        lookuptable[i] = (uchar)(devide * (i / devide)) ;
    }

    auto time = (double)cv::getTickCount();
    double row, col;
    row = orginal.rows;
    col = orginal.cols * orginal.channels();

    if(orginal.isContinuous()){
        col = col * row;
        row = 1;
    }

    for (int j = 0; j < row; ++j) {
        auto* ptr = orginal.ptr<uchar>(j);

        for (int i = 0; i < col; ++i) {
            ptr[i] = lookuptable[ptr[i]];

        }


    }

    time = (cv::getTickCount() - time)/cv::getTickFrequency();
    std::cout << "Zeit eigene Fkt: " << time << std::endl;

    cv::namedWindow("Farb reduktion", cv::WINDOW_AUTOSIZE);
    cv::imshow("Farb reduktion", orginal);


    cv::Mat table(1, 256, CV_8U);
    uchar* p = table.ptr();
    for (int k = 0; k < 256; ++k) {
        p[k] = lookuptable[k];
    }


    time = (double)cv::getTickCount();
    cv::LUT(orginal,table,orginal);
    time = (cv::getTickCount() - time)/cv::getTickFrequency();
    std::cout << "Zeit CV-Fkt: " << time << std::endl;

    cv::namedWindow("Copy", cv::WINDOW_AUTOSIZE);
    cv::imshow("Copy", copy);


    cv::waitKey();

}


