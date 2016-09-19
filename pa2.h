#include <string>
#include <vector>
#ifndef PA2_H
#define PA2_H

class pa2 {

private:


	typedef struct node {
		int data;
		node* next;
	}*nodePtr;

	nodePtr head;
	nodePtr current;
	nodePtr temp;



public:
	pa2();																																																										//constructor for linked list sets all to NULL
	~pa2();																																																										//destructor for linked List
	void addNode(int dataAdd);																																																//Adds node to linked list with specified data
	void printList(std::vector<std::string> & programs);																																			//prints the linked list
	void worstInitiateNodes(int x, std::vector<std::string> &programs, int y, std::vector<int> &holes, std::string name);			//initiates nodes for best and worst alogirithim
	void killProgram(std::vector<std::string> &programs, std::string name, int x, std::vector<int> &holes);										//kills the desired program
	void initiateFreeSpace();																																																	//INitiates free spcae for free list gives initial 128 kb data
	void printFreeSpace();																																																		//prints how much freee memory there is
	void Menu();																																																							//displays the menu for the user
	void addFreeSpace();																																																			//propogates used linked list with nodes containing data of 0
	void addProgram2(int x);																																																	//adds the program to the nodes and pages
	bool exists(std::vector<std::string> &programs, std::string name);																												//checks to see if specified program exists
	int page();																																																								//returns value of a page
	int freeMemoryValue();																																																		//returns the value of the free memory
	int converttoPage(int x);																																																	//converst the program size into pages
	void findFragments(std::vector<int> &holes);																																							//finds and prints how many fragments there are


};


#endif
