#ifndef _QITEM_H
	#define _QITEM_H

//class of a Queue item that holds a row+col coordination and its distance from a source 
//for find shortest path function

class QItem
{
	int _row;
	int _col;
	int _distance;
public:
	QItem(int row, int col, int dist) : _row(row), _col(col), _distance(dist) {};

	int getRow() const { return _row; }
	int getCol() const { return _col; }
	int getDistance() const { return _distance; }
};

#endif