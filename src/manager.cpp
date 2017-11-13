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

#include "manager.h"

#include <fstream>
#include <sstream>
#include <ostream>

using namespace std;

/*
 * This is a constructor that will set the size of for the undo/redo deque.
 * The size is a positive number.
 */
Manager::Manager(unsigned int size) {
	undoRedoSize = size;//set the size
}

/*
 * The manager destructor deletes all clients in the tree
 */
Manager::~Manager(){

}

/*
 * This will read input containing the client information.
 * We will separate the file, first read the clients name (first and last) as well as their id and create the the clients.
 * Next we will read the rest of the file (which contains the ten accounts) and we add the accounts to the client.
 * After all that we insert the clients into the tree.
 * We assume the data is given in correct format.
 */
void Manager::loadClients(ifstream& input){
	while(!input.eof()){
		string line;
		getline(input, line);//get each line
		stringstream ss(line);

		string tmp[3];//make a temp to hold the first three(name, and id)
		int idx = 0;//set index to zero
		while(ss >> tmp[idx++] && idx < 3){}//getting the first three from the line
		Client* client = new Client(atoi(tmp[2].c_str()), tmp[0], tmp[1]);//create a client from the information(first and last name and id)

		string token;
		int type = 0;//set the type to zero
		while(ss >> token && type < 10) {//while reading the accounts and type is less than 10->(type is only from 0-9)
			Account act(type, atoi(token.c_str()));//do the account
			type++;//increment the type each time
			client->addAccount(act);//add the account to the client
		}
		clients.insert(client);//insert the clients into the tree.
	}
}

/*
 * This method will make a transaction. We take the information from transaction data and we split it up.
 * We have a code(D,W,M,H), a source, a destination , and an amount.
 * Then we have a switch between the codes, deposit and withdraw are similar in concept, only a destination and an amount to either deposit or withdraw(check for invariants when making the transaction, for invariants use -1).
 * Next we have history were we only look for the destination when making a transaction(check for invariants when making the transaction, for invariants use -1).
 * Lastly we have move that takes all in the input, a source, destination, and an amount check for invariants when making the transaction, for invariants use -1).
 */
Transaction Manager::makeTransaction(string tokens[], bool& invalid) {
	// if params are invalid set invalid = true
	char code = tokens[0].c_str()[0];//code (D,W,M,H)
	Transaction tr;
	invalid = true;
	int second = atoi(tokens[1].c_str());//source convert from string to int
	int third = atoi(tokens[2].c_str());//destination convert from string to int
	int forth = atoi(tokens[3].c_str());//amount convert from string to int
	//switch case for each code
	switch(code) {
	case 'D':
	case 'W':
		if(second <= 0 || third <= 0 || (second < 10000 || second >= 100000) ) {//check for invariants for destination
			return tr; // it is invalid
		} else {
			tr = Transaction(code, -1, second, third);//make the proper transaction for deposit and withdraw(they are similar in concept)
		}
		break;
	case 'H':
		if(second <= 0 || (second < 999 || second >= 10000)) {//check for invariants for destination
			return tr; // it is invalid
		} else {
			tr = Transaction(code, -1, second, -1);//make the proper transaction for history(only has the destination)
		}
		break;
	case 'M':
		if(second <= 0 || third <= 0 || forth <= 0 || (second < 10000 || second >= 100000) || (third < 10000 || third >= 100000)) {//check for invariants for source and destination
			return tr; // it is invalid
		} else {
			tr = Transaction(code, second, third, forth);//make the proper transaction for move(has source, destination, and amount)
		}
		break;
	default:
		return tr; // unrecognized code
	}
	invalid = false;
	return tr;//return the successfull transaction
}

/*
 * This method will read input from a text file containing the transactions.
 * We read each line, and make the transaction if it is valid.
 * We report any invalid transactions or if the transaction was not performed.
 * If we have a valid transaction we call performTransaction which and performs the respective transaction.
 */
void Manager::loadAndPerformTransactions(ifstream& input){
	while(!input.eof()){
		string line;
		getline(input, line);//get the line
		stringstream ss(line);

		string tmp[4];//make into four
		int idx = 0;//set index to zero
		while(ss >> tmp[idx]){//while feeding in
			idx++;//increment the index
		}

		bool invalid = true;
		Transaction tr = makeTransaction(tmp, invalid);//call makeTransaction to make the respective transaction

		if(invalid) {//id the transaction is invalid
			cerr << "Invalid transaction" << endl;//print error message
			continue;//continue on with the rest of the transactions
		}
		//and then execute the transactions
		if(!performTransaction(tr)) {
			cout << "Transaction not performed" << endl;
		}
	}
}

