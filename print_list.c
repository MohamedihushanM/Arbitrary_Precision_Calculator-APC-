#include "head.h"

/*Display result list*/
void print_list(Dlist *res_head, char res_sign)
{

    /*check list empty or not*/
    if(res_head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    printf("Result: ");
    printf("%c", res_sign);//print sign of result

    /*print all node data*/
    while(res_head != NULL)
    {
        printf("%d", res_head->data);
        res_head = res_head->next;
    }

    printf("\n");

}