#include <iostream>
#include "jitu-vai/wpsl-jitu.h"
#include "wpsl/wpsl.h"
#include "wpsl/wpsl_network.h"
#include "wpsl/wpsl_network_v2.h"
#include <random>

using namespace std;


void test_link_set(){
    set<Link> links;
    for(int i{}; i < 6; ++i) {
        for(int j{i+1}; j < 6; ++j) {
            links.emplace(Link(i, j));
        }
    }

    for(auto a: links){
        cout << a << endl;
    }

    links.erase(Link(0,1));

    for(auto a: links){
        cout << a << endl;
    }
}

void test_wpsl_network(){
    WPSL_Network wpslNetwork;

//    wpslNetwork.viewIndex();
//    wpslNetwork.viewLinks();
//    wpslNetwork.viewAdjacencyList();

//    wpslNetwork.is_neighbor(0, 1);
//    wpslNetwork.is_h_periodic(2, 1);

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
//    wpslNetwork.viewAdjacencyList();

    wpslNetwork.addNode();
    wpslNetwork.viewIndex();
    wpslNetwork.viewLinks();
    wpslNetwork.viewAdjacencyList();
    wpslNetwork.linksFromAdjacencyList();
}

void test_wpsl_network_v2(){
    WPSL_Network_v2 wpslNetwork;

//    wpslNetwork.viewIndex();
//    wpslNetwork.viewLinks();
//    wpslNetwork.viewAdjacencyList();

//    wpslNetwork.is_neighbor(0, 1);
//    wpslNetwork.is_h_periodic(2, 1);

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
//    wpslNetwork.viewAdjacencyList();

    wpslNetwork.addNode();
    wpslNetwork.viewIndex();
    wpslNetwork.viewLinks();
    wpslNetwork.viewAdjacencyList();
    wpslNetwork.linksFromAdjacencyList();
}

void test_wpsl(){
    WPSL wpsl;
//    wpsl.viewIndex();
//
//    wpsl.addPoint();
//    wpsl.viewIndex();
//    wpsl.totalArea();
//
//    wpsl.addPoint();
//    wpsl.viewIndex();
//    wpsl.totalArea();

//    wpsl.chooseIndexPreferentially();
    size_t limit = 1000;
    for(size_t t{}; t < 1000; ++t){
        wpsl.addPoint();
    }
    ofstream fout(wpsl.getClassName() + "_" + to_string(limit) + "_boxes.txt");
    fout << "#<lower left points><upper right points>" << endl;
    auto ll = wpsl.getLowerLeft();
    auto ur = wpsl.getUpperRight();
    for(size_t i{}; i <ll.size(); ++i){
        fout << ll[i] << '\t' << ur[i] << endl;
    }
    fout.close();
}

int main(int argc, char* argv[]) {
    std::cout << "Weighted Planner Stochastic Lattice (WPSL)" << std::endl;
//    srand(time(NULL));

//    main_jitu();

//    main_jitu_test();

    test_wpsl();
//    test_wpsl_network();
//    test_wpsl_network_v2();

//    test_link_set();


    return 0;
}