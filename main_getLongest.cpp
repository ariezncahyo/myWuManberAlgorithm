#include "getData.h"
#include <iostream>



int main(){
	char *inputfile = new char[100];
	char *outputfile = new char[100];

	strcpy(inputfile, "../datafolder/onlydata.txt");
	strcpy(outputfile,"../datafolder/longest.txt");


	//std::string longString = getLongestString(inputfile);
	//writeStringToFile(outputfile, longString);
	delete []inputfile;
	delete []outputfile;
}