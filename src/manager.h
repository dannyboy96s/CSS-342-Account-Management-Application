/*
 * manager.h
 *
 *  Created on: Nov 23, 2016
 *      Author: dan florescu
 * Rob Nash
 * Assignment:
 * HW5 final project
 * All of the business logic is in the Manager class.
 * The manager creates and manages a list of clients using a binary search tree (so lookups are performed in O(NlogN) time.
 * When printed, the clients are traversed in-order (ascending by client ID).
 * The manager will handle sensitive information such as loading clients from a input stream.
 * The manager can create accounts for clients and perform any necessary transactions; successfully performed transactions are recorded in client’s transaction history.
 * The manager also records successful transactions in and an undo deque.
 * The manager keeps track of the transactions in case a client wants to "undo" the most recent transaction or "redo" the most recent undone transaction.
 * The manager is friend to Client and Account and is the only entity that can perform sensitive operations.
 *
 */

#ifndef MANAGER_H_
#define MANAGER_H_


#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <ostream>
#include <fstream>

#include "bst.h"
#include "transaction.h"
#include "client.h"

using namespace std;

/*
 * The manager class has all the business logic.
 * The manager will load clients and accounts from a text file and store them in a binary search tree.
 * Next the manager will load and perform the transactions for each clients.
 * When the manager performs a transaction we record the transaction in the clients history as well in the undo deque.
 * The manager can undo the most recent transaction and redo the most recent undone transaction.
 * After perform all the transactions we display the client with their account before any transactions were performed and
 * when all the transactions have been perform we show the clients with their adjusted accounts, and each of their transaction performed.
 *
 */
class Manager {

private:

	unsigned int undoRedoSize;//positive size for the undo/redo deque

	deque<Transaction> undoStack;//for undoing transaction are stored in a deque

	deque<Transaction> redoStack;//for redoing transaction are stored in a deque

	BSTree<Client> clients;//binary search tree to store clients.


public:

	/*
	 * Manager: This is the default constructor.
	 * Precondition: None.
	 * Postcondition: This is the default constructor
	 */
	Manager(){}

	/*
	 * Manager: This is constructor that will set  a size for the undo/redo.
	 * Precondition: None.
	 * Postcondition: This constructor will set a positive number for the undo /redo size.
	 */
	Manager(unsigned int undoRedoSize);

	/*
	 * ~Manager: This is the destructor.
	 * Precondition: None.
	 * Postcondition: This destructor will deallocate the memory.
	 */
	~Manager();

	/*
	 * performTransaction: This method will perform the transaction be calling doPerformTransaction.
	 * Precondition: None.
	 * Postcondition: The manager will be able to perform the transactions for the clients.
	 */
	bool performTransaction(Transaction& tr);

	/*
	 * undo: This method will undo the most recent transaction(only the manager can perform this operation).
	 * Precondition: None.
	 * Postcondition: The manager can undo the most recent transaction for the clients. It will pop from the back the most recent transaction
	 * 			      and make it the opposite. And then perform the transaction and push the original transaction onto the redo deque.
	 */
	bool undo();

	/*
	 * redo: This method will redo the most recent undone transaction(only the manager can perform this operation).
	 * Precondition: Cannot undo history.
	 * Postcondition: The manager can redo the most recent undone transaction for the clients. It will pop from the back the transaction
	 * 			      and then perform the transaction which gets pushed back onto undo deque.
	 */
	bool redo();

	/*
	 * printClients: This method will display the clients.
	 * Precondition: Cannot redo history..
	 * Postcondition: The manager will be able to display the clients, with all of their information, including name, id, account types, balances and their transactions.
	 */
	void printClients(ostream&) const;

	/*
	 * loadClients: This method will read the client input from a text file and load the clients with their accounts.
	 * Precondition: None.
	 * Postcondition: This will load the read each line and extract the clients information, each client has first and last name,
	 *                 an id,  and 10 accounts with their respective balances. After we finish we then insert the clients into the tree.
	 */
	void loadClients(ifstream& input);

	/*
	 * loadAndPerformTransactions: This method will read the transaction input from a text file and load the transactions.
	 * Precondition: None.
	 * Postcondition: This will load the read each line and extract the transaction information. There are four type of transactions,first
	 * 				  we have Deposit, second, Withdraw, third, Move, and lastly History. After reading the transactions, we perform them by calling performTransaction and
	 * 				  if it was a success then we record the transaction.
	 */
	void loadAndPerformTransactions(ifstream& input);

	/*
	 * This static method is used to make an account.
	 * If the type of the account is out of bounds (0-9) and the balance is negative,
	 * then that is an invalid account. Otherwise return the valid account.
	 */
	static Account makeAccount(int type, int balance, bool& invalid){
		Account acc;
		invalid = true;
		if(type < 0 || type > 9 || balance < 0){//if the type is not between 0-9 and balance is negative
			return acc;//invalid account
		}
		acc = Account(type, balance);//set the account
		invalid = false;
		return acc;//return the valid account
	}

private:

