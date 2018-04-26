#include "actiondamagemultipliedbytripleheadortail.h"

ActionDamageMultipliedByTripleHeadOrTail::ActionDamageMultipliedByTripleHeadOrTail(unsigned short damageByHead) :
    AbstractAction(),
    m_damageByHead(damageByHead)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionDamageMultipliedByTripleHeadOrTail::type()
{
    return AbstractAction::Action_DamageMultipliedByTripleHeadOrTail;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionDamageMultipliedByTripleHeadOrTail::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacked;
}

void ActionDamageMultipliedByTripleHeadOrTail::action()
{
    if(pokemonAttacked() != nullptr)
    {
        unsigned short totalDamage = 0;

        for(int i=0;i<3;++i)
        {
            unsigned short coin = headOrTail();
            if(coin == 1)
                totalDamage += m_damageByHead;
        }

        pokemonAttacked()->takeDamage(totalDamage);
    }
}
