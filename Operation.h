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
	enum PrintType
	{
		Short,
		Long
	};
private:
	Type type;
	char letter;
	int position;

	static PrintType printType;
public:
	Operation();
	Operation(Type type);
	Operation(Type type, char letter);
	Operation(Type type, int position);
	~Operation();

	static void SetPrintType(PrintType printType);
	static PrintType GetPrintType();

	friend std::ostream& operator<<(std::ostream& os, const Operation& o);
};
