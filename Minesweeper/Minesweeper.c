#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define table_border 8
#define number_of_mines 7
#define winning 1
#define losing -1
#define proceed 0

int subtable[table_border+2][table_border+2];
char tab[table_border+2][table_border+2];
int mine,y=0,number_d=0;

void create_subtable();
void create_table();
void print_subtable();
void print_table();
void place_mine();
int game_control();
void discovery(int row, int column);
int exposure(int row,int column);

int main()
{
	int row,column;
	int progress,again;
	char action;
	
	printf("\n\n-----------Welcome to our Minesweeper Game------------\n\n\n");
	
	create_subtable();
	create_table();
	
	do
	{
		print_table();
		printf("\n");
		printf("Please Enter in the format shown: c,row,column or d,row,column ya da e,row,column\n");
		scanf("%c%d%d",&action,&row,&column);
		printf("\n");
		
		if(action == 'c')
		{
			progress = exposure(row,column);
		}
		else if(action == 'd')
		{
			if(mine > number_d)
			{
				number_d++;
				tab[row][column] = 'D';
				progress = game_control();
			}
		}
		else if(action == 'e')
		{
			if(number_d > 0)
			{
				number_d--;
			}
			tab[row][column] = '#';
			progress = exposure(row,column);
		}
		
		if(progress == losing)
		{
			printf("!!!!!------LOSE THE GAME------!!!!!\n");
			print_subtable();
			printf("\nDo You Want To Play The Game Again? [1-YES] [0-NO]\n");
			scanf("%d",&again);
			switch(again)
			{
				case 0: printf("Thanks for Playing!\n--------See you!--------");
						return 0;
						break;
				case 1:
					number_d=0;
					progress=proceed;
					create_subtable();
					create_table();
					break;
				default:printf("You Have Entered a Wrong Value.\n");
				break;
			}
		}
		
		if(progress == winning)
		{
			printf("---------BRAVO YOU HAVE A GREAT WORK!!----------\n");
			print_subtable();
			printf("Do You Want To Play The Game Again? [1-YES] [0-NO]\n");
			scanf("%d",&again);
			switch(again)
			{
				case 0: printf("Thanks for Playing!\n--------See you!--------");
						return 0;
						break;
				case 1:
					number_d=0;
					progress=proceed;
					create_subtable();
					create_table();
					break;
				default:printf("You Have Entered a Wrong Value.\n");
				break;
			}
		}
	}while(1);
	
	return(0);
}

void create_subtable()
{
	int i,j,mine;
	
	for(i=0;i<=table_border+1;i++)
	{
		for(j=0;j<=table_border+1;j++)
		{
			subtable[i][j]=0;
		}
	}
	for(i=0;i<=table_border+1;i++)
	{
		subtable[i][0]=1;
		subtable[i][table_border+1]=1;
	}
	for(j=0;j<=table_border;j++)
	{
		subtable[0][j]=1;
		subtable[table_border+1][j]=1;
	}
	
	mine=number_of_mines;
	place_mine();
}

void create_table()
{
	int i,j;
	
	for(i=0;i<=table_border+1;i++)
	{
		for(j=0;j<=table_border+1;j++)
		{
			tab[i][j]='#';
		}
	}
	for(i=0;i<=table_border+1;i++)
	{
		tab[i][0]='*';
		tab[i][table_border+1]='*';
	}
	for(j=0;j<=table_border;j++)
	{
		tab[0][j]='*';
		tab[table_border+1][j]='*';
	}
	
}

void print_table()
{
	int i,j;
	
	for(i=1;i<=table_border;i++)
	{
		printf("%3d",i);
	}
	printf("\n");
	for(i=1;i<=table_border;i++)
	{
		printf("---");	
	}
	printf("\n");
	
	for(i=1;i<=table_border;i++)
	{
		for(j=1;j<=table_border;j++)
		{
			printf("%3c",tab[i][j]);
		}
		printf("   |%d",i);
		printf("\n");
	}
	for(i=1;i<=table_border;i++)
	{
		printf("---");
	}
}

void print_subtable()
{
	int i,j;
	
	for(i=1;i<=table_border;i++)
	{
		printf("%3d",i);
	}
	printf("\n");
	
	for(i=1;i<=table_border;i++)
	{
		printf("---");	
	}
	printf("\n");
	
	for(i=1;i<=table_border;i++)
	{
		for(j=1;j<=table_border;j++)
		{
			printf("%3d",subtable[i][j]);
		}
		printf("   |%d",i);
		printf("\n");
	}
	for(i=1;i<=table_border;i++)
	{
		printf("---");
	}
}

void place_mine()
{
	srand(time(0));
	int i,j,k,p,row,column;
	mine=number_of_mines;
	
	for(i=1;i<=mine;i++)
	{
		row=1+rand()%table_border;
		column=1+rand()%table_border;
		if(subtable[row][column] == -1)
		{
			i--;
		}
		subtable[row][column]=-1;
		for(k=-1;k<=1;k++)
		{
			for(p=-1;p<=1;p++)
			{
				if(subtable[row][column] == -1)
				{
					if(subtable[row+k][column+p] != -1)
					{
						subtable[row+k][column+p]++;
					}
				}
			}
		}
	}
}

int exposure(int row, int column)
{
	int x=0;
	
	if(subtable[row][column] == -1)
	{
		x=losing;
	}
	else if(subtable[row][column] > 0)
	{
		tab[row][column]= '0'+subtable[row][column];
		x=game_control();
		x=proceed;
	}
	else
	{
		discovery(row,column);
	}
	
	return x;
}

void discovery(int row, int column)
{
	int i,j;
	
	tab[row][column] = '0'+subtable[row][column];
	
	for(i=-1;i<=1;i++)
	{
		for(j=-1;j<=1;j++)
		{
			if(subtable[row+i][column+i] > 0 && tab[row+i][column+j] == '#')
			{
				tab[row+i][column+j] = '0'+subtable[row+i][column+j];
			}
			else if(subtable[row+i][column+j] == 0 && tab[row+i][column+j] == '#')
			{
				discovery(row+i,column+j);
			}
		}
	}
}

int game_control()
{
	int i,j,y=0;
	int statu;
	
	for(i=1;i<=table_border;i++)
	{
		for(j=1;j<=table_border;j++)
		{
			if(tab[i][j] == 'D')
			{
				if(subtable[i][j] == -1)
				{
					y++;
				}
			}
		}
	}
	if(y == number_of_mines)
	{
		statu = winning;
	}
	else
	{
		statu = proceed;
	}
	return statu;
}
