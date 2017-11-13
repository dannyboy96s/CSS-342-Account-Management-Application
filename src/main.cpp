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

#include "manager.h"

#include <iostream>
#include "bst.h"

using namespace std;

/*
 * AT THE BOTTOM IS THE TESTING FOR THE WHOLE PROGRAM.
 * Here is where we test the program.
 * I have done incremental testing, ex, testing the tree with clients.
 * Testing if the accounts and transactions. Also other misc testing.
 * If you wanted to see the tests of the other classes they are commented out.
 *
 */
int main(){

	/*BSTree<int> a;

	cout << (a.isEmpty() ? "true, isempty" : "false, not empty") << endl;

	int* x = new int(10);
	int* y = new int(100);
	int* z = new int(1);
	int* b = new int(25);
	int* c = new int(5);
	int* d = new int(200);
	int* in = new int(50);
	int* init = new int(6);

    a.insert(x);
    a.insert(y);
    a.insert(z);
    a.insert(b);
    a.insert(c);
    a.insert(d);
    if(a.insert(x)) {
    	cerr << "insert or find are broken" << endl;
    	return 1;
    }
    if(a.insert(d)) {
        cerr << "insert or find are broken" << endl;
        return 1;
    }
    a.insert(in);
    a.insert(init);

	a.display();

	if(!a.find(10)) {
		cerr << "insert or find are broken" << endl;
		return 1;
	}

	if(a.find(123423423)) {
		cerr << "insert or find are broken" << endl;
		return 1;
	}

	int* found = nullptr;
	if(!a.retrieve(10, found) || *found != 10) {
		cerr << "retrieve is broken" << endl;
		return 1;
	}

	if(a.retrieve(124323234, found)) {
		cerr << "retrieve is broken" << endl;
		return 1;
	}

	cout << (a.isEmpty() ? "true, isempty" : "false, not empty") << endl;*/





	//client testing

	/*BSTree<Client> ctree;

	Client* first = new Client(1234, "dan", "florescu");
	Client* second = new Client(4567, "dani", "florescu");
	Client* cpy = first;
	Client* four = new Client(6798, "danut", "florescu");
	//Client* five = four;
	Client* six = new Client(1996, "danny", "florescu");
	Client* seven = new Client(1000, "da", "nny");
	Client* same = new Client(4444, "danut", "florescu");
	Client* same2 = new Client(4444, "danut", "florescu");
	Client* mystery = new Client(9999, "mys", "tery");


	ctree.insert(first);
	ctree.insert(second);

	if(ctree.insert(cpy)){
		cerr << "insert or find is broken" << endl;
		return 1;
	}

	Client c1(*first);
	if(ctree.insert(&c1)) {
		cerr << "insert or find is broken" << endl;
		return 1;
	}

	ctree.insert(four);
	ctree.insert(six);
	ctree.insert(seven);

	ctree.display();



	if(!ctree.find(*first)){
		cerr << "find is broken" << endl;
		return 1;
	}

	if(ctree.find(*mystery)){
		cerr << "find is broken" << endl;
		return 1;
	}

	Client* isfound = nullptr;
	if(!ctree.retrieve(*second, isfound) || *isfound != *second){
		cerr << "retrieve is broken" << endl;
		return 1;
	}

	if(ctree.retrieve(*mystery, isfound)){
		cerr << "retrieve is broken" << endl;
		return 1;
	}



	//testing the operators
	if(*first == *second){
		cerr << "operator== is broken" << endl;
		return 1;
	}


	if(!(first == cpy)){
		// this compares POINTERS and NOT using operator==
		cerr << "pointer comparison is broken (my ass!)" << endl;
		return 1;
	}

	if(!(*same2 == *same)){
		cerr <<"operator== is broken" << endl;
		return 1;
	}

	if(!same2->operator==(*same)){
		cerr <<"operator== is broken" << endl;
		return 1;
	}

	if(!(first != second)){
		cerr << "operator!= is broken" << endl;
		return 1;
	}

	if(cpy != first){
		cerr << "operator= is broken" << endl;
		return 1;
	}

	if(!(first <= second)){
		cerr << "operator<= is broken" << endl;
		return 1;
	}

	if(!(second >= first)){
		cerr << "operator>= is broken" << endl;
		return 1;
	}


	// testing transactions
	bool invalid = false;
	Transaction tr = Manager::makeTransaction('D', 1234, 1234, 500, invalid);
	if(!invalid) {
		cerr << "Transaction invariant checking is broken" << endl;
		return 1;
	}
	if(invalid) {
		tr = Manager::makeTransaction('D', -1, 1234, 500, invalid);
	}

	Transaction tr2 = Manager::makeTransaction('W', -1, 4321, 1000, invalid);
	Transaction tr3 = Manager::makeTransaction('M', 7894, 4568, 1500, invalid);
	Transaction tr4 = Manager::makeTransaction('W', -1, 9876, 2000, invalid);
	Transaction tr5 = Manager::makeTransaction('W', -1, 4711, 100, invalid);
	Transaction amystery = Manager::makeTransaction('D', -1, 4711, 100, invalid);

	Transaction broken = Manager::makeTransaction('M', 7894, 4568, -1, invalid);
	if(!invalid) {
		cerr << "Transaction invariant checking is broken" << endl;
		return 1;
	}

	broken = Manager::makeTransaction('M', 7894, -1, 1500, invalid);
	if(!invalid) {
		cerr << "Transaction invariant checking is broken" << endl;
		return 1;
	}

	broken = Manager::makeTransaction('H', 123, 123, 123, invalid);
	if(!invalid) {
		cerr << "Transaction invariant checking is broken" << endl;
		return 1;
	}

	Account ac = Manager::makeAccount(-1, 500, invalid);
	if(!invalid) {
		cerr << "account invariant checking is broken" << endl;
	}
	ac = Manager::makeAccount(1, -100, invalid);
	if(!invalid) {
		cerr << "account invariant checking is broken" << endl;
	}
	ac = Manager::makeAccount(1, 500, invalid);
	Account ac1 = Manager::makeAccount(9, 5500, invalid);*/

	//testing the whole program

	ifstream clientdata("/home/dan/workspace/HW5/src/hw5data.txt");

	if(!clientdata){
		cerr << "could not open file" << endl;
		return 1;
	}

	Manager manager(10);
	manager.loadClients(clientdata);
	cout << endl << "***** Clients BEFORE any transaction *****" << endl;
	manager.printClients(cout);

	clientdata.close();


	//string transactiondatafile = "/home/dan/workspace/HW5/src/hw5command.txt";
	string transactiondatafile = "/home/dan/workspace/HW5/src/cmd.txt";

	ifstream transactioncommands(transactiondatafile);

	manager.loadAndPerformTransactions(transactioncommands);

	cout << endl << "***** Clients AFTER performing transaction from file *****" << endl;
	manager.printClients(cout);

	transactioncommands.close();

	cout << endl << "Performing undo" << endl;
	manager.undo();
	cout << endl << "***** Clients AFTER performing undo *****" << endl;
	manager.printClients(cout);

	cout << endl << "Performing undo" << endl;
	manager.undo();
	cout << endl << "***** Clients AFTER performing undo *****" << endl;
	manager.printClients(cout);

	cout << endl << "Performing redo" << endl;
	manager.redo();

	cout << endl << "***** Clients AFTER performing redo *****" << endl;
	manager.printClients(cout);


	cout.flush();
	cerr.flush();


	/*int id = 12341;
	cout << "num=" << id << ", account type=" <<  Manager::getAccountType(id) << endl;
	int id2 = 67899;
	cout << "num=" << id2 << ", account type=" <<  Manager::getAccountType(id2) << endl;
	int id3 = -12341;
	cout << "num=" << id3 << ", account type=" <<  Manager::getAccountType(id3) << endl;
	int id4 = 123456798;
	cout << "num=" << id4 << ", account type=" <<  Manager::getAccountType(id4) << endl;


	int cid = 12341;
	cout << "num=" << cid << ", client id=" << Manager::getClientId(cid) << endl;
	int cid2 = 67899;
	cout << "num=" << cid2 << ", client id=" << Manager::getClientId(cid2) << endl;
	int cid3 = -12341;
	cout << "num=" << cid3 << ", client id=" << Manager::getClientId(cid3) << endl;
	int cid4 = 12341123;
	cout << "num=" << cid4 << ", client id=" << Manager::getClientId(cid4) << endl;*/



}




