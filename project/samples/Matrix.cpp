#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include <fstream>
#include <iostream>

using namespace std;
Matrix :: Matrix (int _rows, int _cols)
{
  //can either use new (adds to heap) or malloc. Chose malloc because new requires consts
  rows = _rows;
  cols = _cols;

  data = (float **) malloc(rows * sizeof (float *));
  for (int i = 0; i < rows; i ++)
    {
      data[i] = (float*) malloc (cols * sizeof (float));
    }

}

int Matrix::numRows ( )
{
	  return rows;
} 

int Matrix::numCols ( )
{
	return cols;
} 

//const at the end tells compiler we cannot modify immutable data
float* Matrix::access(const int i, const int j) const
{
  return &data[i][j];
}

/* Operator overloading from codeExamples
   ostream& operator<<(ostream &os,  Complex &c) {
   os << c.r << "+" << c.i << "i" ;
   return os ;
   --> Here we are overloading the << operator that handles outsteam to print out 
       matrix, similar to toString()
}
*/
std::ostream& operator<<(std::ostream &os, Matrix &m)
{
  os << m.numRows() << " " << m.numCols() << std::endl;
  for (int i = 0; i < m.numRows(); i++)
	  {
		for (int j = 0; j < m.numCols(); j++)
		{
			os << m.access(i,j) << "  ";	//must be a pointer to where the address points to?? does this apply for ifstream
		}
		os << std::endl;
	  }
  return os;
}

Matrix Matrix::readMatrix (std::string filename)
{
  int row; 
  int col;
  //generate file stream
  std::ifstream fin;
  fin.open(filename.c_str()); //not adding a c_str() costed me about 2 hours. -Lee
  
  if (fin.fail())
  {
	std::cerr<< "Failed to open file : " << filename << std::endl;
	exit(1);
  }
  
  if (fin.is_open())
    {
	  fin >> row >> col;
	  Matrix m = Matrix (row, col);
      for (int i = 0; i < m.numRows(); i++)
	  {
		for (int j = 0; j < m.numCols(); j++)
		{
			fin >> *(m.access(i,j));	//must be a pointer to where the address points to
		}
	  }
	  
	fin.close();
	return m;
	
	}
    else 
	{
		std::cout << "READ FAIL" << std::endl;
	}
}

Matrix::Matrix (const Matrix& m)
{
	//we need to perform deep copy or else it will print uninitialized values
	int row = m.rows;
	int col = m.cols;
	
	data = (float **) malloc(rows * sizeof (float *));
	for (int i = 0; i < rows; i ++)
    {
      data[i] = (float*) malloc (cols * sizeof (float));
    }
    
    for (int j = 0; j < row; j++)
	  {
		for (int k = 0; j < col; k++)
		{
			cout << m.access(j,k) << endl;;
			float t =  *(m.access(j,k));
			data[j][k] = t;	//must be a pointer to where the address points to
		}
	  }
    
    //copy over the datas
    
}
/*
//helpful: http://www.augustcouncil.com/~tgibson/tutorial/iotips.html
// http://stackoverflow.com/questions/15588800/reading-matrix-from-a-text-file-to-2d-integer-array-c
// http://www2.lawrence.edu/fast/GREGGJ/CMSC110/dynamic/dynamic_arrays.html
  
*/
