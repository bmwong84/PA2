// Points to remember:
//
// Cell's object state comprises of two data members: state and a matching face
// 
// The game has an additional element 'displayBoard' which needs to be set to either
// currentLife or nextLife to avoid copying of elements from one board to the other  
// The constructor should set 'display board' to currentLife board, to start with.
// Then, in each cycle the 'display board' needs to be pointed at the other board, 
// which at that point will be hold 'next life' 

#include "GameOfLife2_csci2312.h"

using std::cout;
using std::endl;

namespace csci2312

{

	//Cell::Cell()	//default constructor
	//{
	//};

	//default constructor
	Cell::Cell() : state(false), face(dead)	//sets all to false state and dead face as default
	{
	};

	Cell::Cell(bool state)		//sets cell's state to passed bool
	{
		setState(state);
	}

	Cell::~Cell()
	{
	};		//default destsructor

	//returns the cell's current state, alive or dead
	bool Cell::getState() const
	{
		return state;
	}

	//sets a cell's state to the passed state, if the state is false, face is dead .
	void Cell::setState(bool newState)
	{
		if (newState == false)
		{
			face = dead;
		}
		else if (newState == true)
		{
			face = alive;
		}
		state = newState;
		//sets dead or alive given newState true or false
	}

	//returns face
	char Cell::getFace() const
	{
		return face;
	}

	GameOfLife::GameOfLife()   //default constructor
	{
		boardSize = MAX_BOARD;		//sets boardSize to MAX_BOARD
		currentLife = new CellPtr[boardSize + 2];		//creates an array of CellPtrs that currentLife points to
		nextLife = new CellPtr[boardSize + 2];			//same for above, nextLife points to
		for (unsigned int count = 0; count < boardSize + 2; count++)
		{
			currentLife[count] = new Cell[boardSize + 2];			//creates a two dimensional array "currentLife" with myBoardSize+2 rows by myBoardSize+2 (for halo) columns
			nextLife[count] = new Cell[boardSize + 2];
		}
		//displayBoard = currentLife;		//originally used as efficient display pointer, but found out it is not needed
		//nextBoard = nextLife;
	}

	GameOfLife::GameOfLife(size_t size)   //custom constructor with passed size
	{
		boardSize = size;		//sets boardSize to the passed size
		currentLife = new CellPtr[boardSize + 2];
		nextLife = new CellPtr[boardSize + 2];
		for (unsigned int count = 0; count < boardSize + 2; count++)
		{
			currentLife[count] = new Cell[boardSize + 2];			//creates a two dimensional array "currentLife" with boardSize+2 rows by boardSize+2 (for halo) columns
			nextLife[count] = new Cell[boardSize + 2];
		}
		//displayBoard = currentLife;	//originally used as efficient display pointer, but found out it is not needed
		//nextBoard = nextLife;
	}


	//copy constructor creates a deep copy of the passed game
	GameOfLife::GameOfLife(const GameOfLife& game)
	{
		boardSize = game.boardSize;			//set the copy boardSize to the original's boardSize
		currentLife = new CellPtr[boardSize + 2];		//create a dynamic array as the copy
		nextLife = new CellPtr[boardSize + 2];

		for (unsigned int count = 0; count < boardSize + 2; count++)
		{
			currentLife[count] = game.currentLife[count];		//makes each currentLife CellPtr in the copy point to the CellPtr in the passed game at the same location
			nextLife[count] = game.nextLife[count];				//same as above for nextLife
		}
		//displayBoard = currentLife;		//originally used as efficient display pointer, but found out it is not needed
		//nextBoard = nextLife;
	}

	//overloaded = operator
	GameOfLife & GameOfLife::operator =(const GameOfLife& right)
	{
		if (boardSize != right.boardSize)		//if the two are not the same sized arrays, create a new array of the original's size
		{
			delete[] currentLife;
			delete[] nextLife;
			boardSize = right.boardSize;
			currentLife = new CellPtr[boardSize + 2];
			nextLife = new CellPtr[boardSize + 2];
		}
		
		for (unsigned int count = 0; count < boardSize + 2; count++)
		{
			currentLife[count] = right.currentLife[count];		//copies right side CellPtrs for currentLife to left side
			nextLife[count] = right.nextLife[count];
		}
		return *this;
	}


	//did exception handling with "seedBoard" and failure to open input file
	//GameOfLife::GameOfLife(size_t myBoardSize) throw (std::bad_alloc) 
	//{
	//       // To test the exception, then remove:

	//	 throw (std::bad_alloc());

	//}

	//destructor
	GameOfLife::~GameOfLife()
	{
		delete[] currentLife;
		delete[] nextLife;
		//cout << "Object deconstructed \n";
	};

