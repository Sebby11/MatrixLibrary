//Sebastian Medina                       CruzID: Seamedin               Course: CSE 101
//October 26, 2019                       FIlename: Sparse.c
//Description: Takes file input and produces matrix operation outcomes


#include<stdio.h>
#include<stdlib.h>
#include "Matrix.h"

int main(int argc, char *argv[]) {
  FILE *in;
  FILE *out;
  int n, a, b;
  int row, column;
  double value;
  Matrix A, B, use;

  if(argc != 3){
    printf("Usage: Sparse <input file> <output file>\n");
    exit(EXIT_FAILURE);
  }

  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");

  if(in == NULL){
    fprintf(out,"Input file could not be read\n");
    exit(EXIT_FAILURE);
  }
  else if(out == NULL){
    fprintf(out,"Output file could not set to write to\n");
    exit(EXIT_FAILURE);
  }

  fscanf(in, "%d", &n);
  fscanf(in, "%d", &a);
  fscanf(in, "%d", &b);

  A = newMatrix(n+1);
  B = newMatrix(n+1);

  for(int i = 0; i < a; i++){
    fscanf(in, "%d", &row);
    fscanf(in, "%d", &column);
    fscanf(in, "%lf", &value);
    changeEntry(A, row, column, value);
  }

  for(int j = 0; j < b; j++){
    fscanf(in, "%d", &row);
    fscanf(in, "%d", &column);
    fscanf(in, "%lf", &value);
    changeEntry(B, row, column, value);
  }

  // Introduction
  fprintf(out, "A has %d non-zero entries:\n", a);
  printMatrix(out, A);
  fprintf(out,"\n");
  fprintf(out, "B has %d non-zero entries:\n", b);
  printMatrix(out, B);
  fprintf(out,"\n");

  // (1.5)*A
  fprintf(out, "(1.5)*A =\n");
  use = scalarMult(1.5, A);
  printMatrix(out, use);
  fprintf(out,"\n");

  //A+B =
  fprintf(out, "A+B =\n");
  use = sum(A, B);
  printMatrix(out, use);
  fprintf(out,"\n");

  //A+A =
  fprintf(out, "A+A =\n");
  use = sum(A, A);
  printMatrix(out, use);
  fprintf(out,"\n");

  //B-A =
  fprintf(out, "B-A =\n");
  use = diff(B, A);
  printMatrix(out, use);
  fprintf(out,"\n");

  //A-A =
  fprintf(out, "A-A =\n");
  use = diff(A, A);
  printMatrix(out, use);
  fprintf(out,"\n");

  //Transpose(A) =
  fprintf(out, "Transpose(A) =\n");
  use = transpose(A);
  printMatrix(out, use);
  fprintf(out,"\n");

  //A*B =
  fprintf(out, "A*B =\n");
  use = product(A,B);
  printMatrix(out, use);
  fprintf(out,"\n");

  //B*B =
  fprintf(out, "B*B =\n");
  use = product(B,B);
  printMatrix(out, use);
  //fprintf(out,"\n");

  fclose(in);
  fclose(out);

  return 0;
}
