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

#ifndef CLIENT_H_
#define CLIENT_H_

#include <iostream>
#include <string>
#include <stack>
#include <deque>
#include <list>

#include "transaction.h"
#include "account.h"


using namespace std;

/*
 * This is the client class were the manager is a friend.
 * The manager is the only one that can add accounts to clients as well as recording their transaction history.
 * This class will get the clients first and last name and the clients ID number.
 * We compare clients by id.
 */
class Client {

private:

    friend class Manager;//only the manager can add accounts and get/record the history

	int id; // the client id has 4 digits

	string first;//first name of the client

	string last;//last name of the client

	deque<Transaction> history;//store the transaction history in a deque

	list<Account> accounts;//store the clients accounts in a list

public:


	/*
	 * Client: This is the client constructor.
	 * Precondition: None.
	 * Postcondition: This This constructor will set the client id, (client id is a 4 digit number).
	 * 				  Next will set the clients first and last name.
	 */
    Client(int id, string first, string last);

	/*
	 * ~Client: This is the client destructor.
	 * Precondition: None.
	 * Postcondition: This destructor will deallocate the clients.
	 */
    ~Client();


    /* Copy constructor: This constructor will copy a client.
     * Precondition: None.
     * Postcondition: The copy constructor will make a copy of a client(copying the first and last name as well as the client id).
     * 				  In addition, we will also copy all of the accounts and the transaction history.
     */
    Client(const Client& rhs);

    /*
     * operator=: Copy assignment operator will assign one client to another.
     * Precondition: None.
     * Postcondition: The assignment operator will assign one client to another(assigning the first and last name as well as the client id).
     */
    Client& operator=(const Client& rhs);

    /*
   	 * operator!=: This is the not equal operator, that checks if two clients are not equal(We compare clients based on id).
   	 * Precondition: None.
   	 * Postcondition: The not equal operator will return true if one client is not equal with another one. We check if the
   	 * 				  the clients are the same(if they are return false), then we check if the  client id's are not the same.
     */
    bool operator!=(const Client& other)const;

    /*
   	 * operator==: This is the equality operator, that checks for the equality of two clients(We compare clients based on id).
   	 * Precondition: None.
   	 * Postcondition: The equality operator will return true if one client is equal with another one. We check if the
   	 * 				  the clients are the same or check if the client id's are the same.
     */
    bool operator==(const Client& other)const;

    /*
   	 * operator<: This is the less than operator, that checks if one client is less than another one(We compare clients based on id).
   	 * Precondition: None.
   	 * Postcondition: The less than operator will return true if one client is less than another one. We check if the
   	 * 				  id for the client is less than the other clients  id.
     */
    bool operator<(const Client& other)const;

    /*
   	 * operator>: This is the greater than operator, that checks if one client is greater than another one(We compare clients based on id).
   	 * Precondition: None.
   	 * Postcondition: The greater than operator will return true if one client is greater than another one. We check if the
   	 * 				  id for the client is less than the other clients  id.
     */
    bool operator>(const Client& other)const;

    /*
   	 * operator>=: This is the greater than or equal to operator, that checks if one clients id is greater than another one or equal to it(We compare clients based on id).
   	 * Precondition: None.
   	 * Postcondition: The greater than or equal to operator will return true if the client id is greater than or equal to another one. We check if the
   	 * 				  id for the client is greater than or equal to the other clients id.
     */
    bool operator>=(const Client& other)const;

    /*
   	 * operator<=: This is the less than or equal to operator, that checks if one clients id is less than another one or equal to it(We compare clients based on id).
   	 * Precondition: None.
   	 * Postcondition: The less than or equal to operator will return true if the client id is less than or equal to another one. We check if the
   	 * 				  id for the client is less than or equal to the other clients id.
     */
    bool operator<=(const Client& other)const;

    /*
     * operator<<: This is the ostream operator and it will output the clients id, first name, and last name.
     * 			   In addition, it will also output all of the clients accounts(each client has 10 account in this case) and the transaction history for that respective client.
     * Precondition: None.
     * Postcondition: This will output the clients name(first and last) and their client id to the console.
     * 			      Also it will output the the clients accounts(each client has 10 accounts) as well as the clients transaction history.
     */
    friend ostream& operator<<(std::ostream& os, const Client& obj);

    /*
     * getId: This is a getter method that will get the id from the client.
     * Precondition: None.
     * Postcondition: This will get the id from the client.
     */
    int getId();

    /*
     * getId: This is a getter method that will get the first name from the client.
     * Precondition: None.
     * Postcondition: This will get the first name from the client.
     */
    string getFirst();

    /*
     * getId: This is a getter method that will get the last name from the client.
     * Precondition: None.
     * Postcondition: This will get the last name from the client.
     */
    string getLast();

private:

    /*
     *copy: This private method will copy the clients information (this is a sensitive operation and is performed by the manager).
     *Precondition: None.
     *Postcondition: This will copy the clients id as well as their first and last name. Also it will copy the clients account as well as their transaction history.
     */
    void copy(const Client& rhs);

    /*
     * addAccount: This private method will add an account to a client (this is a sensitive operation and is performed by the manager).
     * Precondition: Cannot add the same account to the client.
     * Postcondition: This will add the accounts(10 accounts) to the client. If the account could not be added, return false, then the client already has the account.
     */
    bool addAccount(Account&);

    /*
     * getAccount: This private method will get an account from a client (this is a sensitive operation and is performed by the manager).
     * Precondition: Cannot get  a clients account that does not exist.
     * Postcondition: This will get the clients accounts. If we could not get the account, return nullptr the client does not have that account.
     */
	Account* getAccount(int type);

    /*
     * getHistory: This private method will get the history of transactions (this is a sensitive operation and is performed by the manager).
     * Precondition: None.
     * Postcondition: This will get the clients history  of transactions.
     */
	deque<Transaction>& getHistory();

    /*
     * recordTransaction: This private method will record the history of transactions in a deque (this is a sensitive operation and is performed by the manager).
     * Precondition: None.
     * Postcondition: This will record ( push back) the transactions in a deque.
     */
    void recordTransaction(const Transaction& tr);

};





#endif /* CLIENT_H_ */
