#ifndef CTRLSELECTINGCARDS_H
#define CTRLSELECTINGCARDS_H

#include <QObject>

class QQmlEngine;
class QQmlApplicationEngine;
class ModelSelectingCards;

class CtrlSelectingCards : public QObject
{
    Q_OBJECT
public:
    explicit CtrlSelectingCards(QObject *parent = nullptr);
    ~CtrlSelectingCards();

    static void declareQML();
    bool install(QQmlApplicationEngine *pEngine);

    void setName(const QString& name);

    Q_INVOKABLE ModelSelectingCards* model();

    Q_INVOKABLE void addANewCard(int id);
    Q_INVOKABLE void removeACard(int id);
    Q_INVOKABLE void changeQuantityCard(int id, int quantity);
    Q_INVOKABLE void fillARandomList();

signals:

private:
    ModelSelectingCards* m_modelSelectingCards;
};

#endif // CTRLSELECTINGCARDS_H
