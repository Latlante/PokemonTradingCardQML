#ifndef TESTSUNITAIREGENERAL_H
#define TESTSUNITAIREGENERAL_H

#include "testsunitaires.h"

class TestsUnitaireGeneral : public TestsUnitaires
{
    Q_OBJECT
public:
    TestsUnitaireGeneral();

private:
    void checkStructCardPokemonByCreatingACustomOne();
    void checkStructCardPokemonByCreatingASpecificOne();
    void checkStructCardEnergyByCreatingACustomOne();
    void checkStructCardEnergyByCreatingASpecificOne();
    void checkModelListEnergiesCountEnergies();
    void checkModelListEnergiesHasEnoughEnergies();
};

#endif // TESTSUNITAIREGENERAL_H
