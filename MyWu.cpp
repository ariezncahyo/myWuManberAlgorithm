#include "MyWu.h"
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include "matrix/Matrix.h"
#include "matrix/Vector.h"
using namespace std;

const std::map<char, Vector>  sMapInit(const Matrix S, const string alphabet)
{
	std::map<char, Vector> sMap;
	for (int i = 0;i < alphabet.length();i++)
		sMap.insert(std::pair<char, Vector>(alphabet[i],S[i]));
	return sMap;
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

Vector vectorShift(Vector inputVector)
{
	for (int i = inputVector.getn()-1; i > 0; i--)
	{
		inputVector[i] = inputVector[i-1];  
	}
	inputVector[0] = 1;

	//std::cout<<inputVector<<std::endl;

	return inputVector;
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

Matrix getExactMatchMatrix(const string Pattern, const string Text, std::map<char,Vector> sMap)
{
	Matrix resultMatrix;
	resultMatrix.setsize(Pattern.length(),Text.length());
	resultMatrix = resultMatrix.transpose();

	Vector tmpVector;
	tmpVector.setsize(Pattern.length());
	
	double *tmparray = new double[Pattern.length()];

	if (Pattern[0] == Text[0])
		tmparray[0] = 1;
	else
		tmparray[0] = 0;

	for (int i = 1; i < Pattern.length(); i++)
		tmparray[i] = 0; 
	tmpVector.set(tmparray);
	resultMatrix[0] = tmpVector;

	for (int i = 1;i < Text.length() ; i++)
	{
		//cout<<tmpVector<<'\t'<<sMap[Text[i]]<<endl;
		tmpVector = vector_AND_Operate( vectorShift(tmpVector), sMap[Text[i]] );
		resultMatrix[i] = tmpVector;
	}
	resultMatrix = resultMatrix.transpose();
	//cout<<resultMatrix<<endl;
  	delete []tmparray;
	return resultMatrix;
}


Matrix getNextMatrix(const string Pattern, const string Text, std::map<char,Vector> sMap, const Matrix CurrentMatrix,int errorCount)
{
	Matrix newMatrix;
	Matrix tmpCurrentMatrix (CurrentMatrix);
	tmpCurrentMatrix = tmpCurrentMatrix.transpose();
	newMatrix.setsize(Pattern.length(),Text.length());
	newMatrix = newMatrix.transpose();

	Vector insertVector;
	Vector deleteVector;
	Vector substiVector;
	Vector finalVector;

	insertVector.setsize(Pattern.length());
	deleteVector.setsize(Pattern.length());
	substiVector.setsize(Pattern.length());
	finalVector.setsize(Pattern.length());
	
	double *tmparray = new double[Pattern.length()];
	for (int i = 0;i < Pattern.length() ; i++)
	{
		if (i < errorCount)
			tmparray[i] = 1;
		else
			tmparray[i] = 0;
	}


	insertVector.set(tmparray);
	deleteVector.set(tmparray);
	substiVector.set(tmparray);
	finalVector.set(tmparray);

	//newMatrix[0] = vector_OR_Operate(vector_OR_Operate(insertVector,deleteVector), substiVector);
	//newMatrix[0] = substiVector;
	newMatrix[0] = insertVector;

	for (int i = 1;i < Text.length() ; i++)
	{
		insertVector = vector_OR_Operate(vector_AND_Operate( vectorShift(insertVector), sMap[Text[i]] ), tmpCurrentMatrix[i-1]);
		deleteVector = vector_OR_Operate(vector_AND_Operate( vectorShift(deleteVector), sMap[Text[i]] ), vectorShift(tmpCurrentMatrix[i]));
		substiVector = vector_OR_Operate(vector_AND_Operate( vectorShift(substiVector), sMap[Text[i]] ), vectorShift(tmpCurrentMatrix[i-1]));
		finalVector = vector_OR_Operate( vector_OR_Operate( vector_AND_Operate( vectorShift(finalVector), sMap[Text[i]] ), vectorShift( vector_OR_Operate( tmpCurrentMatrix[i-1],tmpCurrentMatrix[i] ) ) ), tmpCurrentMatrix[i-1] );
		//newMatrix[i] = vector_OR_Operate(vector_OR_Operate(insertVector,deleteVector), substiVector);
		//newMatrix[i] = substiVector;
		newMatrix[i] = finalVector;
	}

	newMatrix = newMatrix.transpose();
	
	return  newMatrix;

}
