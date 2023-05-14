#include <iostream>
#include<fstream>
#include"/usr/local/cs/cs251/react.h"
#include "helpers.h"
#include "business.h"
#include "business_arr.h"
#include "ReadFile.h"
#include "formulas.h"      
#include "graph.h"

using namespace std;

void create_buffer(int size, ostream& os){
    for(int i = 0; i < size -1; i++){os << '~';}
    os << endl;
}

class State {
    int screen_num;
    int curr_scr_parts;
    str_arr user_text;
  public:
    State(ifstream &is) { 
        is >> screen_num; is.get(); is >> curr_scr_parts; is.get();
        // if(is.peek()!=-1){
        //     ifstream f_size("curr_state"); 
        //     string first_line; getline(f_size, first_line);
        //     user_text.initialize()
        // }
        if(is.peek()!=-1){
            string input; string line;
            while(getline(is, line)){
                input += line + '\n'; 
            }
            user_text.update_str_arr(input,'\n','\n');
        }
                                              //Ideally have a button for it
    }

    int get_screen_num() const { return screen_num; }

    int get_curr_scr_parts() const {return curr_scr_parts;}

    const str_arr& get_user_text() const {return user_text;}

    void print_text(int i,ostream& os)const{
        os << (user_text).get_text(i) << endl;
        //os << "test" << endl;
    }

    void print_state(){      //for debugging
        cout << "printing state for debugging" << endl;
        write_to(cout);
        cout << "curr screen parts:"<< curr_scr_parts << endl;
        cout << endl;
    }

    //fix
    void write_to(ostream &os) const {  
        os << screen_num << ','<< curr_scr_parts<< endl;
        //os << curr_scr_parts << endl;
        if(user_text.get_parr()){         //if the user_text parr (string pointer) does not point to null byte
            for(int i = 0; i < curr_scr_parts; i++){
                print_text(i,os);
            } 
        }
    }

  void update(string input, istream &is);
};

//int u = 3;
str_arr text[23];     //size = 22   //If you want to add a screen, you have to change the size, limit and the for loop guard in read_text_data() accordingly PK
const int limit = 22;  // final screens
bool react = false;
int input_index = 10, prompt_index = 100; //changed this in case user writes more than expected PK
                                                // Would I have to change this in react_yaml or is it updated by how the manager.yaml is updated? PK
void read_text_data() {
    ifstream f_num("screens.txt");
    ifstream f_read("screens.txt");
    string comment;
    for (int i = 0; i < 23; ++i) {
        //cout << "read text started iteration " << i << endl;
        text[i].initialize(f_num,f_read,'#','/');
        getline(f_read,comment); 
        //cout << "read text finished iteration " << i << endl;
        //cout << endl;
    }
}
int get_u(int screen_num){ //gets the right number of buttons to use
    int u = 0;
    if(screen_num == 1){u = 3;}
    else if(screen_num == 2 || screen_num == 22){u = 4;}
    else if(screen_num == 5){u = 5;}
    else if(screen_num == 6 || screen_num == 11 || screen_num == 16){u=6;}
    else{u == 6;}
    return u;
}

void display(const State &state, ostream &os) {
    char button_labels[] = {'1','\0','2','\0','3','\0','4','\0','5','\0','6','\0'};  //I realize every screen has different number of buttons. Will change later if time.
    int button_labels_len = 12; //in order to properly change the number, i think button labels should be dynamic
    int n = state.get_screen_num();
    int scr_parts = text[n].get_size();
    prompt_index = 100; input_index = 10;  
    if (react) {
        _add_yaml("texts.yaml", {{"prompt_index", prompt_index}});
        if(n<3 || n == 5 || n == 6 || n == 11 || n == 16){
        _add_yaml("set_up_buttons.yaml"); 
            int h = get_u(n);
        for (int i = 0; i < h; ++i){
            //_add_yaml("button.yaml", {{"id", i}, {"x", 10 + 110*i},{"button_text_index", 2*i}});
            _add_yaml("button.yaml", {{"id", i}, {"x", "y"}, {"button_text_index", 2*i}}); //if we could put a newline character right before this
        }

        os.write(button_labels, button_labels_len); create_buffer(prompt_index-12,os);
        }
        else if(n == 3 || n == 9 || n== 10 || n == 14 ||n == 15 ||n == 19 ||n == 20 || n == 21 || n==22){
            _add_yaml("button2.yaml", {{"id", 0}, {"x", 10},{"button_text_index", 0}});
            os.write("Main menu\0",10); create_buffer(prompt_index-10,os);
        }
        else{
        _add_yaml("user_input.yaml", {{"input_index", input_index}});
        for(int i = 1; i < scr_parts; i++ ){
            input_index+=20;
            //cout << (text[n]).get_text(i-1) << endl;
            //cout << "length: " << 3+((text[n]).get_text(i-1)).length() << endl; //Add one for null and two endl
            prompt_index += (2+((text[n]).get_text(i-1)).length());
            //cout << "prompt index:"<< prompt_index << endl;  
            _add_yaml("texts.yaml", {{"prompt_index", prompt_index}});    
            _add_yaml("user_input.yaml", {{"input_index", input_index}});
        }
        _add_yaml("button2.yaml", {{"id", 0}, {"x", 10},{"button_text_index", 0}});
        os.write("Main menu\0",10); create_buffer(90,os);
    }
    } else os << "\033c";
    //os << "                   " << "[screen " << n << "]" << endl;
    text[n].display(os);//null printed in the display function
    

    if(n == 3){
        ReadFile c("test1.csv");
        c.get_graph(os);
        c.get_info(os);
    }
    else if(n == 21){
        // cout << "const char parameter for ReadFile c: " << endl;
        // cout << ((state.get_user_text()).get_text(0)).c_str() << endl;
        ReadFile c(((state.get_user_text()).get_text(0)).c_str());
        c.get_graph(os);
        c.get_info(os);
    }
    
    else if(n > 6 && n!= 11 && n!=16 && n<21){    
        char type = 'p';  // products
        if(n > 11){type = 'c';} //capital
        if(n > 16){type = 'e';}  // employees
        business_arr a(type);
        if(n == 9 || n == 14 || n == 19){
            a.display(os);
        }
        else if(n == 10 || n == 15 || n == 20){ //there is still no 4
            os<<endl;
            a.get_graph(os);
            a.get_info(os);
        } 
        //else{cout << "wrong screen_num" << endl;}
    }    
    
    if (react) os << '\0';
    else if (n >= limit) exit(0);
}  

