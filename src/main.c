
#include "piece_siam.h"
#include "plateau_siam.h"
#include "jeu_siam.h"
#include "api_siam.h"
#include "mode_interactif.h"
#include "plateau_modification.h"

#include <stdio.h>
#include <stdlib.h>

void test_lancement()
{
    appel_test_type_piece();
    appel_test_orientation_deplacement();
    appel_test_piece_siam();
}



int main()
{

    jeu_siam* jeu=malloc(sizeof(jeu_siam));
    jeu_initialiser(jeu);
    mode_interactif_lancer();
    return 0;
}
