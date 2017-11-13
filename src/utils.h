/*
 * utils.h
 *
 *  Created on: Nov 29, 2016
 *      Author: dan
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <fstream>
#include <string>
#include <list>

#include "manager.h"

using namespace std;

/*Client* makeClient(stringstream& ss) {
	string tmp[3];
	int idx = 0;

	while(ss >> tmp[idx++] && idx < 3);

	return new Client(atoi(tmp[2].c_str()), tmp[0], tmp[1]);
}

void loadAccounts(stringstream& ss, list<Account> lst) {
	int type = 0;
	string tmp;

	while(ss >> tmp) {
		Account act(type++, atoi(tmp.c_str()));
		lst.push_back(act);
	}
}

Transaction* makeTransaction(stringstream& ss) {
	string tmp[4];
	int idx = 0;

	while(ss >> tmp[idx++] && idx < 4);

	if(tmp[0] != "D" || tmp[0] != "W" || tmp[0] != "M" || tmp[0] != "H") {
		return nullptr;
	}

	if((tmp[0] == "H" && idx != 2) || ((tmp[0] == "D" || tmp[0] == "W") && idx != 3) || (tmp[0] == "M" && idx != 4)) {
		return nullptr;
	}

	Transaction *tr = nullptr;
	if(tmp[0] == "H") {
		tr = new Transaction('H', -1, atoi(tmp[1].c_str()), -1);
	}
	if(tmp[0] == "D") {
		tr = new Transaction('D', -1, atoi(tmp[1].c_str()), atoi(tmp[2].c_str()));
	}
	if(tmp[0] == "W") {
		tr = new Transaction('W', -1, atoi(tmp[1].c_str()), atoi(tmp[2].c_str()));
	}
	if(tmp[0] == "M") {
		tr = new Transaction('M', atoi(tmp[1].c_str()), atoi(tmp[2].c_str()), atoi(tmp[3].c_str()));
	}

	return tr;
}*/

//template<class Object>
//class BST {
//public:
//	struct Node {
//		Object data;
//		Node* left;
//		Node* right;
//		Node(int d, Node* l, Node* r): data(d), left(l), right(r){}
//	};
//
//private:
//
//	Node * root = NULL;
//
//	int size(Node* subtree)const;
//
//	int height(Node* subtree)const;
//
//	void inorderwalk(stringstream& ss, Node* subtree);
//
//	Node* insert(Object input, Node* subtree);
//
//	void clear(Node* subtree);
//
//
//public:
//	BST();
//	~BST();
//
//	bool isEmpty()const;
//
//	int size()const;
//
//	int height()const;
//
//	string inorderwalk();
//
//	void insert(Object input);
//
//	void clear();
//
//	bool find(Object in, Node* subtree);
//
//
//
//};
//
//template <class Object>
//BST<Object>::BST():root(NULL){}
//
//template <class Object>
//BST<Object>::~BST(){
//	clear();
//}
//
//template <class Object>
//void BST<Object>::clear(){
//	clear(root);
//}
//
//template <class Object>
//void BST<Object>::clear(Node* subtree){
//	if(subtree != NULL){
//		clear(subtree->left);
//		clear(subtree->right);
//		delete subtree;
//	}
//}
//
//template <class Object>
//int BST<Object>::size()const{
//	return size(root);
//}
//
//template <class Object>
//int BST<Object>::size(Node* subtree)const{
//	return subtree == NULL ?  0 : 1 + size(subtree->left) + size(subtree->right);
//}
//
//template <class Object>
//string BST<Object>::inorderwalk(){
//	stringstream ss;
//	inorderwalk(ss, root);
//	return ss.str();
//}
//
//template <class Object>
//void BST<Object>::inorderwalk(stringstream& ss, Node* subtree){
//	if(subtree == NULL){
//		return;
//	}
//
//	inorderwalk(ss,subtree->left);
//	ss << " " << subtree->data;
//	inorderwalk(ss,subtree->right);
//
//}
//
//template <class Object>
//int BST<Object>::height()const{
//	return height(root);
//}
//
//template <class Object>
//int BST<Object>::height(Node* subtree)const{
//	return subtree == NULL ? 0 : 1 + max(height(subtree->left), height(subtree->right));
//}
//
//template <class Object>
//void BST<Object>::insert(Object input){
//	root = insert(input, root);
//}
//
//template<class Object>
//typename BST<Object>::Node* BST<Object>::insert(Object input, typename BST<Object>::Node* subtree){
//	if(subtree == NULL){
//		return new Node(input, NULL, NULL);
//	} else if (input <= subtree->data){
//		subtree->left = insert(input, subtree->left);
//	} else{
//		subtree->right = insert(input, subtree->right);
//	}
//	return subtree;
//}
//
//
//template <class Object>
//bool BST<Object>::find(Object target, Node* subtree){
//
//	if(subtree == NULL) {
//		return false;
//	}
//
//	else{
//		if(subtree->data == target){
//			return true;
//		}
//
//		else if(subtree->data <= target){
//			return find(target, subtree->left);
//		}
//		else{
//			return find(target, subtree->right);
//		}
//	}
//}
//







#endif /* UTILS_H_ */
