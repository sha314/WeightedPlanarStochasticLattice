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


class Link{
    // node_a must be smaller than node_b
    int node_a_{-1}, node_b_{-1};
public:
    ~Link()  = default;
    Link() = default;
    Link(int node_a, int node_b);

    friend std::ostream& operator<<(std::ostream& os, const Link& lnk){
        return os << "(" << lnk.node_a_ << " <-> " << lnk.node_b_<< ")";
    }

    /**
     * Since node_a is smaller by construction,
     * @param lnk
     * @return
     */
    bool operator < (const Link& lnk) const{
        if(this->node_a_ == lnk.node_a_) {
            if(this->node_b_ < lnk.node_b_){
                return true;
            }
        }

        return (this->node_a_ < lnk.node_a_);
    }

    int nodeA() const {return node_a_;}
    int nodeB() const {return node_b_;}
};

#endif //WEIGHTEDPLANARSTOCHASTICLATTICE_INDEX_H
