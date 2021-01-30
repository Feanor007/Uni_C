#include <iostream>		// #include adds libraries of code (variables, functions, objects)
						// that you can  use. The library "iostream" has many variables,
						// functions, and objects that you can use. Here, we want to use
						// the cout and cin objects.

using namespace std;	// Having added code from a library, a series of names, such as
						// "cout" and "cin" have been introduced to your code. Since
						// in the present code, you could use the "cout" and "cin" names,
						// the compiler will look for your definitions of cout and cin.
						// So, to tell the compiler that "cout" and "cin" in this code is
						// actually the "cout" and "cin" from another namespace, you must
						// specify it with a scope resolution operator ::. Thus all uses
						// "cout" and "cin" must be written "std::cout" and "std::cin".
						// This can be cumbersome, so what we can do is to add all of the
						// names from the space you want, which in this case, is "std".
						// So, with "using namespace std;", all uses of cout and cin are
						// assumed to be from the std namespace.


// This is the global space. Variables, functions, objects, etc. may be declared here
// and will be made available to the entire program. You may define the variables and
// functions here or after the main() function.

// Tip: do not declare global variables expect for exceptional circumstances


int main()				// When you execute the program, this is the first function called
{
	// This is the first line of code run when you execute your program.

	// Most functions begin with variable declarations and definitions
	char x = 'Q';		// Here, we instruct the computer to allocate memory space big
						// enough to store a character and name that memory space 'x'.
						// We then instruct the computer to assign the 'Q' character
						// into that memory space. We can now use the name x to access
						// this memory space and the value that is stored in it.
	int row;			// Here, we instruct the computer to allocate memory space big
						// enough to store an integer and name that memory space 'row'.
	int col;			// Here, we instruct the computer to allocate memory space big
						// enough to store an integer and name that memory space 'col'.
	char board[2][2];	// Here, we instruct the computer to allocate memory space big
						// enough to store 4 characters and name the memory space 'board'.
						// The [2][2] represents that the memory space will be accessed as
						// a 2 by 2 matrix or array.

	// The board's memory space is initially filled with a random value. To fill the
	// board's memory space with meaningful values (e.g., spaces), we will need to access
	// each memory location using the [] operator.
	//board[0][0] = ' ';	// Here, [0][0] represents the first row and column element.
						// Here, we instruct the computer to place the space character
						// into the location.
	//board[0][1] = ' ';	// We then instruct the computer to fill in the rest of the array
	//board[1][0] = ' ';
	//board[1][1] = ' ';

	// Another way to fill up the array is to loop through the matrix one by one.
	for (int i = 0; i < 2; i++)			// Here, we instruct the computer to create
										// a variable i, assign 0 into it.
										// if i is less than 2,
										// then run one statement after the for ()
										// if not, run the statement after (ie statement 2)
										// after the statement is run, increment i by 1
										// do the comparison again and repeat.
		for (int j = 0; j < 2; j++)		// repeat the loop again, but for the columns
			board[i][j] = ' ';			// assign a space into each element.

	// print the board of spaces
	for (int i = 0; i < 2; i++)			// loop through the twice
	{									// since the for loop will only run one statement
										// after the 'for ()', we signify a group of
										// code as being one statement (relative to for()).
		cout << "-----\n";				// cout is a C++ object defined by the <iostream>
										// library and is used to send text to the console
										// for display. Look at the direction of the
										// arrows here. The "-----\n" string is pushed
										// into the object cout. The '\n' is a newline
										// character. Once the string is pushed into cout
										// then cout does something to have it display on
										// the command console. Magic! Not quite magic,
										// but the method is hidden in iostream.
										// You do not need to know how cout works, but you
										// must know how to use it and the '<<' operator.
										// In C++ language, cout is called an output
										// stream.
		for (int j = 0; j < 2; j++){
			cout << "|" << board[i][j];
        }	                            // Send more characters into the output stream.
		cout << "|\n";					// Send two characters to the output stream
	}
	cout << "-----" << endl;			// Send more characters into the output stream.

	// Now, let's get some user input so that we can update the state of the board
	// and display it to the user.
  
	cout << "Enter a row (0-1): ";
	cin >> row;							
	cout << "Enter a column (0-1): ";
	cin >> col;

	board[row][col] = x;				// update the memory space value at position
										// row, col

	// print the board of spaces (same code as above)
	for (int i = 0; i < 2; i++)
	{
		cout << "-----\n";
		for (int j = 0; j < 2; j++)
			cout << "|" << board[i][j];
		cout << "|\n";
	}
	cout << "-----" << endl;

	return 0;							// Return a 0 value to the operating system
}										// The int main() function is completed.