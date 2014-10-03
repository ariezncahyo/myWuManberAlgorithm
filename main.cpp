#include "MyWu.h"
#include <vector>
#include <cstring>
#include <stdlib.h>
#include "matrix/Matrix.h"
#include "matrix/Vector.h"


double* initWithSpecificChar(double x,int length);//init with 0
void initWithInputString(const string inputString,const string alphabetArray,Matrix &initMatrix);// init with a specific string


void vectorShift(Vector& inputVector);
Vector vector_AND_Operate(Vector lhs,Vector rhs);
Vector vector_OR_Operate(Vector lhs,Vector rhs);
Matrix getNextMatrix(const Matrix CurrentMatrix);





int main(int argc, char* argv[]) {

	string alphabet = "abc";
	string Pattern = "aabac";
	string text = "aabaacaabacab";
	int patternLength = Pattern.length();
	int alphabetSize = alphabet.length();
	int textLength = text.length();

	Matrix S;
	S.setsize(patternLength, alphabetSize);
	S.set(initWithSpecificChar(0.0, patternLength*alphabetSize));
	initWithInputString(Pattern,alphabet,S);


  	std::cout<<S<<std::endl;
  
  	/*Vector tmp1(0,0,1,0);
  	Vector tmp2(1,0,0,0);
  	std::cout<<S<<std::endl;
  	std::cout<<tmp2<<std::endl;
  	std::cout<<vector_AND_Operate(tmp1,tmp2)<<std::endl;
*/  return 0;
}

Vector vector_AND_Operate(const Vector lhs,const Vector rhs)
{
	if(lhs.getn() != rhs.getn())
	{
		std::cout<<"two differnt vector"<<std::endl;
		exit(0);
	}	
	int size = lhs.getn();
	Vector result;
	result.setsize(size);
	for (int i = 0;i < lhs.getn();i++)
	{
		result[i] = double ((int)lhs[i] & (int)rhs[i]);
	}
	return result;
}

Vector vector_OR_Operate(const Vector lhs,const Vector rhs)
{
	if(lhs.getn() != rhs.getn())
	{
		std::cout<<"two differnt vector"<<std::endl;
		exit(0);
	}	
	int size = lhs.getn();
	Vector result;
	result.setsize(size);
	for (int i = 0;i < lhs.getn();i++)
	{
		result[i] = double((int)lhs[i] | (int)rhs[i]);
	}
	return result;
}

void vectorShift(Vector &inputVector)
{
	for (int i = inputVector.getn()-1; i > 0; i--)
	{
		inputVector[i] = inputVector[i-1];  
	}
	inputVector[0] = 1;
	return;
}

void initWithInputString(const string inputString,const string alphabetArray,Matrix &initMatrix)// init with a specific string
{
	int width = initMatrix.ncols();
	int height = initMatrix.nrows();
	for (int i = 0;i < height;i++)
	{
		for (int j = 0; j < width ;j++)
		{
			if (inputString[i] == alphabetArray[j])
				initMatrix[i][j] = 1;
		}
	}
	return;
}

double* initWithSpecificChar(double x,int length)
{
	double* result = new double[length];
	for(int i = 0;i < length;i++)
	{
		result[i] = x;
	}
	return result;
}

Matrix getExactMatchMatrix(string Pattern, string Text)
{
	Matrix resultMatrix;
	resultMatrix.setsize(Pattern.length(),Text.length());
	
	return resultMatrix;
}


Matrix getNextMatrix(const Matrix CurrentMatrix);
{
	Matrix newMatrix;



	
	return  newMatrix;

}
