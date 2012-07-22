#ifndef QTERMBOXCELLFACTORY_H
#define QTERMBOXCELLFACTORY_H

#include "qtermboxcell.h"
#include "qtermbox.h"
#include "qtermboxstyle.h"

class QTermboxCellFactory
{
public:
	QTermboxCellFactory();
	QTermboxCellFactory(const QTermboxStyle &fg, const QTermboxStyle &bg);
	QTermboxCellFactory(const QTermbox::QTermboxColor &fg, const QTermbox::QTermboxColor &bg);

	void setStyle(const QTermboxStyle &fg, const QTermboxStyle &bg);
	void setStyle(const QTermbox::QTermboxColor &fg, const QTermbox::QTermboxColor &bg);

	QTermboxCellFactory* append(QChar ch);
	QTermboxCellFactory* append(QChar ch, const QTermbox::QTermboxColor &fg, const QTermbox::QTermboxColor &bg);
	QTermboxCellFactory* append(QChar ch, const QTermboxStyle &fg, const QTermboxStyle &bg);

	QTermboxCellFactory* append(QString str);
	QTermboxCellFactory* append(QString str, const QTermbox::QTermboxColor &fg, const QTermbox::QTermboxColor &bg);
	QTermboxCellFactory* append(QString str, const QTermboxStyle &fg, const QTermboxStyle &bg);

	QTermboxCellFactory* append(QChar ch, int count);
	QTermboxCellFactory* append(QChar ch, int count, const QTermbox::QTermboxColor &fg, const QTermbox::QTermboxColor &bg);
	QTermboxCellFactory* append(QChar ch, int count, const QTermboxStyle &fg, const QTermboxStyle &bg);

	QList<QTermboxCell> create();

	QTermboxCell create(QChar ch);
	QTermboxCell create(QChar ch, const QTermbox::QTermboxColor &fg, const QTermbox::QTermboxColor &bg);
	QTermboxCell create(QChar ch, const QTermboxStyle &fg, const QTermboxStyle &bg);

	QList<QTermboxCell> create(QString str);
	QList<QTermboxCell> create(QString str, const QTermbox::QTermboxColor &fg, const QTermbox::QTermboxColor &bg);
	QList<QTermboxCell> create(QString str, const QTermboxStyle &fg, const QTermboxStyle &bg);

	QList<QTermboxCell> create(QChar ch, int count);
	QList<QTermboxCell> create(QChar ch, int count, const QTermbox::QTermboxColor &fg, const QTermbox::QTermboxColor &bg);
	QList<QTermboxCell> create(QChar ch, int count, const QTermboxStyle &fg, const QTermboxStyle &bg);

private:
	QList<QTermboxCell> container;
	QTermboxStyle foreground;
	QTermboxStyle background;
};

#endif // QTERMBOXCELLFACTORY_H
