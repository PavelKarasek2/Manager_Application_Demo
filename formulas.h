#ifndef __formulas_h__
#define __formulas_h__

#include<iostream>
using namespace std;
#include <cmath>

double sum(const double d[], const int length);

double mean(const double d[], const int length);

double median(const double d[], const int len);

double mode(const double d[], const int len);

double standard_dev(const double d[], const int len);

double variance(const double d[], const int len);

int partition(double d[], int first, int last);

double* quickSort(double a[], int first, int last);

double lin_regression(double a[], double b[]);

void print_sorted_arr(double a[],const int len, ostream& os);

void get_data(double d[],const int len,ostream& os);

void print_to_file(double d[],const int len);

#endif