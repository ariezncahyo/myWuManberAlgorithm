#include <cstring>
#include <map>
#include <vector>
#include "matrix/Matrix.h"
#include "matrix/Vector.h"

double* initWithSpecificChar(double x,int length);

void initWithInputString(const string inputString,const string alphabetArray,Matrix &initMatrix);// init with a specific string

const std::map<char, Vector> sMapInit(const Matrix S, const string alphabet);

Vector vectorShift(Vector inputVector);

Vector vector_AND_Operate(Vector lhs,Vector rhs);

Vector vector_OR_Operate(Vector lhs,Vector rhs);

Matrix getExactMatchMatrix(const string Pattern, const string Text, std::map<char,Vector> sMap);

//Matrix getNextMatrix(const string Pattern, const string Text, std::map<char,Vector> sMap, const Matrix CurrentMatrix, int errorCount, Matrix &insertMatrix, Matrix &deleteMatrix, Matrix &substiMatrix);

Matrix getNextMatrix(const string Pattern, const string Text, std::map<char,Vector> sMap, const Matrix CurrentMatrix, int errorCount);

void printMatch(const std::string text, const std::string pattern, const std::vector<int> resultVector);

std::vector<int> localInsertSearch(const std::string Text, const std::string Pattern,const int errorCount);

