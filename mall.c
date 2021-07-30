#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define M 30
#define N 30
#define dataLeng 30
#define fSize 30
char hash[M][N];

struct shopnode
{
	char shopname[30];
	char floor[20];
	struct shopnode *next;
};
struct node
{
	char data[30];
	struct shopnode *link;
};
struct node chainList[M];
//main
void Welcome()
{
    printf("                                                                                                         \n");
	printf("---------------------------------------------------------------------------------------------------------------\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t**********************************\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t*\t     WELCOME TO \t *\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t*\t SHOPPING CENTER\t *\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t**********************************\t\t\t\t\t\t|\n");
	printf("|\t\t\t\tAll the items at your fingertips\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t      \"WE BELIEVE IN QUALITY\"\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");

	printf("-----------------------------------------------------------------------------------------------------------------\n");

}

void display(struct shopnode *temp)
{
	
	if(temp==NULL)
	{
		printf("No shops have this item\n");
		return;
	}
	else
	{
		printf("\nYour Desired item is in the following shop(s) with location");
		printf("\n---------------------------------\n");
		printf("|%-15s|%-15s|","Floor","Shop");
		while(temp!=NULL)
		{
			//printf("\n");
			printf("\n---------------------------------\n");
			printf("|%-15s|",temp->floor);
			printf("%-15s|",temp->shopname);
			
			temp=temp->next;
		}
		printf("\n---------------------------------\n");
	}
	
}

int search(char item[],int n)
{
	
	int flag=0;
	
	for(int i=0;i<n && flag==0;i++)
	{
		
		if(strcmpi(item,chainList[i].data)==0)
		{
			display(chainList[i].link);
			flag=1;
		}
		else if(i==n-1 && flag==0)
		{
			printf("\nEnter a valid item name from the list ");
			return 0;
		}
	
	}
	return flag;	
}
void chooseItem(int n)
{
	char item[30];
	int success=0;
	int choice;
	do
	{	
		printf("\nItem List:\n\n");
		for(int i=0;i<n;i++) 
			printf("%s\n",chainList[i].data);
		printf("\nEnter the item you wish to purchase from the above list: ");
		gets(item);
		success=search(item,n);
	}while(success==0);
}


