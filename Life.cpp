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
void display(State world[][MAXCOLS], int row, int col);

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
	char input;
	
	initWorld(world);
	getFile(world);

	//do while for each generation
	do
	{
		cout << "Generation: " << generation << "\t";
		cout << "<Enter> to continue / <Q + Enter> to quit:" << "\n";

		cin.get(input);

		// system("cls") clears the screen; only works on Windows machines
		// You will probably need to comment this out if working on
		// a non-Windows machine
		system("cls");

		// to make it stop or continue depending on generation
		if (input == 'Q' || input == 'q')
		{
			stop = true;
		}
		else
		{
			display(world, MAXWORLDROWS, MAXWORLDCOLS);

			calcNewWorld(world);
		}

		// must increase the generation each time
		generation++;
		
	} while (!stop);

	return 0;
}

int neighborCount(State world[][MAXCOLS], int row, int col)
{
	// need to set the counter at 0
	int count = 0;

	// calculate each one of the eight neighbors
	count = count + (int)world[row - 1][col - 1];
	count = count + (int)world[row + 1][col + 1];
	count = count + (int)world[row + 1][col - 1];
	count = count + (int)world[row - 1][col + 1];
	count = count + (int)world[row][col - 1];
	count = count + (int)world[row][col + 1];
	count = count + (int)world[row - 1][col];
	count = count + (int)world[row + 1][col];

	return count;
}

void calcNewWorld(State world[][MAXCOLS])
{
	// TODO: write calcNewWorld code

	// need to call the neighbor count function
	int count = neighborCount(world, MAXROWS, MAXCOLS);

	// this is the new array so we do not overwrite the original one
	State currentWorld[MAXROWS][MAXCOLS];

	// create for loops to get the number of neighbors for each cell
	// we are setting the new array equal to the original array
	for (int row = 0; row < MAXROWS; row++)
	{
		for (int col = 0; col < MAXCOLS; col++)
		{
			currentWorld[row][col] = world[row][col];
		}
	}

	// calculating the new world now
	for (int row = 0; row < MAXWORLDROWS; row++)
	{
		for (int col = 0; col < MAXWORLDCOLS; col++)
		{
			// create a local variable cnt for another counter 
			int cnt = neighborCount(currentWorld, row, col);

			// if else statements calculating to see if we should add life 
			if (world[row][col] == State::alive && cnt < 2)
			{
				world[row][col] = State::dead;
			}

			else
			{
				if (cnt == 3)
				{
					world[row][col] = State::alive;
				}

				else if (cnt > 3)
				{
					world[row][col] = State::dead;
				}

			}
		}
	}

}

oid getFile(State world[][MAXCOLS])
{
	// TODO: write getFile code
	ifstream inFile;
	char line[MAXCOLS];
	char array[FILENAMESIZE];
	bool check = false;

	// creating variables for reading the file
	char c;
	int col = 0;
	int row = 0;

	// having the user enter the file 
	std::cout << "Enter file name: " << '\n';
	cin.get(array, FILENAMESIZE, '\n');
	inFile.open(array);

	// error if file doesn't open
	if (inFile.fail())
	{
		cerr << "\nERROR: Input file cannot be opened.\n";
	}

	// reading the file and outputting "*" and " "
	while (!inFile.eof())
	{
		if (inFile.get(c)) {

			if (c == '\n')
			{
				row++;
				col = 0;
			}
			else {
			if (c == CELL)
				{
					world[row][col] = State::alive;
				}
				else if (c == EMPTY)
				{
					world[row][col] = State::dead;
				}
				col++;
			}
		}
	}
	// After file reading is finished, this code checks to see if the reading stopped
	// because of too many characters on a line in the file, or too many rows in the file
	// It is possible that you might have to change the conditions here depending on
	// exactly how you choose to read the file
	if (!inFile.eof() && (col >= MAXWORLDCOLS && c != '\n') || (row >= MAXWORLDROWS && c != '\n'))
	{
		if (col >= MAXWORLDCOLS && c != '\n')
		{
			cerr << "\nERROR: There are more than " << MAXWORLDROWS << " lines in the file\n";
		}
		else if (row >= MAXWORLDROWS && c != '\n')
		{
			cerr << "\nERROR: Line " << row << " in input file contains more than " << MAXWORLDCOLS << " chars\n";
		}
		inFile.close();
		exit(1);
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
