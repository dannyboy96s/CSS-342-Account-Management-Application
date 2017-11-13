/*
 * BST.h
 *
 *  Created on: Nov 23, 2016
 *      Author: dan florescu
 * Rob Nash
 * Assignment:
 * HW5 final project
 * This is the binary search tree class.
 * This class will store the clients in a tree, so look ups are performed in O(nlogn) time.
 * The clients are put in the tree based on client id and there are no duplicate in the tree.
 * When printed the clients are traversed in-order, ascending by client id.
 *
 */

#ifndef BST_H_
#define BST_H_


#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

//testing
/*
#include "client.h"
#include "transaction.h"
#include "account.h"*/

using namespace std;

/*
 * This is the binary search tree class.
 * This class will store the clients in a tree, so look ups are performed in O(nlogn) time.
 * The clients are put in the tree based on client id and there are no duplicate in the tree.
 * When printed the clients are traversed in-order, ascending by client id.
 */
template<class Object>
class BSTree {

public:

	/*
	 * BSTree: This is the bstree default constructor.
	 * Precondition: None.
	 * Postcondition: The defualt constructor for the bstree class.
	 */
    BSTree();

    /*
     * ~BSTree: This is the bstree destructor.
     * Precondition: None.
     * Postcondition: This destructor will calls makeEmpty which deallocates all memory.
     */
    ~BSTree();

    /*
     * insert: This method will insert clients into the tree.
     * Precondition: Cannot insert duplicate clients.
     * Postcondition: This will insert objects (clients) into the tree by comparing their client id. The parameter holds a pointer to  object to insert.
     */
    bool insert(Object*);

    /*
     * retrieve: This method will retrieve clients from the tree.
     * Precondition: None.
     * Postcondition: This will retrieve objects (clients)from the tree .
     * 				  First parameter is object to retrieve and the second parameter holds pointer to found object, NULL if not found
     */
    bool retrieve(const Object& , Object*&)const;

    /*
     * display: This method will display clients in-order.
     * Precondition: None.
     * Postcondition: This will display the contents of the tree to cout, performing an in order walk.
     */
    void display()const;

    /*
     * clear: This method will empty the current tree, deallocates all memory.
     * Precondition: None.
     * Postcondition: This will deallocate all the contents of the tree(empty the tree).
     */
    void clear();

    /*
     * isEmpty: This method will check if the tree is empty
     * Precondition: None.
     * Postcondition: This return true is the tree is empty, false if it is populated.
     */
    bool isEmpty()const;

    /*
     * find: This method will find the object in the tree.
     * Precondition: None.
     * Postcondition: This will search through the tree an find the object(client) if it is in the tree.
     */
    bool find(const Object& tofind) const;

private:
    /*
     * struct Node
     * The glue that holds data properly.
     */
    struct Node {
        Object* data;
        Node* right;
        Node* left;
    };

    Node* root = nullptr; // root of the tree

    /*
     * clear: This private method will empty the current tree, deallocates all memory.
     * Precondition: None.
     * Postcondition: This will deallocate all the contents of the tree(empty the tree).
     */
    void clear(Node* subtree);

    /*
     * display: This method will display clients in-order.
     * Precondition: None.
     * Postcondition: This will display the contents of the tree to cout, performing an in order walk.
     */
    void display(stringstream& ss, Node* subtree) const;

    /*
     * insert: This method will insert clients into the tree.
     * Precondition: Cannot insert duplicate clients.
     * Postcondition: This will insert objects (clients) into the tree by comparing their client id. The parameter holds a pointer to  object to insert.
     *                The binary tree takes ownership of 'input' (it will delete it, it has be be allocated on the heap)
     */
    Node* insert(Object* input, Node* subtree);

    /*
     * find: This method will find the object in the tree.
     * Precondition: None.
     * Postcondition: This will search through the tree an find the object(client) if it is in the tree.
     */
    Object* find(const Object& tofind, Node* subtree) const;
};

/*
 * This is the default constructor, we set root to nullptr.
 */
template <class Object>
BSTree<Object>::BSTree():root(nullptr){}

/*
 * This is the destructor were we empty the tree by calling a clear method.
 * We will deallocate all the memory(all the contents), empty the tree.
 */
template <class Object>
BSTree<Object>::~BSTree(){
	clear();//call clear to empty the tree
}

/*
 * This method will determine if a tree is empty or not.
 * Return true if the tree is empty, false if not.
 */
template <class Object>
bool BSTree<Object>::isEmpty()const{
	return root == nullptr;//true if tree is empty, otherwise false
}

/*
 * This method will clear/deallocate all of the trees contents.
 * We will call a private function to empty out the tree.
 */
template <class Object>
void BSTree<Object>::clear(){
	clear(root);//call clear to empty the tree
}

