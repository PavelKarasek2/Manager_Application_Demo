#ifndef __ReadFile_h__
#define __ReadFile_h__
#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include <cmath>
#include "ReadFile.h"
#include "formulas.h"

using namespace std;

//const char* get_str();

class ReadFile{
  
public:        //this is not right, state variables should be encapsulated. That is why we have getters 
  vector<string> title; 

  //changed this to be a pointer         
  double** data;//this needs to be dynamic at some point
  
  //Lets assume there is only x and y values eh? We did not get even close to anything else anyways
  
  //added this
  int size;

  //ReadFile(const char type);
  
  int get_num_imported(const char* file_name); //it seems to me we are compiling this same function unnecessarily twice. Not a problem for now but writing it here so we can do it later. PK

  ReadFile();

  ReadFile(const char * filename);
  
  ~ReadFile();

  //added this
  //void get_info(double *data[])
  void get_info(ostream& os) const;

  void get_graph(ostream& os)const;

  void display(ostream& os, int i) const;

  void printing();

  //void add_new(char type);

  // double mean(const double d[], const int length);

  // double median(const double d[], const int len);

  // double mode(const double d[]);

  // double standard_dev(const double d[], const int len); 
};

#endif