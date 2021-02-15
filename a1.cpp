#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;
struct screen_descriptor_t{
        short width;
        short height;
        unsigned char fields;
        unsigned char background_color_index;
        unsigned char pixel_aspect_ratio;
};
struct rgb_t{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};
int rgb_converter(unsigned char c);
string print_space(int rgb);
int main(){
    string filepath;
    //ask for user input
    cout << "GIF IMAGE VIEWER" << endl;
    cout << "Enter file name: " << endl;
    cin >> filepath;
    //Read the gif file into file stream
    ifstream in_stream;
    in_stream.open(filepath);
    if(in_stream.fail()){
        cerr << "Error opening gif" << endl;
        exit(1);
    }
    //extract the header 
    cout << "Header: " << endl;
    char header[6];
    string sig;
    string version;
    in_stream.read(header,6);
    for (int i = 0; i<6; i++){
        if(i<3){
            sig += header[i];
        }else{
            version += header[i];
        }
    }
    cout << "\n";
    cout << "Signature: " << sig << endl;
    cout << "Version: " << version << endl;

    //Read logical screen descriptor 
    screen_descriptor_t screen_descriptor;
    in_stream.read((char *)&screen_descriptor, 7);
    cout << "width:" << screen_descriptor.width << endl;
    cout << "height: " << screen_descriptor.height << endl;
    //cout << "fields " << bitset<1*8>(screen_descriptor.fields) << endl;
    cout << "global ct flag: "<< bitset<1*8>(screen_descriptor.fields)[7] <<endl;
    int color_rs = bitset<1*8>(screen_descriptor.fields)[6]*2*2 + bitset<1*8>(screen_descriptor.fields)[5]*2 + bitset<1*8>(screen_descriptor.fields)[4];
    cout << "color rs: " << color_rs <<endl;
    cout << "sort flag: " << bitset<1*8>(screen_descriptor.fields)[3] << endl;
    int g_ct_size = bitset<1*8>(screen_descriptor.fields)[2]*2*2 + bitset<1*8>(screen_descriptor.fields)[1]*2 + bitset<1*8>(screen_descriptor.fields)[0];
    cout << "global ct size: " << g_ct_size << endl;
    cout << "background color i: " << (int)screen_descriptor.background_color_index << endl;
    cout << "aspect ratio: " << (int)(screen_descriptor.pixel_aspect_ratio) << endl;

    //Read Global Color Table
    if(g_ct_size != 0){
        //since I will print the rgb values using a for loop, I will dyncamically store the readout in heap
        for(int i =0; i < 4; i++){
            rgb_t *rgb = new rgb_t;
            in_stream.read((char*)rgb,3);
            cout << "#" << i << " ";
            cout << rgb_converter(rgb->r) << print_space(rgb_converter(rgb->r));
            cout << rgb_converter(rgb->g) << print_space(rgb_converter(rgb->g));
            cout << rgb_converter(rgb->b) << print_space(rgb_converter(rgb->b)) << endl;
            delete(rgb);
        }
    }
    return 0;
}
int rgb_converter(unsigned char c){
    int value = 0;
    for(int i = 0; i < 8; i++){
        value += bitset<1*8>(c)[i]*pow(2,i);
    }
    return value;
}
string print_space(int rgb){
    if(rgb == 255){
        return " ";
    }else{
        return "   ";
    }
}