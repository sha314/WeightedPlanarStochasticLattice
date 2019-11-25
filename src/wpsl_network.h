//
// Created by shahnoor on 11/25/19.
//

#ifndef WEIGHTEDPLANARSTOCHASTICLATTICE_WPSL_NETWORK_H
#define WEIGHTEDPLANARSTOCHASTICLATTICE_WPSL_NETWORK_H


#include "wpsl.h"

/**
 * Construct a network while constructing WPSL
 */
class WPSL_Network : public WPSL{
    std::vector<int> networkMapA;
    std::vector<int> networkMapB;
    std::vector<std::vector<int>> _adjacency_list;

public:
    ~WPSL_Network() override = default;
    WPSL_Network();
    void reset() override;

    void addNode();

    void viewLinks();
    void viewAdjacencyList();
    void init() override;

    void seedNetwork();
    void addNeighbor(const Index &ll, const Index &ur);

    void addLink(int a, int b);
    bool is_neighbor(int node_a, int node_b);
};

#endif //WEIGHTEDPLANARSTOCHASTICLATTICE_WPSL_NETWORK_H
