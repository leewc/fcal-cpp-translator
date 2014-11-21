/* This program is just a copy of sample_4.dsl. You should write your
   solution for my_code_1 in this file. */

main () { 
  Matrix m1 = readMatrix ( "../samples/my_code_1a.data" ) ;
  Matrix m2 = readMatrix ( "../samples/my_code_1b.data" ) ;
  
  Int rows1;
  rows1 = numRows(m1);
  Int cols1;
  cols1 = numCols(m1);
  
  Int rows2;
  rows2 = numRows(m2);
  Int cols2;
  cols2 = numCols(m2);
  
  
  
  //do matmul
  Matrix output[rows1,cols2] 
  
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


