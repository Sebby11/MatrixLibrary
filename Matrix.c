//Sebastian Medina                      CruzID: Seamedin           Course: CSE 101
//October 26, 2019                         FIlename: Matrix.c
//Description: Matrix operation ADT



#include<stdio.h>
#include<stdlib.h>
#include "Matrix.h"
#include "List.h"


double vDot(List A, List B);


// Constructors-Destructors -----------------------------------------------

// newEntry(): Creates reference to a new entry
Entry newEntry(int col, double val){
  Entry newE = malloc(sizeof(EntryObj));
  newE->column = col;
  newE->value = val;
  return (newE);
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
  Matrix tmp = malloc(sizeof(MatrixObj));

  tmp->numRows = 0;
  tmp->countNNZ = 0;
  tmp->matrixSize = n;
  tmp->matrixArray = (List*)malloc( n * sizeof(ListObj) );

  for(int i = 1; i <= n; i++){
    tmp->matrixArray[i] = newList();
  }

  return tmp;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.

void freeMatrix(Matrix* pM){
  if (pM != NULL && *pM != NULL){
    
  }

}

// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M){
  if (M == NULL){
    printf("Matrix Error: Cannot call size() on NULL matrix.\n");
    exit(EXIT_FAILURE);
  }

  return M->matrixSize;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
  if (M == NULL){
    printf("Matrix Error: Cannot call NNZ() on NULL matrix.\n");
    exit(EXIT_FAILURE);
  }

  return M->countNNZ;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
  if (A == NULL || B == NULL){
    printf("Matrix Error: Cannot call equals() on NULL matrix.\n");
    exit(EXIT_FAILURE);
  }

  // check their sizes
  if(size(A) != size(B)){
    return 0;
  }
  // check their actuals insides
  else{
    for(int i = 1; i < size(A); i++){
      List lA = A->matrixArray[i];
      List lB = B->matrixArray[i];

      if(length(lA) != length(lB)){
	return 0;
      }

      moveFront(lA); moveFront(lB);

      while(index(lA) >= 0 || index(lB) >= 0){
	Entry eA = (Entry)get(lA);
	Entry eB = (Entry)get(lB);

	// if entries are not the same
	if( (eA->column != eB->column) || (eA->value != eB->value) ){
	  return 0;
	}

	moveNext(A->matrixArray[i]);
	moveNext(B->matrixArray[i]);
      }
    }
  }

  return 1;
}

// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix.
void makeZero(Matrix M){
  if (M == NULL){
    printf("Matrix Error: Cannot call makeZero() on NULL matrix.\n");
    exit(EXIT_FAILURE);
  }

  for(int i = 1; i <= size(M); i++){
    List l = M->matrixArray[i];
    clear(l);
  }
  M->countNNZ = 0;

}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
  if (M == NULL){
    printf("Matrix Error: Cannot call changeEntry() on NULL matrix.\n");
    exit(EXIT_FAILURE);
  }
  if(1 > i > M->matrixSize || 1 > j > M->matrixSize){
    printf("Matrix Error: Cannot call changeEntry() out of bounds entries\n");
    exit(EXIT_FAILURE);
  }

  // create newEntry to be added to the list
  Entry newE = newEntry(j, x);

  if (x == 0){
    List lO = M->matrixArray[i];
    moveFront(lO);
    while(lO->cursor != NULL){
      Entry eO = (Entry)get(lO);

      if((eO->column) == newE->column){
	delete(lO);
	M->countNNZ--;
	return;
      }
      moveNext(lO);
    }
    return;}
  // if row is empty
  // M->matrixArray[i] = the row list (L)
  else if(length(M->matrixArray[i]) == 0 ){
    append(M->matrixArray[i], newE);
    moveFront(M->matrixArray[i]);

  }
  // if row isn't empty
  else{
    //get list
    List l = M->matrixArray[i];

    moveFront(l);

    //get column of cursor 
    Entry e = (Entry)get(M->matrixArray[i]);

    while(l->cursor != NULL){
      e = (Entry)get(M->matrixArray[i]);

      // enter in middle
      if((e->column) > (newE->column)){
	//enter before
	insertBefore(l, newE);

	break;
      }
      // if entry in space replace
      else if ((e->column) == newE->column){
	e->value = newE->value;
	break;
      }
      // enter in back
      else if(l->cursor == l->back){
	append(M->matrixArray[i], newE);
	break;
      }
      moveNext(l);
    }
  }
  M->countNNZ++;
}

// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
  if (A == NULL){
    printf("Matrix Error: Cannot call copy() on NULL matrix.\n");
    exit(EXIT_FAILURE);
  }

  // create new matrix given same size
  Matrix copy = newMatrix(size(A));
  // iterate through A placing every Entry into copy
  for(int i = 1; i <= size(A); i++){
    List l = A->matrixArray[i];
    int count = length(l);
    moveFront(l);

    // iterate
    while(count != 0){
      // if no list
      if(length(l) == 0){
	return copy;
      }
      Entry e = (Entry)get(l);
      changeEntry(copy, i, e->column, e->value);
      count--;
      moveNext(l);
    }
  }
  return copy;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
  if (A == NULL){
    printf("Matrix Error: Cannot call transpose() on NULL matrix.\n");
    exit(EXIT_FAILURE);
  }

  Matrix newA = newMatrix(size(A));

  if (NNZ(A) > 0){
    for(int i = 1; i <= size(A); i++){
      int listSize = length(A->matrixArray[i]);
      if(listSize > 0){
	List row = A->matrixArray[i];
	moveFront(row);

	while(index(row) != -1){
	  Entry newE = (Entry)get(row);
	  changeEntry(newA, newE->column, i, newE->value);
	  moveNext(A->matrixArray[i]);
	}
      }
    }
  }
  return newA;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
  if (A == NULL){
    printf("Matrix Error: Cannot call scalarMult() on NULL matrix.\n");
    exit(EXIT_FAILURE);
  }

  if (size(A) == 0) return A;

  Matrix newA = copy(A);
  for(int i = 1; i < size(A); i++){
    List l = newA->matrixArray[i];

    moveFront(l);

    while (l->cursor != NULL){
      // multiply
      Entry eA = (Entry)get(l);
      eA->value = eA->value*x;
      moveNext(l);
    }
  }

  return newA;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
  if (A == NULL){
    printf("Matrix Error: Cannot call sum() on NULL matrix.\n");
    exit(EXIT_FAILURE);
  }

  if(size(A) != size(B)){
    //throw error
    printf("Matrix Error: Cannot call sum() on two differently sized matrices matrix.\n");
    exit(EXIT_FAILURE);
  }

  if(size(A) == 0 ) return A;

  Matrix tempA = copy(A);
  for(int i = 1; i < size(tempA); i++){
    List lA= tempA->matrixArray[i];
    List lB = B->matrixArray[i];

    // if one of them is empty
    if(length(lA) == 0){
      tempA->matrixArray[i] = lB;
      continue;
    }
    else if (length(lB) == 0){
      tempA->matrixArray[i] = lA;
      continue;
    }

    moveFront(lA);
    moveFront(lB);

    while(lA->cursor != NULL || lB->cursor != NULL){

      //iterate if one or the other is finished
      if(lA->cursor == NULL){//iterate and place -lB 
	while(index(lB) >= 0){
	  Entry tmpA = (Entry)get(lB);
	  changeEntry(tempA, i, tmpA->column, tmpA->value);
	  moveNext(lB);
	}
	break;
      }
      else if (lB->cursor == NULL){//iterate and place lA
	while(index(lA) >= 0){
	  Entry tmpB = (Entry)get(lA);
	  changeEntry(tempA, i, tmpB->column, tmpB->value);
	  tempA->countNNZ--;
	  moveNext(lA);
	}
	break;
      }
      
      Entry eA = (Entry)get(lA);
      Entry eB = (Entry)get(lB);

      if(eA->column == eB->column){
	//add them
	eA->value = eA->value + eB->value;
	moveNext(lA);
	moveNext(lB);
      }
      else if (eA->column < eB->column){
	// move eA forward
	changeEntry(tempA, i, eA->column, eA->value);
	tempA->countNNZ--;
	moveNext(lA);
      }
      else if (eA->column > eB->column){
	// move eB forward
	changeEntry(tempA, i, eB->column, eB->value);
	tempA->countNNZ--;
	moveNext(lB);
      }

    }
  }
  return tempA;
}


