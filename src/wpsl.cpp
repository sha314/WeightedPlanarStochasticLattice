//
// Created by shahnoor on 11/25/19.
//

#include <iostream>
#include "wpsl.h"

using namespace std;


WPSL::WPSL() {
    init();
}

void WPSL::init() {
    index_lower_left.emplace_back(Index(0, 0));
    index_upper_right.emplace_back(Index(1, 1));
    _node_label.emplace_back(0);
    _area.emplace_back(getArea(0));
}

void WPSL::viewIndex() {
    cout << "WPSL::viewIndex" << endl;
    cout << _node_label.size() << " elements" << endl;
    cout << "[label] => {(lower left)" << symbol << "(upper right)}, A=$Area" << endl;
    for(size_t i{}; i < _node_label.size(); ++i){
        cout << "[" << _node_label[i] << "] => " << "{"
             << index_lower_left[i] << symbol
             << index_upper_right[i] << "}  A="
             << _area[i]
             << endl;
    }
}

/**
 * Add new point to the lattice
 */
void WPSL::addPoint() {
//    add_point_v1();
    add_point_v2();

}

/**
 * Lower Left and Upper Right index is provided
 * @param ll
 * @param ur
 */
size_t WPSL::addNeighbor(const Index &ll, const Index &ur) {
    index_lower_left.emplace_back(ll);
    index_upper_right.emplace_back(ur);
    _area.emplace_back(getArea(_node_label.size()));
    _node_label.emplace_back(_node_label.size());
    return _node_label.size()-1;
}

double WPSL::getArea(size_t label) {
    Index ll = index_lower_left[label];
    Index ur = index_upper_right[label];
    double a = ll.getX() - ur.getX();
    double b = ll.getY() - ur.getY();
    return abs(a*b);
}

// give
/**
 * give a random Index inside a rectangle bounded by `ll` and `ur`
 * @param ll  : lower left index
 * @param ur  : upper right index
 * @return    : random Index inside a rectangle bounded by `ll` and `ur`
 */
Index WPSL::randomIndex(const Index &ll, const Index &ur) {
    uniform_real_distribution<double> dist1(ll.getX(), ur.getX());
    uniform_real_distribution<double> dist2(ll.getY(), ur.getY());
    double new_x = dist1(random_engine);
    double new_y = dist2(random_engine);
    return {new_x, new_y};
}

/**
 * preferentially select a box according to their area to divide it into four parts
 * @return
 */
size_t WPSL::chooseIndexPreferentially() {
    std::discrete_distribution<size_t> dist(_area.begin(), _area.end());

//    cout << "{";
//    for(auto a: dist.probabilities()){
//        cout << a << ", ";
//    }
//    cout << "}" << endl << "{";
//    vector<size_t> frequency(_area.size());
//    size_t limit  = 10000;
//    for(size_t i{}; i < limit; ++i) {
//        auto r = dist(random_engine);
//        cout << r << ",";
//        ++frequency[r];
//    }
//    cout << "}" << endl << "frequency {" << endl;
//    for(size_t i{}; i < frequency.size(); ++i) {
//        cout << frequency[i] << ",";
//        cout << frequency[i] / double(limit) << endl;
//    }
//    cout << "}" << endl;

    return dist(random_engine);
}

void WPSL::totalArea() {
    double total{};
    for(auto a: _area){
        total += a;
    }
    cout << "total area A= " << total << endl;
}

size_t WPSL::chooseIndexRandomly() {
    return random_engine() % _node_label.size();
}

void WPSL::add_point_v1() {
// randomly select a box and divide it into four parts
    size_t r = chooseIndexRandomly();
//    size_t r = chooseIndexPreferentially();

    size_t i = _node_label[r];
    Index ll = index_lower_left[i];
    Index ur = index_upper_right[i];

    auto n = randomIndex(ll, ur); // randomly selected new index in the box bounded by ll and ur

    // index is reused for new lower left box
    index_lower_left[i] = ll; // reuse space
    index_upper_right[i] = n; // reuse space
    _area[i] = getArea(i);

    // lower right
    index_lower_left.emplace_back(Index(n.getX(), ll.getY()));
    index_upper_right.emplace_back(Index(ur.getX(), n.getY()));
    _area.emplace_back(getArea(_node_label.size()));
    _node_label.emplace_back(_node_label.size());

    // upper right
    index_lower_left.emplace_back(n);
    index_upper_right.emplace_back(ur);
    _area.emplace_back(getArea(_node_label.size()));
    _node_label.emplace_back(_node_label.size());

    // upper left
    index_lower_left.emplace_back(Index(ll.getX(), n.getY()));
    index_upper_right.emplace_back(Index(n.getX(), ur.getY()));
    _area.emplace_back(getArea(_node_label.size()));
    _node_label.emplace_back(_node_label.size());
}

void WPSL::add_point_v2() {
// randomly select a box and divide it into four parts
    size_t r = chooseIndexRandomly();
//    size_t r = chooseIndexPreferentially();

    size_t i = _node_label[r];
    Index ll = index_lower_left[i];
    Index ur = index_upper_right[i];

    auto n = randomIndex(ll, ur); // randomly selected new index in the box bounded by ll and ur

    // index is reused for new lower left box
    index_lower_left[i] = ll; // reuse space
    index_upper_right[i] = n; // reuse space
    _area[i] = getArea(i);

    // lower right
    addNeighbor(Index(n.getX(), ll.getY()), Index(ur.getX(), n.getY()));
    // upper right
    addNeighbor(n, ur);
    // upper left
    addNeighbor(Index(ll.getX(), n.getY()), Index(n.getX(), ur.getY()));
}