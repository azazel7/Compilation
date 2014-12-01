#ifndef TYPE_HPP 
#define TYPE_HPP 
class Type
{
	public:
	virtual void print(void) const = 0;
	virtual bool operator==(Type const&) const = 0;
	virtual bool operator!=(Type const&) const;
};
#endif
