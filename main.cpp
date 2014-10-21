#include "MyWu.h"
#include <vector>
#include <map>
#include <cstring>
#include <stdlib.h>
#include "matrix/Matrix.h"
#include "matrix/Vector.h"
#include "getData.h"

const int errorLimit = 1;


int main(int argc, char* argv[]) {
	
/* //sample in normal english string

	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	string Pattern = "hall";
	string Text = "hello world chao huang";
*/

 //sample on the pdf

	std::string alphabet = "abc";

	std::string Pattern = "aabac";//aabac

	//std::string Text = "abacabac";//insert modification Text string

	string Text = "aabaacaabacab";

/*	// DNA sequence
	
	char *patternFilename = new char[100];
	strcpy(patternFilename, "../datafolder/one.txt");

	string Pattern = ReturnString(patternFilename,0).substr(0,32);

	char *textFilename = new char[100];
	strcpy(textFilename, "../datafolder/more.txt");
	int totalCheckNumberLine = CountLines(textFilename);
	string Text = ReturnString(textFilename,3);

	string alphabet = "GTAC ";
*/

	int patternLength = Pattern.length();
	int alphabetSize = alphabet.length();
	int textSize = Text.length();

	Matrix S;
	S.setsize(patternLength, alphabetSize);
	S.set(initWithSpecificChar(0.0, patternLength*alphabetSize));
	initWithInputString(Pattern,alphabet,S);
	S=S.transpose();

	std::map<char,Vector> sMap;
	sMap = sMapInit(S,alphabet);

	std::vector<Matrix> SinglePatternResult;
	std::vector<Matrix> SinglePatternResult_Insert;
	std::vector<Matrix> SinglePatternResult_Delete;
	std::vector<Matrix> SinglePatternResult_Substi;

	SinglePatternResult.clear();
	SinglePatternResult.push_back(getExactMatchMatrix(Pattern,Text,sMap));
	SinglePatternResult_Insert.push_back(getExactMatchMatrix(Pattern,Text,sMap));
	SinglePatternResult_Delete.push_back(getExactMatchMatrix(Pattern,Text,sMap));
	SinglePatternResult_Substi.push_back(getExactMatchMatrix(Pattern,Text,sMap));

	Matrix InsertMatrix,DeleteMatrix,SubstiMatrix;
	InsertMatrix.setsize(textSize,patternLength);
	DeleteMatrix.setsize(textSize,patternLength);
	SubstiMatrix.setsize(textSize,patternLength);




	for (int i = 0;i < errorLimit ;i ++){
		SinglePatternResult.push_back(getNextMatrix(Pattern,Text,sMap,SinglePatternResult[i],i,InsertMatrix,DeleteMatrix,SubstiMatrix));
		SinglePatternResult_Insert.push_back(InsertMatrix);
		SinglePatternResult_Delete.push_back(DeleteMatrix);
		SinglePatternResult_Substi.push_back(SubstiMatrix);
	}

	//print the result matrix R
	 
	for (int i = 0;i < Text.size() ;i++)
	{
		cout<<'\t'<<Text[i];//<<'\t';
	}
	cout<<endl;
	cout<<Pattern<<endl;
	cout<<"insert matrix"<<endl;
  	std::cout<<SinglePatternResult_Insert[errorLimit-1]<<std::endl;
	cout<<"delete matrix"<<endl;
  	std::cout<<SinglePatternResult_Delete[errorLimit-1]<<std::endl;
	cout<<"substi matrix"<<endl;
  	std::cout<<SinglePatternResult_Substi[errorLimit-1]<<std::endl;
  	cout<<"-------------------------------------------------------"<<endl;




  	// outputResult is the key result of our algorithm
  	//Vector outputResult(SinglePatternResult[errorLimit][Pattern.length()-1]);


/*	
  	std::vector<int> tmpvector = localInsertSearch(Text,Pattern,errorLimit);
  	cout<<"insert position is: ";
  	for (int i=0;i<tmpvector.size();i++){
  		cout<<tmpvector[i]<<'\t';
	}
	cout<<endl;
	printMatch(Text,Pattern,tmpvector);
*/

/*
  	int posnum = 0;
  	int *pos = new int[Text.length()];

	for (int i = 0;i < outputResult.getn() ;i ++)
	{
		if (outputResult[i] == 1)
		{
			cout<<"find it @ position " <<' '<< i+1 <<endl;
			pos[posnum] = i;
			++ posnum;
		}
	}
	if(posnum == 0 )
		cout<<"not find in "<<endl;
	delete []pos;
*/


/*
  	delete []textFilename;
  	delete []patternFilename;
*/



	return 0;
}

