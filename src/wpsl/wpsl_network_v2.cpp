//
// Created by shahnoor on 11/27/19.
//

#include "wpsl_network_v2.h"


#include <iostream>
#include <iomanip>


using namespace std;


WPSL_Network_v2::WPSL_Network_v2():WPSL() {
    init();
}

void WPSL_Network_v2::reset() {
    WPSL::reset();
    _links_.clear();
    init();
}

void WPSL_Network_v2::addNode() {
// randomly or preferentially select a box and divide it into four parts
//    size_t r = chooseIndexRandomly();
    size_t r = chooseIndexPreferentially();

    auto q = int(r);
    int i = getNode(q);
//    cout << "**********chosen node is " << i << endl;
    Index ll = getLowerLeft(i);
    Index ur = getUpperRight(i);

    auto n = randomIndex(ll, ur); // randomly selected new index in the box bounded by ll and ur

    // index is reused for new lower left box
    setLowerLeft(i, ll);
    setUpperRight(i, n);
    setArea(i, getArea(i));


    // lower right
    auto a_lr = addNeighbor(Index(n.getX(), ll.getY()), Index(ur.getX(), n.getY()));
    // upper right
    auto a_ur = addNeighbor(n, ur);
    // upper left
    auto a_ul = addNeighbor(Index(ll.getX(), n.getY()), Index(n.getX(), ur.getY()));

    auto old_neighbors = _adjacency_list[i]; // old neighbors of the recycleable node

    clearNode(i);
//    cout << "after clearing" << endl;
//    viewAdjacencyList();

    addLink(i, a_lr);
    addLink(i, a_ul);

    addLink(a_lr, a_ur);
    addLink(a_ur, a_ul);

//    cout << "after adding brand new nodes " << endl;
//    viewAdjacencyList();


    vector<int> new_nodes;
    new_nodes.emplace_back(a_lr);
    new_nodes.emplace_back(a_ur);
    new_nodes.emplace_back(a_ul);
    new_nodes.emplace_back(i);
    for(auto a: new_nodes){
//        cout << "a " << a << endl;
        for(auto b: old_neighbors){
//            cout << "b " << b << endl;
            if(is_neighbor(a, b)){
//                cout << "neighbors" << endl;
                addLink(a, b);
            }
        }
    }

}

void WPSL_Network_v2::viewLinks() {
    cout << "WPSL_Network_v2::viewLinks" << endl;
    cout << "Links are organised and not repeated : line " << __LINE__ << endl;
    int i=0;
    for(auto a: _links_){
        cout << "[" << setw(3) << i++ << "] " << a << endl;
    }

}

void WPSL_Network_v2::init() {
//    WPSL::init();
    seedNetwork();
}



void WPSL_Network_v2::seedNetwork() {

// randomly or preferentially select a box and divide it into four parts
//    size_t r = chooseIndexRandomly();
//    size_t r = chooseIndexPreferentially();
//    int i = getNode(r);
    int i = 0; // initially it can only be zero
    cout << "chosen node  " << i<< endl;
    Index ll = getLowerLeft(i);
    Index ur = getUpperRight(i);

    auto n = randomIndex(ll, ur); // randomly selected new index in the box bounded by ll and ur

    // index is reused for new lower left box
    setLowerLeft(i, ll);
    setUpperRight(i, n);
    setArea(i, getArea(i));

    // lower right
    auto a_lr = addNeighbor(Index(n.getX(), ll.getY()), Index(ur.getX(), n.getY()));
    // upper right
    auto a_ur = addNeighbor(n, ur);
    // upper left
    auto a_ul = addNeighbor(Index(ll.getX(), n.getY()), Index(n.getX(), ur.getY()));

    addLink(i, a_lr);
    addLink(i, a_ul);

    addLink(a_lr, a_ur);
    addLink(a_ur, a_ul);

}

void WPSL_Network_v2::addLink(int a, int b) {
    if(a == b) return;
    // node label with small numerical value will be node a
    _links_.emplace(Link(a, b));

    if(a >= _adjacency_list.size()) {
        _adjacency_list.resize(a+1);
    }
    if(b >= _adjacency_list.size()) {
        _adjacency_list.resize(b+1);
    }
    _adjacency_list[a].emplace(b);
    _adjacency_list[b].emplace(a);
}

void WPSL_Network_v2::viewAdjacencyList() {
    cout << "WPSL_Network_v2::viewAdjacencyList" << endl;
    for(size_t i{}; i < _adjacency_list.size(); ++i){
        cout << i << "(size=" << _adjacency_list[i].size() << ") :{";
        for(auto a: _adjacency_list[i]){
            cout << a << ",";
        }
        cout << "}" << endl;
    }
}

/**
 * Find if `node_a` and `node_b` are neighbor of each other using their coordinate and ranges
 * Non periodic version
 * @param node_a
 * @param node_b
 * @return
 */
