//
// Created by shahnoor on 11/25/19.
//

#include <iostream>
#include "wpsl_network.h"


using namespace std;


WPSL_Network::WPSL_Network():WPSL() {
    init();
}

void WPSL_Network::reset() {
    WPSL::reset();
    networkMapA.clear();
    networkMapB.clear();
    init();
}

void WPSL_Network::addNode() {
// randomly or preferentially select a box and divide it into four parts
    size_t r = chooseIndexRandomly();
//    size_t r = chooseIndexPreferentially();

    unsigned i = getNode(r);
    Index ll = getLowerLeft(i);
    Index ur = getUpperRight(i);

    auto n = randomIndex(ll, ur); // randomly selected new index in the box bounded by ll and ur

    // index is reused for new lower left box
    setLowerLeft(i, ll);
    setUpperRight(i, n);
    setArea(i, getArea(i));

    // lower right
    addNeighbor(Index(n.getX(), ll.getY()), Index(ur.getX(), n.getY()));
    // upper right
    addNeighbor(n, ur);
    // upper left
    addNeighbor(Index(ll.getX(), n.getY()), Index(n.getX(), ur.getY()));

    auto old_neighbors = _adjacency_list[i]; // old neighbors of the recycleable node

    // TODO
    // some links will be replaced and some new links will be created

    addLink(1, 2);
    addLink(1, 4);

    addLink(2, 3);
    addLink(3, 4);
}

void WPSL_Network::viewLinks() {
    cout << "WPSL_Network::viewLinks" << endl;
    for(size_t i{}; i < networkMapA.size(); ++i){
        cout << "[" << i << "]  " << networkMapA[i] << " <-> " << networkMapB[i] << endl;
    }
}

void WPSL_Network::init() {
//    WPSL::init();
    seedNetwork();
}

/**
 * Lower Left and Upper Right index is provided
 * @param ll
 * @param ur
 */
void WPSL_Network::addNeighbor(const Index &ll, const Index &ur) {
    addLowerLeft(ll);
    addUpperRight(ur);
    addArea(getArea(nodeCount()));
    addNodeLabel();
}

void WPSL_Network::seedNetwork() {

// randomly or preferentially select a box and divide it into four parts
    size_t r = chooseIndexRandomly();
//    size_t r = chooseIndexPreferentially();

    unsigned i = getNode(r);
    Index ll = getLowerLeft(i);
    Index ur = getUpperRight(i);

    auto n = randomIndex(ll, ur); // randomly selected new index in the box bounded by ll and ur

    // index is reused for new lower left box
    setLowerLeft(i, ll);
    setUpperRight(i, n);
    setArea(i, getArea(i));

    // lower right
    addNeighbor(Index(n.getX(), ll.getY()), Index(ur.getX(), n.getY()));
    // upper right
    addNeighbor(n, ur);
    // upper left
    addNeighbor(Index(ll.getX(), n.getY()), Index(n.getX(), ur.getY()));

    addLink(0, 1);
    addLink(0, 3);

    addLink(1, 2);
    addLink(2, 3);

}

void WPSL_Network::addLink(int a, int b) {
    if(a == b) return;
    if(a < b) {
        // node label with small numerical value will be node a
        networkMapA.emplace_back(a);
        networkMapB.emplace_back(b);
    }else{
        networkMapA.emplace_back(b);
        networkMapB.emplace_back(a);
    }
    if(a >= _adjacency_list.size()) {
        _adjacency_list.resize(a+1);
    }
    if(b >= _adjacency_list.size()) {
        _adjacency_list.resize(b+1);
    }
    _adjacency_list[a].emplace_back(b);
    _adjacency_list[b].emplace_back(a);
}

void WPSL_Network::viewAdjacencyList() {
    cout << "WPSL_Network::viewAdjacencyList" << endl;
    for(size_t i{}; i < _adjacency_list.size(); ++i){
        cout << i << " :{";
        for(size_t j{}; j < _adjacency_list[i].size(); ++j){
            cout << _adjacency_list[i][j] << ",";
        }
        cout << "}" << endl;
    }
}
