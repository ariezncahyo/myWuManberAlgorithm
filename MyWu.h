#include <cstring>
#include <map>
#include <vector>
#include "matrix/Matrix.h"
#include "matrix/Vector.h"

 
double* initWithSpecificChar(double x,int length);//init with 0
void initWithInputString(const string inputString,const string alphabetArray,Matrix &initMatrix);// init with a specific string
const std::map<char, Vector> sMapInit(const Matrix S, const string alphabet);


Vector vectorShift(Vector inputVector);
Vector vector_AND_Operate(Vector lhs,Vector rhs);
Vector vector_OR_Operate(Vector lhs,Vector rhs);


Matrix getExactMatchMatrix(const string Pattern, const string Text, std::map<char,Vector> sMap);
Matrix getNextMatrix(const string Pattern, const string Text, std::map<char,Vector> sMap, const Matrix CurrentMatrix,int errorCount);
