#include "pa3.h"        //Header file needed to define functions
#include <iostream>     //Standard file for cout and cin
#include <string>       //Needed for strings
#include <fstream>      //Needed to read files

//Constructor for Pa3 class / stack constructor
template <typename K>
pa3<K>::pa3()
{
//Setting top node and size to 0 so there is nothing inside when starting out
	top = NULL;
	size = 0;

}

//Pa3 Destructor that uses pop() function to delete the stacks
template <typename K>
pa3<K>::~pa3()
{
//while the size of the stack is not zero it will continue to pop/ delete the contents of the stack
	while (getSize() != 0)
	{

		pop();

	}
}

//Push function that allows a node with data to be placed only on the top of the stack
template <typename K>
void pa3<K>::push(const K& data)
{
  //checks if stack is empty if it is it wil start the stack
	if (top == NULL)
	{

		top = new node(data);
		size += 1;
		return;

	}

//if the stack isn't empty it will add to the top of the stack
	node* wantToAdd = new node(data);

	wantToAdd->next = top;

	top = wantToAdd;

	size += 1;   //increments size by 1 to keep track of the stack size after each stack is added
}

//Pop() function that deletes whatever is on top of the stack at the moment and returns the value within what gets deleted
template <typename K>
K pa3<K>::pop()
{

	K item = top->data;

	node* wantToDelete = top; //Makes new node that is pointing to whatever the top is

	top = top->next;   //Make sure top is pointing to whatever is below it

	delete wantToDelete; //delete the node pointing to top

	size -= 1;       //Decrement after each time an item from the stack is deleted

	return item;
}


/*template<typename K>
std::string pa3<K>::readFile(std::string name)
{
	std::string line;
	std::string oneLine;
  std::ifstream file(name);

  if(file.is_open()){
		while (getline(file, line))
		{
			oneLine += line + '\n';
		}
		file.close();
  }

	return oneLine;

}*/

//function that returns the size of the stack
template <typename K>
int pa3<K>::getSize() const
{

	return size;

}

//Function that removes the whitespace from the file string created in the main and puts each substring into a stack
template <typename K>
void pa3<K>::removeWhitespace(std::string file, pa3 * stack)
{


	std::string newLine = "";

//goes through the file string character by character
	for (size_t i = 0; i < file.length(); i++)
	{

		char character = file.at(i);

    //if the character is a parenthesis ignore it and continue
		if (character == '(' || character == ')')
		{

			continue;
		}

    //if the character is any kind of white space
		else if (character == ' ' || character == '\n' || character == '\t' || character == '\r')
		{
      //if the line being checked contains something push it into the stack and make it empty again
			if (newLine.length() != 0)
			{

				stack->push(newLine);
				newLine = "";

			}
		}
    //Checks for operators and delimiters
		else if (character == '-' || character == '*' || character == '/' || character == '=' || character == ',' || character == ';')
		{
      //push the line into the stack if there is one
			if (newLine.length() != 0)
			{

				stack->push(newLine);
				newLine = "";

			}
      //push operator and delimeter into stack
			newLine += character;
			stack->push(newLine);
			newLine = "";

		}
    //if the character is a + sign and the character after is a + sign consider it a ++ operator
		else if (character == '+' && file.at(i++) == '+')
		{
      //combines the characters to form ++
			newLine += character;
			newLine += file.at(i++);

      //Then push the characters into the stack and empty the line
			stack->push(newLine);
			newLine= "";

		}

    //if character is just one + then push it
		else if (character == '+')
		{
			if (newLine.length() != 0)
			{
        //pushes the line if there is something in it
				stack->push(newLine);
				newLine = "";

        //pushes the + operator into the stack
				newLine += character;
				stack->push(newLine);

				newLine = "";
			}
			else
			{

				newLine += character;

				stack->push(newLine);
				newLine = "";

			}
		}
    //line either contains a character or digit
		else
		{

			newLine += character;

		}
	}
}

