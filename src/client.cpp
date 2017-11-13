/*
 * client.h
 *
 *  Created on: Nov 23, 2016
 *      Author: dan florescu
 * Rob Nash
 * Assignment:
 * HW5 final project
 * This is the client class were the manager is a friend.
 * The manager is the only one that can add accounts to clients as well as recording their transaction history.
 * This class will get the clients first and last name and the clients ID number.
 *
 */

#include "client.h"

/*
 * This is the client constructor where we will set the clients.
 * each client has an id number, first name, and  a last name.
 */
Client::Client(int identifier, string firstName, string lastName){
	id = identifier;//set the id
	first = firstName;//set the first name
	last = lastName;//set the last name
}

/*
 * This is the client destructor.
 */
Client::~Client() {

}

/*
 * This is the client copy constructor where we will copy a client.
 * We will call a separate method to copy the client.
 * Copying a clients consists of taking the id, first/last name, accounts and history.
 */
Client::Client(const Client& rhs){
	copy(rhs);//call copy to make a copy of the accounts
}

/*
 * This private method will copy the clients.
 * To copy a client we will take their id  as well as their first and last name.
 * In addition, we must also take their accounts and their transaction history.
 */
void Client::copy(const Client& rhs) {
	id = rhs.id;//copy the ids
	first = rhs.first;//copy the first name
	last = rhs.last;//copy the last name

	history = rhs.history;//copy the transactions history
	accounts = rhs.accounts;//copy the  clients accounts
}

/*
 * This getter method will get the clients id.
 */
int Client::getId(){
	return id;//return the clients id
}

/*
 * This getter method will get the first name of the client
 */
string Client::getFirst(){
	return first; // return  the first name
}

/*
 *This getter method will get the last name of the client.
 */
string Client::getLast(){
	return last;//return the last name
}

/*
 * This assignment operator will assign one client to another.
 * If the clients are not equal, then we assign one client to the other.
 * When assigning we take their id, first/last name, accounts, transaction history.
 * Return the "assigned" client.
 */
Client& Client::operator=(const Client& rhs){
	if(this != &rhs){//check if they are not equal
		copy(rhs);//then call copy which will copy the clients
	}
	return *this;//Return the "assigned" client.
}

/*
 * This is the equality operator where we check if one client is equal to another (compare based on id).
 * To check if one client is equal with another, we first check if they are both the same(if they are return true).
 * Next we compare the clients based on id's, return true if they are the same. Otherwise return false if they are not the same.
 *
 */
bool Client::operator==(const Client& other)const{
	if(this == &other || this->id == other.id){//if myself is  equal to the other or the id's are the same
		return true;//true the client are the same
	}

	return false;//false the client are not the same
}

/*
 * This is the not equal operator where we check if a client is not equals with another(compare based on id).
 * We first check if they not equal, if so return true.
 * Next we compare the clients based on id's, if they are not equal then return true.
 * If the clients are the same, return false.
 */
bool Client::operator!=(const Client& other)const{
	return !operator==(other);//return the negation of operator==
}

/*
 * This is the less than operator where we will check if one client is less than an other(compare based on id).
 * We are going to check if the client id is less than the other clients id.
 * If they are then return true, one client is less than another.
 */
bool Client::operator<(const Client& other)const{
	return (id < other.id);//is one clients id less than the other one
}

/*
 * This is the greater than operator where we will check if one client is greater than an other(compare based on id).
 * We are going to check if the client id is greater than the other clients id.
 * If they are then return true, one client is greater than another.
 */
bool Client::operator>(const Client& other)const{
	return !operator<=(other);//return the negation of operator<=
}

/*
 * This is the less than or equal to operator where we will check if one client is less than or equal to an other(compare based on id).
 * We are going to check if the client id is less than or equal to the other clients id.
 * If they are then return true, one client is less than or equal to another.
 */
bool Client::operator<=(const Client& other)const{
	if((operator==(other)) || operator<(other)){//if the client id's are equal or less than
		return true;//true one client is less than or equal to another
	}
	return false;//false,  one client is not less than or equal to another
}

/*
 * This is the greater than or equal to operator where we will check if one client is greater than or equal to an other(compare based on id).
 * We are going to check if the client id is greater than or equal to the other clients id.
 * If they are then return true, one client is greater than or equal to another.
 */
bool Client::operator>=(const Client& other)const{
	return !operator<(other);//return the negation of operator<
}

/*
 * This is the ostream operator that will output the clients information.
 * It will output the clients first and last name as well as their id.
 * Also, it will output all of the clients accounts, displaying their type and balance.
 * In addition, we will also display the clients transaction history.
 */
ostream& operator<<(std::ostream& output, const Client& obj){
	output << "Client: id=" << obj.id << ", Last Name=" << obj.last << ", First Name=" << obj.first << endl;//output the clients id, first  and last name
	list<Account>::const_iterator iter = obj.accounts.begin();//iterate through the list of accounts
	output << "\tAccounts:" << endl;//output account header
	while(iter != obj.accounts.end()){//while iterating through the accounts
		output << "\t\t" << *iter << endl;//output the accounts
		iter++;//increment the iterator
	}
	output << "\tTransaction History:" << endl;//output the transaction header
	deque<Transaction>::const_iterator iterhistory = obj.history.begin();//iterate through the deque of transactions
	while(iterhistory != obj.history.end()){//while iterating through the transaction history
		output << "\t\t" << *iterhistory << endl;//output the transaction history
		iterhistory++;//increment the  iterator
	}
	return output;//return the clients information to the console
}

/*
 * This private method will add accounts to clients.(This is a sensitive operation so only the manager can add accounts).
 * When adding an account, we will iterate through the list, and if we want to add an account that is already in the list,return false.
 * Otherwise the manager will add the account to the list.
 * Cannot have two of the same account.
 */
bool Client::addAccount(Account& acc){
	// linear search for the account
	list<Account>::iterator iter = accounts.begin();//iterate the list of accounts
	while(iter != accounts.end()) {//while iterating the list of accounts
		if(acc.getType() == iter->getType()) {//if the type we want to add equals the type in the list
			return false;//false , type of account already in the list
		}
		iter++;//increment the iterator
	}
	accounts.push_back(acc);//if no in the list add the account
	return true;//true the account was added to the list
}

/*
 * This private method will get the account ( this is a sensitive operation so only the manager can get the account).
 * While searching through the list, we check if the account we want to get is in the list, if so, return that account.
 * Otherwise, return nullptr is the account was not found in the list.
 */
Account* Client::getAccount(int type) {
	list<Account>::iterator iter = accounts.begin();//iterate the list of account
	while(iter != accounts.end()){//while iterating through the accounts
		if(type == iter->getType()){//if the type of accounts we want to get is in the list
			return &*iter;//return the target account
		}
		iter++;//increment the iterator

	}
	return nullptr;//nullptr if the account we wanted to get was not in the list.
}

/*
 * This private method will get the transaction history ( this is a sensitive operation so only the manager can get the history).
 * The manager will get the transaction history of the client.
 */
deque<Transaction>& Client::getHistory() {
	return history;//return the transaciton history
}

/*
 * This private method will record the transactions in a deque(this is a sensitive operation so only the manager can record the history).
 * The manager will record each transaction in a deque, allowing client to record their history is illegal as they can alter their history.
 */
void Client::recordTransaction(const Transaction& tr) {
	history.push_back(tr);//push the transaction history in the deque.
}





