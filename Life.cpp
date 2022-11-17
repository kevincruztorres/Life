// Life simulation

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <string>
using namespace std;

const int MAXWORLDROWS = 25;
const int MAXWORLDCOLS = 80;
const int MAXROWS = MAXWORLDROWS + 2;
const int MAXCOLS = MAXWORLDCOLS + 2;
const int FILENAMESIZE = 255;

// ASCII characters to use for display
// https://theasciicode.com.ar/extended-ascii-code/block-graphic-character-ascii-code-219.html
// for interesting effect use code 219 and 176 instead of the asterisk and space
const unsigned char CELL = '*';  // 219;
const unsigned char EMPTY = ' '; // 176;

enum class State { dead = 0, alive = 1 };

/*
* initWorld is used to initialize all positions in the world
* array to the 'dead' state
*/
void initWorld(State world[][MAXCOLS]);

/*
* display is used to draw the 'world' onto the screen
* for each 'alive' cell, the value CELL is displayed
* for each 'dead' cell, the value EMPTY is displayed
* does NOT display any items in:
*   row 0, row MAXROWS-1, column 0, or column MAXCOLS-1
* since these rows and columns are used as a "border"
* around the world grid
*/
void display(State world[][MAXCOLS]);

/*
* getFile will get a filename from the user. It then attmpts
* to open the file, read its contents, and update the world
* based on the contents of the file. The file should contain
* only spaces and asterisks. A space represents a 'dead' cell
* and an asterisk represents an 'alive' cell.
* The function stops reading and exits the program if > MAXWORLDCOLS
* characters are found on one row, or if > MAXWORLDROWS rows are
* found in the file.
*/
void getFile(State world[][MAXCOLS]);

/*
* calcNewWorld is used to calculate the new state of the world
* (i.e. a new generation) based upon analyzing the current world state
*/
void calcNewWorld(State world[][MAXCOLS]);

/*
* neighborCount is used to count the number of 'alive' cells in
* the 8 neighboring positions which are surrounding position
* [row][col] in world
*/
int neighborCount(State world[][MAXCOLS], int row, int col);

int main()
{
	State world[MAXROWS][MAXCOLS];
	int generation = 0;
	bool stop = false;

	
	// TODO: set up and initialize the 'world' array



	do
	{
		// system("cls") clears the screen; only works on Windows machines
		// You will probably need to comment this out if working on
		// a non-Windows machine
		system("cls");

		display(world);
		generation++;
		cout << "Generation: " << generation << "\t";
		cout << "<ENTER> to continue / <Q + ENTER> to quit: ";
		
		// TODO: get input from user and decide whether to quit the loop
		// and whether to compute a new generation



	} while (!stop);

	return 0;
}

int neighborCount(State world[][MAXCOLS], int row, int col)
{
	// This code checks to make sure you aren't trying to count neighbors for any
	// position on row #0, or on row #MAXWORLDROWS+1,
	// or in column 0, or in columnn MAXWORLDCOLUMNS+1
	// because if you are, you are going to run into array out-of-bounds problems
	if (row < 1 || row > MAXWORLDROWS)
	{
		cerr << "ERROR: invalid row parameter " << row << " in neighborCount\n";
		exit(1);
	}
	else if (col < 1 || col > MAXWORLDCOLS)
	{
		cerr << "ERROR: invalid col parameter " << col << " in neighborCount\n";
		exit(1);
	}

	int i = 0;

	// TODO: write neighborCount code
	for (int x = 0; x < MAXROWS; x++)
	{
		// need to get inside 
		for (int y = 0; y < MAXCOLS; y++)
		{
			// first neighbor
			if (State world[x - 1, y - 1] = 1)			// idk how to fix this, like how do we get into the neighbor space
			{
				i++;
			}
			// second neighbor
			if (State world[x - 1, y] = 1)
			{
				i++;
			}
			// third neighbor
			if (State world[x - 1, y + 1] = 1)
			{
				i++;
			}
			// fourth neighbor 
			if (State world[x, y - 1] = 1)
			{
				i++;
			}
			// fifth neighbor
			if (State world[x, y + 1] = 1)
			{
				i++;
			}
			// sixth neighbor
			if (State world[x + 1, y - 1] = 1)
			{
				i++;
			}
			// seventh neighbor
			if (State world[x + 1, y] = 1)
			{
				i++;
			}
			// eigth neighbor
			if (State world[x + 1, y + 1] = 1)
			{
				i++;
			}

			// i also feel like there is a lot easier way to do this


		}



	return i;
}

void calcNewWorld(State world[][MAXCOLS])
{
	// TODO: write calcNewWorld code

	// need to create a new array to hold the new generation so it will not override the original array
	for (int i = 0; i < MAXROWS; i++)
	{
		// initialzing the rows with "empty" 
		for (int j = 0; j < MAXCOLS; j++)
		{
			if (the new neighbor count i = 0, 1, 4, 5, 6, 7, 8)
			{
				snprintf into a new array to hold the new generation[" "];
			}
			else if (the new neighbor count i = 2)
			{
				snprintf into a new array to hold the new generation["*"];
			}
			else if (the new neighbor count i = 3)
			{
				adding a new asterick so it would be the same as neighbor count of 2;
			}
		}
	}

	
}

void getFile(State world[][MAXCOLS])
{
	ifstream inFile;
	int row = 1;

	// TODO: Write getFile code
	// Make sure row is incremented each time you read a line from the file
	const int BUFFERSIZE = 30;
	char buffer[BUFFERSIZE];
	char file;							// shouldn't be a char but idk what type of variable

	cout << "Enter file name: ";
	cin >> file;						// somehow you have to access the file that the user enters
	inFile.open("file");
	
	// After file reading is finished, this code checks to see if the reading stopped
	// because of too many characters on a line in the file, or too many rows in the file
	// It is possible that you might have to change the conditions here depending on
	// exactly how you choose to read the file
	if (!inFile.eof())
	{
		if (row <= MAXWORLDROWS)
		{
			cerr << "\nERROR: Line " << row << " in input file contains more than " << MAXWORLDCOLS << " chars\n";
		}
		else
		{
			cerr << "\nERROR: There are more than " << MAXWORLDROWS << " lines in the file\n";
		}
		inFile.close();
		exit(1);
	}

	// now we have to read the file line by line
	inFile.getline(buffer, BUFFERSIZE); // this would only read one line of text
	while (!inFile.eof()) // we are not at end of file (EOF)
	{
		cout << buffer << endl;
		inFile.getline(buffer, BUFFERSIZE);			// this is how we read from a file
	}


	inFile.close();
}

void display(State world[][MAXCOLS])
{
	// TODO: write the display code

	// somehow we have to make sure that it starts displaying second row in and now in the first row because of the border
	// so we have to fix the for loops 

	for (int i = 0; i < MAXROWS; i++)
	{
		for (int j = 0; j < MAXCOLS; j++)
		{
			if (world[i][j] == (State = dead));
			{
				cout << EMPTY;
			}
			else
			{
				cout << CELL;
			}
		}
	} // we do not need to cout endl; it will reach the max columns and move onto the next one
	// if we did have the endl; then you would be going to a new line each particular point in the array
}

void initWorld(State world[][MAXCOLS])
{
	// TODO: write initWorld code
	// counting through all of the columns   
	for (int i = 0; i < MAXROWS; i++)
	{
		// initialzing the rows with "empty" 
		for (int j = 0; j < MAXCOLS; j++)
		{
			world[i][j] = State = 0;
		}
	}

}