//function that checks for identifiers and returns true if it is one
template <typename K>
bool pa3<K>::ifIdentifier(std::string word)
{
  //for loop goes character by character in the given word
	for (size_t i = 0; i < word.length(); i++)
	{
		char c = word.at(i);
    //if the character at i is a lower case then return true
		if (islower(c))
		{
			return true;
		}



	}
  //if not lowercase then assume upper and or something else and return false
	return false;

}

//function that checks for constants and returns true if it is a constant
template <typename K>
bool pa3<K>::ifConstant(std::string word)
{
  //for loops goes character by character again with given word
	for (size_t i = 0; i < word.length(); i++)
	{
		char c = word.at(i);
    //if the character is a digit then return true
		if (isdigit(c))
		{
			return true;
		}

	}
  //if not a digit return false
	return false;
}

//Funtion that checks for upper case mainly keywords and returns true if it is uppercase
template <typename K>
bool pa3<K>::ifUpper(std::string word)
{
  //goes through word character by character
	for (size_t i = 0; i < word.length(); i++)
	{
		char c = word.at(i);
    //if the word is uppercase return true
		if (isupper(c))
		{

			return true;

		}

	}
  //otherwise return false
	return false;
}

//function that distributes whats in the main stack into individual stacks (keywords, delimeters, operators, errors, constatns)
template <typename K>
void pa3<K>::distributeIntoStacks(pa3* stack, pa3* identifier, pa3 * constants, pa3* keyword, pa3* delimter, pa3* operators, pa3* errors)
{
  //Since we know how many of these specific items make arrays with them to use for checking
	std::string keywords[3] = { "BEGIN", "END", "FOR" };
	std::string delimeters[2] = { ";", "," };
	std::string operatorz[7] = { "++" , "+", "-", "*" , "/", "=", "+ " };

	std::string word;
	bool error = false;
  int keepTrackNestedLoops = 0;     //keeps track of the nested loops
  int numberofNests = 0;            //total number of nestted loops

//while loop that keeps going until the end of the stack is reached
	while (stack->getSize() != 0)
	{
    //set word to whatever pop() returns (top of the stack)
		word = stack->pop();

    //Quick check for nested loops. they start with END so increment by one if the word pops up
    if(word.compare("END") == 0)
    {

      keepTrackNestedLoops++;
      //if the tracker is bigger than 0 then set the value of tracker equal to the number of nests
      if(keepTrackNestedLoops > numberofNests)
      {
        numberofNests = keepTrackNestedLoops;
      }
    }
    //FOR means the end of a nest so decrement the tracker
    else if(word.compare("FOR") == 0)
    {
      keepTrackNestedLoops--;
    }
    //if the word is not a delimiter or single length identifies/constant enter the nest muahahahaha
		if (word.length() > 1)
		{
      //if the word is not a multi-letter identifier (ie sum) go deeper into the nest
			if (ifIdentifier(word) == false)
			{
        //is the word has length greater than or equal to 2 keep going
				if (word.length() >= 2)
				{
          //if the word is upper case go through for loop to check which word it is
					if (ifUpper(word) == true)
					{
            //checks if the keyword is actually one of the three key words
						for (int i = 0; i < 3; i++)
						{
              //if it is then push it into the keyword stack and leave the loop
							if (word.compare(keywords[i]) == 0)
							{

								keyword->push(word);
								error = false;
								break;

							}
              //if the word is not one of the keywords then set boolean error to true
							else
							{
								error = true;
							}
						}
            //if error is true push that word into the errors stack (Syntax errors)
						if (error == true)
						{
							errors->push(word);
						}
					}
				}
        //if the word is a constant (ie a digt) then push that word into the constants stack
				if (ifConstant(word) == true)
				{
					constants->push(word);
				}
        //otherwise check to see if it is an operator
				else
				{
					for (int i = 0; i < 7; i++)
					{
            //if the word is an  operator push it into the operators stack
						if (word.compare(operatorz[i]) == 0)
						{
							operators->push(word);
						}
					}
				}

			}
      //if the word is an identifier greater than 1 letter then push it into the identifier stack
			else if (ifIdentifier(word) == true)
			{
				identifier->push(word);
			}

		}
    //if the word is one letter can assume its either an identifier, operator, or constant, or delimiter
		else
		{
      //if the word lowercase then it is an identifier. Push into the identifiers stack
			if (ifIdentifier(word) == true)
			{
				identifier->push(word);
			}
      //else if the word is not a constant check to see which operator it is and push it into the stack
			else if (ifConstant(word) == false)
			{
        //Check to see if it is an operator
				for (int i = 0; i < 7; i++)
				{
					if (word.compare(operatorz[i]) == 0)
					{
						operators->push(word);
					}
				}
			}
      //if the word is a constant with one digit then push into the constants stack
      else if(ifConstant(word) == true)
      {
        constants->push(word);
      }

      //finally if its none of the above check to see if the word is a delimiter. IF so push into delimiter stack
			for (int i = 0; i < 2; i++)
			{
				if (word.compare(delimeters[i]) == 0)
				{
					delimter->push(word);
				}
			}
		}
	}
  //prints out number of nested loops
  std::cout << "\nThe maximum depth of nested loop(s) is " << numberofNests << std::endl;

}

