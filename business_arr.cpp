#include <iostream>
#include <fstream>
#include "business.h"
#include "helpers.h"
#include "business_arr.h"
#include "formulas.h"
#include "graph.h"


using namespace std;

class arr_d{        //created this so I don't have to worry about deallocating double arrays
    double* arrd;
    int size;
  public:
    arr_d(const business_arr& biz, int val_num){
        if(val_num != 1 && val_num != 0){
            cout << "wrong val_num argument put in arr_d constuctor"<< endl;
        }
        size = biz.get_size();
        arrd = new double[size];
        for(int i = 0; i < size; i++){
            arrd[i] = (*(biz.get_arr())[i]).get_value1(val_num);
        }
    }

    double* get_arr_d(){
        return arrd;
    }

    ~arr_d(){
        delete [] arrd;
    }
};


business_arr::business_arr(const char type){
    //cout << "size: " << size << "in constructor" << endl;
    str filename;
    if(type == 'p'){filename.copy_over("product_list.csv");}
    else if(type == 'c'){filename.copy_over("capital_list.csv");}
    else if(type == 'e'){filename.copy_over("employee_list.csv");}
    
    size = get_num_imported(filename.get_str(), '\n', ',');
    ifstream input(filename.get_str());
    class_var = new str*[2];
    if(!size){
        arr = NULL;
        size = 0;
        str t1(input,',');
        char* title1 = t1.get_str(); //should store "name" in it. We don't need it
        //cout << title1 << endl;
        for(int j = 0; j<2; j++){
            class_var[j] = new str(input,',');
        }
        // for(int j = 0; j<2; j++){
        //     cout << class_var[j] << endl;
        // }
    }
    else{
        if (input.is_open()){
            arr = new business*[size];
            //add names
            str t1(input,',');
            char* title1 = t1.get_str();   
            if(compare(filename.get_str(),"product_list.csv"))    //don't like this repetition
                for(int i = 0; i<size; i++){
                    str n1(input,',');
                    arr[i] = new product(n1.get_str());                                    
                }
            else if(compare(filename.get_str(),"capital_list.csv"))    
                for(int i = 0; i<size; i++){
                    str n1(input,',');
                    arr[i] = new capital(n1.get_str());                                    
                }
            else if(compare(filename.get_str(),"employee_list.csv"))    
                for(int i = 0; i<size; i++){
                    str n1(input,',');
                    arr[i] = new employee(n1.get_str());                                    
                }
            else{cout << "Wrong file." << endl;}
            // add numbers

            for(int j = 0; j<2; j++){
                class_var[j] = new str(input,',');
                //cout << "testing class var allocation " << (*class_var[j]).get_str() << endl;
                //cin.get();
                for(int i = 0; i<size; i++){
                    //cout << "marginal cost iteration " << i << endl;      
                    float num;
                    input >> num;
                    //cout << num << endl;              
                    (*(arr[i])).initialize_value((*class_var[j]).get_str(), num);
                    input.get();
                }
                //input.get();   //why this here? check for this when running the code
            }
        //     cout << "allocted" << endl;
        //     for(int i = 0; i<size; i++){
        //     (*(arr[i])).display();
        // }
        }
        else {cout << "could not open file" << endl;}
        input.close();
    }
    //cin.get();    //for checking if the constructor works correctly.
}

int business_arr::get_size() const{
    return size;
}

business** business_arr:: get_arr() const{
    return arr;
}

void business_arr::write(const char* file) const{
    ofstream output(file);
    output << "name";
    for(int i = 0; i < size; i++){
        output<< "," << (*(arr[i])).get_name();
    }
    output << "\n";
    //cout << "names are in" << endl;
    for(int j=0; j < 2; j++){
        for(int i = 0; ((*class_var[j]).get_str()[i]); i++){
            output << ((*class_var[j]).get_str()[i]);
        }
        for(int i = 0; i < size; i++){
            output << "," <<(*(arr[i])).get_value1(j);
        }
        output << "\n";
    }
    output.close();
    }

void business_arr::display(ostream& os) const{
    if(size){  
        for(int i = 0; i<size; i++){
            (*(arr[i])).display(os);
        }
    }
    else{os<< "no objects added yet" << endl;}
}

void business_arr::delete_arr(){
    for (int i = size-1; i >= 0; i--){
        (*(arr[i])).~business();
    }
    delete [] arr;
}

business_arr::~business_arr(){
    delete_arr();
    delete [] class_var;
}

//get rid of the prompts from text file in this
void business_arr::add_new(const char type, string* input){     //change this
    //cout << "in add new" << endl;
    int num_created;
    num_created = stoi(input[0]);
    //cout << "num created: " << num_created << endl;
    business** new_arr = new business*[size+num_created];
    // cout << "type = " << type << endl;
    for(int i = 0; i < size; i++){
        new_arr[i] = biz_clone(arr[i],type,(*class_var[0]).get_str(),(*class_var[1]).get_str());
    }
    delete_arr();

    arr = new_arr; 
    for (int i = size; i < (size + num_created); i++){
        arr[i] = new_obj(type, input);
    }

    size += num_created;
    //cout << "modified, write to csv file remaining" << endl;
    str filename;
    if(type == 'p'){filename.copy_over("product_list.csv");}
    else if(type == 'c'){filename.copy_over("capital_list.csv");}
    else if(type == 'e'){filename.copy_over("employee_list.csv");}
    write(filename.get_str());
    //cout << "finished add new" << endl;
}

void business_arr::modify(const char type, string* input){ 
    const char* str1 = (input[0]).c_str();
    const char* str2 = (input[1]).c_str();
    double new_val = stod(input[2]);
    double num_change = stod(input[3]); 
    int modified = 0;
    for(int i = 0; i < size; i++){
        //cout << "iteration " << i << endl;
        if(compare((*arr[i]).get_name(),str1)){
            (*arr[i]).initialize_value(str2,new_val);
            modified++;
            //cout << "currently sold: " << currently_sold << endl;
        }
        if(modified >= num_change){
            break;
        }
    }
    if(modified < num_change){
        //os << "You only had " << modified << " objects to modify."<< endl;
    }
    str filename;
    if(type == 'p'){filename.copy_over("product_list.csv");}
    else if(type == 'c'){filename.copy_over("capital_list.csv");}
    else if(type == 'e'){filename.copy_over("employee_list.csv");}
    write(filename.get_str());
}

void business_arr:: get_info(ostream& os) const{
    os<<endl;
    os << (*class_var[0]).get_str() << " data: " << endl;
    arr_d vals1(*this,0);
    get_data(vals1.get_arr_d(),size,os);
    os << (*class_var[1]).get_str() << " data: " << endl;
    arr_d vals2(*this,1);
    get_data(vals2.get_arr_d(),size,os);
}

void business_arr::get_graph(ostream& os) const{
     arr_d vals1(*this,0);arr_d vals2(*this,1);
    graph g(vals1.get_arr_d(),vals2.get_arr_d(),size);
    g.graphing(os,vals1.get_arr_d(),vals2.get_arr_d());
}