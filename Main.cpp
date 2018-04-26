//Bryant Wong PA1 

#include "GameOfLife.h"

using namespace csci2312;

int main()
{
	GameOfLife cell;			//creates a GameOfLife object named cell
	//seed board

	srand(time(NULL));			//random time setter
	char firstMenu = '0';
	char secondMenu = '0';
	char thirdMenu = '0';
	std::ifstream infile;


	std::cout << "Welcome to Conway's Game of Life.  Enter how you would like to play." << std::endl;
	while (firstMenu != 3)
	{
		unsigned int iterations2=0;
		unsigned int iterations=0;
		std::cout << "1: With a randomly seeded board" << std::endl;
		std::cout << "2: With a predefined seeded board" << std::endl;
		std::cout << "3: Exit" << std::endl;
		std::cin >> firstMenu;
		switch (firstMenu)
		{
		case'1':
			cell.seedBoard();
			std::cout << "1: By number of iterations" << std::endl;
			std::cout << "2: By running one iteration at a time" << std::endl;
			std::cin >> secondMenu;
			if (secondMenu=='1')
			{
				std::cout << "Please enter the number of generations you would like the game to cycle through" << std::endl;
				std::cin >> iterations;
				cell.run(iterations);
			}
			else if (secondMenu=='2')
			{
				cell.run();
			}
			else
			{
				std::cout << "Invalid choice." << std::endl;
			}
			break;
		case'2':
			infile.open("seedin.txt");
			cell.seedBoard(infile);
			infile.close();
			std::cout << "1: By number of iterations" << std::endl;
			std::cout << "2: By running one iteration at a time" << std::endl;
			std::cin >> thirdMenu;
			if (thirdMenu == '1')
			{
				std::cout << "Please enter the number of generations you would like the game to cycle through" << std::endl;
				std::cin >> iterations2;
				cell.run(iterations2);
			}
			else if (thirdMenu == '2')
			{
				cell.run();
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


	return 0;
}