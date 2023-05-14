#include <iostream>
#include <fstream>
#include "helpers.h"

using namespace std;

bool compare(const char*a, const char*b){
    int len_a = 0; int len_b = 0;
    while(a[len_a++]){};
    while(b[len_b++]){};
    if(len_a!=len_b){
        return false;
    }
    else{
        for(int i = 0; i < len_a; i++){
            if(a[i]!=b[i]){
                return false;
            }
        }
        return true;
    }
}

void str::copy_over(const char* p){
    int len = 0;
    while(p[len++]){}
    s = new char[len];
    for(int i = 0; i < len; i++){
        s[i] = p[i];
    }
}

str::str(const char* p){copy_over(p);}

str::str(){s = 0;}

char* str::get_str(){return s;}

str::~str(){
    delete [] s;
}


str::str(ifstream& get_str_file, char stop){                                      
    //cout << "in get_str" << endl;
    if (get_str_file.is_open()){
        //cout << "file open" << endl;
        s = new char[50];
        //cout << "allocated" << endl;

        char current = 1;
        int j = 0;
        while(current){
            //cout << "in loop" << endl;
            current = get_str_file.get();
            if(current == '\n'|| current == -1 || current == stop){
                current =0;
            }
            s[j] = current;
            j++;
            //cout << "count: " << j << ", current: " << current << endl;
        }
        //cout << s << endl;
    }
    else {cout << "could not open file" << endl;}
}

int get_num_imported(ifstream& file, const char end, const char separator){
    if (file.is_open()){    
        int num_imported = 0;
        char current = file.get();
        //
        // char test1 = (current>31)? current: 'N';
        // cout << "first character read in:" << test1 << endl;
        //
        while(current != end){
            if(current == separator){
                num_imported++;
            }
            current = file.get();
        }
        //
        // char test2 = (current>31)? current: 'N';
        // cout << "last character read in:" << test2 << endl;
        //
        return num_imported;
    }
    else {cout << "could not open file" << endl;}
    return 0;
}

int get_num_imported(const char* file_name,const char end, const char separator){
    ifstream file(file_name);
    return get_num_imported(file, end, separator);
}

str_arr::str_arr():size(0), parr(nullptr) {}

str_arr::str_arr(char* filename,const char* action){       //create a class of text objects
    ifstream file(filename);                               // Use this one for the terminal functions, seems to be pretty useless.
    char first =1;
    int i = 0;
    string* arr = new string[10];
    while(first != '|'){
        first = file.get();
        if(first == '#'){
            string a; 
            getline(file, a);
            if(compare(a.c_str(),action)){
                first = file.get(); 
                while(first != '|' && first !='#'){
                    getline(file,arr[i]);
                    first = file.get();
                    i++;
                }
            }
        }
    }
    // for(int j = 0; j < i; j++){
    //     cout << arr[j] << endl;
    // }
    //cout << "got here in str_arr" << endl;
    string junk; 
    getline(file,junk);
    //cout << "junk: " << junk << endl;
    //cout << "got here in str_arr" << endl;

    file.get();
    getline(file, arr[i]);
    size = ++i;
    //cout << size <<endl;
    parr = new string[size];
    for(int j = 0; j < size; j++){
        parr[j] = arr[j];
    }
    delete [] arr;
    file.close();
    //cout << "all done here" << endl;
}

void str_arr::initialize(ifstream& f_size,ifstream& f_text,const char end, const char separator){
    //as of now, it does not work with end == -1 and separator == \n
    size = get_num_imported(f_size, end, separator);
    //size++; 
    //cout << "size:" << size << endl;
    f_text.get();
    // if(size==1){
    //     parr = new string;
    //     getline(f_text,*parr,'#');
    //     parr[0].pop_back();                   
    // }
    // else{ 
    parr = new string[size];   
    for(int i = 0; i<size-1; i++){
            getline(f_text, parr[i], separator);
            parr[i].pop_back();
    }
    getline(f_text, parr[size-1], end);
    parr[size-1].pop_back();
    //}
    //display(cout);
}

str_arr::str_arr(ifstream& f_size,ifstream& f_text,const char end, const char separator){
    initialize(f_size,f_text,end,separator);
}

//str_arr::str_arr(str_arr&)

void str_arr::update_str_arr(string input, const char separator, const char end_str){
    int num_sep = 0;
    int len = input.length();
    //cout << "len:" << len << endl;
    for(int i = 0; i < len; i++){
        if(input[i] == separator){
            num_sep++; 
            //cout << "num_sep:" << num_sep << endl;
            int sep_count = 1;
            while(input[i+sep_count] == separator){sep_count++;}
            i += sep_count - 1;
            }
    }
    //cout << "num_sep final:" << num_sep << endl;
    size = num_sep;
    //cout << "size:" <<size << endl;
    if(parr){
        delete [] parr;
    }
    //cout << "got here" << endl;
    parr = new string[size];
    int counter = 0;
    for(int i = 0; i < size; i++){
        //cout << "big iter: " << i << endl;
        while(input[counter]==separator){
            //cout << "input["<< counter <<"]: " << input[counter];
            counter++;
        }
        //cout << endl;
        //cout<<"counter after first while loop: " << counter <<endl;
        //int j = 0;
        string current; 
        while(input[counter]!=end_str){
            //cout << "input["<< counter <<"]: " << input[counter];
            //parr[i][j] = input[counter];
            current.push_back(input[counter]);  
            //((*this).get_text(i)).push_back(input[counter]);
            //j++;
            counter++;
            //cout<<"counter: " << counter <<endl;
        }
        parr[i]=current;
        //parr[i][j]= 0;
        while(input[counter] == end_str){counter++;}
        //cout<<"counter: " << counter <<endl;
        //cout << endl;
    }
}

void str_arr::display(ostream& os) const {
    for(int i = 0; i < size; i++){ 
        os << parr[i];
        if(i != size-1){os << '\0' << endl;}
    }
}

string* str_arr::get_parr()const{
    return parr;
}

string str_arr::get_text(int i)const{
    return parr[i];
}



int str_arr::get_size() const{
    return size;
}

void str_arr::set_null(){
    delete[] parr; parr = 0;
}

str_arr::~str_arr(){
    delete [] parr;
}