/*
 * This method will perform the transaction for the clients.
 * This method will call doPerformTransaction to perform the nessecary transactions for the clients.
 */
bool Manager::performTransaction(Transaction& tr){
	return doPerformTransaction(tr, true);
}

/*
 * This method will perform the and switch between the code.
 * If a code is hit, (D,W,M,H) then we will call a separate methods.
 * Depending on the code the methods will either perform a deposit, withdraw, move or history.
 */
bool Manager::doPerformTransaction(Transaction& tr, bool recordUndo) {
	cout << "Performing transaction: " << tr << endl;
		switch(tr.getCode()) {//switch between the code (D,W,M,H)
		case 'D':
			return doDeposit(tr, true);//call to do the deposit
		case 'W':
			return doWithdraw(tr, true);//call to do the withdraw
		case 'M':
			return doMove(tr, true);//call to do the move
		case 'H':
			return doHistory(tr);//call to do the history
		}
		return true;
}

/*
 * This method will get the history for the client.
 * we will get the client, if the client does not exist return false.
 * Then we get the clients history and iterate through it an display their transaction history
 */
bool Manager::doHistory(const Transaction& tr) {
	cout << "\nHistory for client: " << tr.dst << endl;
	Client* theClient = getClient(tr.dst);//get the destination client
	if(theClient == nullptr){//if the client does not exist then
		cerr << "no such client" << endl;//print error message
		return false;//false no such client
	}

	deque<Transaction> history = theClient->getHistory();//get the clients history
	deque<Transaction>::iterator iter = history.begin();//iterator for the clients history
	while(iter != history.end()){//while iterating through
		 cout << *iter++ << endl;//output the clients transaction history
	}

	return true;//true if successfully reported the history
}

/*
 * This method will deposit funds into a destination account.
 * This method will get the destination client, (check if the client exists).
 * Then get the destination account, (check if account exists).
 * Then deposit the amount into the account.
 * Record the transaction if its a successful transaction and then push the transaction onto the undo deque.
 *
 */
bool Manager::doDeposit(const Transaction& tr, bool recordUndo){
	cout << "\nDeposit for client: " << getClientId(tr.dst) << endl;
	Client* dstClient = getClient(getClientId(tr.dst));//get the destination client
	if(dstClient == nullptr){//if the client does not exist
		cerr << "no such client" << endl;//print error message
		return false;//false no such client
	}

	Account* dstAcct = dstClient->getAccount(getAccountType(tr.dst));//get the destination account
	if(dstAcct == nullptr){//if the account does not exist
		cerr << "null destination account" << endl;//print error message
		return false;//false no such account
	}

	if(!dstAcct->deposit(tr.amount)) {//if could not deposit the amount into the account
		cerr << "cannot do deposit" << endl;//print error message
		return false;//false, unsuccessful deposit
	}

	// record the transaction
	dstClient->recordTransaction(tr);

	if(recordUndo){
		pushUndo(tr);//push the transaction onto the undo deque
	}

	return true;
}

/*
 * This method will withdraw funds from an account.
 * If there are insufficient funds in a an account they we will take the remaining fund from the corresponding account.
 * This is only applicable for accounts (0 and 1) and (2 and 3).
 * Next we will get the destination client, (check if the client exists).
 * Then get the destination account, (check if account exists).
 * Check if there are insufficient funds in a an account and take the corresponding account if applicable.
 * Then withdraw the amount into the account.
 * Record the transaction if its a successful transaction and then push the transaction onto the undo deque.
 */
bool Manager::doWithdraw(const Transaction& tr, bool recordUndo){
	cout << "\nWithdraw for client: " << getClientId(tr.dst) << endl;
	Client* dstClient = getClient(getClientId(tr.dst));//get the destination client
	if(dstClient == nullptr){//if the destination client does not exist
		cerr << "no such client" << endl;//print error message
		return false;//false no such client
	}

	Account* dstAcct = dstClient->getAccount(getAccountType(tr.dst));//get the destination account
	if(dstAcct == nullptr){//if the destination account does not exist
		cerr << "null destination account" << endl;//print error message
		return false;//false no such account
	}

	int dstFinal = dstAcct->getBalance()-tr.amount;//difference between the account balance and transaction amount
	if(dstFinal < 0){//if negative value
		Account* correspondantAcct = dstClient->getAccount(getCorrespondingAcctType(getAccountType(tr.dst)));//get the corresponding account
		if(correspondantAcct == nullptr){//if the corresponding account does not exist
			cerr << "Not enough funds" << endl;//print error message
			return false; //there is no other corresponding account to withdraw the difference from
		}
		Account* dstSecondAcct =  dstClient->getAccount(getCorrespondingAcctType(getAccountType(tr.dst)));//get the second destination account
		int dstSecondFinal = dstSecondAcct->getBalance() - abs(dstFinal);//difference between second destination account balance and the abs of dstfinal
		if(dstSecondFinal < 0){//if negative then
			cerr << "Not enough funds" << endl;//print error message
			return false;
		}
		dstSecondAcct->withdraw(abs(dstFinal));//deposit the remained from the seond destination account
		dstAcct->withdraw(dstAcct->getBalance());//make it zero balance
	}else{
		dstAcct->withdraw(tr.amount);//otherwise just withdraw from the destination account
	}

	dstClient->recordTransaction(tr);//record the transaction

	if(recordUndo){
		pushUndo(tr);//push the transaction onto the undo deque
	}
	return true;
}

