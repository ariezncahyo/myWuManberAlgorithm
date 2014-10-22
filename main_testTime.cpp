#include "MyWu.h"
#include <vector>
#include <map>
#include <cstring>
#include <stdlib.h>
#include "matrix/Matrix.h"
#include "matrix/Vector.h"
#include "getData.h"
#include <time.h>



const int errorLimit = 5;


int main(int argc, char* argv[]) {

	clock_t start, end;
	start = clock();

	// pattern part
	char *patternFilename = new char[100];
	strcpy(patternFilename, "../datafolder/onlydata.txt");
	int totalCheckNumberLine = CountLines(patternFilename);
	int patternLength;


	// text part
	char *textFilename = new char[100];
	strcpy(textFilename, "../datafolder/longest.txt");
	string Text = ReturnString(patternFilename,0);

	// alphabet part
	string alphabet = "GTAC ";
	int alphabetSize = alphabet.length();

	//alphabet matrix S
	Matrix S;
	std::map<char,Vector> sMap;

	//result Matrix
	std::vector<Matrix> SinglePatternResult;

    for (int j = 0; j <= totalCheckNumberLine ;j++)
    {
    	if(j == 57054) continue;

		string Pattern = ReturnString(patternFilename,j).substr(0,32);
		patternLength = Pattern.length();

		S.setsize(patternLength, alphabetSize);
		S.set(initWithSpecificChar(0.0, patternLength*alphabetSize));
		initWithInputString(Pattern,alphabet,S);
		S=S.transpose();

		sMap.clear();
		sMap = sMapInit(S,alphabet);

		SinglePatternResult.clear();
		SinglePatternResult.push_back(getExactMatchMatrix(Pattern,Text,sMap));

		for (int i = 0;i < errorLimit ;i ++)
		{
			SinglePatternResult.push_back(getNextMatrix(Pattern,Text,sMap,SinglePatternResult[i],i));
		}

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
		//if(posnum == 0 )
		//	cout<<"not find in "<<j<<" sequence!!!"<<endl;
		delete []pos;
	}
  	delete []textFilename;
  	delete []patternFilename;
  	
  	end = clock();

  	// show the clock elipse time
 	std::cout<<"Run time: "<<(double)(end - start) / CLOCKS_PER_SEC<<" s"<<std::endl;
	return 0;
}

