#include <iostream>
#include<fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include "ReadFile.h"
#include "graph.h"


using namespace std;


//double data1[] = {100,200,300,400,500,600,700,800,900,1000};//X values
//double data2[] = {1,2,3,4,5,6,7,8,9,10};//Y values
//double data1[] = {1, 6};
//double data2[] = {2,4};

graph::graph(const double* x, const double* y, int s):size(s){
    xaxis = new double[size];
    yaxis = new double[size];
    for(int i = 0; i < size; i++){
        xaxis[i] = x[i];
        yaxis[i] = y[i];
    }
    read_text_data();
}

graph::~graph() {
    delete [] xaxis;
    delete [] yaxis;
}

void graph::display_axis() {
    for (int i = 0; i < size; i++) {
        cout << "x value is " << xaxis[i] << ", ";
        cout << "y value is " << yaxis[i] << endl;
    }
    //cout << "finished display" << endl;
} //used for finding values

void graph::plot(int y, int x) {
    //cerr << x << ", " << y << endl;

    //cerr << text[10-y]<< endl;
    /*if (0 == x) {
        text[10-y].replace(0,1,"."); //specifically for plotting 0s
    } else {
        text[10-y].replace(1+(3*x),1,".");// I changed this to match the cerr above it. Fixed. TM
    }*/
    text[10-y].replace(1+(3*x),1,".");
}


//void graph::plot_adj(int y, int x) {
   //adj_matrix[y][x] = 1;
   //plot(y,x);
//}

double graph::highest_value_x()const{
    double highest = 0;
    for(int i = 0; i < size; i++){
        if(xaxis[i] > highest){
            highest = xaxis[i];
        }
    }
    return highest;
}

double graph::highest_value_y()const{
    double highest = 0;
    for(int i = 0; i < size; i++){
        //cerr << "y axis value" << yaxis[i] << endl;
        if(yaxis[i] > highest){
            highest = yaxis[i];
        }
    }
 //   cerr << "highest" << highest << endl;
    //cerr << "y highest" << highest << endl;
    return highest;
}

void graph::graphing(ostream& os,const double* data1, const double* data2) {
   double row;
   double column;
   double y_multiplier = (10/highest_value_y());
   //cerr << "y multiplier" << y_multiplier << endl;
   double x_multiplier = (10/highest_value_x());
   //cerr << "x multiplier " << x_multiplier << endl;

    //cerr << "size " << size << endl;
   for (int i = 0; i < size; i++) {//these might not correlate with the rows and columns in ReadFile. TM
   
        row = round(data2[i]*y_multiplier);//size-i
        //cerr << "row " << row << endl;
        //cerr << "unrounded "<< data1[i] << ", " << data2[i] << endl;
        column = round(data1[i]*x_multiplier);
        //cerr << "column " << column << endl;
//        row = data1[i];

        //cerr << i << endl;
        plot(row, column);
    }

    display_text(os);
}


void graph::read_text_data() {
    ifstream fs("graph.txt");
    //fs.get();
    for (int i = 0; i < 11; ++i) {
        getline(fs, text[i]);     //might cause issues - we might be popping the char before endl
        if (!text[i].empty()) {
            text[i].pop_back();
        }
        //os << text[i] << endl;
    }
}


void graph::display_text(ostream& os) {
   for (int i = 0; i < 11; i++) { 
       os << text[i] << endl;
   }
}






void graph::y_axis() {
   double multiplier = (10/highest_value_y());
   
   for (int i = 0; i < size; i++) {
       yaxis[i] *= multiplier;
   }
   //return vals;
}


void graph::x_axis() {
   double multiplier = (10/highest_value_x());
   
   for (int i = 0; i < size; i++) {
       xaxis[i] *= multiplier;
       //xaxis[i] = 
   }
}



