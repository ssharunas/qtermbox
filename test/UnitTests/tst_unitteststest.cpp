#include <QString>
#include <QtTest>

class UnitTestsTest : public QObject
{
    Q_OBJECT
    
public:
    UnitTestsTest();
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void stringPrint();
};

UnitTestsTest::UnitTestsTest()
{
}

void UnitTestsTest::initTestCase()
{
}

void UnitTestsTest::cleanupTestCase()
{
}

void UnitTestsTest::stringPrint()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(UnitTestsTest)

#include "tst_unitteststest.moc"
