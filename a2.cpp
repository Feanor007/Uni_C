#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
 #include "tictoc.h"
using namespace std;
//structs
struct Node
{
    char base;
    struct Node *next;
};

struct DNA_file
{
    string name;
    string header;
    struct Node *node;
};
//Classes
class DNADatabase;
class Menu
{
private:
    int *input;

public:
    //constructors & destructor
    Menu();
    Menu(int level, int options, DNADatabase &dna_db);
    ~Menu();

    //access functions
    int get_input();

    //standard functions
    int ask_inputs(int level, DNADatabase &dna_db);
    void display_mainmenu();
    //friends
    friend void add_files(DNA_file dna_file, DNADatabase &dna_db);
};

class DNADatabase
{
private:
    vector<struct DNA_file> dna_files;

public:
    //constructors & destructors
    //access functions
    struct DNA_file get_file(int pos);
    int get_files_size();
    //standard functions
    //friends
    friend void add_files(DNA_file dna_file, DNADatabase &dna_db);
};
//helper methods
string remove_space(string str);
string getFileExt(const string &s);
void create_node(string line, struct Node **first);
void display_linked_list(struct Node *p);
void add_files(DNA_file dna_file);
bool findSeq(struct Node *first, struct Node *second);
//constant value
const string whitespace = " \n\r\t\f\v";
int main()
{
    DNADatabase dna_db;
    Menu *main_menu = new Menu;
    main_menu->ask_inputs(0, dna_db);
    Menu *first_submenu = new Menu(0, main_menu->get_input(), dna_db);
    // struct DNA_file first_file = dna_db.get_file(0);
    // cout << "\n" ;
    // cout << first_file.header << endl;
    if (main_menu->get_input() == 2 || first_submenu->get_input() == 2)
    {
        //first_submenu->ask_inputs(1);
        // for(size_t i=0; i<dna_db.get_files_size(); i++){
        //     cout << "("<<i+1<<")"<< dna_db.get_file(i).name << endl;
        // }
        Menu *second_submenu = new Menu(0, first_submenu->get_input(), dna_db);
        second_submenu->ask_inputs(1, dna_db);
        Menu *third_submenu = new Menu(1, second_submenu->get_input(), dna_db);
        third_submenu->ask_inputs(2, dna_db);
        cout << third_submenu->get_input() << endl;
        switch (third_submenu->get_input())
        {
        case 1:
            string line;
            struct Node **input_seq = NULL;
            while (getline(cin, line))
            {
                cout << line << endl;
            }
            create_node(line, input_seq);
            //findSeq();
            break;
            // case 2:
            //     /* code */
            //     break;
            // case 3:
            //     /* code */
            //     break;
            // case 4:
            //     /* code */
            //     break;
            // case 5:
            //     /* code */
            //     break;
            // case 6:
            //     /* code */
            //     break;
            // case 7:
            //     /* code */
            //     break;
            // case 8:
            //     /* code */
            //     break;
            // case 9:
            //     /* code */
            //     break;
            // default:
            //     break;
        }
        //继续询问选项
    }

    return 0;
}

