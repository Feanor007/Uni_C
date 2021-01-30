#include <iostream>
using namespace std;
int main(){
    int x;
    int y;
    int* p_a;
    x = 1;
    y = 2;
    p_a = &x;
    cout << "x stores the int value " << x << endl;
    cout << "x is located at address (&x) " << &x << endl;
    cout << "x takes up " << sizeof(x) << " bytes" << endl;
    cout << endl;
    cout << "y stores the int value " << y << endl;
    cout << "y is located at address (&y)" << &y << endl;
    cout << "y takes up " << sizeof(y) << " bytes" << endl;
    cout << endl;
    cout << "p_a stores an address value " << p_a << endl;
    cout << "*p_a gain access to the address' content: "<<*p_a<<endl;
    cout << "p_a is located at address (&p_a) " << &p_a << endl;
    cout << "p_a takes up " << sizeof(p_a) << " bytes" << endl;
    cout << endl;
    p_a = &y;
    cout <<"After assigning the address of y (&y) into p_a..."<<endl;
    cout << endl;
    cout << "p_a stores an address value " << p_a << endl;
    cout << "*p_a gain access to the address' content: "<<*p_a<<endl;
    cout << "p_a is located at address (&p_a) " << &p_a << endl;
    cout << "p_a takes up " << sizeof(p_a) << " bytes" << endl;
    cout << endl;
    return 0;
}