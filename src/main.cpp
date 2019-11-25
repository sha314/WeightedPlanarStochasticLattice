#include <iostream>
#include "jitu-vai/wpsl-jitu.h"
#include "wpsl.h"
#include "wpsl_network.h"
#include <random>

using namespace std;




void test_wpsl_network(){
    WPSL_Network wpslNetwork;

    wpslNetwork.viewIndex();
    wpslNetwork.viewLinks();
    wpslNetwork.addNode();
}

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

//    test_class();
    test_wpsl_network();


    return 0;
}