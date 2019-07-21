//
// Created by martin on 24.04.19.
//
#include <iostream>
#include "../include/DisplayImage.h"
#include "../include/core_functionality.h"
#include "../include/random.h"
#include <string>

int main(int argc, char** argv ){

	std::string filePath;

	if (1 >= argc)
	{
		//Kein Argument übergeben
		filePath = "C:\\Users\\Martin\\Pictures\\bild.jpg";
	}
	else
	{
		filePath = argv[1];
	}


    //return color_reduction(argc, argv);
    //return mask_operations(argc, argv);

    //return basic_operations(argc, argv);
    //std::string path1,path2;
    //path1 = "/home/martin/Bilder/hirsch.jpg";
    //path2 = "/home/martin/Bilder/tempel.jpg";

    //blend2images(path1, path2, 0.4);

    //return image_transformation(argc, argv);
    //return drawing();
    //return drawRandomStuff();

    //diskreteFT(argc, argv);
    //diskreteFT(1, argv);

    //fileReader(argc, argv);
    //smoothing(filePath);
	diletation_eroding(filePath);

    //cv::waitKey();
}