/*
 * This is a private method that will empty out the contents from the tree.
 * It will deallocate all the memory from the tree recursively.
 */
template <class Object>
void BSTree<Object>::clear(Node* subtree){
	if(subtree != nullptr){//if the tree is not empty
		clear(subtree->left);//delete contents to the left
		clear(subtree->right);//delete contents to the left
		delete subtree->data;//delete the data
		delete subtree;//deallocate all memory
	}
}

/*
 * This method will display the contents in the tree.
 * It will display the contents by performing an in order walk.
 * We will call a private function that will display the tree.
 */
template <class Object>
void BSTree<Object>::display() const{
	stringstream ss;
	display(ss, root);//call private display method for in order walk
	cout << ss.str() << endl;//display the tree data to the console
}

/*
 * This private method will perform an in order walk.
 * We will check if the the tree is empty, if so, do nothing.
 * Otherwise perform t=an in order walk, go left , then data, then go right.
 */
template <class Object>
void BSTree<Object>::display(stringstream& ss, Node* subtree)const{
	if(subtree == nullptr){//if tree is empty
		return;//do nothing
	}

	display(ss,subtree->left);//get the contents at left
	ss << " " << *subtree->data << endl;//get the contents at data
	display(ss,subtree->right);//get the contents at right
}

/*
 * This method will insert objects(clients) into the tree.
 * We cannot insert a null client and also cannot insert a duplicate client as well.
 * Otherwise we insert objects (clients) into the tree by comparing their client id.
 * The parameter holds a pointer to  object to insert.
 *
 */
template <class Object>
bool BSTree<Object>::insert(Object* input){
	if(input == nullptr) {//cannot inpur nullptr
		return false;//false for incorrect input
	}
	// this is inefficient as we traverse the tree to look for the item
	// but it is still O(NlogN)
	if(find(*input)) {//call find to see if already in the tree
		return false;//false no duplicates in the tree
	}
	root = insert(input, root);
	return true;

}

/*
 * This private method will insert objects(clients) into the tree.
 * Otherwise we insert objects (clients) into the tree by comparing their client id.
 * The parameter holds a pointer to  object to insert.
 * We insert the first client in the root position and the we inserting the remaining clients,
 * we compare their id's, if smaller go left, if larger go right.
 *
 */
template <class Object>
typename BSTree<Object>::Node* BSTree<Object>::insert(Object* input, typename BSTree<Object>::Node* subtree){
	if(subtree == nullptr){//if tree is empty
		//return the node in the root position holding the first object(client id)
		Node *node = new Node();
		node->data = input;
		return node;
	}

	if (*input <= *subtree->data){//if the object to input is less than the one in tree, go left
		subtree->left = insert(input, subtree->left);//insert the object in the left branch
	}else{//otherwise the object to input is greater than the one in tree, go right
		subtree->right = insert(input, subtree->right);//insert the object in the right branch
	}

	return subtree;
}

/*
 * This method will search through the tree to find the respective client.
 * We will call a private method to traverse the tree and search for the client
 * We use find to check for duplicates when we want to insert clients into the tree.
 */
template <class Object>
bool BSTree<Object>::find(const Object& tofind) const {
	return find(tofind, root) != nullptr;
}

/*
 * This private method will search through the tree to find the respective client.
 * We search for the objects (clients) in the tree by comparing their client id's.
 * We first check if the tree is empty if so return nullptr.
 * Next we if is in the tree, we search left or right depending on what we want to find.
 * Return the object if it is found in the tree.
 */
template <class Object>
Object* BSTree<Object>::find(const Object& tofind, Node* subtree) const {
	if(subtree == nullptr){//if the tree is empty
		return nullptr;//return nullptr cannot find client in empty tree
	}

	if(tofind == *subtree->data){//if the client to find is in the tree
		return subtree->data;//return the respective client
	}

	if(tofind < *subtree->data){//if the client id we want to find is less  then
		return find(tofind, subtree->left);//return the client from the left branch
	}else{//if the client id we want to find is greater  then
		return find(tofind, subtree->right);//return the client from the right branch
	}

}

/*
 * This method will retrieve an object from the tree.
 * The First parameter is the object to retrieve.
 * The second parameter holds pointer to found object, NULL if not found.
 * We will call find to see if the object is in the tree, if it is return true, object retrieved.
 */
template <typename Object>
bool BSTree<Object>::retrieve(const Object& toRetrieve, Object*& foundObj)const{
	Object* found = find(toRetrieve, root);//call find to see if the object is in the tree
	if(found == nullptr) {//if the object is not in the tree
		return false;//false could not retrieve as object is not in the tree
	}
	foundObj = found;//yes the object is found in the tree
	return true;//true retrieve the object
}


#endif /* BST_H_ */
