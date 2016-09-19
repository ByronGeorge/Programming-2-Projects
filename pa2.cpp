
#include <cstdlib>
#include <iostream>
#include "pa2.h"
#include <string>
#include <vector>


/*
  Dear TA grading my program,

  I apologize in adavance for this sloppy program. Did not manage my time correclty at all and thought I could handle this in a few days. I am going to list out the things I could not implement.

  **no error checks for program size other than if its too big
  **best and worst fit algorithims are the same although i think my code works for best the best
  **When killing programs and then adding them things get weird really quick
  **Fixing one thing only broke another thing
  **did my best to comment everything out hope its easy to follow

*/

//Sets all pointers to null when a new node object is created
pa2::pa2() {
	head = NULL;
	current = NULL;
	temp = NULL;
}

//Destructor that deletes the entire linked list
pa2::~pa2() {
	nodePtr del = head;

	while (del != NULL) {

		head = head->next;
		delete del;
		del = head;
		std::cout << "\nsuccesffully deleted Node" << std::endl;

	}

	temp = head = NULL;

}


//adds a node to the linked list
void pa2::addNode(int dataAdd) {

	nodePtr n = new node;
	n->next = NULL;
	n->data = dataAdd;

 //If already have a list advance current pointer to the front to the last node
	if (head != NULL) {

    //Set head to the front of the list. Make current pointer start at the head
		current = head;

    //Condition only satisfies when at the end of the list
		while (current->next != NULL) {

      //Advances the current pointers until at last node of the list
			current = current->next;
		}

		current->next = n;

	}

   // If don't have a list make head point to n the front
	else {

		head = n;
	}
}

//Prints the linked List
void pa2::printList(std::vector<std::string>& programs) {

  //Two iterators
  //i iterates the spacing
  //j iterates the programs vector
	int i = 0;
	int j = 0;

  //Setting current pointer to head
	current = head;

  //While current is not null traverse through the list
	while (current != NULL) {

    //if the data stored inside the node is 0 then print Free
		if ((current->data) == 0) {

			std::cout << "Free" << "\t";

		}

    //if not 0 print whatever name is stored in the programs vector
		else if ((current->data) > 0) {

			std::cout << programs[j] << "\t";

		}

		i++;

    //prints the linked list in an 8x4 way
		if (i % 8 == 0) {

			std::cout << "\n";

		}

		current = current->next;
		j++;
	}

}

//Function that uses worst fit to add nodes to the linked list
void pa2::worstInitiateNodes(int x, std::vector<std::string> &programs, int y, std::vector<int> &holes, std::string name) {

	int nodestoAdd = x;
	current = head;

  for(int i = 0; i < 32; i++){
    if(programs[i].compare("killed") == 0){
      programs[i] = name;
    }
  }
	for (int i = 0; i < nodestoAdd; i++) {

      //if nodestoAdd is 32 then go ahead and make every node's data 4 and iterate through
			if (nodestoAdd == 32) {

				current->data = page();
				current = current->next;

			}

      //else if the data stored is 0 and the program size is bigger than or equal to a page
      //iterate through the nodes and make the data = to a page then subtract a page from the program size
			else if (current->data == 0 && y >= page()) {

				current->data = page();
				y -= page();
				current = current->next;
				continue;

			}

      //if program size is less than a page and the data is 0 then store that program size as data
			else if (current->data == 0 && y < page()) {

				current->data = y;
				current = current->next;

			}

      //if current data is > 0 or already holding data then move to next node and add 1 to the for loop to keep it going
			else if (current->data > 0) {

				current = current->next;
				nodestoAdd++;

			}

      //if
			else if (holes[i] > 0) {

				current = current->next;
				nodestoAdd++;

			}

		}
}

