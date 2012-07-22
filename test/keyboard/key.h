#ifndef KEY_H
#define KEY_H

#include <QTermboxCore>

class Key : QObject
{

public:
	explicit Key(QObject* parent, int x, int y, QList<QChar> &drawData, bool isShift = false, int drawWidth = -1);

	void draw(bool pressed);
	bool isShift();

private:
	int _x;
	int _y;
	bool _isShift;

	QTermboxCellContainer* key;
	QTermboxCellContainer* keyPressed;
};

#endif // KEY_H
