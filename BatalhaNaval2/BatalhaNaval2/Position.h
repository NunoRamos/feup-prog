#ifndef POSITION_H
#define POSITION_H

template <class T>
struct Position
{
	T line;
	T column;
};

//class Position
//{
//public:
//	Position();
//	Position(T line, T column);
//	T GetLine() const;
//	T GetColumn() const;
//	void SetLine(T line);
//	void SetColumn(T column);
//	void SetPosition(T line, T column);
//	Position<T>& operator=(const Position<T>& right);
//private:
//	T line;
//	T column;
//};
//
//template<class T>
//Position<T>::Position()
//{
//		line = 0;
//		column = 0;
//}
//
//template<class T>
//Position<T>::Position(T line, T column)
//{
//	this->line = line;
//	this->column = column;
//}
//
//template<class T>
//T Position<T>::GetLine() const
//{
//	return line;
//}
//
//template<class T>
//T Position<T>::GetColumn() const
//{
//	return column;
//}
//
//template<class T>
//void Position<T>::SetLine(T line)
//{
//	this->line = line;
//}
//
//template<class T>
//void Position<T>::SetColumn(T column)
//{
//	this->column = column;
//}
//
//template<class T>
//void Position<T>::SetPosition(T line, T column)
//{
//	this->line = line;
//	this->column = column;
//}
//
//template<class T>
//Position<T>& Position<T>::operator=(const Position<T>& right)
//{
//	this->line = right.GetLine();
//	this->column = right.GetColumn();
//	return *this;
//}

#endif