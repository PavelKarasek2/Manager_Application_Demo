#include<iostream>
#include<fstream>
#include <cmath>
#include "formulas.h"
using namespace std;

    double sum(const double d[], const int length){
        double sum = 0;
        for(int  i = 0; i < length; i++){
            sum += d[i];
        }
        return sum;
    }

    double mean(const double d[], const int length) {
        double total = 0;
        double mean;
        for (int i = 0; i < length; i++) {
            total = total + d[i];
        }
        mean = total/length;

        return mean;
    }

    double median(const double d[], const int len) {
        double median;
        if (len%2 == 0) {
            median = (d[(len)/2] + d[(len)/2-1])/2;
            return median;
        } else {
            median = (d[len/2]);
            return median;
        }
    }

    double mode(const double d[], const int len) {
        double number = d[0];
        double mode = number;
        int count = 1;
        int countMode = 1;

        for (int i=1; i<len; i++) {
            if (d[i] == number) { // count occurrences of the current number
            ++count;
            } else { // now this is a different number
                if (count > countMode) {
                  countMode = count; // mode is the biggest ocurrences
                  mode = number;
                }
                count = 1; // reset count for the new number
                number = d[i];
            }    
        }

        if (1 == count) {
            return 0;
        } else {
            return mode;
        }
        
    }

    double standard_dev(const double d[], const int len) {
        double stand_dev = 0;
        double mn;
        mn = mean(d,len);
        for (int i = 0; i < len; i++) {
            stand_dev += (d[i]-mn) * (d[i]-mn);
        }

        return sqrt(stand_dev/(len-1));
    }

    double variance(const double d[], const int len) {
        double v;
        v = standard_dev(d, len)*standard_dev(d, len); 
        return v;
    }

    int partition(double d[], int first, int last) {
        int pivotvalue = d[first];

        int rightmark = last;
        int leftmark = first+1;

        bool done = false;

        while(not done){
            while(leftmark<=rightmark && d[leftmark]<=pivotvalue){
                leftmark++;
            }
            while(rightmark>=leftmark && d[rightmark]>=pivotvalue){
                rightmark--;
            }
            if(rightmark<leftmark){
                done = true;
            } else{
                swap(d[rightmark], d[leftmark]);
            }
        }   

        swap(d[rightmark], d[first]);

        return rightmark;
    }
    
    double* quickSort(double a[], int first, int last) {
        int splitpoint;

        if (first<last) {
            splitpoint = partition(a,first,last); //divide array in 2
            quickSort(a,first,splitpoint-1); //sort array values before splitpoint
            quickSort(a,splitpoint+1,last); //sort array values after splitpoint

        }
        return a;
    }

    void print_sorted_arr(double a[],const int len, ostream& os){
        double* b = quickSort(a,0,len-1); 
        for(int i = 0; i < len; i++){
            os << b[i] << " ";
        }
        os << endl;
    }

    void get_data(double d[],const int len,ostream& os){
        
        os << "The sum of your data is " << sum(d,len) << endl;
        os << "The mean of your data is " << mean(d,len) << endl;
        os << "The median of your data is " << median(d,len) << endl;
        os << "The mode of your data is " << mode(d, len) << endl;
        os << "The standard deviation of your data is " << standard_dev(d,len) << endl;
        os << "sorted data: "; print_sorted_arr(d,len,os); os << endl;  
        
    } 

