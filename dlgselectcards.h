#ifndef DLGSELECTCARDS_H
#define DLGSELECTCARDS_H

#include <QObject>

class AbstractCard;

class DlgSelectCards : public QObject
{
    Q_OBJECT

public:
    explicit DlgSelectCards(const QString& name, QObject *parent = 0);
    ~DlgSelectCards();

    QList<AbstractCard*> listOfSelectedCards();
    QList<AbstractCard*> listOfRandomCards();

private:
    QString m_name;
};

#endif // DLGSELECTCARDS_H
