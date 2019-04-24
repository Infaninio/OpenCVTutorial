//
// Created by martin on 24.04.19.
//
#include <iostream>
#include "../include/DisplayImage.h"

int main(int argc, char** argv ){

    if(argc == 1){
        std::cout << "Es wurden nicht genug argumente übergeben.\n Beispiel: " << argv[0] << " test.jpg\n";
        return -1;
    }


    return displayImage(argc, argv);



}
