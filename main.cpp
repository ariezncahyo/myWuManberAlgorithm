#include "MyWu.h"
#include <vector>
#include <map>
#include <cstring>
#include <stdlib.h>
#include "matrix/Matrix.h"
#include "matrix/Vector.h"
#include "getData.h"


int main(int argc, char* argv[]) {

	char *filename = new char[100];
	strcpy(filename, "out.txt");
	
	string Pattern = ReturnString(filename,0).substr(0,32);

	int errorLimit = 10;
	//string alphabet = "abcdefghijklmnopqrstuvwxyz";
	string alphabet = "GTAC ";
	//string Pattern = "hall";
	//string Text = "hello world chao huang";

	int patternLength = Pattern.length();
	int alphabetSize = alphabet.length();
	//int textLength = Text.length();

	Matrix S;
	S.setsize(patternLength, alphabetSize);
	S.set(initWithSpecificChar(0.0, patternLength*alphabetSize));
	initWithInputString(Pattern,alphabet,S);
	//cout<<S<<endl;
	S=S.transpose();

	std::map<char,Vector> sMap;
	sMap = sMapInit(S,alphabet);

	std::vector<Matrix> SinglePatternResult;


    for (int j = 1;j < 100 ;j++)
    {
		string Text = ReturnString(filename,j);
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

  	cout<<vector_AND_Operate(test,test2)<<endl;*/
  	delete []filename;
	 return 0;
}

