/*
 * Transaction.h
 *
 *  Created on: Nov 23, 2016
 *      Author: dan florescu
 * Rob Nash
 * Assignment:
 * HW5 final project
 * This is the transaction class were the manager performs transactions for clients.
 * This class gets the code (D, W, M, H) which determines the type of transaction.
 * Next, we obtain the source account(-1 if no source account) and get the destination account(cannot be -1, there always has to be a destination).
 * Lastly, we get the amount we either want to deposit, move or withdraw.
 *
 */

#ifndef TRANSACTION_H_
#define TRANSACTION_H_

/*
 * This is the transaction class were the manager performs transactions for clients.
 * This class gets the code (D, W, M, H) which determines the type of transaction.
 * Next, we obtain the source account(-1 if no source account) and get the destination account(cannot be -1, there always has to be a destination).
 * Lastly, we get the amount we either want to deposit, move or withdraw.
 */
class Transaction {

private:

	friend class Manager;

	char code; // ('D', 'W', 'M', 'H')

	int src; // 5 digit, -1 if no source account

	// 5 digit if code is 'D', 'W' or 'M' (cannot be -1, always have destination). 4 digit client id if code 'H'
	int dst;

	int amount; // -1 if no amount (eg history transaction)

public:

	/*~Transaction: This is the transaction destructor.
	 * Precondition: None.
	 * Postcondition: The destructor will the delete the transactions.
	 */
	~Transaction() {}

	/* Copy constructor: This constructor will copy a transaction.
	 * Precondition: None.
	 * Postcondition: We copy a transaction, a transaction consists of a code, source, destination, and amount.
	 */
	Transaction(const Transaction& rhs){
	   code = rhs.code;//copy the code
	   src = rhs.src;//copy the source
	   dst = rhs.dst;//copy the destination
	   amount = rhs.amount;//copy the amount
	}

	/*
	 * operator=: This is the copy assignment operator.
	 * Precondition: None.
	 * Postcondition: The copy assignment operator will make a copy of a transaction, copying the code, source, destination, and the amount.
	 */
	Transaction& operator=(const Transaction& rhs){
    	if(this != &rhs){//if 'this' is no equal to the right hand side then we copy
    		code = rhs.code;//copy the code
    		src = rhs.src;//copy the source
        	dst = rhs.dst;//copy the destination
        	amount = rhs.amount;//copy the amount
    	}
    	return *this;
    }

	/*
	 * operator==: This is the equality operator, that checks for equality for transactions.
	 * Precondition: None.
	 * Postcondition: The equality operator will return true if one transaction is equal with another one. We check if the
	 * 				  the transaction is the same or check if the code, source, destination, and amount are the same.
	 */
    bool operator==(const Transaction& rhs)const{
    	//check if myself is the same as the transaction or check if the code, source, destination, and the amount are the same
    	if(this == &rhs || ( this->code == rhs.code && this->dst == rhs.dst && this->src == rhs.src && this->amount == rhs.amount)){
    		return true;//if the transactions are the same return true
    	}
    	return false;//return false if the transactions are not the same
    }

    /*
     * operator<<: This is the ostream operator and it will output the transaction.
     * Precondition: None.
     * Postcondition: Depending on the code('D','W','M','H'), it will output a different message for each of the cases.('D' and 'W' have the same message).
     */
    friend std::ostream& operator<<(std::ostream& output, const Transaction& obj){
    	output << "Code=" << obj.code;//output the code from the transaction
    	switch(obj.code) {//have a switch for the different codes ('D','W','M','H')
    	case 'D':
    	case 'W':
    		output << ", Destination Account=" << obj.dst << ", Amount=" << obj.amount;//output message for case deposit and withdraw
    		break;
    	case 'M':
    		output << ", Source Account=" << obj.src << ", Destination Account=" << obj.dst << ", Amount=" << obj.amount;//output message for case move
    		break;
    	case 'H':
			output << ", Client ID=" << obj.dst;//output message for case history
			break;
    	}
    	return output;//return the output to the console
    }

    /*
     * getCode: This is a getter method that will get the code.
     * Precondition: None.
     * Postcondition: This will get the code from the transaction('D','W','M','H').
     */
	char getCode() const {
		return code;//return the code ('D','W','M','H')
	}

    /*
     * getSrc: This is a getter method that will get the source account.
     * Precondition: None.
     * Postcondition: This will get the source account from the transaction.
     */
	int getSrc() const {
		return src;//return the source account
	}

    /*
     * getSrc: This is a getter method that will get the destination account.
     * Precondition: None.
     * Postcondition: This will get the destination account from the transaction.
     */
	int getDst() const {
		return dst;//return the destination account
	}

    /*
     * getSrc: This is a getter method that will get the amount.
     * Precondition: None.
     * Postcondition: This will get the amount from the transaction.
     */
	int getAmount() const {
		return amount;//return the amount
	}

private:

	/*
	 * Private constructor that will set the transactions.
	 */
	Transaction(char clientCode, int source, int destination, int amt) {
	    code = clientCode;//set the code
	    src = source;//set the source account
	    dst = destination;//set the destination account
	    amount = amt;//set the amount
	}

	/*
	 * Private default constructor.
	 */
	Transaction() {
	}

};


#endif /* TRANSACTION_H_ */
