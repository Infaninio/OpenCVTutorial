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

    /*
     * Char in Zahl umwandeln, C++ Style
     */
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

    /*
     * Bibliotheks Funktion, muss aber auch mit LookUpTable gefüttert werden
     *
    time = (double)cv::getTickCount();
    cv::LUT(orginal,table,orginal);
    time = (cv::getTickCount() - time)/cv::getTickFrequency();
    std::cout << "Zeit CV-Fkt: " << time << std::endl;

    cv::namedWindow("Copy", cv::WINDOW_AUTOSIZE);
    cv::imshow("Copy", copy);
    */

    cv::waitKey();

}

int mask_operations(int argc, char** argv){


    if(argc < 2){
        std::cout << "Es wurden zu wenig Argumente übergeben, Aufruf: " << argv[0] << " Bildpfad.jpg" << std::endl;
        return -1;
    }

    cv::Mat bild, bildn;
    bild = cv::imread(argv[1]);

    if(bild.empty())
    {
        std::cout << "Fehler beim Lesen der Datei: " << argv[1] << std::endl;
        return -1;
    }

    /*
     * Eigene Funktion wird aufgerufen
     * Bei uns wird keine individuelle Matrix übergeben
     */
    sharpen(bild, bildn);


    cv::namedWindow("Bild", cv::WINDOW_AUTOSIZE);
    cv::imshow("Bild", bildn);
    cv::imshow("Orginal", bild);

    /*
     * OpenCV Funktion
     */
    cv::Mat Mask = (cv::Mat_<char>(3,3) << 0,-1,0,
                                            -1,5,-1,
                                            0,-1,0);

    cv::filter2D(bild, bildn, bild.depth(), Mask);

    cv::imshow("Bild2", bildn);




    cv::waitKey();

    return 0;



}

int basic_operations(int argc, char** argv){

    if(argc < 2){
        std::cout << "Es wurden zu wenig Argumente übergeben. Bitte Dateipfad als ersten Paramter übergeben\n";
        std::cout << "Beispiel:\t DisplayImage ~/Bilder/test.jpg" << std::endl;
        return -1;
    }



    cv::Mat img1, img2, img3;

    /*
     * IMREAD_GRAYSCALE = Lädt das Bild in grauen Farbstufen
     * IMREAD_REDUCED_COLOR_X = Verkleinert das gelesen Bild um den angegeben Faktor
     *          X = 2 || 4 || 8
     *
     */
    img1 = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    img2 = cv::imread(argv[1], cv::IMREAD_REDUCED_COLOR_2);

    /*
     * Speicher eines Bildes
     */
    //cv::imwrite("/home/martin/Bilder/test.jpg", img2);


    if(img1.empty() || img2.empty()){
        std::cout << "Fehler beim Lesen der Datei";
        return -2;
    }






    cv::imshow("Image 1", img1);
    cv::imshow("Image 2", img2);

    cv::waitKey();

    return 1;

}

cv::Mat* sharpen(cv::Mat& input, cv::Mat& output){
    CV_Assert(input.depth() == CV_8U);

    output.create(input.size(), input.type());

    int nChannels = input.channels();

    for (int i = 1; i < input.rows - 1; ++i) {
        uchar* previous = input.ptr(i - 1);
        uchar* current = input.ptr(i);
        uchar* next = input.ptr(i + 1);
        uchar* out = output.ptr(i);

        for (int j = nChannels; j < (input.cols * nChannels) - nChannels; ++j) {
            out[j] = cv::saturate_cast<uchar>( 5*current[j] - current[j-nChannels] - current[j+nChannels] - previous[j] - next[j]);
        }

    }

    output.row(0).setTo(cv::Scalar(0));
    output.row(output.rows - 1).setTo(cv::Scalar(0));

    output.col(0).setTo(cv::Scalar(0));
    output.col(output.cols - 1).setTo(cv::Scalar(0));

    return &output;

}