	//gives the board size
	size_t GameOfLife::getBoardSize() const
	{
		return boardSize;
	}

	//seed board from file using overloaded >> operator with exception throwing if failure to open file
	void GameOfLife::seedBoard(istream& fileName) throw(FileIOException)
	{
		if (fileName.fail())		//if the file fails to open...
		{
			throw FileIOException();		//throw FileIOException
		}
		else
		{
			std::cout << "Seeding board from file..." << std::endl;
			fileName >> *this;								//uses overloaded >> operator to seed the board from file
		}
	}

	void GameOfLife::seedBoard(size_t seeds)		//passed number of seeds, seeds the board randomly based on random number generator
	{
		unsigned int count = 0;
		std::cout << "Seeding initial board randomly" << std::endl;
		while (count < seeds)
		{
			int vert = (rand() % boardSize+1);		//randomizes location
			int horiz = (rand() % boardSize+1);
			if (currentLife[vert][horiz].getState() == false)		//if the cell at location is dead, set the cell to alive and increment the number of seeded cells
			{
				count++;
				currentLife[vert][horiz].setState(true);	//sets current cell to alive
			}
		}
			//std::cout << currentLife[vert][horiz].getFace();		//displays the status of the current board so the user can see the parent board.  this was replaced with std::cout << *this in the run function
	}
	

	//member function to check the status of neighbors (alive or dead) and returns an int of number of alive neighbors
	unsigned int GameOfLife::CheckNeighbors(int vert, int horiz)
	{
		unsigned int neighborAlive = 0;
		if (currentLife[vert - 1][horiz - 1].getState())			//checks cell to the upper left of current cell
			neighborAlive++;										//increments if the cell is alive
		if (currentLife[vert - 1][horiz].getState())				//checks cell to the top of current cell
			neighborAlive++;
		if (currentLife[vert - 1][horiz + 1].getState())			//checks cell to the upper right of current cell
			neighborAlive++;
		if (currentLife[vert][horiz - 1].getState())				//etc etc.
			neighborAlive++;
		if (currentLife[vert][horiz + 1].getState())
			neighborAlive++;
		if (currentLife[vert + 1][horiz - 1].getState())
			neighborAlive++;
		if (currentLife[vert + 1][horiz].getState())
			neighborAlive++;
		if (currentLife[vert + 1][horiz + 1].getState())
			neighborAlive++;

		return neighborAlive;										//returns the number of neighboring cells that are alive
	}

	//runs the game asking whether the user wants to run another iteration using efficient calculateNextGen function
	void GameOfLife::run()
	{
		int count = 0;		//counts number of generations
		std::string yn = "y";
		do
		{		//runs a do while loop, running the game 1 generation
			count++;
			std::cout << "Generation " << count << std::endl;
			std::cout << *this;				//uses overloaded << operator to print the entire board
			calculateNextGen();			
			//calculateNextGen(displayBoard, nextBoard);		//was used in previous efficient display, but found out not needed

			std::cout << std::endl;
			std::cout << "Would you like to run another iteration (y)?  Or press any other key to return to menu" << std::endl;
			std::cin >> yn;
			std::cout << std::endl;
		} while (yn == "y" || yn == "Y");
	}


	//runs the game for certain number of iterations using efficient calculateNextGen function
	void GameOfLife::run(unsigned int numberOfIterations)	//passed number of generations
	{
		for (unsigned int count = 0; count < numberOfIterations; count++)		//while the counter is greater than the number of iterations requested
		{
			
			std::cout << "Generation " << count+1 << std::endl;
			std::cout << *this;					//cout the entire board with overloaded << operator
			//calculateNextGen(displayBoard, nextBoard);	//was used in previous efficient display, but found out not needed
			calculateNextGen();
		}
	}

	//switches between displaying "currentLife" and "nextLife" boards based on which is the actual "next" board
	void GameOfLife::calculateNextGen()
	{
		CellPtr *temp;		//creates a temporary CellPtr pointer
		for (unsigned int vert = 1; vert < boardSize + 1; vert++)			//sets the nextLife board 
		{
			for (unsigned int horiz = 1; horiz < boardSize + 1; horiz++)
			{
				nextLife[vert][horiz].setState(executeRules(CheckNeighbors(vert, horiz), currentLife[vert][horiz].getState()));	//sets state of nextLife cell at position based on # of neighbors alive and whether or not itself is alive
			}																							
		}

		temp = currentLife;					//toggles between current and next 
		currentLife = nextLife;				
		nextLife = temp;

		/*displayBoard = next;
		nextBoard = current;			//was used in previous efficient display, but found out not needed
		currentLife = displayBoard;
		nextLife = nextBoard;*/
	}
	

