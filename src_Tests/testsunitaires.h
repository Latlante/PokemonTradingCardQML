#ifndef TESTSUNITAIRES_H
#define TESTSUNITAIRES_H

#include <QObject>
#include <QDebug>

#define COMPARE(arg1,arg2)  (Q_ASSERT_X(arg1 == arg2, __FUNCTION__, messageToDisplayInConsole(#arg1, arg1, arg2)))

class TestsUnitaires : public QObject
{
    Q_OBJECT
public:
    explicit TestsUnitaires(QObject *parent = nullptr);

signals:

private:
    //template<typename T> void COMPARE(T arg1, T arg2);

    void checkStructCardPokemonByCreatingACustomOne();
    void checkStructCardPokemonByCreatingASpecificOne();
    void checkStructCardEnergyByCreatingACustomOne();
    void checkStructCardEnergyByCreatingASpecificOne();

    const char *messageToDisplayInConsole(const char* nameVar, QVariant arg1, QVariant arg2);
};

#endif // TESTSUNITAIRES_H