//CREATE A COUNT THAT COUNTS NNZ numbers
// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
  if (A == NULL){
    printf("Matrix Error: Cannot call sum() on NULL matrix.\n");
    exit(EXIT_FAILURE);
  }

  if(size(A) != size(B)){
    //throw error
    printf("Matrix Error: Cannot call diff() on two differently sized matrices matrix.\n");
    exit(EXIT_FAILURE);
  }

  Matrix tempA = copy(A);
  Matrix tempB = copy(B);
  if(size(A) == 0 ) return A;

  if(equals(A, B)){
    makeZero(tempA);
    return tempA;
  }

  for(int i = 1; i < size(tempA); i++){
    List lA= tempA->matrixArray[i];
    List lB = tempB->matrixArray[i];

    // if A is empty add the B list but make it negative
    if(length(lA) == 0){
      //tempA->matrixArray[i] = lB;
      moveFront(lB);
      while(index(lB) >= 0){
	Entry eR = (Entry)get(lB);
	eR->value = eR->value*-1;
	append(lA, eR);
	moveNext(lB);
      }

      continue;
    }
    else if (length(lB) == 0){
      // make A negative
      moveFront(lA);
      while (lA->cursor != NULL){
	Entry temp = (Entry)get(lA);
	temp->value = temp->value;
	moveNext(lA);
      }
      tempA->matrixArray[i] = lA;
      continue;
    }

    moveFront(lA);
    moveFront(lB);

    while(lA->cursor != NULL || lB->cursor != NULL){

      //iterate if one or the other is finished
      if(lA->cursor == NULL){//iterate and place -lB 
	while(index(lB) >= 0){
	  Entry tmpA = (Entry)get(lB);
	  changeEntry(tempA, i, tmpA->column, -1*tmpA->value);
	  moveNext(lB);
	}
	break;
      }
      else if (lB->cursor == NULL){//iterate and place lA
	while(index(lA) >= 0){
	  Entry tmpB = (Entry)get(lA);
	  changeEntry(tempA, i, tmpB->column, tmpB->value);
	  tempA->countNNZ--;
	  moveNext(lA);
	}
	break;
      }
      
      Entry eA = (Entry)get(lA);
      Entry eB = (Entry)get(lB);

      if(eA->column == eB->column){
	//add them
	eA->value = eA->value - eB->value;
	moveNext(lA);
	moveNext(lB);
      }
      else if (eA->column < eB->column){
	// move eA forward

	changeEntry(tempA, i, eA->column, eA->value);
	tempA->countNNZ--;
	moveNext(lA);
      }
      else if (eA->column > eB->column){
	// move eB forward
	changeEntry(tempA, i, eB->column, -1*eB->value);
	tempA->countNNZ--;
	moveNext(lB);
      }

    }
  }
  tempA->countNNZ--;
  return tempA;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
  Matrix new = newMatrix(size(A));
  Matrix cA = copy(A);
  Matrix cB = copy(B);
  cB = transpose(cB);
  double prod = 0;

  if(NNZ(cA) == 0 || NNZ(cB) == 0){
    return new;
  }

  for(int i = 1; i < size(cA); i++){
    List lA = cA->matrixArray[i];

    moveFront(lA);

    if(length(lA) == 0){
      continue;
    }

    for(int j = 1; j < size(cB); j++){
      List lB = cB->matrixArray[j];
      moveFront(lB);

      if(length(lB) == 0){
	continue;
      }

      prod = vDot(lA, lB);
      //Entry e = newEntry(j, prod);

      changeEntry(new, i, j, prod);
    }

  }

  return new;
}

double vDot(List A, List B){
  double prod = 0;

  moveFront(B);
  moveFront(A);

  while(A->cursor != NULL && B->cursor != NULL){
    
    Entry eA = (Entry)get(A);
    Entry eB = (Entry)get(B);

    if(eA->column > eB->column){
      moveNext(B);
    }
    else if(eA->column < eB->column){
      moveNext(A);
    }
    else{
      prod = prod + (eA->value * eB->value);
      moveNext(A);
      moveNext(B);
    }
  }
  return prod;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
  int count;

  // # of rows
  for(int i = 1; i < size(M); i++){
    List l = M->matrixArray[i];

    // check if another list
    if(length(l) == 0){
      continue;
    }

    moveFront(l);
    Entry e = (Entry)get(l);

    //get size
    count = length(l);

    //printf("%d: ", i);
    fprintf(out, "%d: ", i);
    while(count != 0){
      if(count != 1){
	e = (Entry)get(l);
	if(e->value == 0){}
	else
	  fprintf(out, "(%d, %.1f) ", e->column, e->value);
      }
      else{
	e = (Entry)get(l);
	if(e->value == 0){}
	else
	  fprintf(out, "(%d, %.1f)\n", e->column, e->value);

      }
      count--;
      moveNext(l);
    }
  }

}



