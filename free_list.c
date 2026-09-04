#include "head.h"

/*Delete result list*/
void free_list(Dlist **head, Dlist **tail)
{
    Dlist *temp;

    /*Delete all node*/
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    *tail = NULL;
}