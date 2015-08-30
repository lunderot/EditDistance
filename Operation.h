#include <iostream>

class Operation
{
public:
	enum Type
	{
		None,
		Copy,
		Replace,
		Delete,
		Insert,
		Twiddle,
		Kill
	};
private:
	Type type;
	char letter;
	int position;
public:
	Operation();
	Operation(Type type);
	Operation(Type type, char letter);
	Operation(Type type, int position);
	~Operation();

	friend std::ostream& operator<<(std::ostream& os, const Operation& o);
};