/*
 * This method will move fund from one account into another(could be with one or two clients).
 * If there are insufficient funds in a an account they we will take the remaining fund from the corresponding account.
 * This is only applicable for accounts (0 and 1) and (2 and 3).
 * Next we will get the source client, (check if the client exists).
 * Next we will get the destination client, (check if the client exists).
 * hen get the source account, (check if account exists).
 * Then get the destination account, (check if account exists).
 * Check if there are insufficient funds in a an account and take the corresponding account if applicable.
 * Then move the amount into the respective account.
 * Record the transaction if its a successful transaction and then push the transaction onto the undo deque.
 *
 */
bool Manager::doMove(const Transaction& tr, bool recordUndo){
	cout << endl << "Move " << tr.amount << " from client " << getClientId(tr.src) << " to " << getClientId(tr.dst) << endl;
	Client* srcClient = getClient(getClientId(tr.src));//get the source client
	Client* dstClient = getClient(getClientId(tr.dst));//get the destination client
	if(srcClient == nullptr || dstClient == nullptr){//if the clients do not exist
		cerr << "no such client" << endl;//print error message
		return false;//false no such client
	}

	Account* srcAcct = srcClient->getAccount(getAccountType(tr.src));//get the source account
	Account* dstAcct = dstClient->getAccount(getAccountType(tr.dst));//get the destination account
	if(srcAcct == nullptr || dstAcct == nullptr){//if the account do not exist
		cerr << "null source or destination account" << endl;//print error message
		return false;//false no such account
	}

	int srcFinal = srcAcct->getBalance() - tr.amount;//difference between the source account balance and transaction amount
	if(srcFinal < 0){//if value negative
		Account* srcCorrespondantAcct = srcClient->getAccount(getCorrespondingAcctType(getAccountType(tr.src)));//get the source corresponding account
		if(srcCorrespondantAcct == nullptr){//if the source corresponding account do not exist
			cerr << "Not enough funds" << endl;//print error message
			return false; // not enough money in the account
		}
		Account* srcSecondAcct = srcClient->getAccount(getCorrespondingAcctType(getAccountType(tr.src)));//get the second source corresponding account
		int srcSecondFinal = srcSecondAcct->getBalance() - abs(srcFinal);//difference between second source account balance and the abs of srcfinal
		if(srcSecondFinal < 0){//if value negative
			cerr << "Not enough funds" << endl;//print error message
			return false; // not enough funds in both accounts
		}
		srcSecondAcct->withdraw(abs(srcFinal));//withdraw remainder from second source corresponding account
		srcAcct->withdraw(srcAcct->getBalance()); // basically setting the balance to zero
		dstAcct->deposit(tr.amount);//deposit the amount to the destination account
	}else{
		srcAcct->withdraw(tr.amount);//just withdraw from source account
		dstAcct->deposit(tr.amount);//and then just deposit into the destination account
	}

	srcClient->recordTransaction(tr);// record the transaction
	if(srcClient != dstClient){//if the client are not the same
		dstClient->recordTransaction(tr); // record the transaction
	}

	if(recordUndo){
		pushUndo(tr);//push the transaction onto the undo deque
	}

	return true;
}

/*
 * This method will display the clients from the tree.
 * They will be displayed in - order.
 */
void Manager::printClients(ostream& output)const{
	clients.display();//display the client

}

/*
 * This private method will add the client to the tree.
 * Only the manager can add clients.
 * We do not allow duplicates of any kind.
 * After traversing the tree and if no duplicates were found then we can insert the client into the tree.
 */
bool Manager::addClient(Client* theClient){
	//cannot add the same client
	if(clients.find(*theClient)){
		return false;//false no duplicates
	}
	//otherwise insert the client in the tree.
	clients.insert(theClient);
	return true;
}

