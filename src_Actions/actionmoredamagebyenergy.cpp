#include "actionmoredamagebyenergy.h"
#include "gamemanager.h"
#include "src_Packets/fightarea.h"
#include "src_Cards/cardpokemon.h"

ActionMoreDamageByEnergy::ActionMoreDamageByEnergy(unsigned short damageByEnergy) :
    AbstractAction(),
    m_damageByEnergy(damageByEnergy)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionMoreDamageByEnergy::type()
{
    return AbstractAction::Action_MoreDamageByEnergy;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionMoreDamageByEnergy::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacked
            << AbstractAction::CheckPokemonAttacking;
}

void ActionMoreDamageByEnergy::action()
{
    bool status = false;
    unsigned short countEnergies = 0;

    if((pokemonAttacking() != nullptr) && (indexAttack() != -1))
    {
        AbstractCard::Enum_element elementEnergy = pokemonAttacking()->element();
        countEnergies = pokemonAttacking()->countEnergies(elementEnergy);
        countEnergies -= pokemonAttacking()->listAttacks()[indexAttack()].costEnergies[elementEnergy];
        status = true;
    }

    if(status == true)
    {
        if(pokemonAttacked() != nullptr)
        {
            pokemonAttacked()->takeDamage(m_damageByEnergy * countEnergies);
        }

    }
}
