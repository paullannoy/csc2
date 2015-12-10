#include "type_piece.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

void appel_test_type_piece(void)
{

    test_type_correspondre_caractere_animal();
    test_type_etre_animal();
    test_type_etre_integre();
    test_type_nommer_nom_cours();
}

int type_etre_integre(type_piece type)
{
    // L'enumeration designe un type integre si elle est comprise
    //  entre 0 et 4.
    // Une enumeration etant un type non signee, il est forcement positif.
    // Il suffit donc que type soit < 4 pour designer un type valide.
    if(type<4)
        return 1;
    return 0;
}

void test_type_etre_integre(void)
{
    puts("Test type_etre_integre \n");
    int i = 0;
    // test pour les valeurs de 0 a 3, correspondant elephant, rhinoceros, rocher et case_vide
    for(i=0;i<4;i++)
        if(type_etre_integre(i) != 1)
            printf("%d KO \n",i);
    // test pour des valeurs ne correspondant à rien
    for(i=4;i<100;i++)
        if(type_etre_integre(i) != 0)
            printf("%d KO \n",i);
}


int type_etre_animal(type_piece type)
{
    if( (type == elephant) || (type == rhinoceros) )
    //verifie si le type est soit un rhinoceros soit un elephant
        return 1;
    return 0;
}

void test_type_etre_animal(void)
{
    puts("Test type_etre_animal \n");


    /*Cas 1 type elephant */
    if( type_etre_animal(elephant)!=1 )
         puts("elephant KO");

    /*Cas 2 type rhinoceros */
    if( type_etre_animal(rhinoceros)!=1 )
        puts("rhinoceros KO");

    /*Cas 3 type rocher */
    if( type_etre_animal(rocher)!=0 )
        puts("rocher KO");

    /*Cas 4 type case_vide*/
    if(type_etre_animal(case_vide) != 0)
        puts("case vide KO");

    /*Cas 5 type>=4*/
    int k=0;
    for(k=4;k<100;++k)
        if(type_etre_animal(k) != 0)
            printf("valeur %d KO \n",k);


}


const char* type_nommer(type_piece type)
{
    // "Look up table" (LUT) convertissant un type de piece vers
    //    la chaine de caractere correspondante.

    switch(type)
    {
    case elephant:
        return "elephant"; break;
    case rhinoceros:
        return "rhinoceros"; break;
    case rocher:
        return "rocher"; break;
    case case_vide:
        return "vide"; break;
    default:
        printf("Erreur, type piece %d non reconnue",type);
        abort();
    }

    puts("Ne devrait jamais entrer sur cette ligne");
    abort();
}


const char* type_nommer_nom_cours(type_piece type)
{
    // "Look up table" (LUT) convertissant un type de piece vers
    //    la chaine de caractere courte correspondante.

    switch(type)
    {
    case elephant:
        return "e"; break;
    case rhinoceros:
        return "r"; break;
    case rocher:
        return "RRR"; break;
    case case_vide:
        return "***"; break;
    default:
        printf("Erreur, type piece %d non reconnue",type);
        abort();
    }

    puts("Ne devrait jamais entrer sur cette ligne");
    abort();
}
// UTILISER BIBLIOTHEQUE STRING.H
void test_type_nommer_nom_cours(void)
{
    puts("Test type_nommer_nom_cours \n");

     if(strcmp(type_nommer_nom_cours(elephant), "e") != 0)
         puts("elephant KO\n");
     if(strcmp(type_nommer_nom_cours(rhinoceros), "r") != 0)
         puts("rhinoceros KO\n");
     if(strcmp(type_nommer_nom_cours(rocher), "RRR") != 0)
         puts("rocher KO\n");
     if(strcmp(type_nommer_nom_cours(case_vide), "***") != 0)
         puts("vide KO\n");
}

int type_caractere_animal_etre_integre(char type)
{
    // Verifie que le caractere correspond a elephant (e) ou rhinoceros (r).
    if(type=='e' || type=='r')
        return 1;
    return 0;
}

type_piece type_correspondre_caractere_animal(char type)
{
    assert( type_caractere_animal_etre_integre(type) ); // prevention si le type n'est pas un animal

    type_piece type_enum = elephant; // initialisation de ce que la fonction va retourner

    if(type == 'e')
        type_enum = elephant; //assigne le type elephant si la chaine est "e"
    else if(type == 'r')
        type_enum = rhinoceros; //assigne le type rhinoceros si la chaine est "r"

    return type_enum; //renvoie un type animal
}

void test_type_correspondre_caractere_animal(void)
{
    puts("Test type_correspondre_caractere_animal \n");

    char chaine1 = 'e';
    char chaine2 = 'r';

    /*Cas 1 chaine = "e" */
    if(type_correspondre_caractere_animal(chaine1) != elephant)
        puts("elephant 'e' KO\n");

    /*Cas 2 chaine = "r" */
    if(type_correspondre_caractere_animal(chaine2) != rhinoceros)
        puts("'rhinoceros 'r' KO\n");

}