void makeHash(char slot[],char shop[],char floor2[])
{
	struct shopnode *newnode=(struct shopnode*)malloc(sizeof(struct shopnode));
	newnode->next=NULL;
	strcpy(newnode->floor,floor2);
	strcpy(newnode->shopname,shop);
	for(int i=0;i<M;i++)
	{
		if(strcmpi(chainList[i].data,slot)==0)
		{
			//if linked list is empty
			if(chainList[i].link==NULL)
				chainList[i].link=newnode;

			//else insert at end
			else
			{
				struct shopnode *temp=chainList[i].link;
				while(temp->next!=NULL)
					temp=temp->next;
				temp->next=newnode;
				
			}
		}
	}
	//null for next slot
	for(int i=0;slot[i]!='\0';i++)
        strcpy(&slot[i],"\0") ;				
}
void buildHash(FILE *f)
{
	f=fopen("mallOutline.txt","r");
	char curFloor[fSize]={'\0'},curShop[dataLeng]={'\0'},curSlot[dataLeng]={'\0'};
	
	int spaceCount=0,i=0;
	char line[30]={'\0'};
	char ch=getc(f);
	
	while(ch!='\n' && ch!=EOF)
	{
		ch=getc(f);
	}
	
	ch=getc(f); //sp1
	
	//to find the next
	while(ch!=EOF)
	{
		
		//0 space
		if(ch!=' ')
		{
			
			spaceCount=0;
			break;			
		}
		else
		{
			spaceCount++;
			ch=getc(f); //space2
			//counting the spaces
			while(ch==' ')
			{
				spaceCount++;
				ch=getc(f);
			}
			
		
			switch (spaceCount)
			{
				case 4:
					//floor
					//Null to clear the prev vals
					curFloor[0]='\0';
					curShop[0]='\0';
					curSlot[0]='\0';
					
					while(ch!='\n' && ch!=EOF)
					{
						line[i]=ch;
						i++;
						ch=getc(f);
					}
				
					strcpy(curFloor,line);
					ch=getc(f);
					break;

				case 8:
					//shop name
					while(ch!='\n' && ch!=EOF)
					{
						line[i]=ch;
						i++;

						ch=getc(f);
					}
					strcpy(curShop,line);
					ch=getc(f);
					break;

				case 12:
					
					//slot
					while(ch!='\n' && ch!=EOF)
					{
						line[i]=ch;
						i++;
						ch=getc(f);
					}
					
					strcpy(curSlot,line);
					makeHash(curSlot,curShop,curFloor);
					ch=getc(f);
					break;	
			}
			
			spaceCount=0;
			for(int i=0;line[i]!='\0';i++)
				strcpy(&line[i],"\0") ;
			i=0;
		}
	}
    fclose(f);
}
void main()
{
    int i,j,k,l,m,choice,s;
    i=j=k=0;
	char ch;
    Welcome();
    printf("\n");

	//file pointer
    FILE *sectionPtr=fopen("type.txt","r");
    FILE *mallPtr=fopen("mallOutline.txt","r");
	char line[N];

    if(sectionPtr==NULL)
	{
        printf("Section file does not exist");
		return;
	}
	if(mallPtr==NULL)
	{
        printf("mall file does not exist");
		return;
	}

	//assigning null to all
	for(j=0;j<M;j++)
		for(k=0;k<N;k++)
			hash[j][k]='\0';

	j=0;
	//storing values from file to hash table
    while((ch=getc(sectionPtr))!=EOF)
    {
		while(ch!='\n' && ch!=EOF)
		{
			line[i]=ch;
			i++;
			ch=getc(sectionPtr);
		}
		for(k=0;k<i;k++)
		{
			hash[j][k]=line[k];
		}
		i=0;
		j++;
    }

	int n_row=j;
	//assigning null values to chainlist
	for(j=0;j<M;j++)
		for(k=0;k<N;k++)
			chainList[j].data[k]='\0';
			
	//assigning the chain list with all slots of shops
	for(i=0;i<n_row;i++)
		for(k=0;hash[i][k];k++)
			chainList[i].data[k]=hash[i][k];

	buildHash(mallPtr);
	do
	{
		chooseItem(n_row);
		printf("Do you want to search more items \nEnter 1 for yes else any other number: ");
		scanf("%d",&s);
		fflush(stdin);

	}while(s==1);
	fclose(mallPtr);//purchase
}
/* 
---------------------------------------------------------------------------------------------------------------  
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                               **********************************                                              |
|                               *            WELCOME TO          *                                              |
|                               *        SHOPPING CENTER         *                                              |
|                               **********************************                                              |
|                               All the items at your fingertips                                                |
|                                                                                                               |
|                                     "WE BELIEVE IN QUALITY"                                                   |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
-----------------------------------------------------------------------------------------------------------------


Item List:

Shoes
Sandals
Slippers
Kids Wear
Male Wear
Female Wear
Bags
Watches
Silver
Gold
Diamond
Platinum
Novels
Short Stories
Stationary
Art Pieces
Sweets

Enter the item you wish to purchase from the above list: gold

Your Desired item is in the following shop(s) with location
---------------------------------
|Floor          |Shop           |
---------------------------------
|First Floor    |Malabar        |
---------------------------------
|Second Floor   |Tanishq        |
---------------------------------
Do you want to search more items
Enter 1 for yes else any other number: 1

Item List:

Shoes
Sandals
Slippers
Kids Wear
Male Wear
Female Wear
Bags
Watches
Silver
Gold
Diamond
Platinum
Novels
Short Stories
Stationary
Art Pieces
Sweets

Enter the item you wish to purchase from the above list: shoes

Your Desired item is in the following shop(s) with location
---------------------------------
|Floor          |Shop           |
---------------------------------
|Ground Floor   |Bata           |
---------------------------------
|Ground Floor   |Woodland       |
---------------------------------
|Ground Floor   |Adidas         |
---------------------------------
|Third Floor    |Nike           |
---------------------------------
Do you want to search more items
Enter 1 for yes else any other number: 1

Item List:

Shoes
Sandals
Slippers
Kids Wear
Male Wear
Female Wear
Bags
Watches
Silver
Gold
Diamond
Platinum
Novels
Short Stories
Stationary
Art Pieces
Sweets

Enter the item you wish to purchase from the above list: bags

Your Desired item is in the following shop(s) with location
---------------------------------
|Floor          |Shop           |
---------------------------------
|Ground Floor   |Adidas         |
---------------------------------
|Third Floor    |Nike           |
---------------------------------
Do you want to search more items
Enter 1 for yes else any other number: 1

Item List:

Shoes
Sandals
Slippers
Kids Wear
Male Wear
Female Wear
Bags
Watches
Silver
Gold
Diamond
Platinum
Novels
Short Stories
Stationary
Art Pieces
Sweets

Enter the item you wish to purchase from the above list: novels

Your Desired item is in the following shop(s) with location
---------------------------------
|Floor          |Shop           |
---------------------------------
|Second Floor   |Om Book Shop   |
---------------------------------
Do you want to search more items
Enter 1 for yes else any other number: 1

Item List:

Shoes
Sandals
Slippers
Kids Wear
Male Wear
Female Wear
Bags
Watches
Silver
Gold
Diamond
Platinum
Novels
Short Stories
Stationary
Art Pieces
Sweets

Enter the item you wish to purchase from the above list: food

Enter a valid item name from the list
Item List:

Shoes
Sandals
Slippers
Kids Wear
Male Wear
Female Wear
Bags
Watches
Silver
Gold
Diamond
Platinum
Novels
Short Stories
Stationary
Art Pieces
Sweets

Enter the item you wish to purchase from the above list: watches

Your Desired item is in the following shop(s) with location
---------------------------------
|Floor          |Shop           |
---------------------------------
|First Floor    |Casio          |
---------------------------------
Do you want to search more items 
Enter 1 for yes else any other number: 1 

Item List:

Shoes
Sandals
Slippers
Kids Wear
Male Wear
Female Wear
Bags
Watches
Silver
Gold
Diamond
Platinum
Novels
Short Stories
Stationary
Art Pieces
Sweets

Enter the item you wish to purchase from the above list: coats

Enter a valid item name from the list
Item List:

Shoes
Sandals
Slippers
Kids Wear
Male Wear
Female Wear
Bags
Watches
Silver
Gold
Diamond
Platinum
Novels
Short Stories
Stationary
Art Pieces
Sweets

Enter the item you wish to purchase from the above list: SLIPPERS

Your Desired item is in the following shop(s) with location
---------------------------------
|Floor          |Shop           |
---------------------------------
|Ground Floor   |Bata           |
---------------------------------
|Ground Floor   |Adidas         |
---------------------------------
|Third Floor    |Nike           |
---------------------------------
Do you want to search more items
Enter 1 for yes else any other number: 0
*/