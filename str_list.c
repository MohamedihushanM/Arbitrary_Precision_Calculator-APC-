#include "head.h"

/*Convert string to node*/
int Convert_str_list(char *num1, char *num2, Dlist **head1, Dlist **tail1, 
                    Dlist **head2, Dlist **tail2, char *sign1, char *sign2)
{
    int i;

    /* Create list for first number */
    for(i = 0; num1[i] != '\0'; i++)
    {
        /*check first index contain any sign*/
        if(num1[i] == '+' || num1[i] == '-')
        {
            *sign1 = num1[i];
            continue;
        }

        /*insert data into list one by one*/
        if(insert_last(head1, tail1, num1[i] - '0') == FAILURE)
            return FAILURE;
    }

    /* Create list for second number */
    for(i = 0; num2[i] != '\0'; i++)
    {
        /*Check first index contain any sign*/
        if(num2[i] == '+' || num2[i] == '-')
        {
            *sign2 = num2[i];
            continue;
        }

        /*Insert data into list one by one*/
        if(insert_last(head2, tail2, num2[i] - '0') == FAILURE)
            return FAILURE;
    }

    return SUCCESS;

}

/*Insert last function*/
int insert_last(Dlist **head, Dlist **tail, int data)
{
    /*new list memory allocation*/
    Dlist *new = malloc(sizeof(Dlist));

    /*check list empty or not*/
    if(new == NULL)
        return FAILURE;

    /*Assign value to new list*/
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    
    //for empty list
    if(*head == NULL)
    {
        *head = *tail = new;
    }

    /*for non empty list*/
    else
    {
        /*update link*/
        new->prev = *tail;
        (*tail)->next = new;
        *tail = new;
    }

    return SUCCESS;
}