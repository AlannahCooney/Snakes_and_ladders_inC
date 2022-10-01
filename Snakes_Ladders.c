#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 /*
    C-Programming Assignment 2
    Alannah Cullinane Cooney
    SD2-A
    R00204418
*/

 /*
    Creating a singly Linked List
*/
struct node
{
    int value;
    struct node *next;
    int player1;
    int snakes;
    int ladders;
};
/*
    A function to generate the random number for the dice roll
*/ 
int random(int num)
{
    while (1)
    {
        int result;
        result=rand()%num;
        if(result!=0)
        {
            return result;
        }
    }
}

int main()
{
/*
    Using a random number generator to create the random length of the board
*/ 
    srand(time(0));
    int length;
    while (1)
    {
        int randomnumber;
        randomnumber = random(64);
        if (randomnumber >31 && randomnumber <65)
        {
            length = randomnumber;
            printf("Length: %d\n", length);
            break;
        }
    }
    /*
        Assigning the the nodes to values from the linked list.
    */ 
    struct node *headNode, *currentNode, *temp;
    for (int i=1; i<=length; i++)
    {
        currentNode = (struct node *)malloc(sizeof(struct node));
        currentNode->value = i;
        currentNode->player1=0;
        currentNode->ladders=0;
        currentNode->snakes=0;
        if (i == 1)
        {
            headNode = temp = currentNode;
            currentNode->player1=1;
        }
        else
        {
            temp->next = currentNode;
            temp = currentNode;
        }
    }
    temp->next = NULL;
    temp = headNode;
    
      
    int obstacles[24];
    /*
        Snakes : 09-07  13-08   20-15   31-26   47-45   59-51
        Ladders: 02-12  14-19   21-29   39-40   46-50   57-60   
    */
     /*
        Setting the points on the board for the snakes and ladders.   
    */
    while (temp!=NULL)
    {
        if (temp->value==2)
        {
            temp->ladders=12;
        }
        else if (temp->value==9)
        {
            temp->snakes=7;
        }
        else if (temp->value==13)
        {
            temp->snakes=8;
        }
        else if (temp->value==14)
        {
            temp->ladders=19;
        }
        else if (temp->value==20)
        {
            temp->snakes=15;
        }
        else if (temp->value==21)
        {
            temp->ladders=29;
        }
        else if (temp->value==31)
        {
            temp->snakes=26;
        }
        else if (temp->value==39)
        {
            temp->ladders=40;
        }
        else if (temp->value==46)
        {
            temp->ladders=50;
        }
        else if (temp->value==47)
        {
            temp->snakes=45;
        }
        else if (temp->value==57)
        {
            temp->ladders=60;
        }
        else if (temp->value==59)
        {
            temp->snakes=51;
        }
        temp=temp->next;
    }
    
     /*
        Connecting to the file for printing the game play report. 
        Intializing the function for the dice  
    */
    FILE *slgame = fopen("S&L.txt", "w");
    int player1 = 1;
    temp = headNode;
    while (temp->value != length)
    {
        int randomnumber, dice;
        diceRoll:
        randomnumber = random(6);
        if (randomnumber >0 && randomnumber <7)
        {
            dice = randomnumber;
            printf("Roll: %d\n", dice); 
            fprintf(slgame, "Roll: %d\n", dice);
        }
        else
        {
            goto diceRoll;
        }
        /*
            Implementing the player moves when dice is rolled
        */
        if (temp->player1==1)
        {
            temp->player1=0;
            int limit = temp->value + dice;
            if (limit>length)
            {
                dice = length - temp->value;
            }
            for (int x=0; x<dice; x++)
            {
                temp = temp->next;
            }
            /*
                if player hits a ladder than move forward i amount of spaces
            */ 
            if (temp->ladders>0)
            {
                int forward = temp->ladders - temp->value;
                printf("Player1 hit ladder: %d \n", temp->value); 
                fprintf(slgame, "Player1 hit ladder: %d \n", temp->value);
                if (temp->ladders>length)
                {
                    forward = length-temp->value;
                }
                
                for (int i=0; i<forward; i++)
                {
                    temp = temp->next;
                }
                temp->player1=1;
                player1=temp->value;
            }
            /*
                else if player hits a Snake than move backward i amount of spaces
            */
            else if (temp->snakes>0)
            {
                printf("Player1 hit snake: %d \n", temp->value); 
                fprintf(slgame, "Player1 hit snake: %d \n", temp->value);
                int snake = temp->snakes;
                temp=headNode;
                for(int x=1; x<snake; x++)
                {
                    if (temp->value==snake)
                    {
                        temp->player1=1;
                        player1=temp->value;
                    }
                    temp = temp->next;
                }
            }
            /*
                Using temp to tell where the player is on the board when the dice is rolled.
            */ 
            temp->player1=1;
            player1=temp->value;

            printf("Player1 moved: %d \n", temp->value); 
            fprintf(slgame, "Player1 moved: %d \n", temp->value);
            if (temp->next == NULL)
            {
                printf("You win!! Game Complete!\n");
                fprintf(slgame, "You win!! Game Complete!\n");
                /*
                    Closing the file and then exiting the program.
                */ 
                fclose(slgame); 	
                exit(0);
            } 
        }
        else
        {
            temp = temp->next;
        }
    }
}