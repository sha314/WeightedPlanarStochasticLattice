//
// Created by shahnoor on 11/25/19.
//

#ifndef WEIGHTEDPLANARSTOCHASTICLATTICE_WPSL_NETWORK_H
#define WEIGHTEDPLANARSTOCHASTICLATTICE_WPSL_NETWORK_H


#include <set>
#include "wpsl.h"

/**
 * Construct a network while constructing WPSL
 */
class WPSL_Network : public WPSL{
    std::vector<int> networkMapA;
    std::vector<int> networkMapB;

    /**
     * We need to be able to add and remove elements within the list.
     * Using set makes it easier to find element by value, unlike vector, not by index
     */
    std::vector<std::set<int>> _adjacency_list;

public:
    ~WPSL_Network() override = default;
    WPSL_Network();
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
};

#endif //WEIGHTEDPLANARSTOCHASTICLATTICE_WPSL_NETWORK_H
