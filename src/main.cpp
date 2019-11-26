#include <iostream>
#include "jitu-vai/wpsl-jitu.h"
#include "wpsl.h"
#include "wpsl_network.h"
#include <random>

using namespace std;




void test_wpsl_network(){
    WPSL_Network wpslNetwork;

//    wpslNetwork.viewIndex();
//    wpslNetwork.viewLinks();
    wpslNetwork.viewAdjacencyList();

//    wpslNetwork.is_neighbor(0, 1);
    wpslNetwork.is_h_periodic(2, 1);

//    for(int a{}; a < 4; ++a) {
//        cout << a << " ";
//        for(int b{}; b < 4; ++b) {
//            cout << b << " ";
//            if (wpslNetwork.is_neighbor(a, b)) {
//                cout << " are neighbors" << endl;
//            }else{
//                cout << " are not" << endl;
//            }
//        }
//    }

    wpslNetwork.addNode();
//    wpslNetwork.viewIndex();
//    wpslNetwork.viewLinks();
    wpslNetwork.viewAdjacencyList();

    wpslNetwork.addNode();
//    wpslNetwork.viewIndex();
//    wpslNetwork.viewLinks();
    wpslNetwork.viewAdjacencyList();
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
    std::cout << "Weighted Planner Stochastic Lattice (WPSL)" << std::endl;
//    srand(time(NULL));

//    main_jitu();

//    main_jitu_test();

//    test_class();
    test_wpsl_network();


    return 0;
}