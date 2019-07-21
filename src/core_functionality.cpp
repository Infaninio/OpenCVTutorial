//
// Created by martin on 01.05.19.
//

#define wSize 1000

#include "../include/core_functionality.h"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string>


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

    /*
     * Färben eines Bildes in Rot. Entscheident hier ist der Zugriff auf einzelne Pixelwerte.
     *
    cv::Vec3b farben;
    farben[0] = 0;
    farben[1] = 0;
    farben[2] = 255;

    for (int i = 0; i < img2.rows ; ++i) {
        for (int j = 0; j < img2.cols; ++j) {
            img2.at<cv::Vec3b>(i,j) = farben;
        }
    }
     */



    //std::cout << "Typ Grayscale: " << img1.type() << "\t Typ Klein: " << img2.type() << std::endl;
    //std::cout << CV_8UC1 << "\t" << CV_8UC3 << std::endl;

    cv::Sobel(img2, img3, CV_32F,1,0);

    //cv::imshow("Image 1", img1);
    cv::imshow("Image 2", img2);
    cv::imshow("Image 3", img3);


    cv::waitKey();

    return 1;

}

int image_transformation(int argc, char** argv){
    if(argc < 2){
        std::cout << "Zu wenig Argumente übergebn, bitte wie folgt aufrufen\n" << argv[0] << " /ordner/bild.jpg" << std::endl;
        return -1;
    }

    // Einlesen der Werte für die Helligkeits und Kontrast überarbeitung
    float alpha, beta, gamma;
    std::cout << "Bitte alpha-Wert eingeben: ";
    std::cin >> alpha;

    std::cout << "Bitte beta-Wert eingeben: ";
    std::cin >> beta;

    std::cout << "Bitte gamma-Wert eingeben: ";
    std::cin >> gamma;

    //Einlesen des Bildes
    cv::Mat src, dst1, dst2;
    src = cv::imread(argv[1],cv::IMREAD_COLOR);


    //Klassische Art und Weise, Pixel werte mit alpha multipliziern und beta addieren
    linearTransformation(src,dst1,alpha,beta);



    //Gamma überarbeitung des Bildes
    gammaTransformation(src,dst2,gamma);

    cv::imshow("Orginal", src);
    cv::imshow("Lineare Transformation", dst1);
    cv::imshow("Gamma Transformation", dst2);

    cv::waitKey();

    return 0;


}

