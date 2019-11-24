//
// Created by shahnoor on 11/24/19.
//

#ifndef WEIGHTEDPLANARSTOCHASTICLATTICE_VIEW_H
#define WEIGHTEDPLANARSTOCHASTICLATTICE_VIEW_H

#include <vector>
#include <iostream>

template <typename Ttype>
void print(std::vector<Ttype> &v) {
    std::cout << "1D vector {" << std::endl;
    for(size_t i{}; i < v.size(); ++i){
        std::cout << v[i] << ",";
    }
    std::cout << "}" << std::endl;
}

template <typename Ttype>
void print(std::vector<std::vector<Ttype>> &vv) {
    std::cout << "2D vector {" << std::endl;
    for(size_t i{}; i < vv.size(); ++i){
        std::cout << "{";
        for(size_t j{}; j < vv[0].size(); ++j) {
            std::cout << vv[i][j] << ",";
        }
        std::cout << "}" << std::endl;
    }
    std::cout << "}" << std::endl;
}


template <typename Ttype>
void print_coordinate(std::vector<std::vector<Ttype>> &vv1, std::vector<std::vector<Ttype>> &vv2) {
    std::cout << "coordinate (x,y) : {" << std::endl;
    for(size_t i{}; i < vv1.size(); ++i){
        std::cout << "{";
        for(size_t j{}; j < vv1[0].size(); ++j) {
            std::cout << "(" << vv1[i][j] << "," << vv2[i][j] << ")";
        }
        std::cout << "}" << std::endl;
    }
    std::cout << "}" << std::endl;
}

#endif //WEIGHTEDPLANARSTOCHASTICLATTICE_VIEW_H
