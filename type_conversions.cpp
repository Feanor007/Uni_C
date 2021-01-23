#include <iostream>
using namespace std;
int main(){
//Int to Double conversions
int x = 5;
int y = 2.2;
int z = x + 1.1;
double f = 5.5;
cout << "This is the start of int2double conversions: \n";
cout << "int(a): " << int(f) << endl;
cout << "int(y): " << int(y) << endl;
cout << "x/2: " << x/2 << endl;
cout << "x/2.0: " << x/2.0 << endl; 
//Bool to int conversions
bool a = true;
bool b = false;
bool c = 5;
bool d = -1;
bool e = !1;
int q = a + b;
int s = a*b;
int t = c-5;
cout << "This is the start of bool2int conversions: \n";
cout << "a: " << a << endl; 
cout << "b: " << b << endl; 
cout << "c: " << c << endl; 
cout << "d: " << d << endl; 
cout << "e: " << e << endl; 
cout << "q: " << q << endl; 
cout << "s: " << s << endl; 
cout << "t: " << t << endl;
//Char to int conversions
char g = 'D';
char h = 'O';
char i = 71;
int j = 'a' + 2;
int k = 'a';
int l = 116;
cout << "This is the start of char2int conversions: \n";
cout << "g: " << g << endl;
cout << "h: " << h << endl;
cout << "i: " << i << endl;
cout << "j: " << j << endl;
cout << "k " << k << endl;
cout << "l " << l << endl;
cout << "char(l): " <<  char(l) << endl;
cout << "char(j): " << char(j) << endl;
g = j;
h = k;
i = l;
cout << "g: " << g  << endl;
cout << "h: " << h << endl;
cout << "i: " << i << endl;
return 0;
}