#include <iostream>
using namespace std;
int main(){
    char char_in = 'a';
    int int_in = 1;
    cout << "Welcome to the Programming 2 Information Program" << endl;
    cout << "\n";

    while(char_in != 'c'){
        cout << "Select one of the following options to learn more about the course:" << endl;
        cout << "(a)Your Class mates" << endl;
        cout << "(b)Course Material" << endl;
        cout << "(c)Exit the program" << endl;
        cin >> char_in;
        if(char_in == 'a'){
            cout << "\n";
            cout << "Your classmates:" << endl;
            cout << "122 BME students" << endl;
            cout << "48 MBE students" << endl;
            cout << "\n" ;
        }
        else if(char_in == 'b'){
            cout << "\n";
            while(int_in != 3){
                cout << "Select what you would like to learn more about:" << endl;
                cout << "(1) Course textbook "<< endl;
                cout << "(2) Assignments" << endl;
                cout << "(3) Exit" << endl;
                cin >> int_in;
                if(int_in > 3){
                    cout << "please enter an integer from 1 to 3" << endl;
                }
                if(int_in == 1){
                    cout << "\n";
                    cout << "Problem Solving with C++ (Global Edition - Night Edition) by Walter Savitch & Kendrick Mock." << endl;
                    cout << "\n";
                }
                if(int_in == 2){
                    cout << "\n";
                    cout << "Assignment 1: 50% of final mark, due 4 PM on 19 February 2021" << endl;
                    cout << "Assignment 2: 50% of final mark, due 4 PM on 26 March 2021" << endl;
                    cout << "\n";
                }
            }
            cout << "\n";
            int_in = 1;
        }
        else if(char_in > 'c'){
            cout << "Please enter a character from a, b, c" << endl;
        }
    }
    cout << "\n";
    cout << "Farewell" <<endl;
    return 0;
}