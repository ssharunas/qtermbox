#ifndef KEYCONTAINER_H
#define KEYCONTAINER_H

#include <QObject>
#include <QHash>
#include <QStringList>
#include "key.h"

class KeyContainer : public QObject
{
	Q_OBJECT
public:
	explicit KeyContainer(QObject *parent = 0);

	QList<Key*> allKeys();
	QList<Key*> getKeys(QTermboxKeyEvent &ev);
	QString qtKeyAsString(int key);

private:
	void registerKeys();
	void registerQtKeys();

private:
	QHash<QString, Key*> keys;
	QHash<int, QString> qtKey;
};

#endif // KEYCONTAINER_H
