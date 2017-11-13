/*
 * account.h
 *
 *  Created on: Nov 23, 2016
 *      Author: dan florescu
 * Rob Nash
 * Assignment:
 * HW5 final project
 * This is the account class were the manager is a friend.
 * The manager is the only one that can deposit or withdraw funds.
 * This class will get the balance for each account.
 * In addition, this class will get the type of LOSE account.
 * There are ten LOSE accounts that each client has:
 * 0: Money Market, 1: Prime Money Market, 2:  Long-Term Bond, 3:  Short-Term Bond,
 * 4: 500 Index Fund, 5: Capital Value Fund, 6: Growth Equity Fund, 7: Growth Index Fund,
 * 8: Value Fund, 9: Value Stock Index.
 *
 */

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <ostream>

using namespace std;

/*
 * This is the account class were the manager is a friend.
 * The manager is the only one that can deposit or withdraw funds.
 * This class will get the balance for each account.
 * In addition, this class will get the type of LOSE account.
 * There are ten LOSE accounts that each client has:
 * 0: Money Market, 1: Prime Money Market, 2:  Long-Term Bond, 3:  Short-Term Bond,
 * 4: 500 Index Fund, 5: Capital Value Fund, 6: Growth Equity Fund, 7: Growth Index Fund,
 * 8: Value Fund, 9: Value Stock Index.
 */
class Account {

private:

    friend class Manager; // only the Manager can deposit/withdraw

	int type; // 1 digit from (0-9) they represent the type of account

	int balance;// the balance of an account

public:

	/*
	 * ~Account: This is the account destructor.
	 * Precondition: None.
	 * Postcondition: This destructor will deallocate the accounts.
	 */
    ~Account();

    /* Copy constructor: This constructor will copy an account.
     * Precondition: None.
     * Postcondition: The copy constructor will make a copy of an account(copy the type and balance).
     */
    Account(const Account& rhs);

    /*
     * operator=: Copy assignment operator will assign one account to another.
     * Precondition: None.
     * Postcondition: The assignment operator will assign one account to another(assign the type and balance).
     */
    Account& operator=(const Account& rhs);

    /*
   	 * operator!=: This is the not equal operator, that checks if two accounts are not equal.
   	 * Precondition: None.
   	 * Postcondition: The not equal operator will return true if one account is not equal with another one. We check if the
   	 * 				  the accounts are the same  and check if the  type and balance are not the same.
     */
    bool operator!=(const Account& other)const;

    /*
   	 * operator==: This is the equality operator, that checks for the equality of two accounts.
   	 * Precondition: None.
   	 * Postcondition: The equality operator will return true if one account is equal with another one. We check if the
   	 * 				  the accounts are the same or check if the type and balance are the same.
     */
    bool operator==(const Account& other)const;

    /*
   	 * operator<: This is the less than operator, that checks if one account is less than another one.
   	 * Precondition: None.
   	 * Postcondition: The less than operator will return true if one account is less than another one. We check if the
   	 * 				  type and balance for the account are less than the other account.
     */
    bool operator<(const Account& other)const;

    /*
   	 * operator>: This is the greater than operator, that checks if one account is greater than another one.
   	 * Precondition: None.
   	 * Postcondition: The greater than operator will return true if one account is greater than another one. We check if the
   	 * 				  type and balance for the account are greater than the other account.
     */
    bool operator>(const Account& other)const;

    /*
   	 * operator>=: This is the greater than or equal to operator, that checks if one account is greater than another one or equal to it.
   	 * Precondition: None.
   	 * Postcondition: The greater than or equal to operator will return true if one account is greater than or equal to another one. We check if the
   	 * 				  type and balance for the account are greater than or equal to the other account.
     */
    bool operator>=(const Account& other)const;

    /*
   	 * operator<=: This is the less than or equal to operator, that checks if one account is less than another one or equal to it.
   	 * Precondition: None.
   	 * Postcondition: The less than or equal to operator will return true if one account is less than or equal to another one. We check if the
   	 * 				  type and balance for the account are less than or equal to the other account.
     */
    bool operator<=(const Account& other)const;

    /*
     * operator<<: This is the ostream operator and it will output the account.
     * Precondition: None.
     * Postcondition: This will output the accounts to the console showing the type and balance.
     */
    friend ostream& operator<<(std::ostream& os, const Account& obj);

    /*
     * getBalance: This is a getter method that will get the balance for the account.
     * Precondition: None.
     * Postcondition: This will get the balance from the account.
     */
	int getBalance();

    /*
     * getType: This is a getter method that will get the type for the account.
     * Precondition: None.
     * Postcondition: This will get the type (type of account ranges from 0-9) from the account.
     */
    int getType();

private:

    /*
     * Private account constructor that will set an account.
     * An account has a type (ranging from 0-9) and it has a balance(not negative).
     */
    Account(int type, int balance);

    /*
     * Private default constructor.
     */
    Account(){}

    /*
     * This is the deposit method were the manager can perform a deposit.
     * When depositing, there cannot be a negative input.
     */
	bool deposit(int);

    /*
     * This is the withdraw method were the manager can perform a withdraw.
     * When withdrawing, there cannot be a negative input.
     * (cannot have initial withdraw be negative or balance - withdraw amount be negative as well).
     */
	bool withdraw(int);

};


#endif /* ACCOUNT_H_ */