/*
 * This private method will get the respective client.
 * Only the manager can get the client.
 * If we search through the tree and retrieve  find the client,
 * Then return the client, otherwise the client is not in the tree.
 */
Client* Manager::getClient(int clientId)const{
	Client *ret = nullptr;
	const Client toFind(clientId, "", "");//client to find with just id, and empty name
	clients.retrieve(toFind, ret);//search through the tree to retrieve the client
	return ret;//return the retrieved client
}

/*
 * This private method will get the corresponding account type.
 * If there are insufficient funds in a an account they we will take the remaining fund from the corresponding account.
 * This is only applicable for accounts (0 and 1) and (2 and 3).
 *
 */
int Manager::getCorrespondingAcctType(int acctType){
	if(acctType == 1){//if type is one then
		return 0;//return type zero
	} else if (acctType == 0){//if type is zero
		return 1;//return type one
	}
	if (acctType == 3){//if type is three then
		return 2;//return type two
	} else if (acctType == 2){//if type is two then
		return 3;//return type three
	}
	cerr << "no corresponding account" << endl;//print error message
	return -1;

}

/*
 * This will get the client id.
 * Enforce any invariant for invalid input.
 * This method will get the first four digits, ex: 1234 from 12341.
 */
int Manager::getClientId(int id){
	if(id < 0 || id > 99999){//if not in range
		cerr << "Invalid input for client id" << endl;//print error message
		return -1;
	}
	return id/10;//return the first 4 digits

}

/*
 * This will get the Account Type.
 * Enforce any invariant for invalid input.
 * This method will get the last digit, ex: 1 from 12341.
 */
int Manager::getAccountType(int id){
	if(id < 0 || id > 99999){//if not in range
		cerr << "Invalid input for account type" << endl;//print error message
		return -1;
	}
	return id % 10;//return the last digit
}

/*
 * This private method will push the transaction onto the undo deque.
 */
void Manager::pushUndo(const Transaction& tr) {
	push(tr, undoStack);//call push
}

/*
 * This private method will push the transaction onto the redo deque.
 */
void Manager::pushRedo(const Transaction& tr) {
	push(tr, redoStack);//call push
}

/*
 * This private method pushes a Transaction either on undo stack or the redo stack.
 * Makes sure that the depth of the stack is not bigger than undoRedoSize.
 */
void Manager::push(const Transaction& tr, deque<Transaction>& dq){
	if(dq.size() >= undoRedoSize){//depth of the stack is not bigger than undoRedoSize.
		dq.pop_front();//pop oldest transaction
	}
	dq.push_back(tr);//push back most recent transaction
}

/*
 * This private method will make a transaction the opposite.
 * For case D, it now becomes a withdraw.
 * For case W, it now becomes a deposit.
 * For case M, it now becomes a move but the source and destination are switched.
 */
Transaction Manager::makeOppositeTransaction(const Transaction& tr) const{
	switch(tr.code){
	case 'D':
		return Transaction('W',-1, tr.getDst(), tr.getAmount());//For case D, it now becomes a withdraw.
	case 'W':
		return Transaction('D', -1, tr.getDst(), tr.getAmount());//For case W, it now becomes a deposit.
	case 'M':
		return Transaction('M', tr.getDst(), tr.getSrc(), tr.getAmount());//For case M, it now becomes a move but the source and destination are switched
	}
	return tr;
}

/*
 * This method will undo the most recent transaction.
 * We check the size and if its zero, print message and do nothing.
 * Get and pop the most recent transaction.
 * Perform the opposite of the most recent transaction.
 * Then push the original transaction onto the redo deque.
 */
bool Manager::undo(){
	if(undoStack.size() == 0){//if size is zero
		cout << "Cannot undo, stack is empty" << endl;//print error message
		return true; // do nothing
	}
	Transaction original = undoStack.back();//get the most recent original transaction
	undoStack.pop_back();//pop it off
	Transaction opposite = makeOppositeTransaction(original);//make it the opposite
	if(doPerformTransaction(opposite, false)) { // do NOT record the opposite in the undo deque
		pushRedo(original);//push the original transaction on the redo deque
		return true;
	}
	return false;
}

/*
 * This method will redo the most recent undone transaction.
 * We check the size and if its zero, print message and do nothing.
 * Get and pop the most recent undone transaction.
 * Perform the the most recent undone transaction.
 */
bool Manager::redo(){
	if(redoStack.size() == 0){//if size is zero
		cout << "Cannot redo, stack is empty" << endl;//print error message
		return true; // do nothing
	}
	Transaction tr = redoStack.back();//get the most recent undone original transaction
	redoStack.pop_back();//pop it off
	return doPerformTransaction(tr, true); // 'true' means to record the transaction in the undo deque
}



