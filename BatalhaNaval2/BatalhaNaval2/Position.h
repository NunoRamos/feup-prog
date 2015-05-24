#ifndef POSITION_H
#define POSITION_H

template <class T>
class Position
{
public:
	Position();
	Position(T line, T column);
	T GetLine() const;
	T GetColumn() const;
	void SetLine(T line);
	void SetColumn(T column);
	void SetPosition(T line, T column);
	Position<T>& operator=(const Position<T>& right);
private:
	T line;
	T column;
};

struct PositionChar // to store a board position in char format
{ // example: 'B','d'
	char lin, col; // ranges: lin - ['A'..'Z']; col - ['a'..'z']
};
//-----------------------------------------------------------------------------
struct PositionInt // to store a board position in unsig. integer format
{ // example: 7,0
	unsigned int lin, col; // ranges: lin - [0..26]; col - [0..26]
};
#endif