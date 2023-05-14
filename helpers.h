#ifndef __helpers_h__
#define __helpers_h__

#include <iostream>
#include <fstream>

using namespace std;

bool compare(const char*a, const char*b);

class str{
    char* s;
public:
    void copy_over(const char* p);

    str(const char* p);

    str();

    str(ifstream& get_str_file, char stop = 0);

    char* get_str();

    ~str();
};

int get_num_imported(ifstream& file,const char end, const char separator);
//gets the number of text objects separated by separator until character end is found. 
// Takes in a reference ifstream object to that this can be done multiple times in one text file, 
//assuming the text file has more that one of the end characters.

int get_num_imported(const char* file_name,const char end, const char separator);

class str_arr{  //one str_arr object belongs to one screen
int size;       // I could use inheritance for this with state possibly
string*parr;
public:
    str_arr();

    str_arr(char* filename,const char* action);  //for distinguishing output in a common function for all three business objects

    str_arr(ifstream& f_size,ifstream& f_text,const char end, const char separator);

    void initialize(ifstream& f_size,ifstream& f_text,const char end, const char separator);

    void update_str_arr(string input, const char separator, const char end_str);

    void display(ostream& os) const;

    string* get_parr()const;

    string get_text(int i)const;

    int get_size()const;

    void set_null();

    ~str_arr();
};

#endif