//Function that prints and deletes the identifiers stack
template<typename K>
void pa3<K>::printIdentifiers(pa3* identifiers)
{

	const int size = identifiers->getSize();               //declare a const size of the stack using getSize() function
	std::string * identifiersArr = new std::string[size];  //Declare dynamic array with the size

	std::string word;
	std::string temp;

	int increment = 0;   //used to iterate through array


  //while loop that pops until entire stack is deleted
	while (identifiers->getSize() != 0)
	{
		word = identifiers->pop();            //set word equal to whatever was in the top
		identifiersArr[increment] = word;     //put the word into the position i of the array
		increment++;

	}
  //print the array
	std::cout << "\nIdentifier: ";

	for (int i = 0; i < size; i++)
	{
    //if there are multiple values ignore and only print each unique identifier once
		if (identifiersArr[i].compare(temp) != 0)
		{
			std::cout << identifiersArr[i] << " ";
		}

		temp = identifiersArr[i];
	}

	delete[] identifiersArr;       //delete the array when finished to prevent memory leaks

}

//prints the delimiter stack and deletes it as it goes through very similiar to how printIdentifiers() works
template <typename K>
void pa3<K>::printDelimiters(pa3* delimiter)
{
	const int size = delimiter->getSize();
	std::string * delimitersArr = new std::string[size];

	std::string word;
	std::string temp;

	int increment = 0;



	while (delimiter->getSize() != 0)
	{

		word = delimiter->pop();
		delimitersArr[increment] = word;
		increment++;

	}

	std::cout << "\nDelimiter: ";

	for (int i = 0; i < size; i++)
	{
		if (delimitersArr[i].compare(temp) != 0)
		{
			std::cout << delimitersArr[i] << " ";
		}

		temp = delimitersArr[i];
	}

	delete[] delimitersArr;


}

//function that prints the keywords stack and deletes it as it goes using pop()
//very similiar to the other print functions
template <typename K>
void pa3<K>::printKeywords(pa3* keywords)
{

	const int size = keywords->getSize();
	std::string * keywordsArr = new std::string[size];

	std::string word;
	std::string temp;

	int increment = 0;

	while (keywords->getSize() != 0)
	{

		word = keywords->pop();
		keywordsArr[increment] = word;
		increment++;

	}

	std::cout << "\nKeyword: ";

	for (int i = 0; i < size; i++)
	{
		if (keywordsArr[i].compare(temp) != 0)
		{
			std::cout << keywordsArr[i] << " ";
		}

		temp = keywordsArr[i];
	}

	delete[] keywordsArr;

}

