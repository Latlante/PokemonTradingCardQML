#include "actiondamagemultipliedbydoubleheadortail.h"

ActionDamageMultipliedByDoubleHeadOrTail::ActionDamageMultipliedByDoubleHeadOrTail(unsigned short damageByHead) :
    AbstractAction(),
    m_damageByHead(damageByHead)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionDamageMultipliedByDoubleHeadOrTail::type()
{
    return AbstractAction::Action_DamageMultipliedByDoubleHeadOrTail;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionDamageMultipliedByDoubleHeadOrTail::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacked;
}

void ActionDamageMultipliedByDoubleHeadOrTail::action()
{
    if(pokemonAttacked() != nullptr)
    {
        unsigned short totalDamage = 0;

        for(int i=0;i<2;++i)
        {
            unsigned short coin = headOrTail();
            if(coin == 1)
                totalDamage += m_damageByHead;
        }

        pokemonAttacked()->takeDamage(totalDamage);
    }
}
