#ifndef UTILS_H
#define UTILS_H

#include <QObject>

class Utils : public QObject
{
    Q_OBJECT
public:
    explicit Utils(QObject *parent = nullptr);

    static unsigned short headOrTail();
    static unsigned short selectFirstPlayer(int count);
    static unsigned short selectRandomCardsPokemon();
    static unsigned short selectRandomCardsEnergy();

private:
    static int randomValue(int min, int max);
};

#endif // UTILS_H