	//for setting the next state to alive or dead
	bool GameOfLife::executeRules(unsigned int countAlive, bool curState)
	{
		//if itself is alive and less than 2 neighbors are alive, cell dies
		if (curState && countAlive < 2)
			return false;
		//	else if (self==alive && (neighborAlive ==2 || neighborAlive==3))
		else if (curState && (countAlive == 2 || countAlive == 3))
			return true;
		//	else if (self == alive && neighborAlive>3)
		else if (curState && countAlive > 3)
			return false;
		//	else if (self== dead && neighborAlive ==3)
		else if (curState == false && countAlive == 3)
			return true;
		//all other instances, cell is dead
		else
			return false;
	}

	//reads in data from file and sets current state to predefined board
	istream& operator >> (std::istream& in, GameOfLife& board)		//overloaded >> operator to read in data and seed predefined board
	{
		for (unsigned int vert = 1; vert < board.boardSize + 1; vert++)					//for each cell in visible board
		{
			for (unsigned int horiz = 1; horiz < board.boardSize + 1; horiz++)
			{
				int input;
				in >> input;
				board.currentLife[vert][horiz].setState(input);				//sets the state of the currentLife at each cell coordinate to the state from the seeding file
			}
		}
		return in;
	}

	
	//  Display game's board 
	ostream& operator << (ostream& out, const GameOfLife& board)
	{
		for (unsigned int vert = 1; vert < board.boardSize + 1; vert++)					//displays the initial board
		{
			for (unsigned int horiz = 1; horiz < board.boardSize + 1; horiz++)
			{
				out << board.currentLife[vert][horiz].getFace();		//couts the cell's face at position
			}
			out << std::endl;							//at the end of each horizontal row, new line
		}
		out << std::endl;		//new line at the end of the output
		return out;
	}

	void GameOfLife::printBoard()		//used for testing copy constructor
	{
		std::cout << *this;
	}
}



//seeds the board without using overloaded >> operator, replaced by seedBoard that uses overloaded >> operator
//void GameOfLife::seedBoard(istream& fileName) throw(FileIOException)
//{
//	if (fileName.fail())
//	{
//		throw FileIOException();
//	}
//	else
//	{
//		std::cout << "Seeding board from file..." << std::endl;
//		int totalCells = boardSize * boardSize;
//		typedef int *inputArrayPtr;		//pointer to dynamic array to hold file input
//		inputArrayPtr intcount;
//		intcount = new int[totalCells];		//creates a dynamic array to hold the input data for each cell in the board
//		for (int input = 0; input < totalCells; input++)
//			fileName >> intcount[input];								//adds each input line to the array in order
//		int inputseeding = 0;
//		for (int vert = 1; vert < boardSize + 1; vert++)					//for each cell in visible board
//		{
//			for (int horiz = 1; horiz < boardSize + 1; horiz++)
//			{
//				bool seeding = false;
//				if (intcount[inputseeding] == 0)						//if the seeding file has a 0
//					seeding = false;									//set bool to false
//				else if (intcount[inputseeding] == 1)
//					seeding = true;
//				currentLife[vert][horiz].setState(seeding);				//sets the state of the currentLife at each cell coordinate to the state from the seeding file
//				inputseeding++;
//			}
//		}
//		delete[] intcount;
//	}
//}

//replaced by file exception throwing version of seedBoard
//void GameOfLife::seedBoard(istream& fileName) 
//{
//	std::cout << "Seeding board from file..." << std::endl;
//	int totalCells = boardSize * boardSize;
//	typedef int *inputArrayPtr;		//pointer to dynamic array to hold file input
//	inputArrayPtr intcount;
//	intcount = new int[totalCells];		//creates a dynamic array to hold the input data for each cell in the board
//	for (int input = 0; input < totalCells; input++)
//		fileName >> intcount[input];								//adds each input line to the array in order
//	int inputseeding = 0;
//	for (int vert = 1; vert < boardSize + 1; vert++)					//for each cell in visible board
//	{
//		for (int horiz = 1; horiz < boardSize + 1; horiz++)
//		{
//			bool seeding=false;
//			if (intcount[inputseeding] == 0)						//if the seeding file has a 0
//				seeding = false;									//set bool to false
//			else if (intcount[inputseeding] == 1)
//				seeding = true;
//			currentLife[vert][horiz].setState(seeding);				//sets the state of the currentLife at each cell coordinate to the state from the seeding file
//			inputseeding++;
//		}
//	}
//	delete[] intcount;
//}


