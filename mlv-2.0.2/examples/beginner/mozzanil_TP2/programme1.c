#include <stdio.h>

#define NBL 1000
#define NBC 2000

int main()
{
    int matrice[NBL][NBC];
    int i,j,sum;
    for(i=0;i<NBL;i++)
        for(j=0;j<NBC;j++)
            sum+=matrice[i][j];
    return sum;
}

// cree une matrice de 1000 lignes et 2000 colonnes,
// le programmes parcour toutes les lignes pour additionner toutes les valeurs
// methode legerement plus longue que le programme2
