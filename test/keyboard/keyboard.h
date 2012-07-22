#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QObject>
#include <QHash>
#include <QTermboxCore>
#include"keycontainer.h"

class Keyboard : public QObject
{
	Q_OBJECT
public:
	explicit Keyboard(QObject *parent = 0);
	~Keyboard();

private:
	void initVariables();
	void paintKeyboard();
	void drawPressed(QTermboxKeyEvent &ev);
	void prettyPrintPress(QTermboxKeyEvent &ev);
	void prettyPrintPressAlternative(QTermboxKeyEvent &ev);
	void prettyPrintResize(QTermboxResizeEvent &ev);

private:
	QTermboxCellContainer* vBorder;
	QTermboxCellContainer* vBar;
	QTermboxCellContainer* hBorder;
	KeyContainer *keys;
	bool ctrlxpressed;
	long lastAlternativeKeyX;
	long lastAlternativeTextX;


public slots:
	void onKeyEvent(QTermboxKeyEvent event);
	void onKeyEventAlternative(QTermboxKeyEvent event);
	void onResizeEvent(QTermboxResizeEvent event);
};

#endif // KEYBOARD_H
