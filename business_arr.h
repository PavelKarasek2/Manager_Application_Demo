#ifndef __business_arr_h__
#define __business_arr_h__

#include <iostream>
#include <fstream>
#include "helpers.h"
#include "business.h"

using namespace std;

class business_arr{
  protected:
    business** arr;
    int size;
    str** class_var;
  
  public:
    business_arr(const char type);

    void write(const char* file) const;

    int get_size() const;

    business** get_arr() const;

    void display(ostream& os) const;

    void delete_arr();

    ~business_arr();

    void add_new(const char type, string* input);

    void modify( const char type, string* input);

    void get_info(ostream& os) const;

    void get_graph(ostream& os) const;
  
};

#endif