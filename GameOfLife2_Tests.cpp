#include <iostream>
#include <iomanip>
#include <cmath>		
#include <cassert>


#include "ErrorContext.h"		
#include "GameOfLife2_Tests.h"

using std::cout;
using std::endl;
using std::setprecision;		//viewing correct number of decimals
using csci2312::Cell;		//needed to test cell class
using Testing::ErrorContext;		//for testing errors
using csci2312::GameOfLife;			//needed to test GameOfLife Class

#define DESC(x) desc(x, __LINE__)  // ugly hack, but saves some time


///////// STUDENT TASK:  Fill in implementatin for Cell tests


//  Test Cell constructor and destructor
void test_cell_smoketest(ErrorContext &ec) 
{
	Cell c;				//create an instance of class Cell named c
	bool pass;
	ec.DESC("Cell Default Constructor");	
	pass = (c.getState() == false && c.getFace() == '-');		//pass is true if the default constructor sets cell to false and face to '-'
	ec.result (pass);	
    // to do
}

//  Test Cell setters and getters
void test_cell_setget(ErrorContext &ec) 
{
	Cell c;
	bool pass;
	ec.DESC("Cell setState and getFace");
	c.setState(true);						//sets Cell c state to true (to test setter)
	pass = (c.getFace()== Cell::alive);		//pass is true if cell c is alive (to test getter)
	ec.result(pass);
}


///////// END TASK

//  Test GameOfLife constructor and destructor
void test_game_smoketest(ErrorContext &ec) {
    bool pass;
	GameOfLife* myGame;	

    ec.DESC("--- Test - GameOfLife - Smoketest ---");

    ec.DESC("Default Constructor");
    pass = true;  
        // Construct a Default GameOfLife - boardSize should be set to MAX_BOARD      
		myGame = new GameOfLife;              
		pass = (myGame->getBoardSize() == myGame->MAX_BOARD);		//if no user input, pass is true if default board size is MAX_BOARD
        ec.result(pass);
	
	ec.DESC("Destruct Default Test Game");  
        // Cleans up after previous test, destruct the object        
	    delete myGame;		   

	ec.DESC("Custom Constructor requesting a specific boad size");
	    pass = true;
	    // Construct a Custom GameOfLife - boardSize should be set to what was requested   
	    myGame = new GameOfLife(50);
	    pass = (myGame->getBoardSize() == 50);
	    ec.result(pass);

    
	ec.DESC("Destruct Custom Test Game");    
	   // Cleans up after previous test, destruct the object        
	   delete myGame;
        
}

// Game rules test
void test_game_rules(ErrorContext &ec) {
    bool pass;
	GameOfLife *myGame;

    // Run at least once!!
    // assert(numRuns > 0);

    ec.DESC("--- Test - Game Rule 110  ---");
    	
	pass = true;
	// Construct a Default GameOfLife - boardSize should be set to MAX_BOARD      
	myGame = new GameOfLife;
    
	ec.DESC("--------- Alive cell with 2 alive neighbors or 3 alive neighbors  ---");
	pass = (myGame->executeRules(2, true) == true)&&(myGame->executeRules(3, true)==true);
	ec.result(pass);

	ec.DESC("--------- Dead cell with NOT 3 alive neighbors  ---");		//one shot test to see if cell stays dead in next generation if number of neighbors is not 3
	pass = (myGame->executeRules(2, false) == false)&& (myGame->executeRules(1, false) == false)&& (myGame->executeRules(0, false) == false)
		&& (myGame->executeRules(4, false) == false)&& (myGame->executeRules(5, false) == false)&& (myGame->executeRules(6, false) == false)
		&& (myGame->executeRules(7, false) == false)&& (myGame->executeRules(8, false) == false);
	ec.result(pass);

    ///////// STUDENT TASK:  add test for the remaining rule outcomes
	ec.DESC("Alive cell with less than 2 live neighbors");		//to see if live cell dies with less than 2 live neighbors
	pass = (myGame->executeRules(1, true) == false) && (myGame->executeRules(0, true) == false);
	ec.result(pass);

	ec.DESC("Alive cell with more than 3 live neighbors");		//one shot test to see if live cell dies with more than 3 live neighbors
	pass = (myGame->executeRules(4, true) == false) && (myGame->executeRules(5, true) == false) &&
		(myGame->executeRules(6, true) == false) &&(myGame->executeRules(7, true) == false) &&
		(myGame->executeRules(8, true) == false);
	ec.result(pass);

	ec.DESC("Dead cell with 3 alive neighbors");	//test to see if dead cell comes to life with exactly 3 neighbors
	pass = (myGame->executeRules(3, false) == true);
	ec.result(pass);

    ///////// END TASK

	// Destruct the object at the end of test
	
	ec.DESC("Destruct Test Game");
	// Cleans up after previous test, destruct the object        
	delete myGame;
  
}



