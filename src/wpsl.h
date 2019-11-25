//
// Created by shahnoor on 11/25/19.
//

#ifndef WEIGHTEDPLANARSTOCHASTICLATTICE_WPSL_H
#define WEIGHTEDPLANARSTOCHASTICLATTICE_WPSL_H

#include <vector>
#include <random>
#include "index.h"

/**
 *
 */
class WPSL{
    std::vector<Index> index_lower_left;
    std::vector<Index> index_upper_right;
    std::vector<unsigned> _node_label;
    std::vector<double > _area;
//    const string symbol = " _< ^> ";
    const std::string symbol = " to ";

    std::mt19937 random_engine; // Mersenne Twister 19937 generator (class )
//    std::mt19937_64 random_engine_64; // Mersene Twister 19937 generator (64 bit) (class )
    size_t random_state{};
private:
    double getArea(size_t label);
    Index randomIndex(const Index &ll, const Index &ur);

    size_t chooseIndexRandomly();

    void add_point_v1();
    void add_point_v2();
public:
    WPSL();

    virtual ~WPSL() = default;

    virtual void reset(){
        index_lower_left.clear();
        index_upper_right.clear();
        _node_label.clear();
        _area.clear();
    }

    void setRandomState(size_t rs, bool a){
        random_state = rs;
        if(a) {
            std::random_device r;
            random_state = r();
        }
        random_engine.seed(random_state);
    }

    void viewIndex();
    void addPoint();
    void totalArea();

    size_t chooseIndexPreferentially(); // to be declared private
    void addNeighbor(const Index &ll, const Index &ur);
};

#endif //WEIGHTEDPLANARSTOCHASTICLATTICE_WPSL_H
