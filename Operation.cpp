#include "Operation.h"


Operation::Operation()
{
	this->type = None;
	this->letter = '\0';
	this->position = -1;
}

Operation::Operation(Type type)
{
	this->type = type;
	this->letter = '\0';
	this->position = -1;
}

Operation::Operation(Type type, char letter)
{
	this->type = type;
	this->letter = letter;
	this->position = -1;
}

Operation::Operation(Type type, int position)
{
	this->type = type;
	this->letter = '\0';
	this->position = position;
}



Operation::~Operation()
{
}

std::ostream& operator<<(std::ostream& os, const Operation& o)
{
	switch (o.type)
	{
		case Operation::None:
			os << "None";
		break;
		case Operation::Copy:
			os << "Copy";
			break;
		case Operation::Replace:
			os << "Replace " << o.letter;
			break;
		case Operation::Delete:
			os << "Delete";
			break;
		case Operation::Insert:
			os << "Insert " << o.letter;
			break;
		case Operation::Twiddle:
			os << "Twiddle";
			break;
		case Operation::Kill:
			os << "Kill " << o.position;
			break;
		default:
			break;
	}
	return os;
}
