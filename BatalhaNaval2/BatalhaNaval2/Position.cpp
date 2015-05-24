#include "Position.h"

template<class T>
Position<T>::Position()
{
	if (T == char)
	{
		line = 'A';
		column = 'a';
	}
	else
	{
		line = 0;
		column = 0;
	}
}

template<class T>
Position<T>::Position(T line, T column)
{
	this->line = line;
	this->column = column;
}

template<class T>
T Position<T>::GetLine() const
{
	return line;
}

template<class T>
T Position<T>::GetColumn() const
{
	return column;
}

template<class T>
void Position<T>::SetLine(T line)
{
	this->line = line;
}

template<class T>
void Position<T>::SetColumn(T column)
{
	this->column = column;
}

template<class T>
void Position<T>::SetPosition(T line, T column)
{
	this->line = line;
	this->column = column;
}

template<class T>
Position<T>& Position<T>::operator=(const Position<T>& right)
{
	this->line = right.GetLine();
	this->column = right.GetColumn();
	return *this;
}