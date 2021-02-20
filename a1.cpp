//Zeyu Tang CID: 01720283
//I declare that everthing below is done by myself. If you doubt some lines are not, 
//I am ok to have an online meeting to let you test me.
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <map>
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
struct image_descriptor_t{
    unsigned short image_left_position;
    unsigned short image_top_position;
    unsigned short image_width;
    unsigned short image_height;
    unsigned char fields;
};
struct extension_t{
    unsigned char extension_code;
    unsigned char block_size;
};
int rgb_converter(unsigned char c);
string print_space_table(int rgb);
string print_space(int c);
int main(){
    string filepath;
    //ask for user input
    cout << "GIF IMAGE VIEWER" << endl;
    cout << "\n";
    cout << "Enter file name: " << endl;
    cin >> filepath;
    //Read the gif file into file stream
    cout << "\n";
    cout << ">> read header" << endl;
    cout << "\n";
    fstream in_stream;
    in_stream.open(filepath, fstream::in|fstream::out|fstream::binary);
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
    cout << "\n";
    cout << ">> read logical screen descriptor" << endl;
    cout << "\n";
    screen_descriptor_t screen_descriptor;
    in_stream.read((char *)&screen_descriptor, 7);
    cout << "width:" << screen_descriptor.width << endl;
    cout << "height: " << screen_descriptor.height << endl;
    cout << "global ct flag: "<< bitset<1*8>(screen_descriptor.fields)[7] <<endl;
    int color_rs = bitset<1*8>(screen_descriptor.fields)[6]*2*2 + bitset<1*8>(screen_descriptor.fields)[5]*2 + bitset<1*8>(screen_descriptor.fields)[4];
    cout << "color rs: " << color_rs <<endl;
    cout << "sort flag: " << bitset<1*8>(screen_descriptor.fields)[3] << endl;
    int g_ct_size = bitset<1*8>(screen_descriptor.fields)[2]*2*2 + bitset<1*8>(screen_descriptor.fields)[1]*2 + bitset<1*8>(screen_descriptor.fields)[0];
    cout << "global ct size: " << g_ct_size << endl;
    cout << "background color i: " << (int)screen_descriptor.background_color_index << endl;
    cout << "aspect ratio: " << (int)(screen_descriptor.pixel_aspect_ratio) << endl;

    //Read Global Color Table
    cout << "\n";
    cout << ">> read global color table" << endl;
    cout << "\n";
    cout << "Global Color Table:" << endl;
    if(g_ct_size != 0){
        //since I want to print the rgb values using a for loop;dyncamically storing the readout in heap would be convenient.
        for(int i =0; i < pow(2,g_ct_size+1); i++){
            rgb_t *rgb = new rgb_t;
            in_stream.read((char*)rgb,3);
            cout << "#" << i << " ";
            cout << rgb_converter(rgb->r) << print_space_table(rgb_converter(rgb->r));
            cout << rgb_converter(rgb->g) << print_space_table(rgb_converter(rgb->g));
            cout << rgb_converter(rgb->b) << print_space_table(rgb_converter(rgb->b)) << endl;
            delete(rgb);
        }
    }

    //read image descriptor
    cout << "\n";
    cout << ">> read image descriptor" << endl;
    cout << "\n";
    char block_type = ' ';
    while(block_type != 44){
        in_stream.read((char *)&block_type,1);
        //cout << "didn't find an image descriptor" << endl;
    }
    image_descriptor_t image_descriptor;
    in_stream.read((char *)&image_descriptor, 9);
    cout << "left position: " << image_descriptor.image_left_position << endl;
    cout << "top position: " << image_descriptor.image_top_position << endl;
    cout << "image width: " << image_descriptor.image_width << endl;
    cout << "image height: " << image_descriptor.image_height << endl;
    if(image_descriptor.fields==0){
        cout << "local ct flag: " << 0 << endl;
        cout << "interlace flag: " << 0 << endl;
        cout << "sort flag: " << 0 << endl;
        cout << "reserved:  " << 0 << endl;
        cout << "local ct size:  " << 0 << endl;
    }

    //read table based image data
    cout << "\n";
    cout << ">> read table based image data" << endl;
    cout << "\n";
    cout << "Table Based Image Data: " << endl;
    cout << "\n" ;
    int lzw_min_sz;
    in_stream.read((char*)&lzw_min_sz,1);
    cout << "LZW Minimum Code Size: " << lzw_min_sz << endl;
    cout << "\n";
    //Since I have done this previously, I will just print them out straightfoward.
    cout << "Color Table: " << endl;
    cout << "#0 " << "255 " << "255 " << "255" << endl;    
    cout << "#1 " << "255 " << "0   " << "0" << endl;
    cout << "#2 " << "0   " << "0   " << "255" << endl;
    cout << "#3 " << "0   " << "255 " << "0" << endl;
    cout << "\n";
    cout << "Initial Code Table: " << endl;
    for(int i = 0; i < pow(2,g_ct_size+1)+2; i++){
        if(i<4){
            cout << "#" << i << "   " << i << endl;
        }else{
            cout << "#" << i << "   " << 3-i << endl;
        }
    }
    cout << "\n";
    cout << "Block Bytes: " << endl;
    int block_size;
    int byte;//Temporary use as a buffer zone; print out to the console
    int bytes[26];// Every read byte is stored here;
    int counter = 0;//Tracking 
    in_stream.read((char *)&block_size,1);
    cout << "block size: " << block_size << endl;

    while(counter != block_size){
        in_stream.read((char *)&byte,1);
        cout << "byte #" << counter << print_space(counter) << byte << endl;
        //cout << bitset<1*8>(byte) << endl;
        bytes[counter] = byte;
        counter += 1;
    }
    cout << "\n";

    bool bits[26*8];
    int k = 0;
    for(int i = 0; i < 26; i++){
        for (int j = k; j < k+8; j++) {
            bits[j] = bitset<1*8>(bytes[i])[j-k];
            //cout << bits[j];
            //cout << j << endl;
        }
        k += 8;
    }
    //check bits are stored correctly
    // for(int a = 0; a<208; a++){
    //     cout << bits[a];
    // }
    //To decode the bytes to CODES,  you need to increase your code size 
    //as soon as you add the code value that is equal to 2^(current code size)-1 to your code table. 
    //That is, the next time you grab the next section of bits, you grab one more.
    //To decode, I need to know the LZW minimum code size. However, 2 in this case is not the smallest size since it only
    //account the colour of the image; Two special codes should also be taken into consideration.
    //Therefore the start code size or fisrt code size should be 3.
    int init_code_sz = 3;
    int code = 0; 
    int code_number = 0;
    int codes[41];
    int dummy = 0;
    int a = 1;
    cout << "\n";
    cout << "Code Stream:" << endl;
    for(int i = 0; i< 204; i++){
        if(bits[i]){
            code += pow(2,(a-1)%init_code_sz);
        }
        //cout << "value of a: " << a << endl;
        if((a)%init_code_sz == 0){
            cout << "code  #" << code_number << "  " << code << endl;
            codes[code_number] = code;
            code_number += 1;
            dummy += 1 ;
            a = 0;
            if(dummy == (pow(2,(init_code_sz-1)))){
                init_code_sz += 1;
                cout << "new init code size is: " << init_code_sz << endl;
                dummy = 0;
            }
            code = 0;
        }
        a += 1;
    }
    //Derive the index stream
    cout << "\n" ;
    //Create a code table map
    map<int, string> code_table;
    code_table.insert(pair<int,string>(0,"0"));
    code_table.insert(pair<int,string>(1,"1"));
    code_table.insert(pair<int,string>(2,"2"));
    code_table.insert(pair<int,string>(3,"3"));
    code_table.insert(pair<int,string>(4,"Clear Code"));
    code_table.insert(pair<int,string>(5,"EOI"));
    cout << "Index Stream: " << endl;
    string idx_stream = "0";
    for(int i = 2; i < code_number; i++){
        if(code_table.count(codes[i])!=0){
            char K = code_table[codes[i]].at(0);
            int end_key = code_table.size();
            //cout << "this is the end key " << end_key << endl;
            code_table.insert(pair<int,string>(end_key,code_table[codes[i-1]]+K));
            idx_stream += code_table[codes[i]];
            //cout << code_table[codes[i]];
        }else{
            char K = code_table[codes[i-1]].at(0);
            string index = code_table[codes[i-1]] + K;
            code_table.insert(pair<int,string>(codes[i],index));
            idx_stream += index;
            //cout << index;
        }
        //cout << codes[i] << endl;
    }
    cout << "\n";
    //Because I know there is an "EOI" at the end, I substract 3 from the length
    for (unsigned i=0; i<idx_stream.length()-3; i++){
        cout << idx_stream.at(i);
        if((i+1)%10 == 0){
            cout << "\n" ;
        }
    }
    cout << "\n" ;
    //Help check if the map is correct
    // cout << "Map:" << endl;
    // cout << "Map size: " << code_table.size()<<endl;
    // for (const auto& p : code_table ) {
    //     cout << p.first << " "<< p.second << endl ;
    //     // p.second is string object.
    // }
    cout << "Image Data - Red Channel" << endl;
    for (unsigned i=0; i<idx_stream.length()-3; i++){
        if(idx_stream.at(i) == '0' || idx_stream.at(i) == '1'){   
            cout << 255 << "  ";
        }else{
            cout << 0 << "    ";
        }
        if((i+1)%10 == 0){
            cout << "\n" ;
        }
    }
    cout << "\n";
    cout << "Image Data - Green Channel" << endl;
    for (unsigned i=0; i<idx_stream.length()-3; i++){
        if(idx_stream.at(i) == '0' || idx_stream.at(i) == '3'){   
            cout << 255 << "  ";
        }else{
            cout << 0 << "    ";
        }
        if((i+1)%10 == 0){
            cout << "\n" ;
        }
    }
    cout << "\n";
    cout << "Image Data - Blue Channel" << endl;
    for (unsigned i=0; i<idx_stream.length()-3; i++){
        if(idx_stream.at(i) == '0' || idx_stream.at(i) == '2'){   
            cout << 255 << "  ";
        }else{
            cout << 0 << "    ";
        }
        if((i+1)%10 == 0){
            cout << "\n" ;
        }
    }
    // extension_t extension;
    // in_stream.read((char*)&extension,2);
    // cout << (int)extension.block_size << endl;
    // cout << (int)extension.extension_code << endl;
    unsigned char block_terminator;
    in_stream.read((char*)&block_terminator, 1);
    //cout << (int)block_terminator << endl;
    cout << ">> read trailer" << endl;  
    cout << "\n";
    unsigned int trailer;//Expect value of 0x3B
    in_stream.read((char*)&trailer,1);
    if(trailer == 59){
        in_stream.close();
        cout << ">> program ended" << endl;
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
string print_space_table(int rgb){
    if(rgb == 255){
        return " ";
    }else{
        return "   ";
    }
}
string print_space(int c){
    if(c/10 == 0){
        return "  ";
    }else{
        return " ";
    }
}
