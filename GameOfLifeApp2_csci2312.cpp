// *********************************************************************
//  This program demostrates the Game Of Life 
//  
// *********************************************************************


#include <iostream>
#include <cstdlib>
#include <string>

#include "GameOfLife2_csci2312.h"

using std::cout;
using std::endl;
using std::cin;
using namespace csci2312;		//custom namespace with Cell and GameOfLife classes


// ======================
//     main function
// ======================
int main()

{

	GameOfLife* myGame;		//creates an instance of class GameOfLife named myGame

    // Construct the game anticipating memory allocation issues  note::I chose the exception throwing for file input
	try {
		
		myGame = new GameOfLife(20);
	}
	catch (std::bad_alloc) {
		cout << "Failed to allocate memory for a new game" << endl;

        system("pause");
		return(1);
	};

	////////// STUDENT TASK - go on with your menus etc

	/*testing copy constructor.  commented out for actual program
	test succeeds, copy constructor and overloaded = operator both successfully copy testGame*/
	//GameOfLife testGame;
	//std::ifstream testInfile;
	//testInfile.open("seedin.txt");		
	//testGame.seedBoard(testInfile);		
	//testInfile.close();
	//std::cout << "test game contents:" << std::endl;
	//testGame.printBoard();
	//GameOfLife copyGame(testGame);	
	//std::cout << "copy game contents:" << std::endl;
	//copyGame.printBoard();
	//GameOfLife comparatorGame;
	//comparatorGame = testGame;
	//std::cout << "overloaded = copy game contents:" << std::endl;
	//comparatorGame.printBoard();
	//std::cin.get();


	srand(time(NULL));			//random time setter
	char firstMenu = '0';		
	char secondMenu = '0';
	char thirdMenu = '0';
	std::ifstream infile;		//creates an input stream named infile
	unsigned int inputBoardSize;	//to hold custom board size
	std::cout << "Welcome to Conway's Game of Life." << std::endl;
	std::cout << "Please enter your desired board size of X by X rows and columns " << std::endl<< "when using a randomly seeded board" << std::endl;
	std::cin >> inputBoardSize;
	GameOfLife gameLife(inputBoardSize);		//creates gameLife with boardSize = inputBoardSize
	GameOfLife predefGameLife;		//creates an instance of GameOfLife class for the predefined board
	while (firstMenu != 3)
	{
		unsigned int iterations2 = 0;
		unsigned int iterations = 0;
		unsigned int numberOfSeeds = 0;

		std::cout << "1: Play Conway's Game of Life with a randomly seeded board " << std::endl<< "of the size you entered. (You entered " << inputBoardSize <<")"<< std::endl;
		std::cout << "2: Play Conway's Game of Life with a predefined seeded board of size 30" << std::endl;
		std::cout << "3: Exit" << std::endl;
		std::cin >> firstMenu;

		switch (firstMenu)
		{
		case'1':
			std::cout << "Please enter the number of starting live cells you would like in this board" << std::endl;
			std::cin >> numberOfSeeds;
			if (numberOfSeeds > (inputBoardSize*inputBoardSize))
			{
				std::cout << "Board cannot hold that many cells, returning to main menu" << std::endl;
				break;
			}
			gameLife.seedBoard(numberOfSeeds);				//calls the member function to randomly seed the board
			std::cout << "1: By number of iterations" << std::endl;
			std::cout << "2: By running one iteration at a time" << std::endl;
			std::cin >> secondMenu;
			if (secondMenu == '1')
			{
				std::cout << "Please enter the number of generations you would like the game to cycle through" << std::endl;
				std::cin >> iterations;
				gameLife.run(iterations);		//calls the member function to run the game for "iterations" number of generations
			}
			else if (secondMenu == '2')
			{
				gameLife.run();			//calls the member function to run the game, asking the user if they want to run another iteration
			}
			else
			{
				std::cout << "Invalid choice." << std::endl;
			}
			break;
		case'2':
			try
			{
				infile.open("seedin.txt");		//opens the text document "seedin" that has the predefined seeded board for input
				//infile.open("");			//to test exception handling
				predefGameLife.seedBoard(infile);		//calls the member function to seed the board from infile
				infile.close();
			}
			catch (FileIOException)		//if there is a file input exception, this runs
			{
				std::cout << "Could not open seedin.txt file, returning to main menu" << std::endl;
				break;
			}
			
			std::cout << "1: By number of iterations" << std::endl;
			std::cout << "2: By running one iteration at a time" << std::endl;
			std::cin >> thirdMenu;
			if (thirdMenu == '1')
			{
				std::cout << "Please enter the number of generations you would like the game to cycle through" << std::endl;
				std::cin >> iterations2;
				predefGameLife.run(iterations2);	//runs the predefined board through number of iterations
			}
			else if (thirdMenu == '2')
			{
				predefGameLife.run();		//runs the predefined board for 1 generation, asking if the user wants to run more
			}
			else
			{
				std::cout << "Invalid choice." << std::endl;
			}
			break;
		case '3':
		{
			return 0;
			break;
		}
		default:
			std::cout << "Invalid choice." << std::endl;
		}
	}


    ///////// END TASK

	delete myGame;  // invokes GameOfLife destructor 

	return 0;
}