//function that kills the desired program and restores the memory
void pa2::killProgram(std::vector<std::string> &programs, std::string name, int x, std::vector<int> &holes) {

	current = head;            //sets current pointer to head
	int programsKilled = 0;    //Keeps track of how many programs killed to print
	int limit = x;             //limit keeps track of how many times to iterate through
	int hole = 0;              //Keep track of the memory to return

	for (int i = 0; i < limit; i++) {

    //if the program name entered is found in the list and the data in the node is not 0
    //then add the nodes data value into the holes vector and set the data in the node to 0
		if (programs[i].compare(name) == 0 && current->data > 0) {

			hole += current->data;
			holes[i] = current->data;
			current->data = 0;
			programsKilled++;

		}

		current = current->next;
	}

	std::cout << "Program " << name << " successfully killed, " << programsKilled << " page(s) reclaimed." << std::endl;


}

//function to add the "free" space in the linked list
//Essentially creating a linked list of 32 nodes all set to 0
void pa2::addFreeSpace() {

	for (int i = 0; i < 32; i++) {

		addNode(0);

	}

}

//function that initiates the free memory linked list
void pa2::initiateFreeSpace() {

  //Makes one node with the value 128
	addNode(4*32);

}

void pa2::printFreeSpace() {

	current = head;
	while (current != NULL) {

		std::cout << current->data << std::endl;

		current = current->next;

	}
}

int pa2::page() {

  //sets the page size to a constant 4
	const int pageSize = 4;

	return pageSize;

}

//Mainly used for the free list to update the amount of freee memory based on how much the program takes
//Works similiar tothe converttoPage function
void pa2::addProgram2(int x) {

	int memorytoUse = x;
	int i = 0;
	current = head;

	while (current != NULL) {

		if (memorytoUse == page()) {

			current->data -= page();
			i++;

		}

		else {

			current->data -= memorytoUse;

			while (memorytoUse > 0) {

				memorytoUse -= page();
				i++;

			}

		}

		current = current->next;

	}

}

void pa2::Menu() {

	std::cout << "\n1. Add program " << "\n""2. Kill program" << "\n""3. Fragmentation" << "\n""4. Print memory" << "\n""5. Exit\n" << std::endl;

}

int pa2::freeMemoryValue() {

	int freeSpace = 0;
	current = head;
	freeSpace = current->data;

	return freeSpace;
}

int pa2::converttoPage(int x) {

	int memorytoUse = x;
	int i = 0;

  //while the program size is bigger than 0
  //keep subtracting a page from it and increment i by 1
  //i is the number of pages
	while (memorytoUse > 0) {

		memorytoUse -= page();
		i++;

	}

	return i;
}

bool pa2::exists(std::vector<std::string> &programs, std::string name) {

	int exists = 0;
	bool exist;

  //for loop traverses the programs vector to search for the program name
	for (int i = 0; i < 32; i++) {

    //if there's a match increment exists variable by 1
		if (programs[i].compare(name) == 0) {

			exists++;

		}

	}

  //if exists is greater than 0 then the program exists
	if (exists > 0) {

		exist = true;

	}

  //otherwise it doesn't exist
	else {

		exist = false;

	}

	return exist;

}


void pa2::findFragments(std::vector<int> &holes) {

	int fragments = 0;
	current = head;

  //Traverse the linked list
	while (current != NULL) {

    //if the data in the node is 1 then increment fragments by 1
		if (current->data == 1) {

			fragments++;
		}

		current = current->next;

		}

    //After traversing the linked list traverse the holes vector
		for  (int i = 0; i < 32; i++) {

      //if the number at i is not 0 and less than 4 then increment fragments by 1
      //Mainly comes into play when killing programs as they leave holes
			if (holes[i] > 0 && holes[i] < page()) {

				fragments++;

			}
		}

	std::cout << "\nThere are " << fragments << " fragment(s)" << std::endl;

}


