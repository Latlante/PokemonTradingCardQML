#include "abstractaction.h"

AbstractAction::AbstractAction() :
    m_gameManager(nullptr),
    m_playerAttacked(nullptr),
    m_playerAttacking(nullptr),
    m_pokemonAttacked(nullptr),
    m_pokemonAttacking(nullptr),
    m_benchPlayerAttacked(nullptr),
    m_benchPlayerAttacking(nullptr)
{

}

AbstractAction::~AbstractAction()
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
void AbstractAction::executeAction()
{
    //Vérifications
    QList<AbstractAction::Enum_ElementsToCheck> listElementsToCheck = elementToCheck();
    bool statusCanBeExecuted = true;

    foreach(AbstractAction::Enum_ElementsToCheck element, listElementsToCheck)
    {
        switch(element)
        {
        case AbstractAction::CheckGameManager:
            statusCanBeExecuted &= checkGameManager();
            break;
        case AbstractAction::CheckPlayerAttacked:
            statusCanBeExecuted &= checkPlayerAttacked();
            break;
        case AbstractAction::CheckPlayerAttacking:
            statusCanBeExecuted &= checkPlayerAttacking();
            break;
        case AbstractAction::CheckPokemonAttacked:
            statusCanBeExecuted &= checkPokemonAttacked();
            break;
        case AbstractAction::CheckPokemonAttacking:
            statusCanBeExecuted &= checkPokemonAttacking();
            break;
        case AbstractAction::CheckBenchPlayerAttacked:
            statusCanBeExecuted &= checkBenchPlayerAttacked();
            break;
        case AbstractAction::CheckBenchPlayerAttacking:
            statusCanBeExecuted &= checkBenchPlayerAttacking();
            break;
        default:
            qCritical() << __PRETTY_FUNCTION__ << "Erreur elementToCheck" << element;
            statusCanBeExecuted = false;
        }
    }

    //Execution
    if(statusCanBeExecuted == true)
    {
        action();
    }
    else
    {
        qCritical() << __PRETTY_FUNCTION__ << "L'action n'a pas pu être executée";
    }
}

/************************************************************
*****				FONCTIONS PROTEGEES					*****
************************************************************/
//Pourra être utile plus tard pour les tests
unsigned short AbstractAction::headOrTail()
{
    unsigned short coin = 0;

    if(gameManager() != nullptr)
        coin = gameManager()->headOrTail();

    return coin;
}

GameManager* AbstractAction::gameManager()
{
    return m_gameManager;
}

Player* AbstractAction::playerAttacked()
{
    return m_playerAttacked;
}

Player* AbstractAction::playerAttacking()
{
    return m_playerAttacking;
}

CardPokemon* AbstractAction::pokemonAttacked()
{
    return m_pokemonAttacked;
}

CardPokemon* AbstractAction::pokemonAttacking()
{
    return m_pokemonAttacking;
}

BenchArea* AbstractAction::benchPlayerAttacked()
{
    return m_benchPlayerAttacked;
}

BenchArea* AbstractAction::benchPlayerAttacking()
{
    return m_benchPlayerAttacking;
}


/************************************************************
*****				FONCTIONS PRIVEES					*****
************************************************************/
bool AbstractAction::checkGameManager()
{
    GameManager *manager = GameManager::instance();

    if(manager != nullptr)
    {
        m_gameManager = manager;
        return true;
    }

    qCritical() << __PRETTY_FUNCTION__ << ", manager is NULL";
    return false;
}

bool AbstractAction::checkPlayerAttacked()
{
    if(checkGameManager())
    {
        Player* playerAttacked = m_gameManager->playerAttacked();

        if(playerAttacked != nullptr)
        {
            m_playerAttacked = playerAttacked;
            return true;
        }
        else
            qCritical() << __PRETTY_FUNCTION__ << ", playerAttacked is NULL";
    }

    return false;
}

bool AbstractAction::checkPlayerAttacking()
{
    if(checkGameManager())
    {
        Player* playerAttacking = m_gameManager->currentPlayer();

        if(playerAttacking != nullptr)
        {
            m_playerAttacking = playerAttacking;
            return true;
        }
        else
            qCritical() << __PRETTY_FUNCTION__ << ", playerAttacking is NULL";
    }

    return false;
}

bool AbstractAction::checkPokemonAttacked()
{
    if(checkPlayerAttacked())
    {
        FightArea *fightAr = m_playerAttacked->fight();

        if(fightAr != nullptr)
        {
            CardPokemon *pokemonAttacked = fightAr->pokemonFighting(0);

            if(pokemonAttacked != nullptr)
            {
                m_pokemonAttacked = pokemonAttacked;
                return true;
            }
            else
                qCritical() << __PRETTY_FUNCTION__ << ", pokemonAttacked is NULL";
        }
        else
            qCritical() << __PRETTY_FUNCTION__ << ", fightAr is NULL";
    }

    return false;
}

bool AbstractAction::checkPokemonAttacking()
{
    if(checkPlayerAttacking())
    {
        FightArea *fightAr = m_playerAttacking->fight();

        if(fightAr != nullptr)
        {
            CardPokemon *pokemonAttacking = fightAr->pokemonFighting(0);

            if(pokemonAttacking != nullptr)
            {
                m_pokemonAttacking = pokemonAttacking;
                return true;
            }
            else
                qCritical() << __PRETTY_FUNCTION__ << ", pokemonAttacking is NULL";
        }
        else
            qCritical() << __PRETTY_FUNCTION__ << ", fightAr is NULL";
    }

    return false;
}

bool AbstractAction::checkBenchPlayerAttacked()
{
    if(checkPlayerAttacked())
    {
        BenchArea* bench = m_playerAttacked->bench();

        if(bench != nullptr)
        {
            m_benchPlayerAttacked = bench;
            return true;
        }
        else
            qCritical() << __PRETTY_FUNCTION__ << ", bench is NULL";
    }

    return false;
}

bool AbstractAction::checkBenchPlayerAttacking()
{
    if(checkPlayerAttacking())
    {
        BenchArea* bench = m_playerAttacking->bench();

        if(bench != nullptr)
        {
            m_benchPlayerAttacking = bench;
            return true;
        }
        else
            qCritical() << __PRETTY_FUNCTION__ << ", bench is NULL";
    }

    return false;
}
