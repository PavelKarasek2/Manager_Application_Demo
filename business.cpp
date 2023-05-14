#include <iostream>
#include <fstream>
#include "helpers.h"
#include "business.h"

using namespace std;

void business::set_name(const char* n){
        int len = 0;
        while(n[len++]){}
        name = new char[len];
        for(int i = 0; i < len; i++){
            name[i] = n[i];
        }
    }

business::business(const char* n){
        set_name(n); 
    }

business::business(string* input){
        set_name(input[1].c_str()); 
    }

business::business(const business& b){
    set_name(b.name);
}

business& business:: operator=(const business& b){
    delete [] name;
    set_name(b.name);
    return *this;
} 

char* business::get_name() const {
        return name;
    }

void business::display(ostream& os) const {
        os << "name: ";  
        for(int i = 0; name[i]; i++){
            os << name[i];
        }
        os << endl;
}

business::~business(){
    delete [] name;
}

void product::set_marginal_cost(double c){
    marginal_cost = c;
}

void product::set_selling_price(double p){
    selling_price = p;
}

product::product(char* n):business(n){
        selling_price = 0;
        marginal_cost = 0;    
    }

product::product(string* input):business(input){
        selling_price = 0;
        marginal_cost = stod(input[2]);    
    }

product::product(const product& p): business(p), selling_price(p.selling_price), marginal_cost(p.marginal_cost){}

product& product::operator=(const product& p){
    business::operator=(p);
    marginal_cost = p.marginal_cost;
    selling_price = p.selling_price;
    return *this;
}

//getters

double product::get_price() const{
    return selling_price;
}

double product::get_cost() const{
    return marginal_cost;
}

void product::display(ostream& os) const {
    os<< "Product's ";
    business::display(os);          
    os << "selling price: " << selling_price << endl;
    os << "marginal cost: " << marginal_cost << endl;
}

// void product::sell_product(){
//     cout << "What price did you sell it for?" << endl;
//     cin >> selling_price;
// }

double product::get_value1(int i)const{
    if(i==0){
        return get_price();
    }
    else if(i == 1){
        return get_cost();
    }
    else{
        cout << "error in product::get_value1"<<endl;
        return 0;
    }
}

void product:: initialize_value(const char* var, double x){
    if (compare(var,"marginal_cost")){
        marginal_cost = x;
    }
    else if(compare(var,"selling_price")){
        selling_price = x;
    }
    else{cout<<"Not a valid class variable."<<endl;}
}

void employee::set_wage(double w){
    wage = w;
}

void employee::set_hours(double h){
    hours = h;
}

employee::employee(char* n):business(n), wage(0), hours(0){}

employee::employee(string* input):business(input){
    wage = stod(input[2]);
    hours = stod(input[3]);
}

employee::employee(const employee& e): business(e), wage(e.wage), hours(e.hours){}

employee& employee::operator=(const employee& e){
    business::operator=(e);
    set_wage(e.wage);
    set_hours(e.hours);
    return *this;
}

double employee::get_wage() const{
    return wage;
}

double employee::get_hours() const{
    return hours;
}

double employee::get_monthly_wage() const{
    return (hours*wage);
}

void employee::display(ostream& os) const{
    os << "Employee's ";
    business::display(os);
    os << "Wage: " << wage << endl;
    os << "Hours per month: " << hours << endl;
}

double employee::get_value1(int i)const{
    if(i==0){
        return get_wage();
    }
    else if(i == 1){
        return get_hours();
    }
    else{
        cout << "error in employee::get_value1"<<endl;
        return 0;
    }
}

void employee:: initialize_value(const char* var, double x){
if (compare(var,"wage")){
    wage = x;
}
else if(compare(var,"hours")){
    hours = x;
}
else{cout<<"Not a valid class variable."<<endl;}
}

void capital::set_cost(double c){cost = c;}

capital::capital(char* n):business(n), current_value(0), cost(0){}          //might have to change this //works well

capital::capital(string* input):business(input){
    cost = stod(input[2]);
    current_value = cost;
}

capital::capital(const capital& c): business(c), current_value(c.current_value), cost(c.cost){}

capital& capital::operator&(const capital& c){
    business::operator=(c);
    current_value = c.current_value;
    cost = c.cost;
    return *this;
}

double capital::get_cost() const{
    return cost;
}

double capital::get_value() const{
    return current_value;
}

void capital::display(ostream& os) const{
    os << "Capital's ";
    business::display(os);
    os << "Current value: " << current_value << endl;
    os << "Buying price: " << cost << endl;
}

double capital::get_value1(int i)const{
    if(i==0){
        return get_value();
    }
    else if(i == 1){
        return get_cost();
    }
    else{
        cout << "error in capital::get_value1"<<endl;
        return 0;
    }
}

void capital::initialize_value(const char* var, double x){
if (compare(var,"cost")){
    cost = x;
}
else if(compare(var,"current_value")){
    current_value = x;
}
else{cout<<"Not a valid class variable."<<endl;}
}

business* biz_clone(const business* bptr, char type,const char* cv1,const char* cv2){
    business* b;
    if(type == 'c'){
        b = new capital((*bptr).get_name());
    }
    else if(type == 'p'){
        b = new product((*bptr).get_name());
    }
    else if(type == 'e'){
        b = new employee((*bptr).get_name());
    }
    else {cout << "error in biz_clone in business.cpp" << endl;}
    (*b).initialize_value(cv1, (*bptr).get_value1(0));
    (*b).initialize_value(cv2, (*bptr).get_value1(1));
    return b;
}

business* new_obj(char type, string* input){
    if(type == 'c'){
        capital* c = new capital(input);
        return c;
    }
    else if (type == 'p'){
        product* p = new product(input);
        return p;
    } 
    else if(type == 'e'){
        employee* e = new employee(input);
        return e;
    }
    else{cout << "incorrect type entered"<<endl;}
    return 0;
}

