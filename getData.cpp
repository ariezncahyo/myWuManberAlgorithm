#include <cstring>
#include <iostream>
#include <fstream>
#include "getData.h"
using namespace std;
//#include "getData.h"
/*
return how man lines in the file
input: filename
output: number of lines in this file
*/
int CountLines(char *filename)  
{  
    ifstream ReadFile;  
    int n=0;  
    string tmp;  
    ReadFile.open(filename,ios::in);
    if(ReadFile.fail())
    {  
        return 0;  
    }  
    else
    {  
        while(getline(ReadFile,tmp,'\n'))  
        {  
            n++;  
        }  
        ReadFile.close();  
        return n;  
    }   
}  
/*
return a specific given the lines
input: 
	filename: file name
	selectNum: selected number
output:
	tmp: specific string
*/
string ReturnString(char *filename,int selectNum)  
{  
    ifstream ReadFile;  
    int n=0;  
    string tmp;  
    ReadFile.open(filename,ios::in);
    if(ReadFile.fail())
    {  
        return 0;  
    }  
    else
    {  
        while(getline(ReadFile,tmp,'\n'))  
        {  
        	if (selectNum == n)
        	{
        		ReadFile.close();  
        		return tmp;
        	}
            n++;  
        }  
        ReadFile.close();  
        return NULL;  
    }   
}  

/*
write new file through an old file
input:
	filename: old file name
output:
	outFileName: new file name

*/

void WriteNewFile(char *filename, char *outFileName)  
{  
    ifstream ReadFile;  
    ofstream WriteFile;
    int n=0;  
    string tmp;  
    ReadFile.open(filename,ios::in);
    WriteFile.open(outFileName,ios::out);

    if(ReadFile.fail())
    {  
        return;  
    }  
    else
    {  
        while(getline(ReadFile,tmp,'\n'))  
        {  
            n++; 
            if (tmp[0] == '>')
            	continue;
        }  
        WriteFile<<tmp<<std::endl;// write the string to the file
        ReadFile.close();
        WriteFile.close();  
        return;  
    }   
}  

/*
find the longest string in the text

input: filename
output: the longest string itself

*/
std::string getLongestString(char *filename)
{
    ifstream ReadFile;  
    string tmp; 
    int maxSize = 0; 
    int count = 0;
    int maxLineNumber = 0;
    ReadFile.open(filename,ios::in);
    if(ReadFile.fail())
    {  
        return 0;  
    }  
    else
    {  
        while(getline(ReadFile,tmp,'\n'))  
        {  
            //std::cout<<tmp.length()<<std::endl;
            if(tmp.length() > maxSize){
                maxSize = tmp.length();
                maxLineNumber = count; 
            }
            count++;
        }  

        tmp = ReturnString(filename,maxLineNumber); 
       
        ReadFile.close();  
        std::cout<<"sequence number is "<< maxLineNumber <<std::endl;
        return tmp;  
    }   
}



/*
--- write the string to the file
input: filename
        input string
output: null
*/

void writeStringToFile(char* filename, std::string inputString)
{
    ofstream WriteFile;
    WriteFile.open(filename,ios::out | ios::app);

    if(WriteFile.fail())
    {  
        return;  
    }  
    else
    {  
        WriteFile<<inputString<<std::endl;  
        WriteFile.close();  
        return;  
    }   
}