int main(int argc, char *argv[]){

  if(argc != 2){
    std::cout << "Wrong number of arguments" <<std::endl;
    return -1;
  }

  //Worst fit algorithim
  else if(std::string(argv[1]) == "worst"){

    std::vector<std::string> programs(32);               //vector to store the names of each program
  	std::vector<int> holes(32);                          //vector to keep track of holes in the memory
  	char choice = '0';                                   //choice variable for the user to navigate the menu
  	std::string name = "";                               //stores the program name
  	int progSize = 0;                                    //stores the program size
  	int keepTrack = 0;                                   //Keeps track of the number programs and helps with positioning
  	bool exist;                                          //boolean to keep track of whther a program exists or not
  	pa2 * usedList = new pa2;                            //Used List
  	pa2 *freeList = new pa2;                             //Free space list
  	freeList->initiateFreeSpace();                       //INitiates free linked list with 128 kb memory
  	usedList->addFreeSpace();                            //INitiates used linked list "FREE" space
  	int freeMemory = freeList->freeMemoryValue();        //Stores value of free memory into free meomry variable


    std::cout << "\nUsing the worst fit Algorithim" << std::endl;
    usedList->Menu();
    std::cout << "\nChoice - ";
    std::cin >> choice;


  	while (choice != 5) {

      switch(choice) {

        default: {

          std::cout << "\ninput not recognized! (spagett)" << std::endl;
          usedList->Menu();
        	std::cout << "\nChoice - ";
        	std::cin >> choice;
          break;

        }

        //Add program
  			case '1': {

          //if there's enough free memory
  				if (freeMemory >= 4) {

  					std::cout << "Program name - ";
  					std::cin >> name;
  					std::cout << "Program size (KB) - ";
  					std::cin >> progSize;

            //quick check to see if program exists or not
  					exist = usedList->exists(programs, name);

            //if it exists print the error and make them try again
  					if (exist == true) {
  						std::cout << "\nError, Program " << name << " is already running." << std::endl;
              usedList->Menu();
            	std::cout << "\nChoice - ";
            	std::cin >> choice;
  					}

            //else run the add node programs
  					else {

              //if there is enough memory for the program
  						if (freeMemory >= progSize) {

                //when program is being added modifies free memory
  							freeList->addProgram2(progSize);

                //subtracts the programsize from the free memory to keep updated
  							freeMemory -= progSize;

                //finds the number of pages needed based off program size
  							int toAdd = usedList->converttoPage(progSize);

  							int goThrough = 0;    //used to help iterate

                //adds the name into the programs vector based off the position of keep track
                //this makes sure that the name is put in the corrrect number of times
  							while (goThrough < toAdd) {

  								programs[keepTrack] = name;
  								keepTrack++;
  								goThrough++;

  							}

                //worstfit nodes are created
  							usedList->worstInitiateNodes(toAdd, programs, progSize, holes, name);

  							std::cout << "\nProgram " << name << " added successfully: " << toAdd << " page(s) used.\n";

                usedList->Menu();
              	std::cout << "\nChoice - ";
              	std::cin >> choice;

  						}

  						else {

  							std::cout << "\nError: Not enough memory for Program " << name << std::endl;

                usedList->Menu();
              	std::cout << "\nChoice - ";
              	std::cin >> choice;

  						}

  					}

  				}

          break;
  			}

      //Kill program
      case '2': {

  				std::cout << "Program name - ";
  				std::cin >> name;

          //quick check to see if program exists or not
  				exist = usedList->exists(programs, name);

          //if it does exist run kill program function
					if (exist == true) {

  					usedList->killProgram(programs, name, keepTrack, holes);

            //when program is killed it is renamed "killed" in the programs vector
            // it is done this way so when the free memory is added back it is only done so once
  					for (int i = 0; i < keepTrack; i++) {

  						if (programs[i].compare("killed") != 0 && holes[i] != 0) {

  							programs[i] = "killed";
  							freeMemory += holes[i];

  						}

  					}

            usedList->Menu();
          	std::cout << "\nChoice - ";
          	std::cin >> choice;

					}

          //if program does not exist then prints this error statement and has user try again
  				else {

  					std::cout << "\nProgram " << name << " is not being used!" << std::endl;

  					usedList->Menu();
  					std::cout << "\nChoice - ";
  					std::cin >> choice;

  				}

          break;

  			}

        //Fragmentation
  			case '3': {

          //executes findFragments method taking in the holes vector as an argument
  				usedList->findFragments(holes);

          usedList->Menu();
        	std::cout << "\nChoice - ";
        	std::cin >> choice;
          break;
  			}

        //print list
  			case '4': {

  				usedList->printList(programs);

          usedList->Menu();
        	std::cout << "\nChoice - ";
        	std::cin >> choice;
          break;
  			}

  		case '5': {
  				delete usedList;
  				delete freeList;
          exit(0);
  				break;
  			}


    }

  }

}

  //best fit algorithim
  else if(std::string(argv[1]) == "best"){

    std::vector<std::string> programs(32);               //vector to store the names of each program
  	std::vector<int> holes(32);                          //vector to keep track of holes in the memory
  	char choice = '0';                                   //choice variable for the user to navigate the menu
  	std::string name = "";                               //stores the program name
  	int progSize = 0;                                    //stores the program size
  	int keepTrack = 0;                                   //Keeps track of the number programs and helps with positioning
  	bool exist;                                          //boolean to keep track of whther a program exists or not
  	pa2 * usedList = new pa2;                            //Used List
  	pa2 *freeList = new pa2;                             //Free space list
  	freeList->initiateFreeSpace();                       //INitiates free linked list with 128 kb memory
  	usedList->addFreeSpace();                            //INitiates used linked list "FREE" space
  	int freeMemory = freeList->freeMemoryValue();        //Stores value of free memory into free meomry variable



    std::cout << "\nUsing the best fit Algorithim" << std::endl;
    usedList->Menu();
    std::cout << "\nChoice - ";
    std::cin >> choice;


  	while (choice != 5) {

      switch(choice) {

        default: {

          std::cout << "\ninput not recognized" << std::endl;
          usedList->Menu();
        	std::cout << "\nChoice - ";
        	std::cin >> choice;
          break;

        }

        //Add program
  			case '1': {

          //if there's enough free memory
  				if (freeMemory >= 4) {

  					std::cout << "Program name - ";
  					std::cin >> name;
  					std::cout << "Program size (KB) - ";
  					std::cin >> progSize;

            //quick check to see if program exists or not
  					exist = usedList->exists(programs, name);

            //if it exists print the error and make them try again
  					if (exist == true) {
  						std::cout << "\nError, Program " << name << " is already running." << std::endl;
              usedList->Menu();
            	std::cout << "\nChoice - ";
            	std::cin >> choice;
  					}

            //else run the add node programs
  					else {

              //if there is enough memory for the program
  						if (freeMemory >= progSize) {

                //when program is being added modifies free memory
  							freeList->addProgram2(progSize);

                //subtracts the programsize from the free memory to keep updated
  							freeMemory -= progSize;

                //finds the number of pages needed based off program size
  							int toAdd = usedList->converttoPage(progSize);

  							int goThrough = 0;    //used to help iterate

                //adds the name into the programs vector based off the position of keep track
                //this makes sure that the name is put in the corrrect number of times
  							while (goThrough < toAdd) {

  								programs[keepTrack] = name;
  								keepTrack++;
  								goThrough++;

  							}

                //worstfit nodes are created
  							usedList->worstInitiateNodes(toAdd, programs, progSize, holes, name);

  							std::cout << "\nProgram " << name << " added successfully: " << toAdd << " page(s) used.\n";

                usedList->Menu();
              	std::cout << "\nChoice - ";
              	std::cin >> choice;

  						}

  						else {

  							std::cout << "\nError: Not enough memory for Program " << name << std::endl;

                usedList->Menu();
              	std::cout << "\nChoice - ";
              	std::cin >> choice;

  						}

  					}

  				}

          break;
  			}

      //Kill program
      case '2': {

  				std::cout << "Program name - ";
  				std::cin >> name;

          //quick check to see if program exists or not
  				exist = usedList->exists(programs, name);

          //if it does exist run kill program function
					if (exist == true) {

  					usedList->killProgram(programs, name, keepTrack, holes);

            //when program is killed it is renamed "killed" in the programs vector
            // it is done this way so when the free memory is added back it is only done so once
  					for (int i = 0; i < keepTrack; i++) {

  						if (programs[i].compare("killed") != 0 && holes[i] != 0) {

  							programs[i] = "killed";
  							freeMemory += holes[i];

  						}

  					}

            usedList->Menu();
          	std::cout << "\nChoice - ";
          	std::cin >> choice;

					}

          //if program does not exist then prints this error statement and has user try again
  				else {

  					std::cout << "\nProgram " << name << " is not being used!" << std::endl;

  					usedList->Menu();
  					std::cout << "\nChoice - ";
  					std::cin >> choice;

  				}

          break;

  			}

        //Fragmentation
  			case '3': {

          //executes findFragments method taking in the holes vector as an argument
  				usedList->findFragments(holes);

          usedList->Menu();
        	std::cout << "\nChoice - ";
        	std::cin >> choice;
          break;
  			}

        //print list
  			case '4': {

  				usedList->printList(programs);

          usedList->Menu();
        	std::cout << "\nChoice - ";
        	std::cin >> choice;
          break;
  			}

  		case '5': {
  				delete usedList;
  				delete freeList;
          exit(0);
  				break;
  			}

    }

  }

  }

  else{
    std::cout << "Input not recognized!" << std::endl;
    return -1;
  }


 /*	std::vector<std::string> programs(32);
	std::vector<int> holes(32);
	int choice = 0;
	std::string name = "";
	int progSize = 0;
	int keepTrack = 0;
	bool exist;
	bool master = false;
	bool loop = false;
	pa2 * usedList = new pa2;                                                      //Used List
	pa2 *freeList = new pa2; //Free space list
	Spagett2->initiateFreeSpace(); //INitiates free linked list with 128 kb memory
	usedList->addFreeSpace(); //INitiates used linked list "FREE" space
	int freeMemory = Spagett2->freeMemoryValue();
	int pagesFree = 32;
	int pagesUsed = 0;



	while (master == false) {

		usedList->Menu();
		std::cout << "\nChoice - ";
		std::cin >> choice;

		if (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5) {

			while (loop == false) {


				if (choice == 1) {

					if (freeMemory >= 4) {


						std::cout << "Program name - ";
						std::cin >> name;
						std::cout << "Program size (KB) - ";
						std::cin >> progSize;

						exist = usedList->exists(programs, name);

						if (exist == true) {
							std::cout << "\nError, Program " << name << " is already running." << std::endl;
						}
						else {

							if (freeMemory >= progSize) {

								Spagett2->addProgram2(progSize, name);
								freeMemory -= progSize;
								int toAdd = Spagett->converttoPage(progSize);
								int goThrough = 0;


								while (goThrough < toAdd) {

									programs[keepTrack] = name;
									keepTrack++;
									goThrough++;

								}

								usedListt->worstInitiateNodes(toAdd, programs, progSize, holes, name);
								std::cout << "\nProgram " << name << " added successfully: " << toAdd << " page(s) used.\n";

							}

							else {

								std::cout << "\nError: Not enough memory for Program " << name << std::endl;


							}


						}
					}
				}
				if (choice == 2) {
					int programsKilled = 0;
					std::cout << "Program name - ";
					std::cin >> name;

					exist = Spagett->exists(programs, name);

					if (exist == true) {

						Spagett->killProgram(programs, name, keepTrack, holes, freeMemory);

						for (int i = 0; i < keepTrack; i++) {
							if (programs[i].compare("killed") != 0 && holes[i] != 0) {
								programs[i] = "killed";
								freeMemory += holes[i];
							}
						}



						std::cout << "\nFree memory now: " << freeMemory << std::endl;


					}
					else {

						std::cout << "\nProgram " << name << " is not being used!" << std::endl;

						usedList->Menu();
						std::cout << "\nChoice - ";
						std::cin >> choice;

					}


				}



				if (choice == 3) {
					usedList->findFragments(holes);
				}


				if (choice == 4) {
					usedList->printList(programs);
				}

				if (choice == 5) {
					delete usedList;
					delete Spagett2;
					loop = true;
					master = true;
					break;
				}




			}




		}
		else {

			std::cout << "\nInvalid input! " << std::endl;
			Spagett->Menu();
			std::cout << "\nChoice - ";
			std::cin >> choice;


		}
	}*/






    return 0;
}
