#ifndef PA3_H
#define PA3_H
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

template <typename K>
class pa3
{
	struct node {
		node * next;
		K data;

		node(const K& item) {
			data = item;
			next = NULL;
		}
	};

public:
	pa3();
	~pa3();
	void push(const K& data);
	K pop();
	void print() const;
	int getSize() const;
	//std::string readFile(std::string name);
  //bool doesFileExist(std::string nameOfTextFile);
	void removeWhitespace(std::string n, pa3* stack);
	bool ifIdentifier(std::string word);
  //void openTextFile(std::string nameOfTextFile,std::ifstream& textFile);
	bool ifConstant(std::string word);
	bool ifUpper(std::string word);
	void distributeIntoStacks(pa3* stack, pa3* identifier, pa3 * constants, pa3 * keyword, pa3* delimter, pa3* operators, pa3* errors);
	void printIdentifiers(pa3* identifier);
	void printDelimiters(pa3* delimiter);
	void printKeywords(pa3* keywords);
	void printConstants(pa3* constants);
	void printOperators(pa3* operators);
	void printErrors(pa3* errors);
  //std::string verifyArgs(int argc, char** argv);

private:
	int size;
	node * top;

};

#endif
