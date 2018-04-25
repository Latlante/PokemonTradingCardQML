#ifndef CTRLPOPUPS_H
#define CTRLPOPUPS_H

#include <QObject>

class AbstractCard;
class AbstractPacket;
class BenchArea;
class ModelPopupSelectCardInPacket;
class QQmlEngine;
class QQmlApplicationEngine;

class CtrlPopups : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)

public:
    explicit CtrlPopups(QObject *parent = nullptr);
    ~CtrlPopups();

    static void declareQML();
    bool install(QQmlApplicationEngine *pEngine);

    bool visible();
    void setVisible(bool state);

    Q_INVOKABLE ModelPopupSelectCardInPacket* model();
    Q_INVOKABLE QList<int> displayBench(BenchArea* packet);

    Q_INVOKABLE void selectionCardsFinished();

signals:
    void visibleChanged();
    void selectionFinished();

private:
    ModelPopupSelectCardInPacket* m_modelPopups;
    bool m_visible;
};

#endif // CTRLPOPUPS_H
