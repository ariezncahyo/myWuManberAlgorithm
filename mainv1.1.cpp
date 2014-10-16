#include "MyWu.h"
#include <vector>
#include <map>
#include <cstring>
#include <stdlib.h>
#include "matrix/Matrix.h"
#include "matrix/Vector.h"
#include "getData.h"

const int errorLimit = 15;


int main(int argc, char* argv[]) {
	
/*
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	string Pattern = "hall";
	string Text = "hello world chao huang";
*/
	char *patternFilename = new char[100];
	strcpy(patternFilename, "../datafolder/one.txt");
	string Pattern = ReturnString(patternFilename,0).substr(0,32);

	char *textFilename = new char[100];
	strcpy(textFilename, "../datafolder/more.txt");
	int totalCheckNumberLine = CountLines(textFilename);

	string alphabet = "GTAC ";

	

	int patternLength = Pattern.length();
	int alphabetSize = alphabet.length();

	Matrix S;
	S.setsize(patternLength, alphabetSize);
	S.set(initWithSpecificChar(0.0, patternLength*alphabetSize));
	initWithInputString(Pattern,alphabet,S);
	S=S.transpose();

	std::map<char,Vector> sMap;
	sMap = sMapInit(S,alphabet);

	std::vector<Matrix> SinglePatternResult;


    for (int j = 1;j <= totalCheckNumberLine ;j++)
    {
		string Text = ReturnString(textFilename,j);
		SinglePatternResult.clear();
		SinglePatternResult.push_back(getExactMatchMatrix(Pattern,Text,sMap));

		for (int i = 0;i < errorLimit ;i ++)
		{
			SinglePatternResult.push_back(getNextMatrix(Pattern,Text,sMap,SinglePatternResult[i],i));

		}

		/*for (int i = 0;i < SinglePatternResult.size() ;i ++)
		{
	  		std::cout<<SinglePatternResult[i]<<std::endl;
	  		cout<<"-------------------------------------------------------"<<endl;
		}*/

	  	Vector outputResult(SinglePatternResult[errorLimit][Pattern.length()-1]);
	  	int posnum = 0;
	  	int *pos = new int[Text.length()];

		for (int i = 0;i < outputResult.getn() ;i ++)
		{
			if (outputResult[i] == 1)
			{
				cout<<"find it @ position " <<' '<< i+1 << " in "<<j<<" sequence!!!"<<endl;
				pos[posnum] = i;
				++ posnum;
			}
		}
		if(posnum == 0 )
			cout<<"not find in "<<j<<" sequence!!!"<<endl;
		delete []pos;
	}





/*	Vector test;
  	test.setsize(5);
  	double *input = new double[5];
  	input[0]=1;
  	input[1]=1;
  	input[2]=0;
  	input[3]=0;
  	input[4]=0;
  	test.set(input);


  	Vector test2;
  	test2.setsize(5);
  	double *input2 = new double[5];
  	input2[0]=1;
  	input2[1]=0;
  	input2[2]=0;
  	input2[3]=1;
  	input2[4]=0;
  	test2.set(input2);

  	cout<<vector_AND_Operate(test,test2)<<endl;
*/
  	delete []textFilename;
  	delete []patternFilename;
	 return 0;
}

