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


#include "account.h"

/*
 * This is the account constructor that will set an account.
 * An account has a type ranging from 0-9, and it also has a balance.
 */
Account::Account(int typ, int bal){
	type = typ;//set the type of account
	balance = bal;//set the balance of the account
}

/*
 * This account destructor.
 */
Account::~Account(){}

/*
 * This is the copy constructor where it will copy an account.
 * We will copy the type of account ranging from 0-9, and the balance of the account.
 */
Account::Account(const Account& rhs){
	type = rhs.type;//copy the type
	balance = rhs.balance;//copy the balance
}

/*
 * This is the assign operator where we will assign an account to another.
 * We first check if they are not the same and then we assign the account,
 * with the respective type(type can range from 0-9) and the account balance.
 */
Account& Account::operator=(const Account& rhs){
	if(this != &rhs){//if myself is not equals to right hand side
		type = rhs.type;//assign the type to the account
		balance = rhs.balance;//assign the balance to the account
	}
	return *this;
}

/*
 * This the equality operator where we will check if one account equals another.
 * We first check if they are both equal, if so return true.
 * If not, then we check if the type of the account and the balance of the account are the same, if they are return true.
 * If none match then the accounts are not the same, return false.
 */
bool Account::operator==(const Account& rhs)const{
	if(*this == rhs) {//check if they are the same, and if they are
		return true;//return true they are the same
	}
	if(type == rhs.type && balance == rhs.balance){//check if the type and balance are the same if so,
		return true;//true they are the same account
	}
	return false;//false they are not the same account
}

/*
 * This is the not equal operator where we check if accounts are not equals with each other.
 * We first check if they not equal, if so return true.
 * Then we check if the type of the account and the balance of the account are not the same, if they are return true.
 * If the accounts are the same, return false.
 */
bool Account::operator!=(const Account& rhs)const{
	return !operator==(rhs);//negation of operator==
}

/*
 * This is the less than operator where we will check if one account is less than an other.
 * We are going to check if the type of account ( type ranging from 0-9) and the balance are less than the other account.
 * If they are then return true, one account is less than another.
 */
bool Account::operator<(const Account& rhs)const{
	if(type < rhs.type && balance < rhs.balance){//check if the type and balance are less then the other
		return true;//true is account is less than the other
	}
	return false;//false, the account is not less than the other one
}

/*
 * This is the greater than operator where we will check if one account is greater than an other.
 * We are going to check if the type of account ( type ranging from 0-9) and the balance are greater than the other account.
 * If they are then return true, one account is greater than another.
 */
bool Account::operator>(const Account& rhs)const{
	return !operator<=(rhs);//return the negation of operator<=
}

/*
 * This is the less than or equal to operator where we will check if one account is less than or equal to an other.
 * We are going to check if the type of account ( type ranging from 0-9) and the balance are less than or equal to the other account.
 * If they are then return true, one account is less than or equal to another.
 */
bool Account::operator<=(const Account& rhs)const{
	if(operator<(rhs) || operator==(rhs)){//check if account is less than or equal to by call operator< and operator==
		return true;//true if the account is less than or equal to another account
	}
	return false;//false if greater than another account
}

/*
 * This is the greater than or equal to operator where we will check if one account is greater than or equal to an other.
 * We are going to check if the type of account ( type ranging from 0-9) and the balance are greater than or equal to the other account.
 * If they are then return true, one account is greater than or equal to another.
 */
bool Account::operator>=(const Account& rhs)const{
	return !operator<(rhs);//return the negation of operator<
}

/*
 * This is operator<< and it will output to the console the account information.
 * This will output the account type (ranging from 0-9) and the account balance.
 */
ostream& operator<<(std::ostream& output, const Account& obj){
	output << "Account Type=" << obj.type << ", Account Balance=" << obj.balance;//output the account type and balance
	return output;
}

/*
 * This getter method will get the type of the account.
 * The types of accounts range from 0-9.
 */
int Account::getType(){
	return type;//return the type of account
}

/*
 * This getter method will get the balance of the account.
 */
int Account::getBalance(){
	return balance;//return the balance of the account
}

/*
 * The deposit method will deposit money into an account.
 * The is a sensitive operation so only the manager can perform this operation.
 * The value to deposit must be positive.
 */
bool Account::deposit(int value){
	if(value < 0) {//if the deposit  value is negative
		return false;//false, cannot deposit a negative value
	}
	balance += value;//add the deposit to the balance
	return true;//true for correct deposit
}

/*
 * The withdraw method will withdraw money from an account.
 * This is a sensitive operation so only the manager can perform this operation.
 * The value withdrawn cannot be negative in any case.
 */
bool Account::withdraw(int value){
	if(value < 0 || balance - value < 0) {//if value is negative or account balance minus the withdraw is negative
		return false;//false, illegal withdraw
	}
	balance -= value;//subtract the withdraw from the account balance
	return true;//true for correct withdraw
}




