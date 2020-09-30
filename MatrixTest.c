//Sebastian Medina                   CruzID: Seamedin               Course: CSE 101
//October 26, 2019                      FIlename: MatrixTest.c
//Description: Test client for the Matrix ADT

#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"

int main(){
  /*
    int n = 2;
    Matrix A = newMatrix(n);//create array of lists of size 2

    changeEntry(A, 1,2,1);changeEntry(A, 2, 3, 3);
    changeEntry(A, 1,1,4);changeEntry(A, 2, 1, 4);
    changeEntry(A, 2,2,1);
    changeEntry(A, 1, 5, 6);

    printf("%d\n", NNZ(A));
    printMatrix(stdout, A);
  */

  int n=100000;
  Matrix A = newMatrix(n);
  Matrix B = newMatrix(n);
  Matrix testChange = newMatrix(n);

   
  changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
  changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
  changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
  changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
  changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
  changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
  changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
  changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
  changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);

  // Check equals
  Matrix copyA = copy(A);
  int boolean = equals(A, copyA);

  if(boolean == 1)
    printf("true\n");
  else
    printf("false\n");


  boolean = equals(B, copyA);

  if(boolean == 1)
    printf("true\n");
  else
    printf("false\n");

  // check the NNZ of matrices
  printf("%d\n", NNZ(A));
  printMatrix(stdout, A);
  printf("\n");

  printf("%d\n", NNZ(B));
  printMatrix(stdout, B);
  printf("\n");

  // check equality
  boolean = equals(A, B);

  if(boolean == 1)
    printf("true\n");
  else
    printf("false\n");

  // make zero
  makeZero(A);
  makeZero(B);

  boolean = equals(A, B);

  if(boolean == 1)
    printf("true\n");
  else
    printf("false\n");

  // print empty functions
  printf("%d\n", NNZ(A));
  printMatrix(stdout, A);
  printf("\n");

  printf("%d\n", NNZ(B));
  printMatrix(stdout, B);
  printf("\n");

  // test changing of a column.
  changeEntry(testChange, 1,1,2); changeEntry(testChange, 1,2,3);

  printMatrix(stdout, testChange);

  changeEntry(testChange, 1,2,2);
  printMatrix(stdout, testChange);

  changeEntry(testChange, 1,1,4);
  printMatrix(stdout, testChange);


  //Test transpose
  changeEntry(A, 1,1,1); 
  changeEntry(A, 1,2,2); 
  changeEntry(A, 2,1,3); 
  changeEntry(A, 2,2,4);


  printf("\n");
  printf("Current A:\n");
  printMatrix(stdout, A);
  Matrix tA = transpose(A);
  printf("Transpose A:\n");
  printMatrix(stdout, tA);
  printf("\n");

  // Test sum function
  changeEntry(A, 1,1,1); 
  changeEntry(A, 1,2,2);
  changeEntry(A, 1,3,3); 
  changeEntry(A, 2,1,4); 
  changeEntry(A, 2,2,5);
  changeEntry(A, 2,3,6);
  changeEntry(A, 3,1,7);
  changeEntry(A, 3,2,8);
  changeEntry(A, 3,3,9);

  changeEntry(B, 1,1,1);
  changeEntry(B, 1,3,1);
  changeEntry(B, 3,1,1);
  changeEntry(B, 3,2,1);
  changeEntry(B, 3,3,1);

  printf("A:\n");
  printMatrix(stdout, A);
  printf("\nB:\n");
  printMatrix(stdout, B);

  Matrix testSum = sum(A, B);

  printf("sum:\n");
  printMatrix(stdout, testSum);
  printf("\n");

  // Test difference function
  printf("A:\n");
  printMatrix(stdout, A);
  printf("\nB:\n");
  printMatrix(stdout, B);

  Matrix testDiff = diff(A, B);
  printf("Difference:\n");
  printMatrix(stdout, testDiff);
  printf("\n");

  //test scalar
  printf("\nA:\n");
  printMatrix(stdout, A);

  Matrix testScalar = scalarMult(1.5, A);

  printf("\nScalar Mult:\n");
  printMatrix(stdout, testScalar);

  //test Product AB
  printf("A:\n");
  printMatrix(stdout, A);
  printf("\nB:\n");
  printMatrix(stdout, B);

  Matrix testProd = product(A,B);

  printf("\nProduct:\n");
  printMatrix(stdout, testProd);

  

  return EXIT_SUCCESS;
}



