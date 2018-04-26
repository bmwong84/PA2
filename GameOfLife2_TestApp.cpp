// GameOfLife2_TestApp.cpp
#include <iostream>

#include "ErrorContext.h"
#include "GameOfLife2_Tests.h"

using std::cout;
using std::endl;

using namespace Testing;
using namespace csci2312;

int main() {

	ErrorContext ec(cout);

    cout << endl << "Testing PA2!!" << endl << endl;
        
	// Cell tests
	test_cell_smoketest(ec);		//calls cell tests for default constructor

	test_cell_setget(ec);			//for setters an dgetters


    // GameOfLife tests
    test_game_smoketest(ec);		//for default constructor GameOfLife

	test_game_rules(ec);		//for execute rules

	system("pause");

    return 0;
}