bool WPSL_Network_v2::is_neighbor_non_periodic(int node_a, int node_b) {
    if(node_a == node_b){
        cout << "same node" << endl;
        return false;
    }
    auto lla = getLowerLeft(node_a);
    auto ura = getUpperRight(node_a);

    auto llb = getLowerLeft(node_b);
    auto urb = getUpperRight(node_b);
    // horizontal neighbor check
    if(ura.getX() == llb.getX() || urb.getX() == lla.getX()) {
        cout << "Horizontal :";
        if (ura.getY() <= urb.getY() || ura.getY() >= llb.getY()) {
            cout << "upper right of node " << node_a << " is within the range of node " << node_b << endl;
            return true;
        } else if (urb.getY() <= ura.getY() || urb.getY() >= lla.getY()) {
            cout << "upper right of node " << node_b << " is within the range of node " << node_a << endl;
            return true;
        }
    }
    // vertical neighbor check
    if(ura.getY() == llb.getY() || urb.getY() == lla.getY()) {
        cout << "Vertical :";
        if (ura.getX() <= urb.getX() || ura.getX() >= llb.getX()) {
            cout << "upper right of node " << node_a << " is within the range of node " << node_b << endl;
            return true;
        } else if (urb.getX() <= ura.getX() || urb.getX() >= lla.getX()) {
            cout << "upper right of node " << node_b << " is within the range of node " << node_a << endl;
            return true;
        }
    }

    return false;
}

/**
 * Find if `node_a` and `node_b` are neighbor of each other using their coordinate and ranges
 * Non periodic version
 * @param node_a
 * @param node_b
 * @return
 */
bool WPSL_Network_v2::is_neighbor(int node_a, int node_b) {
    if(node_a == node_b){
        cout << "same node" << endl;
        return false;
    }
    auto lla = getLowerLeft(node_a);
    auto ura = getUpperRight(node_a);

    auto llb = getLowerLeft(node_b);
    auto urb = getUpperRight(node_b);
    // horizontal neighbor check
    if(ura.getX() == llb.getX() || urb.getX() == lla.getX() || is_h_periodic(node_a, node_b)) {
//        cout << "Horizontal :";
        if (ura.getY() <= urb.getY() || ura.getY() >= llb.getY()) {
//            cout << "upper right of node " << node_a << " is within the range of node " << node_b << endl;
            return true;
        } else if (urb.getY() <= ura.getY() || urb.getY() >= lla.getY()) {
//            cout << "upper right of node " << node_b << " is within the range of node " << node_a << endl;
            return true;
        }
    }
    // vertical neighbor check
    if(ura.getY() == llb.getY() || urb.getY() == lla.getY() || is_v_periodic(node_a, node_b)) {
//        cout << "Vertical :";
        if (ura.getX() <= urb.getX() || ura.getX() >= llb.getX()) {
//            cout << "upper right of node " << node_a << " is within the range of node " << node_b << endl;
            return true;
        } else if (urb.getX() <= ura.getX() || urb.getX() >= lla.getX()) {
//            cout << "upper right of node " << node_b << " is within the range of node " << node_a << endl;
            return true;
        }
    }

    return false;
}

/**
 * Find if `node_a` and `node_b` are neighbor of each other using their coordinate and ranges
 * periodic version
 * only horizontal periodic case
 * @param node_a
 * @param node_b
 * @return
 */
bool WPSL_Network_v2::is_h_periodic(int node_a, int node_b) {
    if(node_a == node_b){
        cout << "same node" << endl;
        return false;
    }
    auto lla = getLowerLeft(node_a);
    auto ura = getUpperRight(node_a);

    auto llb = getLowerLeft(node_b);
    auto urb = getUpperRight(node_b);
    // horizontal neighbor check
    // one x coordinate is zero and other is 1 gives sum = 1
    if((ura.getX()+llb.getX()) == 1 || (lla.getX() + urb.getX()) == 1){
//        cout << "horizontally periodic" << endl;
        return true;
    }
    return false;
}

/**
 * Find if `node_a` and `node_b` are neighbor of each other using their coordinate and ranges
 * periodic version
 * only vertical periodic case
 * @param node_a
 * @param node_b
 * @return
 */
bool WPSL_Network_v2::is_v_periodic(int node_a, int node_b) {
    if(node_a == node_b){
        cout << "same node" << endl;
        return false;
    }
    auto lla = getLowerLeft(node_a);
    auto ura = getUpperRight(node_a);

    auto llb = getLowerLeft(node_b);
    auto urb = getUpperRight(node_b);
    // one x coordinate is zero and other is 1 gives sum = 1
    // vertical neighbor check
    if((lla.getY() + urb.getY()) == 1 || (llb.getY() + ura.getY())==1){
//        cout << "vertically periodic" << endl;
        return true;
    }
    return false;
}

/**
 * Clear node `label` from the adjacency list
 * @param label
 */
void WPSL_Network_v2::clearNode(int label) {
    auto neighbors = _adjacency_list[label];
    for(auto a: neighbors){
        _links_.erase(Link(a, label));
        _adjacency_list[a].erase(label);
    }
    _adjacency_list[label].clear();
}

void WPSL_Network_v2::linksFromAdjacencyList() {
    std::set<Link> links;
    for(size_t i{}; i < _adjacency_list.size(); ++i){
        auto a = int(i);
        for(auto b: _adjacency_list[i]){
            links.emplace(Link(a, b));
        }
    }
    int i=0;
    for(auto a: links){
        cout << "[" << setw(3) << i++ << "] " << a << endl;
    }
}
