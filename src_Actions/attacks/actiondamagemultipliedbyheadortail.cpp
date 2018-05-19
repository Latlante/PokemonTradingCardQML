#include "actiondamagemultipliedbyheadortail.h"


ActionDamageMultipliedByHeadOrTail::ActionDamageMultipliedByHeadOrTail(unsigned short damageByHead, unsigned short numberOfCoins) :
    AbstractAction(),
    m_damageByHead(damageByHead),
    m_numberOfCoins(numberOfCoins)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionDamageMultipliedByHeadOrTail::type()
{
    return AbstractAction::Action_DamageMultipliedByHeadOrTail;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionDamageMultipliedByHeadOrTail::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacked;
}

void ActionDamageMultipliedByHeadOrTail::actionAfterAttack()
{
    if(pokemonAttacked() != nullptr)
    {
        unsigned short totalDamage = 0;

        for(int i=0;i<m_numberOfCoins;++i)
        {
            unsigned short coin = headOrTail();
            if(coin == 1)
                totalDamage += m_damageByHead;
        }

        pokemonAttacked()->takeDamage(totalDamage);
    }
}
