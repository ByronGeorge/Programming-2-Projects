#ifndef PA1_H
#define PA1_H


class pa1
{
private:
  int size;

public:
  void setSize();
  int getSize();
  void Square(int x);
  void printSum(int arrRow[], int arrCol[], int arrDiag[]);
  ~pa1();
  pa1();
};

#endif
