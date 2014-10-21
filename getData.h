#include <cstring>
#include <iostream>
#include <fstream>
/*---  file operation -----*/
/*
return how man lines in the file
input: filename
output: number of lines in this file
*/
int CountLines(char *);  

/*
return a specific given the lines
input: 
	filename: file name
	selectNum: selected number
output:
	tmp: specific string
*/
	
std::string ReturnString(char *,int );  

/*
write new file through an old file
input:
	filename: old file name
output:
	outFileName: new file name

*/
void WriteNewFile(char *, char *);  
/*
find the longest string in the text

input: filename
output: the longest string itself

*/

std::string getLongestString(char *);



/*
--- write the string to the file
input: filename
        input string
output: null
*/
void writeStringToFile(char*, std::string);