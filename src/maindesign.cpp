/*
 * main.cpp
 *
 *  Created on: Nov 23, 2016
 *      Author: dan florescu
 * Rob Nash
 * Assignment:
 * HW5 final project
 * This is the main class were we test the program.
 * The main will open a file input stream for a text file containing client information("hw5data.txt").
 * Then we ask the manager to load the clients and their accounts.
 * Then will open a file input stream for a text file("hw5commands.txt") containing a list of transactions.
 * Then we ask the manager to read and perform the transactions.
 * The manager will decide what to do with invalid clients and/or transactions.
 * Then and the end of the (end of the program)  the manager will print all clients and their transaction history.
 *
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "manager.h"

#include "bst.h"

using namespace std;

/*
int main() {

	Manager manager(10); // depth of undo/redo stack(s) is 10

	ifstream clientData;
	string clientDataFile = "/home/dan/workspace/HW5/src/hw5data.txt";

	clientData.open(clientDataFile.c_str());

	if(!clientData) {
		cerr << "Could not open client data file " << clientDataFile << endl;
		return 1;
	}

	manager.loadClients(clientData);
	clientData.close();

	ifstream commandData;
	string commandDataFile = "/home/dan/workspace/HW5/src/hw5command.txt";

	commandData.open(commandDataFile.c_str());
	if(!commandData){
		cerr << "Could not open command data file " << commandDataFile << endl;
		return 1;
	}

	manager.loadAndPerformTransactions(commandData);

	commandData.close();

	manager.printClients(cout);

	return 0;
}*/




