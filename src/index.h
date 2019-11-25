//
// Created by shahnoor on 11/25/19.
//

#ifndef WEIGHTEDPLANARSTOCHASTICLATTICE_INDEX_H
#define WEIGHTEDPLANARSTOCHASTICLATTICE_INDEX_H

#include <ostream>

class Index{
    double x_{}, y_{};
public:
    Index(double x, double y):x_{x}, y_{y}{}
    friend std::ostream& operator<<(std::ostream& os, const Index& index){
        return os << "(" << index.x_ << "," << index.y_ << ")";
    }
    double getX() const {return x_;}
    double getY() const {return y_;}
};

#endif //WEIGHTEDPLANARSTOCHASTICLATTICE_INDEX_H
