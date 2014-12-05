#ifndef TYPE_HPP 
#define TYPE_HPP 

#define INT_TYPE 1
#define FLOAT_TYPE 2
#define VOID_TYPE 3
#define POINTER_TYPE 4

class Type
{
	public:
	virtual void print(void) const = 0;
	virtual bool operator==(Type const&) const = 0;
	virtual bool operator!=(Type const&) const;
};
#endif