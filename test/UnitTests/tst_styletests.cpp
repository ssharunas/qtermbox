#include <QString>
#include <QtTest>
#include "../../src/core/QTermboxCore"
#include "AutoTest.h"

class QTermboxStyleTest : public QObject
{
	Q_OBJECT

public:
	QTermboxStyleTest();

private Q_SLOTS:
	void equalTest();
};

QTermboxStyleTest::QTermboxStyleTest()
{
}

void QTermboxStyleTest::equalTest()
{
	QTermboxStyle *cellA = new QTermboxStyle(QTermbox::Yellow, QTermbox::Underline);
	QTermboxStyle *cellB = new QTermboxStyle(QTermbox::Yellow, QTermbox::Bold);
	QTermboxStyle *cellC = new QTermboxStyle(QTermbox::Yellow, QTermbox::Underline);

	QVERIFY(*cellA == *cellC);
	QVERIFY(*cellB != *cellA);
	QVERIFY(*cellB != *cellC);

	delete cellA;
	delete cellB;
	delete cellC;
}

DECLARE_TEST(QTermboxStyleTest)

#include "tst_styletests.moc"
