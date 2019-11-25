//
// Created by shahnoor on 11/24/19.
//

/******
 * Originally Written by
 * Zahidul Islam Jitu vai
 */
#ifndef WEIGHTEDPLANARSTOCHASTICLATTICE_WPSL_JITU_H
#define WEIGHTEDPLANARSTOCHASTICLATTICE_WPSL_JITU_H

#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <sstream>
#include <string.h>


void remove_neighbor(std::vector<std::vector<int> > &neighbor, int i, int j) ;

void add_neigbor(std::vector<std::vector<int> > &neighbor, int i, int j) ;

//this evaluates whether x<z<y
bool is_it_between(double x, double y, double z);

bool is_neighbor(std::vector<std::vector<double> > x_lim, std::vector<std::vector<double> > y_lim, int site1, int site2);

void
generate_new_site(std::vector<std::vector<int> > &neighbor,
                  std::vector<std::vector<double> > &x_lim,
                  std::vector<std::vector<double> > &y_lim,
                  int site, double x_new, double y_new) ;

int find_site(std::vector<std::vector<double> > x_lim, std::vector<std::vector<double> > y_lim, double x_new, double y_new) ;
//Another testing function
double my_rand();

void neighbor_init(std::vector<std::vector<int> > &neighbor,
                   std::vector<std::vector<double> > &x_lim,
                   std::vector<std::vector<double> > &y_lim) ;

//this is a testing function
void test_neighbor_init(std::vector<std::vector<int> > &neighbor);
//testing parameter starts here

double x_cube(std::vector<std::vector<double> > x_lim);
double moments(std::vector<std::vector<double> > x_lim, std::vector<std::vector<double> > y_lim, double n) ;
//this function is for testing purpose
//delete it if you plan to use it as module
int main_jitu();
void main_jitu_test();
#endif //WEIGHTEDPLANARSTOCHASTICLATTICE_WPSL_H