//function that prints the onstants stack and deltes it along the way using pop()
//very similiar to the other printing functions
template <typename K>
void pa3<K>::printConstants(pa3* constants)
{

	const int size = constants->getSize();
	std::string * constantsArr = new std::string[size];

	std::string word;
	std::string temp;

	int increment = 0;

	while (constants->getSize() != 0)
	{

		word = constants->pop();
		constantsArr[increment] = word;
		increment++;

	}

	std::cout << "\nConstant: ";

	for (int i = 0; i < size; i++)
	{
		if (constantsArr[i].compare(temp) != 0)
		{
			std::cout << constantsArr[i] << " ";
		}

		temp = constantsArr[i];
	}

	delete[] constantsArr;

}

//function that prints the operators stack and deletes it along the way using pop()
//very similiar to the other print fuctions
template <typename K>
void pa3<K>::printOperators(pa3* operators)
{

	const int size = operators->getSize();
	std::string * operatorsArr = new std::string[size];

	std::string word;
	std::string temp;

	int increment = 0;

	while (operators->getSize() != 0)
	{

		word = operators->pop();
		operatorsArr[increment] = word;
		increment++;

	}

	std::cout << "\nOperators: ";

	for (int i = 0; i < size; i++)
	{
		if (operatorsArr[i].compare(temp) != 0)
		{

			std::cout << operatorsArr[i] << " ";
		}

		temp = operatorsArr[i];
	}

	delete[] operatorsArr;

}

//function that prints from the errors stack and deletes it as it goes using pop()
//vvery similiar to the other print functions
template <typename K>
void pa3<K>::printErrors(pa3* errors)
{

	const int size = errors->getSize();
	std::string * errorsArr = new std::string[size];

	std::string word;
	std::string temp;

	int increment = 0;



	while (errors->getSize() != 0)
	{

		word = errors->pop();
		errorsArr[increment] = word;
		increment++;

	}

	std::cout << "\nSyntax Error(s): ";

	for (int i = 0; i < size; i++)
	{

		if (errorsArr[i].compare(temp) != 0)
		{

			std::cout << errorsArr[i] << " ";
		}

		temp = errorsArr[i];
	}

	std::cout << '\n';

	delete[] errorsArr;
}


//main takes in command line arguments
int main(int argc, char* argv[])
{
  //initiate all the stacks!
  pa3<std::string>* stack = new pa3<std::string>();         //textfile stack
	pa3<std::string> * identifier = new pa3<std::string>();   //identifier stack
	pa3<std::string> * constants = new pa3<std::string>();    //constants stack
	pa3<std::string> * keyword = new pa3<std::string>();      //keyword stack
	pa3<std::string> * delimeter = new pa3<std::string>();    //delimeter stack
	pa3<std::string> * operators = new pa3<std::string>();    //operators stack
	pa3<std::string> * errors = new pa3<std::string>();       //errors stack



  std::string line;         //needed to read file and get the file information
  std::string oneLine;      //variable that holds the file information

  //error check to make sure user uses two arguments
  if(argc != 2)
  {
    std::cout << "Error, invalid number of arguments. Please enter the name of a text file" << std::endl;
  }
  else
  {
      //takes string from second argument as the file name and opens it
      std::ifstream file(argv[1]);

      if(file.is_open())
      {
        //takes file information and stores it all into one giant string
        while (getline(file, line))
        {
             oneLine += line + '\n';
        }
      //closes the file
      file.close();
      }
      else{
        std::cout << "Error unable to open file" << std::endl;
      }

}
  std::string fileContents = oneLine;  //stores the giants string into a new string

  //removes the white space and creates the first big stack
	stack->removeWhitespace(fileContents, stack);

  //distribute the correct tokens into their correct stacks
	stack->distributeIntoStacks(stack, identifier, constants, keyword, delimeter, operators, errors);


  //prints all the stacks
	keyword->printKeywords(keyword);
	identifier->printIdentifiers(identifier);
	constants->printConstants(constants);
	operators->printOperators(operators);
	delimeter->printDelimiters(delimeter);
	errors->printErrors(errors);


	return 0;

}
