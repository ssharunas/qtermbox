#include "qtermboxcellfactory.h"
#include "qtermboxcore.h"
#include <QString>

QTermboxCellFactory::QTermboxCellFactory()
	: foreground(QTermbox::White), background (QTermbox::Black)
{
	foreground = QTermboxCore::clearForeground();
	background = QTermboxCore::clearBackground();
}

QTermboxCellFactory::QTermboxCellFactory(const QTermboxStyle &fg, const QTermboxStyle &bg)
	: foreground(fg), background(bg)
{
}

QTermboxCellFactory::QTermboxCellFactory(const QTermbox::QTermboxColor &fg, const QTermbox::QTermboxColor &bg)
	: foreground(fg), background(bg)
{
}

void QTermboxCellFactory::setStyle(const QTermboxStyle &fg, const QTermboxStyle &bg)
{
	foreground = fg;
	background = bg;
}

void QTermboxCellFactory::setStyle(const QTermbox::QTermboxColor &fg, const QTermbox::QTermboxColor &bg)
{
	foreground = fg;
	background = bg;
}

QTermboxCellFactory* QTermboxCellFactory::append(QChar ch)
{
	return append(ch, foreground, background);
}

QTermboxCellFactory *QTermboxCellFactory::append(QChar ch, const QTermbox::QTermboxColor &fg, const QTermbox::QTermboxColor &bg)
{
	return append(ch, QTermboxStyle(fg), QTermboxStyle(bg));
}

QTermboxCellFactory *QTermboxCellFactory::append(QChar ch, const QTermboxStyle &fg, const QTermboxStyle &bg)
{
	container << create(ch, fg, bg);
	return this;
}

QTermboxCellFactory *QTermboxCellFactory::append(QString str)
{
	return append(str, foreground, background);
}

QTermboxCellFactory *QTermboxCellFactory::append(QString str, const QTermbox::QTermboxColor &fg, const QTermbox::QTermboxColor &bg)
{
	return append(str, QTermboxStyle(fg), QTermboxStyle(bg));
}

QTermboxCellFactory *QTermboxCellFactory::append(QString str, const QTermboxStyle &fg, const QTermboxStyle &bg)
{
	container << create(str, fg, bg);
	return this;
}

QTermboxCellFactory* QTermboxCellFactory::append(QChar ch, int count)
{
	return append(ch, count, foreground, background);
}

QTermboxCellFactory *QTermboxCellFactory::append(QChar ch, int count, const QTermbox::QTermboxColor &fg, const QTermbox::QTermboxColor &bg)
{
	return append(ch, count, QTermboxStyle(fg), QTermboxStyle(bg));
}

QTermboxCellFactory *QTermboxCellFactory::append(QChar ch, int count, const QTermboxStyle &fg, const QTermboxStyle &bg)
{
	container << create(ch, count, fg, bg);
	return this;
}

QList<QTermboxCell> QTermboxCellFactory::create()
{
	QList<QTermboxCell> result = container;
	container.clear();
	return result;
}

QTermboxCell QTermboxCellFactory::create(QChar ch)
{
	return create(ch, foreground, background);
}

QTermboxCell QTermboxCellFactory::create(QChar ch, const QTermbox::QTermboxColor &fg, const QTermbox::QTermboxColor &bg)
{
	return QTermboxCell(ch, fg, bg);
}

QTermboxCell QTermboxCellFactory::create(QChar ch, const QTermboxStyle &fg, const QTermboxStyle &bg)
{
	return QTermboxCell(ch, fg, bg);
}

QList<QTermboxCell> QTermboxCellFactory::create(QString str)
{
	return create(str, foreground, background);
}

QList<QTermboxCell> QTermboxCellFactory::create(QString str, const QTermbox::QTermboxColor &fg, const QTermbox::QTermboxColor &bg)
{
	return create(str, QTermboxStyle(fg), QTermboxStyle(bg));
}

QList<QTermboxCell> QTermboxCellFactory::create(QString str, const QTermboxStyle &fg, const QTermboxStyle &bg)
{
	QList<QTermboxCell> result;

	foreach(QChar ch, str){
		result << create(ch, fg, bg);
	}

	return result;
}

QList<QTermboxCell> QTermboxCellFactory::create(QChar ch, int count)
{
	return create(ch, count, foreground, background);
}

QList<QTermboxCell> QTermboxCellFactory::create(QChar ch, int count, const QTermbox::QTermboxColor &fg, const QTermbox::QTermboxColor &bg)
{
	return QTermboxCell(ch, fg, bg).multiply(count);
}

QList<QTermboxCell> QTermboxCellFactory::create(QChar ch, int count, const QTermboxStyle &fg, const QTermboxStyle &bg)
{
	return QTermboxCell(ch, fg, bg).multiply(count);
}
