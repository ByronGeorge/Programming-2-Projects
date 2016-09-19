#include <iostream>
#include <string>
#include <sstream>
//#include "pa1.h"

class pa1{
  int size;

public:
  void setSize();
  int getSize();
  void Square(int x);
  void printSum(int arrRow[], int arrCol[], int arrDiag[]);
  pa1();
  ~pa1();
};

pa1::~pa1(){};

pa1::pa1(){this->size = 0;};


void pa1::setSize(){
bool resume = false;
int temp = 0;
while(resume == false){


  if(!(std::cin >> this->size)){
    std::cin.clear();
    std::cin.ignore();
  }

  if(this->size == 3 || this->size == 5 || this->size == 7 || this->size == 9 || this->size == 11 || this->size == 15){
    temp = this->size;
    if((temp*10) % 10 == 0){
      resume = true;
    }
    else{
      this->size = 0;
    }
  }
  else{
      std::cout << "\nShould be an odd number bettween 3 and 15\n";
        std::cout << "\nEnter the size of a MagicSquare: ";
  }
}

  }


int pa1::getSize(){
  return this->size;
}

void pa1::Square(int z){

  //Dynamically Allocating Memory
  int** array = new int*[z];
  int** array2 = new int*[z];
  int** array3 = new int*[z];


  for(int i = 0; i < z; i++){
    array[i] = new int[z];
    array2[i] = new int[z];
    array3[i] = new int[z];

  }
  //Setting each array to 0
  for(int i = 0; i < z; i++){
    for(int j = 0; j < z; j++){
      array[i][j] = 0;
      array2[i][j] = 0;
      array3[i][j] = 0;

    }
  }

  //Magic Square #1 is created
    int x = z/2;   //sets x and y to starting position for first value
    int y = z - 1;
    for(int value = 1; value <= z*z; value++){ //Generates magic square 1 while adhering to conditions
      array[x][y] = value; //value is stored if no conditions apply
      x--;
      y++;
      if(x < 0 && y == z){ //First condition if x is negative and y is equal to the size
        x++;
        y--;
        y--;
      }
      if(x < 0){ //Second condition applies only if x is negative or y is equal to size
        x = z - 1;
      }
      if(y == z){
        y = 0;
      }
      if(array[x][y] > 0){ // Third condition applies if there is a number in the spot calculated
        x++;
        y -= 2;
      }
    }

  //Magic Square #2
    int temp = 0; //Made temp variable to store values from the first magic square array
    int tempArr [z][z]; //Made temp array to hold the temp values
      for(int x = 0; x < z; x++){
        for(int y = 0; y < z; y++){ //Stores the values into temp variable first
          temp = array[x][y];
          tempArr[x][y] = temp; //Temp values are then stored into the temp array
          array2[x][y] = array[y][x]; //Second magic square is created by transposing the first magicSquare's columns into rows

          array2[y][x] = temp; //Array2 is set equal to temp values to make sure nothing is missing

        }
      }

    //Magic Square #3
      int tempArr2 [z][z]; //Second temp array is made to store temp array 1's values
        for(int i = 0; i < z; ++i){ //Temp 1 array's values are stord into temp array 2 but values are reversed
          int end = z - 1;
          for(int j = 0; j < z; ++j ){
            tempArr2[i][j] = tempArr[i][end]; //Temp array 1 starts storing values into temp array 2 starting from the last index
            end--; //temp array 2 is now a reversed version of temp array 1
          }
        }
        for(int x = 0; x < z; x++){ //Here store temparray 2 values into array 3
          for(int y = 0; y < z; y++ ){
            array3[x][y] = tempArr2[x][y]; //Result is a 3rd unique magic square
          }
        }

      //Prints Magic Square #1 in a square

      int sumRow [z];
      int sumColumn[z];
      int sumdiagnoal[2];
      int sumdiagnoal1 = 0;
      int sumdiagnoal2 = 0;
      std::cout << "\nMagic Square #1 is: " << "\n";
        for(int i = 0; i < z; i++){
          int sumRow1 = 0;
          int sumColumn1 = 0;
          for(int j = 0; j < z; j++){
            sumRow1 += array[i][j];
            sumColumn1 += array[j][i];
            if(i == j){
              sumdiagnoal1 += array[i][j];
            }
            std::cout << array[i][j] << "\t";
          }
          sumColumn[i] = sumColumn1;
          sumRow[i] = sumRow1;
          std::cout << "\n";
        }
        for(int i = 0, j= z-1; i < size; i++,j--){
          sumdiagnoal2 += array[i][j];
        }
        sumdiagnoal[0] = sumdiagnoal1;
        sumdiagnoal[1] = sumdiagnoal2;

        printSum(sumRow, sumColumn, sumdiagnoal);
        std::cout << "\n";


      //Prints Magic Square #2 in a square
      sumdiagnoal1 = 0;
      sumdiagnoal2 = 0;
      std::cout << "\nMagic Square #2 is: " << "\n";
        for(int i = 0; i < z; i++){
            int  sumRow1 = 0;
            int  sumColumn1 = 0;
          for(int j = 0; j < z; j++){
            sumRow1 += array2[i][j];
            sumColumn1 += array2[j][i];
            if(i == j){
              sumdiagnoal1 += array2[i][j];
            }
            std::cout << array2[i][j] << "\t";
          }
          sumColumn[i] = sumColumn1;
          sumRow[i] = sumRow1;
          std::cout << "\n";
        }
        for(int i = 0, j= z-1; i < size; i++,j--){
          sumdiagnoal2 += array[i][j];
        }
        sumdiagnoal[0] = sumdiagnoal1;
        sumdiagnoal[1] = sumdiagnoal2;

        printSum(sumRow, sumColumn, sumdiagnoal);
          std::cout << "\n";


      //Prints Magic Square #3 in a square
      sumdiagnoal1 = 0;
      sumdiagnoal2 = 0;
      std::cout << "\nMagic Square #3 is: " << "\n";
        for(int i = 0; i < z; i++){
            int  sumRow1 = 0;
            int  sumColumn1 = 0;
          for(int j = 0; j < z; j++){
            sumRow1 += array3[i][j];
            sumColumn1 += array3[j][i];
            if(i == j){
              sumdiagnoal1 += array3[i][j];
            }
            std::cout << array3[i][j] << "\t";
          }
          sumColumn[i] = sumColumn1;
          sumRow[i] = sumRow1;
          std::cout << "\n";
        }
        for(int i = 0, j= z-1; i < size; i++,j--){
          sumdiagnoal2 += array[i][j];
        }
        sumdiagnoal[0] = sumdiagnoal1;
        sumdiagnoal[1] = sumdiagnoal2;

        printSum(sumRow, sumColumn, sumdiagnoal);
        std::cout << "\n";

      /*std::cout << "Magic Square #3 is: " << "\n";
        for(int i = 0; i < z; i++){
          for(int j = 0; j < z; j++){
            std::cout << array3[i][j] << "\t";
          }
          std::cout << "\n";
        }*/

      //Final step memory is set free!
        for(int i = 0; i < z; i++){
          delete [] array[i];
          delete[] array2[i];
          delete[] array3[i];
        }
        delete [] array;
        delete[] array2;
        delete[] array3;


}

void pa1::printSum(int arrRow[], int arrCol[], int arrDiag[]){

  std::cout << "\nChecking the sum of every row: ";
  for(int i =0; i < size; i++){
    std::cout << arrRow[i] << " ";
  }
  std::cout << "\n";

  std::cout << "Checking the sum of every column: ";
  for(int i =0; i < size; i++){
    std::cout << arrCol[i] << " ";
  }
  std::cout << "\n";

  std::cout << "Checking the sum of every Diagnoal: ";
  for(int i =0; i < 2; i++){
    std::cout << arrDiag[i] << " ";
  }


  for(int i = 0; i < size; i++){
    arrRow[i] = 0;
    arrCol[i] = 0;
  }
  for(int i = 0; i < 2; i++){
    arrDiag[i] = 0;
  }
}

int main(){
  pa1 create;
  int size;
  std::cout << "Enter the size of a MagicSquare: ";
  create.setSize();
  size = create.getSize();
  create.Square(size);
}
