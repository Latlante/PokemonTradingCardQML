#include "listplayers.h"
#include <QDebug>
#include <QtQml/qqml.h>

ListPlayers::ListPlayers(QObject *parent) : QAbstractListModel(parent)
{
    addNewPlayer();
    addNewPlayer();
}

/************************************************************
*****				FONCTIONS STATIQUES					*****
************************************************************/
void ListPlayers::declareQML()
{
    qmlRegisterUncreatableType<ListPlayers>("model", 1, 0, "ListPlayers", "BenchArea error");
}

QStringList ListPlayers::listOfPlayers()
{
    return m_listOfPlayers;
}

void ListPlayers::addNewPlayer()
{
    qDebug() << "nouveau joueur";
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_listOfPlayers.append("Player " + QString::number(m_listOfPlayers.count()+1));
    endInsertRows();
}

void ListPlayers::removeOnePlayer()
{
    qDebug() << "supprimer joueur";
    beginRemoveRows(QModelIndex(), rowCount()-1, rowCount());
    m_listOfPlayers.removeLast();
    endRemoveRows();
}

QVariant ListPlayers::data(const QModelIndex &index, int role) const
{
    qDebug() << __PRETTY_FUNCTION__ << index << role;
    int iRow = index.row();
    if ((iRow < 0) || (iRow >= rowCount()))
    {
        qCritical() << __PRETTY_FUNCTION__ << "bad column num : " << iRow;
        return QVariant();
    }

    if (Qt::DisplayRole == role)
    {
        return m_listOfPlayers[iRow];
    }

    return QVariant();
}

int ListPlayers::rowCount(const QModelIndex &) const
{
    return m_listOfPlayers.count();
}

/************************************************************
*****				FONCTIONS PROTEGEES					*****
************************************************************/
QHash<int, QByteArray> ListPlayers::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "name";

    return roles;
}