int drawing(){
    cv::Mat atomImage = cv::Mat::zeros(wSize,wSize, CV_8UC3);
    cv::Mat turmImage = cv::Mat::zeros(wSize,wSize,CV_8UC3);

    cv::Point punkt(wSize/2, wSize/2);

    cv::circle(atomImage,punkt,wSize/25,cv::Scalar(0,0,255),cv::FILLED,cv::LINE_8);

    cv::ellipse(atomImage,punkt,cv::Size(wSize/4,wSize/16),0,0,360,cv::Scalar(255,0,0),5,cv::LINE_4);
    cv::ellipse(atomImage,punkt,cv::Size(wSize/4,wSize/16),45,0,360,cv::Scalar(0,255,0),5,cv::LINE_8);
    cv::ellipse(atomImage,punkt,cv::Size(wSize/4,wSize/16),-45,0,360,cv::Scalar(255,255,0),5,cv::LINE_AA);
    cv::ellipse(atomImage,punkt,cv::Size(wSize/4,wSize/16),90,0,360,cv::Scalar(0,255,0),5,cv::LINE_4);



    cv::Point turmArr[20];

    turmArr[0] = cv::Point(    wSize/4,   7*wSize/8 );
    turmArr[1]  = cv::Point(  3*wSize/4,   7*wSize/8 );
    turmArr[2]  = cv::Point(  3*wSize/4,  13*wSize/16 );
    turmArr[3]  = cv::Point( 11*wSize/16, 13*wSize/16 );
    turmArr[4]  = cv::Point( 19*wSize/32,  3*wSize/8 );
    turmArr[5]  = cv::Point(  3*wSize/4,   3*wSize/8 );
    turmArr[6]  = cv::Point(  3*wSize/4,     wSize/8 );
    turmArr[7]  = cv::Point( 26*wSize/40,    wSize/8 );
    turmArr[8]  = cv::Point( 26*wSize/40,    wSize/4 );
    turmArr[9]  = cv::Point( 22*wSize/40,    wSize/4 );
    turmArr[10] = cv::Point( 22*wSize/40,    wSize/8 );
    turmArr[11] = cv::Point( 18*wSize/40,    wSize/8 );
    turmArr[12] = cv::Point( 18*wSize/40,    wSize/4 );
    turmArr[13] = cv::Point( 14*wSize/40,    wSize/4 );
    turmArr[14] = cv::Point( 14*wSize/40,    wSize/8 );
    turmArr[15] = cv::Point(    wSize/4,     wSize/8 );
    turmArr[16] = cv::Point(    wSize/4,   3*wSize/8 );
    turmArr[17] = cv::Point( 13*wSize/32,  3*wSize/8 );
    turmArr[18] = cv::Point(  5*wSize/16, 13*wSize/16 );
    turmArr[19] = cv::Point(    wSize/4,  13*wSize/16 );

    const cv::Point* ppt[1] = {turmArr};
    int npt[1];
    *npt = 20;


    cv::fillPoly(turmImage, ppt,npt,1,cv::Scalar(255,255,255),cv::LINE_8);

    cv::rectangle(turmImage,cv::Point(0,7*wSize/8),cv::Point(wSize,wSize),cv::Scalar(0,130,130),cv::FILLED);



    cv::imshow("Atom", atomImage);
    cv::moveWindow("Atom", 200,200);
    cv::imshow("Turm", turmImage);
    cv::moveWindow("Turm",1300,200);

    cv::waitKey();

    return 0;
}

cv::Mat blend2images(std::string path1, std::string path2, float alpha){
    if (alpha < 0 || alpha >1){
        std::cout << "Alpha muss einen Wert zwischen 0 und 1 haben\nAngegebenr Wert: " << alpha << std::endl;
    }
    cv::Mat src1, src2, dst;
    src1 = cv::imread(path1);
    src2 = cv::imread(path2);

    cv::Size2i newSize;
    newSize.height = 1080;
    newSize.width = 1920;

    if(src1.empty()){
        std::cout << "Fehler beim Lesen der Datei: " << path1 << std::endl;
        return dst;
    } else if (src2.empty()){
        std::cout << "Fehler beim Lesen der Datei: " << path2 << std::endl;
    }

    cv::resize(src1, src1, newSize);
    cv::resize(src2,src2,newSize);

    cv::addWeighted(src1,alpha,src2,1-alpha,0,dst);

    cv::imshow("Übereinander Gelegte Bilder",dst);
    cv::waitKey();
    return dst;
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

cv::Mat linearTransformation(cv::Mat& src, cv::Mat& dst, float alpha, float beta){
    dst = cv::Mat::zeros(src.size(),src.type());


    cv::Mat lookupTable(1,256,CV_8U);

    uchar* p = lookupTable.ptr();

    for (int i = 0; i < 256; ++i) {
        p[i] = cv::saturate_cast<uchar>(alpha*i + beta);
    }

    cv::LUT(src,lookupTable,dst);

    return dst;
}


cv::Mat gammaTransformation(cv::Mat& src, cv::Mat& dst, float gamma){

    dst = cv::Mat::zeros(src.size(),src.type());


    cv::Mat lookupTable(1,256,CV_8U);

    uchar* p = lookupTable.ptr();

    for (int i = 0; i < 256; ++i) {
        p[i] = cv::saturate_cast<uchar>(cv::pow(i/255.0,gamma) * 255.0);
    }

    cv::LUT(src,lookupTable,dst);

    return dst;

}


int diskreteFT(int argc, char** argv){

    std::string filename;

    if(argc < 2){
        //std::cout << "Zu wenig übergabe Werte, bitte Pfad zu bild angeben: " << argv[0] << " ../test.jpg" << std::endl;
        //return -1;
        filename = "/home/martin/Bilder/sudoku.png";
    } else {

        filename = argv[1];
    }

    using namespace std;
    using namespace cv;



    Mat I = imread(filename, IMREAD_GRAYSCALE);
    if( I.empty()){
        cout << "Error opening image" << endl;
        return -1;
    }
    Mat padded;                            //expand input image to optimal size
    int m = getOptimalDFTSize( I.rows );
    int n = getOptimalDFTSize( I.cols ); // on the border add zero values
    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros
    dft(complexI, complexI);            // this way the result may fit in the source matrix
    // compute the magnitude and switch to logarithmic scale
    // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    Mat magI = planes[0];
    magI += Scalar::all(1);                    // switch to logarithmic scale
    log(magI, magI);
    // crop the spectrum, if it has an odd number of rows or columns
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
    // rearrange the quadrants of Fourier image  so that the origin is at the image center
    int cx = magI.cols/2;
    int cy = magI.rows/2;
    Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right
    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);
    normalize(magI, magI, 0, 1, NORM_MINMAX); // Transform the matrix with float values into a
    // viewable image form (float between values 0 and 1).
    imshow("Input Image" + argc       , I   );    // Show the result
    imshow("spectrum magnitude" + argc, magI);

    //waitKey();
    return 0;
}

