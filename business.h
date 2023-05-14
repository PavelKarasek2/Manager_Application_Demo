#ifndef __bussiness_h_
#define __bussiness_h_

#include <iostream>
#include <fstream>

using namespace std;

class business{
    char* name;

public:
    
    void set_name();

    void set_name(const char* n);

    business(const char* n);

    business(string* input);

    business(const business& b);

    business& operator=(const business& b);

    char* get_name() const;

    virtual void display(ostream& os) const;

    virtual void initialize_value(const char* var, double x) = 0; 

    virtual double get_value1(int i) const = 0;

    ~business();
};

class product : public business{
    double selling_price;
    double marginal_cost;
  public:
    void set_marginal_cost(double c);

    void set_selling_price(double p);

    product(char* n);

    product(string* input);

    product(const product& p);

    product& operator=(const product& p); 

    double get_price() const;

    double get_cost() const;

    void display(ostream& os) const;

    void add_fixed_cost() const;

    double get_value1(int i) const;

    void initialize_value(const char* var, double x);
};


class employee : public business{
    double wage;      //hourly
    double hours;      // assume the employee works the same hours every week
  public:
    void set_wage(double w);

    void set_hours(double h);

    employee(char* n);

    employee(string* input);

    employee(const employee& e);

    employee& operator=(const employee& e);

    double get_wage() const;

    double get_hours() const;

    double get_monthly_wage() const;

    void display(ostream& os) const;

    double get_value1(int i) const;

    void initialize_value(const char* var, double x);
};

class capital : public business{
    double current_value;
    double cost;
  public:
    void set_cost(double c);

    capital(char* n);

    capital(string* input);

    capital(const capital& c);

    capital& operator&(const capital& c);

    double get_cost() const;

    double get_value() const;

    double get_total_value() const;

    void display(ostream& os) const; 

    double get_value1(int i) const;

    void initialize_value(const char* var, double x);
};

business* biz_clone(const business* bptr, char type,const char* cv1,const char* cv2);

business* new_obj(char type, string* input);

#endif