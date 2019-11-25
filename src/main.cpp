#include <iostream>
#include "jitu-vai/wpsl-jitu.h"
#include "wpsl.h"
#include <random>

using namespace std;






void test_class(){
    WPSL wpsl;
    wpsl.viewIndex();

    wpsl.addPoint();
    wpsl.viewIndex();
    wpsl.totalArea();

    wpsl.addPoint();
    wpsl.viewIndex();
    wpsl.totalArea();

    wpsl.chooseIndexPreferentially();
}

int main(int argc, char* argv[]) {
    std::cout << "Hello, World!" << std::endl;
//    srand(time(NULL));

//    main_jitu();

//    main_jitu_test();

    test_class();


    return 0;
}