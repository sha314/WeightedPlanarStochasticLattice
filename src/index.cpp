//
// Created by shahnoor on 11/25/19.
//

#include <iostream>
#include "index.h"

using namespace std;

Link::Link(int node_a, int node_b) : node_a_{node_a}, node_b_{node_b} {
    if(node_b < node_a){
        node_a_ = node_b;
        node_b_ = node_a;
    }
    if(node_a == node_b){
        cerr << "self linking : Link::Link(int, int): line " << endl;
    }
}