	/*
	 * addClient: This method will add the  clients to the tree.
	 * Precondition: Cannot add duplicates into the tree.
	 * Postcondition: This will first check if the the client is in the tree, if so return false, cannot add duplicates.
	 * 			      Otherwise if not in the tree then we add the client to the tree.
	 */
	bool addClient(Client*);

	/*
	 * getClient: This method will get the  clients from the tree.
	 * Precondition: None.
	 * Postcondition: This will search through the tree and retrieve the client if he/she does exist.
	 *                Otherwise we return null if no such client exists.
	 */
	Client* getClient(int clientId) const;

	/*
	 * doPerformTransaction: This method will perform the transactions.
	 * Precondition: None.
	 * Postcondition: The manager will be able to perform the transactions for the clients by calling helper methods based on the type of transaction(D,W,M,H).
	 */
    bool doPerformTransaction(Transaction& tr, bool recordUndo);

	/*
	 * getClientId: This method will get the client id from the 5 digit number from the transaction.
	 * Precondition: None.
	 * Postcondition: The method will return the four digit client id, but before returning we check for any invariants.Ex(returns 1234 from 12341).
	 */
    static int getClientId(int id);

	/*
	 * getAccountType: This method will get the account type from the 5 digit number from the transaction.
	 * Precondition: None.
	 * Postcondition: The method will return the single digit account type, but before returning we check for any invariants.Ex(returns 1 from 12341).
	 */
    static int getAccountType(int id);

	/*
	 * getCorrespondingAcctType: This method will get the corresponding account type.
	 * Precondition: None.
	 * Postcondition: The method will return the corresponding account type,or -1 if no such correspondence.
	 *                Ex: returns 0 if passed 1 (and the other way around, as 0 and 1 are correspondent).
                      return 2 if passed 3 (and the other way around, as 2 and 3 are correspondent).
                      This will only happen for accounts (0 and 1) as well as (2 and 3) when their is insufficient funds in one account.
	 */

    int getCorrespondingAcctType(int acctType);

	/*
	 * makeOppositeTransaction: This method will get the take the orignal transaction and make it the opposite.
	 * Precondition: Cannot make history transaction opposite.
	 * Postcondition: The method will return the opposite transaction.
	 * 				  Ex(if case deposit, make it withdraw).
	 * 				  Ex(if case withdraw , make it deposit).
	 * 				  Ex(if case Move , make it Move but switch the source and destination clients).
	 *
	 */
    Transaction makeOppositeTransaction(const Transaction& tr) const;

	/*
	 * pushUndo: This method will push the transaction onto the undo deque.
	 * Precondition: None.
	 * Postcondition: The method will  call push which will push back the transaciton in the undo deque.
	 */
    void pushUndo(const Transaction& tr);

	/*
	 * pushRedo: This method will push the transaction onto the redo deque.
	 * Precondition: None.
	 * Postcondition: The method will  call push which will push back the transaction in the redo deque.
	 */
    void pushRedo(const Transaction& tr);

	/*
	 * push: This method will push the transaction onto the undo or redo deque.
	 * Precondition: None.
	 * Postcondition: The method pushes a Transaction either on undo stack or the redo stack. Makes sure that the depth of the stack is not bigger than undoRedoSize.
	 */
    void push(const Transaction& tr, deque<Transaction>& dq);

	/*
	 * makeTransaction: This method will make a proper transaction.
	 * Precondition: None.
	 * Postcondition: The method will make a transaction, by doing so we check for an invariants, if there are then it is an invalid transaction.
	 *
	 */
    static Transaction makeTransaction(string tokens[], bool& invalid);

	/*
	 * doHistory: This method will return the transaction history for the client.
	 * Precondition: None.
	 * Postcondition: The method gets the client, return false if no such client and return the clients transaction history.
	 */
    bool doHistory(const Transaction& tr);

	/*
	 * doDeposit: This method will return the a deposit for the client.
	 * Precondition: None.
	 * Postcondition: The method gets the destination client and account and deposit the amount(check for any invariants). If a successful transaction record it in the clients history and push the transaction onto the undo deque.
	 */
    bool doDeposit(const Transaction& tr, bool recordUndo);

	/*
	 * doWithdraw: This method will return the a withdraw for the client.
	 * Precondition: None.
	 * Postcondition: The method gets the destination client and account and withdraws the amount(check for any invariants). If a successful transaction record it in the clients history and push the transaction onto the undo deque.
	 */
    bool doWithdraw(const Transaction& tr, bool recordUndo);

	/*
	 * doMove: This method will return the a move for the client.
	 * Precondition: None.
	 * Postcondition: The method gets the destination and source clients and accounts and moves the amount(check for any invariants). If a successful transaction record it in the clients history and push the transaction onto the undo deque.
	 */
    bool doMove(const Transaction& tr, bool recordUndo);

};


#endif /* MANAGER_H_ */
