//
// Created by shahnoor on 11/25/19.
//

#ifndef WEIGHTEDPLANARSTOCHASTICLATTICE_WPSL_H
#define WEIGHTEDPLANARSTOCHASTICLATTICE_WPSL_H

#include <vector>
#include <random>
#include "../index/index.h"

/**
 *
 */
class WPSL{
    std::vector<Index> index_lower_left;
    std::vector<Index> index_upper_right;
    std::vector<int> _node_label;
    std::vector<double > _area;
//    const string symbol = " _< ^> ";
    const std::string symbol = " to ";

    std::mt19937 random_engine; // Mersenne Twister 19937 generator (class )
//    std::mt19937_64 random_engine_64; // Mersene Twister 19937 generator (64 bit) (class )
    size_t random_state{};
private:




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
        init();
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


    virtual int addNeighbor(const Index &ll, const Index &ur);

    virtual void init();

    int getNode(int i) const {return _node_label[i];}
    Index getUpperRight(int label) const {return index_upper_right[label];}
    Index getLowerLeft(int label) const {return index_lower_left[label];}
    void setUpperRight(int label, Index in) {index_upper_right[label] = in;}
    void setLowerLeft(int label, Index in)  {index_upper_right[label] = in;}

    void addUpperRight(Index in) {index_upper_right.emplace_back(in);}
    void addLowerLeft(Index in)  {index_upper_right.emplace_back(in);}

    size_t chooseIndexRandomly();
    size_t chooseIndexPreferentially();
    double getArea(int label);
    void setArea(int label, double A)  {_area[label] = A;}
    void addArea(double A){_area.emplace_back(A);}
    Index randomIndex(const Index &ll, const Index &ur);
    size_t nodeCount() const {return _node_label.size();}
    size_t addNodeLabel(){_node_label.emplace_back(_node_label.size()); return _node_label.size()-1;}
    std::string getClassName() const { return  "WPSL";}
    std::vector<Index> getUpperRight() const {return index_upper_right;}
    std::vector<Index> getLowerLeft() const {return index_lower_left;}
};

#endif //WEIGHTEDPLANARSTOCHASTICLATTICE_WPSL_H