int fileReader(int argc, char** argv){
    std::string filename = "/home/martin/test.yaml";

    cv::FileStorage file(filename, cv::FileStorage::WRITE);

    std::vector<std::string> filenames;
    filenames.push_back("/home/martin/Bilder/sudoku_gedreht.png");
    filenames.push_back("/home/martin/Bilder/hirsch.png");
    filenames.push_back("/home/martin/Bilder/tempel.jpg");

    file << "TestAttr" << "TRUE";
    file << "NextAttr" << "FALSE";

    file << "Files" << filenames;


    //auto bild = cv::imread(argv[1],cv::IMREAD_COLOR);

    //file << "BildMatrix" << bild;



    file.release();





    /*
     * Lesen
     */

    cv::FileStorage readfile;
    readfile.open(filename,cv::FileStorage::READ);

    std::string test;

    //Lesen eines einzelnen Attributs
    readfile["TestAttr"] >> test;
    std::cout << test << std::endl;


    cv::FileNode testnode = readfile["NextAttr"];

    if(!testnode.isSeq()){
        std::cout << (std::string)testnode;
    } else {
        std::cout << "NextAttr, schein eine Sequenz zu sein";
    }

    cv::FileNode node = readfile["Files"];

    if(!node.isSeq()){
        std::cout << "Attribute Files ist keine Sequenz";
        return -1;
    }

    cv::FileNodeIterator it = node.begin(), end = node.end();

    for (; it != end ; ++it) {
        std::cout << (std::string)*it << std::endl;
    }

    std::cout << (std::string)readfile["TestAttr"];

    std::cout << readfile["TestAttr"].empty();


    //cv::Mat neuesBild;

    //readfile["BildMatrix"] >> neuesBild;

    //cv::imshow("Yaml-Bild",neuesBild);


    readfile.release();

    cv::waitKey();


}



