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

public:
    ~WPSL_Network() override = default;
    WPSL_Network();
    void reset() override;

    void addNode();

};

#endif //WEIGHTEDPLANARSTOCHASTICLATTICE_WPSL_NETWORK_H
