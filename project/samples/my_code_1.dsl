/* Matrix multiplication */

main () {
  
  
  //print ("Beginning to read in 2 matrices "); 
  Matrix m1 = readMatrix ( "../samples/my_code_1a.data" ) ;
  Matrix m2 = readMatrix ( "../samples/my_code_1b.data" ) ;
  
  //print (" Read Complete ");
  Int rows1;
  rows1 = numRows(m1);
  Int cols1;
  cols1 = numCols(m1);
  
  Int rows2;
  rows2 = numRows(m2);
  Int cols2;
  cols2 = numCols(m2);
  
  //zero initialize matrix
  Matrix output [ rows1, cols2 ] rows , cols = 0;
  

  Int i;
  Int j;
  Int k;
  
  //do matmul
  for (i = 0 : rows1-1) {
      for (j = 0 : cols1-1) {
          for (k = 0 : cols2-1) {
              output[i,j] =  output[i,j] + m1[i,k] * m2[k,j];
          }
      }
  }
  
  print(output);
}


/* cpp matrix multiply for reference
int** mulMat(int x, int y, int z, int ** A, int ** B) {
  int ** R = newMat(x,z);
  for(int i = 0; i < x; i++) {
    for(int j = 0; j < z; j++) {
      R[i][j] = 0;
      for(int k = 0; k < y; k++) {
        R[i][j] += A[i][k]*B[k][j];
      }
    }
  }
  return R;
}
*/


