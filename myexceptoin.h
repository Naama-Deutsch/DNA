#ifndef __MYEXCEPTION_H__
#define __MYEXCEPTION_H__
#include <exception>

class invalid_inputs:public std::exception
{
public:
	const char* what();
private:	
};

inline const char* invalid_inputs::what(){
	return "not match input";
}



class open_file_error:public std::exception
{
public:
	const char* what();
private:	
};

inline const char* open_file_error::what(){
	return "you failed open file in dna";
}
#endif

