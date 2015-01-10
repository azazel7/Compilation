#pragma once

#include <string>
#define INT_TYPE 'a' 
#define FLOAT_TYPE 'b'
#define VOID_TYPE 'c'
#define POINTER_TYPE 'd'
#define FUNCTION_TYPE 'e'

class Type
{
	public:
	virtual void print(void) const = 0;
	virtual bool operator==(Type const&) const = 0;
	virtual bool operator!=(Type const&) const;
	virtual char getType(void) const = 0;
	virtual int getSize() const = 0;
	virtual std::string getString(void) const = 0;
	virtual ~Type();
};
