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
		tmpVector = vector_AND_Operate( vectorShift(tmpVector), sMap[Text[i]] );
		resultMatrix[i] = tmpVector;
	}
	resultMatrix = resultMatrix.transpose();
  	delete []tmparray;
	return resultMatrix;
}

/*
--- this getNextMatrix function can change Matrix including insert, delete and sub ---
*/
Matrix getNextMatrix(const string Pattern, const string Text, std::map<char,Vector> sMap, const Matrix CurrentMatrix, int errorCount, Matrix &insertMatrix, Matrix &deleteMatrix, Matrix &substiMatrix)
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

	newMatrix[0] = insertVector;

	for (int i = 1;i < Text.length() ; i++)
	{
		insertVector = vector_OR_Operate(vector_AND_Operate( vectorShift(insertVector), sMap[Text[i]] ), tmpCurrentMatrix[i-1]);
		deleteVector = vector_OR_Operate(vector_AND_Operate( vectorShift(deleteVector), sMap[Text[i]] ), vectorShift(tmpCurrentMatrix[i]));
		substiVector = vector_OR_Operate(vector_AND_Operate( vectorShift(substiVector), sMap[Text[i]] ), vectorShift(tmpCurrentMatrix[i-1]));
		finalVector = vector_OR_Operate( vector_OR_Operate( vector_AND_Operate( vectorShift(finalVector), sMap[Text[i]] ), vectorShift( vector_OR_Operate( tmpCurrentMatrix[i-1],tmpCurrentMatrix[i] ) ) ), tmpCurrentMatrix[i-1] );

		/*--- there will be three modification: insert, delete and substitution-----*/  


		insertMatrix[i] = insertVector;
		deleteMatrix[i] = deleteVector;
		substiMatrix[i] = substiVector;

		newMatrix[i] = finalVector;
	}

	newMatrix = newMatrix.transpose();
	
	return  newMatrix;
}

/*
--- this edition is just for final result  ---
*/

Matrix getNextMatrix(const string Pattern, const string Text, std::map<char,Vector> sMap, const Matrix CurrentMatrix, int errorCount)
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

	newMatrix[0] = insertVector;

	for (int i = 1;i < Text.length() ; i++)
	{
		insertVector = vector_OR_Operate(vector_AND_Operate( vectorShift(insertVector), sMap[Text[i]] ), tmpCurrentMatrix[i-1]);
		deleteVector = vector_OR_Operate(vector_AND_Operate( vectorShift(deleteVector), sMap[Text[i]] ), vectorShift(tmpCurrentMatrix[i]));
		substiVector = vector_OR_Operate(vector_AND_Operate( vectorShift(substiVector), sMap[Text[i]] ), vectorShift(tmpCurrentMatrix[i-1]));
		finalVector = vector_OR_Operate( vector_OR_Operate( vector_AND_Operate( vectorShift(finalVector), sMap[Text[i]] ), vectorShift( vector_OR_Operate( tmpCurrentMatrix[i-1],tmpCurrentMatrix[i] ) ) ), tmpCurrentMatrix[i-1] );

		/*--- there will be three modification: insert, delete and substitution-----*/  

		newMatrix[i] = finalVector;
	}

	newMatrix = newMatrix.transpose();
	
	return  newMatrix;
}
/*
----- Print the pattern and text using the errorPosVector
*/
void printMatch(const std::string Text, const std::string Pattern, const std::vector<int>unmatchPosVector){

	int textSize = Text.size();
	int lines = textSize / 100;
	int i = 0,j = 0;
	int errorCount = 0;
	for (i;i <= lines ;++i)
	{
		cout<<Text.substr(i*100,100)<<endl;
		if( unmatchPosVector[errorCount]< (i+1)*100 )
		{
			cout<<Pattern.substr(i*100,unmatchPosVector[errorCount]-i*100)<<" ";//first part
			for (j; j<unmatchPosVector.size();j ++)
			{
				cout<<Pattern.substr(i*100+unmatchPosVector[errorCount],unmatchPosVector[errorCount+1]-unmatchPosVector[errorCount])<<" ";
				++errorCount;
				if( unmatchPosVector[errorCount] > (i+1)*100 )
					break;
			}
		}
		else
		{
			cout<<Pattern.substr(i*100,100);
		}
		cout<<endl;
	}
}

// local search between Text and Pattern
/*
input:
	TEXT: TEXT input has already selected by the algorithm, so the TEXT should always be the best fix for the PATTERM.
	PATTERN: test string
	erroorCount: error amount that we can bear 
output:
	vector: it contains numbers that need to insert in the PATTERN

ps: insert always means insert into tht pattern string
*/
std::vector<int> localInsertSearch(const std::string Text, const std::string Pattern,const int errorCount)
{
	std::vector<int> unmatchPosVector;
	/*---- for insert part -----*/
	int textSize = Text.size();
	int patternSize = Pattern.size();
	int startPos = 0,num,i;

	std::string::const_iterator pattern_Ptr = Pattern.begin();
	std::string::const_iterator text_Ptr = Text.begin();

	while(startPos <= errorCount)
	{
		num = 0;
		for (i = 0 ;i <patternSize; i++)
		{
			if(*( pattern_Ptr + i ) != *( text_Ptr + i + startPos + num ))
			{
				num++;
				if(num > errorCount)
					break;
				cout<<"i = "<<i<<endl;
				unmatchPosVector.push_back(i); 
				i--;
			}
		}
		if(i == Pattern.size())
			break;
		startPos ++;
	}
	return unmatchPosVector;
}


/*
* edition distance function
* input:
	pattern string and text string
* output:
	value for edition distance

PS: we can use edition distance to konw which error cost least is better
*/

int editionDistance(std::string pattern, std::string text){

}
