//
// Created by shahnoor on 11/27/19.
//

#ifndef WEIGHTEDPLANARSTOCHASTICLATTICE_WPSL_NETWORK_V2_H
#define WEIGHTEDPLANARSTOCHASTICLATTICE_WPSL_NETWORK_V2_H


#include <set>
#include <vector>
#include "../index/index.h"
#include "wpsl.h"

/**
 * Construct a network while constructing WPSL
 * Additional to WPSL_v1
 *      1. Links are organized in an accending order
 *      2. Nor possibility of repeated links since std::set is used instead of std::vector
 */
class WPSL_Network_v2 : public WPSL{
    std::set<Link> _links_;

    /**
     * We need to be able to add and remove elements within the list.
     * Using set makes it easier to find element by value, unlike vector, not by index
     */
    std::vector<std::set<int>> _adjacency_list;

public:
    ~WPSL_Network_v2() override = default;
    WPSL_Network_v2();
    void reset() override;

    void addNode();
    void clearNode(int label);

    void viewLinks();
    void viewAdjacencyList();
    void init() override;

    void seedNetwork();

    void addLink(int a, int b);
    bool is_neighbor(int node_a, int node_b);
    bool is_neighbor_non_periodic(int node_a, int node_b);
    bool is_h_periodic(int node_a, int node_b);
    bool is_v_periodic(int node_a, int node_b);

    void linksFromAdjacencyList();
};


#endif //WEIGHTEDPLANARSTOCHASTICLATTICE_WPSL_NETWORK_V2_H