void State::update(string input, istream &is) {    //create loops to do this once time
  //cout << input << endl;
//   if(screen_num != 21){
//     if(user_text.get_parr()){
//         user_text.set_null();
//     }
//   }
  int button_index = -1;
  //Not everything is buttons. Only the menus are. The rest is user input. For that, we will have to use what you have commented out below.
  // To distinguish between whatt we will do we will depend on the screen_num. PK

  /*if (react && _received_event()) {
    // get input from the stream
    is.get(); is.get();  // skip first two characters
    if ('~' != is.peek()) getline(is, input, '\0');
  }*/
  if(screen_num < 3 || screen_num == 5 || screen_num == 6 || screen_num == 11 || screen_num == 16){ //
    curr_scr_parts =1;
    //cout << screen_num << endl;
    if (react && _received_event()) {
        int h = get_u(screen_num);
        for (int i = 0; i < h; ++i) {
            if (_event_id_is("b", i)){
                button_index = i;
            }
        }
    }
    else if (!react && input.length() > 0) {    //not react
        //cout << input << endl;
        //cout << "testing" << endl;
        if ('1' <= input[0] && input[0] <= '6') {
            button_index = input[0] - '1';
        } 
    }
  }
  else if(screen_num == 3 || screen_num == 9 || screen_num == 10 || screen_num == 14 ||screen_num == 15 ||screen_num == 19 ||screen_num == 20 ||screen_num == 21|| screen_num ==22){
        curr_scr_parts = 1;
        //don't do anything in react
        //if(!react)cin.get();
   }
   else if(screen_num == 4){
     if (react && _received_event()) {
        if(_event_id_is("b", 0)){
            //button_index = 0;
                //back to main menu
            }
        // get input from the stream
        //is.get(); is.get();  // skip first two characters
        else{
            string menu; getline(is,menu,'\0');
            getline(is, input);
            user_text.update_str_arr(input,'~','\0');
            //print_state();
            curr_scr_parts = user_text.get_size(); // =1 
            }  //there is one more screen than strings in user_text because the first input only
        //cout << "here" << endl;
        //char type = 'p';  // products
        //ReadFile c((user_text.get_text(0)).c_str());
     }
     else if(!react){
        user_text.update_str_arr(input, '/', '/'); 
        curr_scr_parts = user_text.get_size(); //=1
     }
   }
  else{
        if (react && _received_event()) {
        // get input from the stream
            if(_event_id_is("b", 0)){}
            else{
                //cout << "in else" << endl;
                string menu; getline(is,menu,'\0');
                getline(is, input);
                user_text.update_str_arr(input,'~','\0');
                curr_scr_parts = user_text.get_size();   //there is one more screen than strings in user_text because the first input only
                //cout << "here" << endl;
                char type = 'p';  // products
                if(screen_num > 11){type = 'c';} //capital
                if(screen_num > 16){type = 'e';}  // employees
                business_arr a(type);
            
                //print_state();
                if(screen_num == 7 || screen_num == 12 || screen_num == 17){
                    a.add_new(type,user_text.get_parr());
                }
                else if(screen_num == 8 || screen_num == 13 || screen_num == 18){
                    a.modify(type,user_text.get_parr());
                }
            }
        //else if(screen_num == 2)
        //print_state(); cout << endl;
        }
        else if(!react){
            user_text.update_str_arr(input,'/','/');
            curr_scr_parts = user_text.get_size();   //there is one more screen than strings in user_text because the first input only
            //cout << "here" << endl;
            char type = 'p';  // products
            if(screen_num > 11){type = 'c';} //capital
            if(screen_num > 16){type = 'e';}  // employees
            business_arr a(type);
        
            //print_state();
            if(screen_num == 7 || screen_num == 12 || screen_num == 17){
                a.add_new(type,user_text.get_parr());
            }
            else if(screen_num == 8 || screen_num == 13 || screen_num == 18){
                a.modify(type,user_text.get_parr());
            }
        }

  }

  if (0 == screen_num || 22==screen_num) {screen_num = 1;}
  else if(screen_num == 3 || screen_num == 7 ||screen_num == 8||screen_num == 9||screen_num == 10||screen_num == 12||screen_num == 13||screen_num == 14||screen_num == 15||screen_num == 17||screen_num == 18||screen_num == 19||screen_num == 20 || screen_num==21){
    screen_num = 1;
  }
  //cout << "testing" << endl;
  else{
    int input_num= button_index + 1;
    // if(react){input_num = button_index + 1;}
    // else{//this is not right for the terminal version
    
    //     if(input.empty()){        //I put this here so it when we press enter it for the cin it does not do anything PK
    //     input_num = 0;        //Don't this is necessary though
    //     }
    // }

    if(screen_num == 1){

       if(input_num == 1){
            screen_num = 2;

       }else if(input_num == 2){
            screen_num = 5;
            
       }
       else if(input_num == 3){
            screen_num = 22;
       }
       
       
       else{cout << "Enter a valid number" << endl;}
    }
    
    else if(screen_num == 2){
        if(input_num == 1){
            screen_num = 3;
        }
        else if(input_num == 2){
            screen_num = 4;
        }
        else if(input_num == 3){
            screen_num = 1;
        }
        else if(input_num == 4){
            screen_num = 22;
        }
        else{cout << "Enter a valid number" << endl;}
    }
    else if(screen_num == 4){
        if(button_index==0){screen_num = 1;}
        else{screen_num = 21;}
    }
  
    else if(screen_num == 5){
        if(input_num == 1){
                screen_num = 6;
        }
        else if(input_num == 2){
                screen_num = 11;
        }
        else if(input_num == 3){
                screen_num = 16;
        }
        else if(input_num == 4){
                screen_num = 1;
        }
        else if(input_num == 5){
                screen_num = 22;       //exits the program
        }
        else{cout << "Enter a valid number" << endl;}
        }
        else if(screen_num == 6){ 
            if(input_num == 1){
                screen_num = 7;
            }
            else if(input_num == 2){
                screen_num = 8;
            }
            else if(input_num == 3){
                screen_num = 9;
            }
             else if(input_num == 4){ 
                screen_num = 10;
             }
            else if(input_num == 5){
                screen_num = 1;
            }
            else if(input_num == 6){
                screen_num = 22;
            }
            else{cout << "Enter a valid number" << endl;}
        }

        else if(screen_num == 11){ 
            if(input_num == 1){
                screen_num = 12;
            }
            else if(input_num == 2){
                screen_num = 13;
            }
            else if(input_num == 3){
                screen_num = 14;
            }
             else if(input_num == 4){ 
                screen_num = 15;
             }
            else if(input_num == 5){
                screen_num = 1;
            }
            else if(input_num == 6){
                screen_num = 22;
            }
            else{cout << "Enter a valid number" << endl;}
        }

        else if(screen_num == 16){ 
            if(input_num == 1){
                screen_num = 17;
            }
            else if(input_num == 2){
                screen_num = 18;
            }
            else if(input_num == 3){
                screen_num = 19;
            }
             else if(input_num == 4){ 
                screen_num = 20;
             }
            else if(input_num == 5){
                screen_num = 1;
            }
            else if(input_num == 6){
                screen_num = 22;
            }
            else{cout << "Enter a valid number" << endl;}
        }
        else if(screen_num == 21){
            screen_num = 1;
        }
       
    else{cout << "Enter a valid number" << endl;}
    }

     //print_state(); cout << "size: " << user_text.get_size();cin.get();

    if(!react &&screen_num > 21){exit(0);}
    //cout << "screen num "<< screen_num << " input:" << input << endl;
    
}


int main(int argc, char **argv) {
  react = (argc > 1);
  read_text_data();

  bool just_starting = react ? _read_event_info() : true;
  while(1) {
	ifstream fs1(just_starting ? "initial_state" : "curr_state");
	State state(fs1);
	fs1.close();

    //state.print_state();  for debugging
    //cin.get();

	string input;
	if (just_starting) just_starting = false;    //at first iteration, input is an empty string
	else if (!react) getline(cin, input);

	ifstream fs2("incoming_text");
	state.update(input, fs2);
    // cout << "printing state in main:"<< endl;
    // state.print_state();

	ofstream fs3("outgoing_text"), fs4(react ? "end_state" : "curr_state");
	display(state, react ? fs3 : cout);
	state.write_to(fs4);

	if (react) {             
  	_write_react_yaml();
  	break;
	}
  }
}