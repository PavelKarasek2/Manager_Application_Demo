#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include <cmath>
#include "ReadFile.h"
#include "business.h"
#include "formulas.h"
#include "helpers.h"
#include "graph.h"

using namespace std;

    ReadFile::ReadFile(const char * filename){ //reads CSV into title (vector of strings) and data (array of arrays of doubles)
   
                ifstream file(filename);
                if(file.is_open()){
                    string line;

                    string graphTitle;
                    getline(file, graphTitle);
                    //os << graphTitle << endl;

                    data = new double*[2];
                    size = get_num_imported(filename);
                    data[0] = new double[size];
                    data[1] = new double[size];

                    int j = 0; //column
                    while(getline(file, line)) {//increments through the line

                        stringstream s(line);//makes a 'line' string
                        int i = -1;//row
  
                        string word;

                        while(getline(s, word, ',')) { //uses the line string to increment comma by comma && j !=0
                            if(i == -1){
                                title.push_back(word);//saves the axises into title vector
                                i++;
                            }
                            else{
                                data[j][i] = stod(word);
                                i++;//increments along the row
                            }
                            //cout << endl;
                        }
                        
                        j++;//increments along the column
                    }
                    file.close();
                }  
            }
  
    /*ReadFile::ReadFile(){ //reads CSV into title (vector of strings) and data (array of arrays of doubles)

            const char* str;
            
            if(compare(str,"2")){
                ifstream file("test1.csv");
            }
            else{    
                ifstream file(str);

                if(file.is_open()){ 
                    string line;

                    data = new double*[2];
                    size = get_num_imported(str);
                    data[0] = new double[size];
                    data[1] = new double[size];


                    
                    int j = 0;//column
                    string graphTitle;
                    getline(file, graphTitle);
                    //os << graphTitle << endl;

                    while(getline(file, line)) {//increments through the line
                        stringstream s(line);//makes a 'line' string
                        int i = -1;//row
                        int count = 0;
                        string word;
                        while(getline(s, word, ',')) { //uses the line string to increment comma by comma
                            if(i == -1){
                                title.push_back(word);//saves the axises into title vector
                                //os << word << ", ";
                                i++;
                            }
                            else if(i !=-1){
                                data[j][i] = stod(word);
                                //cout << data[j][i] << ", ";
                                i++;//increments along the row
                            }
                            count++;//increments when you complete a line
                           
                        }
                        j++;//increments along the column
                    }
                
                }
            file.close();
        }
    }*/

        int ReadFile::get_num_imported(const char* file_name){//to determine how many lines are in the file that we are importing
            ifstream get_num_imported(file_name);
            if (get_num_imported.is_open()){    
                string line;
                getline(get_num_imported, line);
                int num_imported = 0;
                char current = get_num_imported.get();
                if(current == -1){
                    cout << "empty file" << endl;
                    num_imported = 0;
                }
                else {  
                    while(current != '\n'){
                        if(current == ','){
                            num_imported++;
                        }
                        current = get_num_imported.get();
                    }
                }
                get_num_imported.close();
                return num_imported;
            }
            else {cout << "could not open file" << endl;}
            return 0;
        }

         void ReadFile::display(ostream& os, int i) const{

            
                os << title[i] << ',';

                for(int j = 0; j < size; j++){
                    os << data[i][j];
                    if(j !=size-1){
                        os << ',';//puts the comma after everthing except the last num
                    }
                    //cout << data[i][j];
                }
                os << '\n';
            
        }

        void ReadFile::get_info(ostream& os)const{
            os<<endl;
            display(os, 0);
            get_data(data[0],size,os);
            display(os, 1);
            get_data(data[1],size, os);
        }

        void ReadFile::get_graph(ostream& os)const{
            graph g(data[0],data[1],size);
            g.graphing(os,data[0],data[1]);
        }

        ReadFile::~ReadFile(){
            for(int i = 1; i>=0;i--){
                delete [] data[i];
            }
            delete [] data;
        }