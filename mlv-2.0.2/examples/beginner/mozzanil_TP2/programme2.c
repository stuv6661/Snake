#include <stdio.h>

#define NBL 1000
#define NBC 2000

int main()
{
    int matrice[NBL][NBC];
    int i,j,sum;
    for(j=0;j<NBC;j++)
        for(i=0;i<NBL;i++)
            sum+=matrice[i][j];
    return sum;
}

// cree une matrice de 1000 lignes et de 2000 colonnes
// le programmes parcour toutes les colonnes pour additionner toutes les valeurs
// cette methode est legereemnt plus rapide que le programme1