int smoothing(std::string path){

    cv::Mat original;
    original = cv::imread(path,cv::IMREAD_COLOR);

    if(original.empty()){
        std::cout << "Datei " << path << " konnte nicht gelesen werden. Abbruch" << std::endl;
    }

    cv::Mat smoothed;
    std::cout << "Bitte Smoothing Methode angeben, zur Auswahl stehen: \nblur, gaus, median, bilateral" << std::endl;

    std::string method;
    std::cin >> method;

    if(method == "blur"){
        cv::blur(original,smoothed,cv::Size(31,31));

    } else if (method == "gaus") {
        cv::GaussianBlur(original, smoothed, cv::Size(31,31),0,0);


    } else if (method == "median"){
        cv::medianBlur(original, smoothed,31);

    } else if (method == "bilateral"){
        cv::bilateralFilter(original,smoothed,31,62,16);

    } else {
        std::cout << "Als Methode wurde " << method << " angegeben, dies ist nicht möglich nur: \n";
        std::cout << "blur, gaus, median, bilateral" << std::endl;
        return -1;
    }


    cv::imshow("Bild",original);
    cv::imshow("Verändertes Bild", smoothed);

    cv::waitKey();

    return 0;

}


cv::Mat srcDilEro;

//Function which is called when one of the Trackbars (Diletation_Type or Diletation_Strength) has been changed.
void diletation_TB(int, void*) {
	int type, kernelSize;
	type = cv::getTrackbarPos("Diletation_Type", "Diletation");
	kernelSize = cv::getTrackbarPos("Diletation_Kernel_Size", "Diletation");

	switch (type)
	{
	case 0:
		type = cv::MORPH_RECT;
		break;
	case 1:
		type = cv::MORPH_ELLIPSE;
		break;
	case 2:
		type = cv::MORPH_CROSS;
		break;
	default:
		std::cout << "Fehler: Diletation Trackbar Wert zu groß";
		break;
	}
	cv::Mat dst;
	if (kernelSize < 1) {
		std::cout << "Warnung KernelSize darf nicht kleiner als 1 sein" << std::endl;
		kernelSize = 1;
	}

	cv::Mat kernel = cv::getStructuringElement(type, cv::Size(kernelSize, kernelSize));
	cv::dilate(srcDilEro, dst, kernel);

	cv::imshow("Diletation", dst);

}


//Function which is called when one of the Trackbars (Erosion_Type or Erosion_Strength) has been changed.
void erosion_TB(int, void*) {
	int type, kernelSize;
	type = cv::getTrackbarPos("Erosion_Type", "Erosion");
	kernelSize = cv::getTrackbarPos("Erosion_Kernel_Size", "Erosion");

	switch (type)
	{
	case 0:
		type = cv::MORPH_RECT;
		break;
	case 1:
		type = cv::MORPH_ELLIPSE;
		break;
	case 2:
		type = cv::MORPH_CROSS;
		break;
	default:
		std::cout << "Fehler: Erosion Trackbar Wert zu groß";
		break;
	}
	cv::Mat dst;
	if (kernelSize < 1) {
		std::cout << "Warnung KernelSize darf nicht kleiner als 1 sein" << std::endl;
		kernelSize = 1;
	}
	cv::Mat kernel = cv::getStructuringElement(type, cv::Size(kernelSize, kernelSize));
	cv::erode(srcDilEro, dst, kernel);

	cv::imshow("Erosion", dst);



}



int diletation_eroding(std::string path) {
	srcDilEro = cv::imread(path);

	if (srcDilEro.empty()) {
		std::cout << "Fehler beim laden der Datei:\n" << path << std::endl;
		return -1;
	}

	cv::resize(srcDilEro, srcDilEro, cv::Size(1080, 720));

	cv::namedWindow("Erosion", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Diletation", cv::WINDOW_AUTOSIZE);
	cv::moveWindow("Diletation", 1920, 0);

	int a = 0;
	int* pa = &a;


	//Trackbars for Diletation
	cv::createTrackbar("Diletation_Type", "Diletation", pa, 2, diletation_TB);
	cv::createTrackbar("Diletation_Kernel_Size", "Diletation", pa, 50, diletation_TB);


	//Trackbars for Erosion
	cv::createTrackbar("Erosion_Type", "Erosion", pa, 2, erosion_TB);
	cv::createTrackbar("Erosion_Kernel_Size", "Erosion", pa, 50, erosion_TB);


	cv::waitKey();




}