//runs the game until user wishes to stop.  replaced with efficient display using calculateNextGen
//void GameOfLife::run() 
//{
//	std::string yn = "y";
//	do
//	{
//		std::cout << *this;
//		for (int vert = 1; vert < boardSize + 1; vert++)			//sets the nextLife board 
//		{
//			for (int horiz = 1; horiz < boardSize + 1; horiz++)
//			{
//				nextLife[vert][horiz].setState(executeRules(CheckNeighbors(vert, horiz), currentLife[vert][horiz].getState()));	//O_o  set the state of the nextLife at coordinates vert/horiz 
//			}																							//to the bool returned by the member function CheckNeighbors at vert/horiz, passing vert horiz
//		}
//		for (int vert = 1; vert < boardSize + 1; vert++)					//sets currentLife array to nextLife array in preparation for next generation
//		{
//			for (int horiz = 1; horiz < boardSize + 1; horiz++)
//			{
//				currentLife[vert][horiz].setState(nextLife[vert][horiz].getState());
//			}
//		}
//		std::cout << std::endl;
//		std::cout << "Would you like to run another iteration (y)?  Or press any other key to return to menu" << std::endl;
//		std::cin >> yn;
//		std::cout << std::endl;
//	}
//	while (yn == "y" || yn == "Y");
//}


//runs the game for certain number of iterations.  replaced with efficient display using calculateNextGen
//void GameOfLife::run(unsigned int numberOfIterations)
//{
//	for (unsigned int count = 0; count < numberOfIterations; count++)
//	{
//		std::cout << *this;
//		for (int vert = 1; vert < boardSize + 1; vert++)			//sets the nextLife board 
//		{
//			for (int horiz = 1; horiz < boardSize + 1; horiz++)
//			{
//				nextLife[vert][horiz].setState(executeRules(CheckNeighbors(vert, horiz), currentLife[vert][horiz].getState()));	//O_o  set the state of the nextLife at coordinates vert/horiz 
//			}																							//to the bool returned by the member function CheckNeighbors at vert/horiz, passing vert horiz
//		}
//		for (int vert = 1; vert < boardSize + 1; vert++)					//sets currentLife array to nextLife array in preparation for next generation
//		{
//			for (int horiz = 1; horiz < boardSize + 1; horiz++)
//			{
//				currentLife[vert][horiz].setState(nextLife[vert][horiz].getState());
//			}
//		}
//	}
//}

////switches between displaying "currentLife" and "nextLife" boards based on which is the actual "next" board
////previously used 2 pointers "displayBoard" and "nextBoard" until figured out we could do the same thing wtih "currentLife" and "nextLife"
//void GameOfLife::calculateNextGen(CellPtr* current, CellPtr* next)
//{
//	CellPtr *temp;
//	//current = currentLife;
//	//next = nextLife;
//	for (unsigned int vert = 1; vert < boardSize + 1; vert++)			//sets the nextLife board 
//	{
//		for (unsigned int horiz = 1; horiz < boardSize + 1; horiz++)
//		{
//			next[vert][horiz].setState(executeRules(CheckNeighbors(vert, horiz), current[vert][horiz].getState()));	//O_o  set the state of the nextLife at coordinates vert/horiz 
//		}																							//to the bool returned by the member function CheckNeighbors at vert/horiz, passing vert horiz
//	}

//	temp = currentLife;					//toggles between current and next 
//	currentLife = nextLife;
//	nextLife = temp;

//	/*displayBoard = next;
//	nextBoard = current;
//	currentLife = displayBoard;
//	nextLife = nextBoard;*/
//}


////reads in data from file and sets current state to predefined board, replaced with more efficient version
//istream& operator >> (std::istream& in, GameOfLife& board)		//overloaded >> operator to read in data and seed predefined board
//{
//	int totalCells = board.boardSize * board.boardSize;
//	typedef int *inputArrayPtr;		//pointer to dynamic array to hold file input
//	inputArrayPtr intcount;
//	intcount = new int[totalCells];		//creates a dynamic array to hold the input data for each cell in the board
//	for (int input = 0; input < totalCells; input++)
//		in >> intcount[input];								//adds each input line to the array in order
//	int inputseeding = 0;
//	for (unsigned int vert = 1; vert < board.boardSize + 1; vert++)					//for each cell in visible board
//	{
//		for (unsigned int horiz = 1; horiz < board.boardSize + 1; horiz++)
//		{
//			bool seeding = false;
//			if (intcount[inputseeding] == 0)						//if the seeding file has a 0
//				seeding = false;									//set bool to false
//			else if (intcount[inputseeding] == 1)
//				seeding = true;
//			board.currentLife[vert][horiz].setState(seeding);				//sets the state of the currentLife at each cell coordinate to the state from the seeding file
//			inputseeding++;
//		}
//	}
//	delete[] intcount;
//	return in;
//}