Menu::Menu()
{
    input = new int;
    display_mainmenu();
}
Menu::Menu(int level, int options, DNADatabase &dna_db)
{
    input = new int;
    if (level == 0)
    {
        switch (options)
        {
        case 1:
        {
            cout << "Enter the DNA file names:" << endl;
            cout << "For multiple files, separate them by a comma. Only .fna are recognised." << endl;
            fstream instream;
            string buffer;
            vector<string> files;
            int line_counter = 0;
            getline(cin, buffer);
            stringstream s_stream(buffer);
            while (s_stream.good())
            {
                string filename;
                string ext;
                string trim_filename;
                getline(s_stream, filename, ',');
                trim_filename = remove_space(filename);
                ext = getFileExt(trim_filename);
                if (ext.compare("fna") == 0)
                {
                    //cout << "entered file type is correct" << endl;
                    files.push_back(trim_filename);
                }
                else
                {
                    cout << "entered file type is incorrect" << endl;
                    exit(1);
                }
            }
            for (int i = 0; i < files.size(); i++)
            {
                string line;
                string buffer;
                struct DNA_file file;
                file.name = files.at(i);
                //cout << files.at(i)<< "??"<< endl;
                instream.open(files.at(i), fstream::in | fstream::out);
                if (instream.fail())
                {
                    cerr << "Error opening DNA files" << endl;
                    exit(1);
                }
                while (getline(instream, line))
                {
                    line_counter = line_counter + 1;
                    if (line_counter == 1)
                    {
                        file.header = line;
                    }
                    else
                    {
                        buffer = buffer + line;
                    }
                    //cout << line << endl;
                }
                create_node(buffer, &file.node);
                //cout << "filename is " << file.name << endl;
                //cout << "file header is " << file.header << endl;
                //cout << "sequence stored in the linked_list is the following: " << endl;
                //display_linked_list(file.node);
                add_files(file, dna_db);
                instream.close();
            }
            display_mainmenu();
            *input = 0;
            ask_inputs(0, dna_db);
            break;
        }
        case 2:
        {
            cout << "Select a DNA to process:" << endl;
            for (size_t i = 0; i < dna_db.get_files_size(); i++)
            {
                cout << "(" << i + 1 << ")" << dna_db.get_file(i).name << endl;
            }
            //add stored DNA file names
            break;
        }
        case 3:
        {
            cout << "Enter the DNA file name you would like to analyze: " << endl;
            break;
        }
        case 4:
        {
            exit(1);
            break;
        }
        }
    }
    if (level == 1)
    {
        if (options != 0)
        { //之后要改成在1到N的范围内
            cout << "(1) Find DNA sequence by input" << endl;
            cout << "(2) Find DNA sequence by file" << endl;
            cout << "(3) Add DNA sequence by input" << endl;
            cout << "(4) Add DNA sequence by file" << endl;
            cout << "(5) Delete DNA sequence by input" << endl;
            cout << "(6) Replace DNA sequence by input" << endl;
            cout << "(7) Replace DNA sequence by file" << endl;
            cout << "(8) Save edited DNA sequence" << endl;
            cout << "(9) Exit submenu" << endl;
            cout << ">" << endl;
        }
    }
}
Menu::~Menu()
{
    delete input;
}
//access functions
int Menu::get_input()
{
    return *input;
}
//standard functions
int Menu::ask_inputs(int level, DNADatabase &dna_db)
{
    switch (level)
    {
    case 0:
        while (*input > 4 || *input < 1)
        {
            string temp;
            getline(cin, temp);
            stringstream(temp) >> *input;
            if (*input<5 & *input> 0)
            {
                return *input;
            }
            cout << "please enter a number between 1 and 4 (include both ends)" << endl;
            cout << "\n";
            Menu *main_menu = new Menu;
            delete main_menu;
        }
        //return input;
    case 1:
        while (*input > dna_db.get_files_size() - 1 || *input < 1)
        {
            string temp;
            getline(cin, temp);
            stringstream(temp) >> *input;
            if (*input<dna_db.get_files_size() & *input> 0)
            {
                break;
            }
            cout << "please enter a number between 1 and " << dna_db.get_files_size() << " (include both ends)" << endl;
        }
        return *input;
    case 2:
        while (*input > 9 || *input < 1)
        {
            string temp;
            getline(cin, temp);
            stringstream(temp) >> *input;
            if (*input<10 & *input> 0)
            {
                break;
            }
            cout << "please enter a number between 1 and 9 (include both ends)" << endl;
        }
        return *input;
    default:
        cout << "Please enter a number between 0 and 2" << endl;
        *input = 0;
        return *input;
    }
}
void Menu::display_mainmenu()
{
    cout << "Welcome to the DNA Editing program" << endl;
    cout << '\n';
    cout << "Select an option:" << endl;
    cout << "(1) Load DNA(s)." << endl;
    cout << "(2) Process a DNA." << endl;
    cout << "(3) Analyse the DNA database" << endl;
    cout << "(4) Quit." << endl;
    cout << ">";
}

struct DNA_file DNADatabase::get_file(int pos)
{
    return dna_files.at(pos);
}
int DNADatabase::get_files_size()
{
    return dna_files.size();
}
//friends
void add_files(DNA_file dna_file, DNADatabase &dna_db)
{
    dna_db.dna_files.push_back(dna_file);
}
//Helper functions
string remove_space(string str)
{
    //cout << "string entered: " << str << endl;
    string temp1;
    string temp2;
    size_t lfound = str.find_first_not_of(whitespace);
    temp1 = lfound == string::npos ? "" : str.substr(lfound, str.length() - lfound);
    size_t rfound = temp1.find_last_not_of(whitespace);
    temp2 = rfound == string::npos ? "" : temp1.substr(0, rfound + 1);
    //cout << "trimmed string is " << temp2 << "??" << endl;
    return temp2;
}

string getFileExt(const string &s)
{
    size_t i = s.rfind('.', s.length());
    if (i != string::npos)
    {
        return (s.substr(i + 1, s.length() - i));
    }
    return "";
}

void create_node(string line, struct Node **first)
{
    struct Node *temp, *last;
    *first = new Node;
    (*first)->base = line.at(0);
    (*first)->next = NULL;
    last = *first;
    for (size_t i = 1; i < line.length(); i++)
    {
        temp = new Node;
        temp->base = line.at(i);
        temp->next = NULL;
        last->next = temp;
        last = temp;
    }
}
void display_linked_list(struct Node *p)
{
    while (p != NULL)
    {
        cout << p->base;
        p = p->next;
    }
}
bool findSeq(Node *first, Node *second)
{
    Node *ptr1 = first, *ptr2 = second;

    // If both linked lists are empty, return true
    if (first == NULL && second == NULL)
    {
        return true;
    }

    // Else If one is empty and other is not return
    // false
    if (first == NULL ||
        (first != NULL && second == NULL))
    {
        return false;
    }

    // Traverse the second list by picking nodes
    // one by one
    while (second != NULL)
    {
        // Initialize ptr2 with current node of second
        ptr2 = second;

        // Start matching first list with second list
        while (ptr1 != NULL)
        {
            // If second list becomes empty and first
            // not then return false
            if (ptr2 == NULL)
            {
                return false;
            }

            // If data part is same, go to next
            // of both lists
            else if (ptr1->base == ptr2->base)
            {
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
            }

            // If not equal then  break the loop
            else
                break;
        }

        // Return true if first list gets traversed
        // completely that means it is matched.
        if (ptr1 == NULL)
        {
            return true;
        }

        // Initialize ptr1 with first again
        ptr1 = first;

        // And go to next node of second list
        second = second->next;
    }
    return false;
}