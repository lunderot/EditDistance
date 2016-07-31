#include "Operation.h"

Operation::PrintType Operation::printType = Operation::PrintType::Long;

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

Operation::Type Operation::GetType() const
{
	return type;
}

void Operation::SetPrintType(PrintType printType)
{
	Operation::printType = printType;
}

Operation::PrintType Operation::GetPrintType()
{
	return printType;
}

std::ostream& operator<<(std::ostream& os, const Operation& o)
{
	if (o.printType == Operation::PrintType::Long)
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
	}
	else
	{
		switch (o.type)
		{
		case Operation::None:
			os << "n ";
			break;
		case Operation::Copy:
			os << "c ";
			break;
		case Operation::Replace:
			os << "r" << o.letter;
			break;
		case Operation::Delete:
			os << "d ";
			break;
		case Operation::Insert:
			os << "i" << o.letter;
			break;
		case Operation::Twiddle:
			os << "t ";
			break;
		case Operation::Kill:
			os << "k" << o.position;
			break;
		default:
			break;
		}
	}
	return os;
}
