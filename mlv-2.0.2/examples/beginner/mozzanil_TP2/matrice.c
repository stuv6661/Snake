#include <stdio.h>
#include <stdlib.h>

#define Max 100

void SaisieMatrice(int Mat[100][100],int *l,int *c)
{
	int i,j;
	printf("Saisie dimension du matrice (nombre de lignes et de colonnes max=100)\n") ;
	do
	{
		printf("Donner nombre de ligne= ");
		scanf("%d",l);
		printf("Donner nombre de colonne= ");
		scanf("%d",c);
	}
	while ((*c>Max)||(*l>Max)||(*c<1)||(*l<1));
	printf("Saisie élément du matrice \n") ;
	for(i=0;i<*l;i++)
	{
		for(j=0;j<*c;j++)
		{
			printf("Donner valeur de case [%d,%d]= ",i+1,j+1);
			scanf("%d",&Mat[i][j]);
		}
	}
}


void AfficheMatrice (int Mat[100][100],int *l,int *c)
{
	int i,j;
	printf ("Votre matrice comprend les nombres suivants : \n");
	for(i=0;i<*l;i++)
	{
		for(j=0;j<*c;j++)
		{
			printf("%d ",Mat[i][j]);
		}
		printf ("\n");
	}
}

void AddLigne (int Mat[100][100], int *l,int *c)
{
	int i,j,a;
	for(i=0;i<*l;i++)
	{
		a=0;
		for(j=0;j<*c;j++)
		{
			a+=Mat[i][j];
		}
		printf ("l'adition de toutes les valeurs de la ligne %d vaut : %d \n",i+1,a);
	}
}


int main(void)
{
	int l,c,i,j;
	int Matrice[100][100];
	SaisieMatrice(Matrice,&l,&c);
	AfficheMatrice(Matrice,&l,&c);
	AddLigne(Matrice,&l,&c);
	return 0;
}
