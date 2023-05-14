#ifndef __graph_h__
#define __graph_h__
#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include <cmath>
#include "ReadFile.h"


using namespace std;


//global variables
//int np[40][2]; //points in data set that would not appear on a 10x10 graph
//int y_scale = 1; //number data set had to be divided by to fit on a 10x10 graph
//int x_scale = 1;
//double data[40][40];//this needs to be dynamic at some point
//int adj_matrix[10][10] = {0}; //the adjacency matrix is 10x10. Each value in our mayrix corresponds to a position on the graph

class graph {
string text[11];
double* yaxis;
double* xaxis;
int size;
//int num_vals;
public:
graph(const double* x, const double* y, int s);

~graph();

void display_axis();

double highest_value_y() const;

double highest_value_x() const;

//void plot_adj(int y, int x);

void plot(int y, int x);

void graphing(ostream& os, const double* data1, const double* data2);

void read_text_data();

void display_text(ostream& os);

void y_axis();

void x_axis();

};


#endif
