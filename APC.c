#include "head.h"

/*APC Addition operation using DLL*/
int APC_Addition(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, 
                Dlist **res_head, Dlist **res_tail, char sign1, char sign2, 
                char *res_sign)
{
    /*Initialise result list as empty*/
    *res_head = NULL;
    *res_tail = NULL;

    /*Declare sum,digit and initialise carry as zero*/
    int sum;
    int carry = 0;
    int digit;

    /*Sign of two operand is not same*/
    if(sign1 != sign2)
    {
        /*Call APC subtraction operation*/
        APC_Subtraction(head1, tail1, head2, tail2, res_head, 
                        res_tail, sign1, sign2,res_sign);

        /*Compare two list*/
        int cmp = compare_lists(head1, head2);

        /*if list1 > list2*/
        if(cmp > 0)
            *res_sign = sign1;

        /*if list2 > list1*/
        else if(cmp < 0)
            *res_sign = sign2;

        return SUCCESS;
    }

    /*if sign of two operand is same*/
    if(((sign1 == '+' && sign2 == '+') || (sign1 == 0 && sign2 == 0)) || (sign1 == '-' && sign2 == '-'))
    {
        /*Assign sign1 as res_sign*/
        *res_sign = sign1;

        /*Addition of two list*/
        while(tail1 || tail2 || carry)
        {
            //assign sum as carry
            sum = carry;

            /*if tail is not null,add tail1 data with sum and store in sum*/
            if(tail1)
            {
                sum += tail1->data;
                tail1 = tail1->prev;//update link for traversel
            }

            /*if tail2 is not null, add tail2 data with sum and store in sum*/
            if(tail2)
            {
                sum += tail2->data;
                tail2 = tail2->prev;//update link for traversel
            }

            digit = sum % 10;//Extract current result digit 
            carry = sum / 10;//calculate carry for next addition

            /*Insert first the digit in result list*/
            insert_first(res_head, res_tail, digit);
       }
    return SUCCESS;
    }

    return FAILURE;
}

/*APC Subtraction operation using DLL*/
int APC_Subtraction(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, 
                    Dlist **res_head, Dlist **res_tail, char sign1, char sign2, 
                    char *res_sign)
{
    /*initialise borrow as 0 and declare diff,cmp as integer*/
    int borrow = 0;
    int diff;
    int cmp;

    /*compare two list for Subtraction*/
    cmp = compare_lists(head1, head2);

    /* Equal numbers */
    if(cmp == 0)
    {
        /*insert 0 into the result list*/
        insert_first(res_head, res_tail, 0);
        return SUCCESS;
    }

    /* Ensure larger magnitude is first */
    if(cmp < 0)
    {
        /*declare temp as Dlist*/
        Dlist *temp;

        /*swap the list1 and list2 using temp*/
        temp = head1;
        head1 = head2;
        head2 = temp;

        temp = tail1;
        tail1 = tail2;
        tail2 = temp;

        /*assign result sign as negative*/
        *res_sign = '-';
    }

    /*until tail1 became null run loop*/
    while(tail1)
    {
        /*subtract borrow from taildata store it in digit1*/
        int digit1 = tail1->data - borrow;
        //digit2 as 0
        int digit2 = 0;

        /*if tail2 is not null*/
        if(tail2)
        {
            /*put tail2 data in digit2*/
            digit2 = tail2->data;
            /*update link for traversal*/
            tail2 = tail2->prev;
        }

        /*if digital less than digital2*/
        if(digit1 < digit2)
        {
            /*add digit1 with 10 */
            digit1 += 10;
            borrow = 1;//update borrow with 1
        }
        else
        {
            borrow = 0;
        }

        /*subtract digit2 from digit1 and store it in diff*/
        diff = digit1 - digit2;

        /*insert first the diff value in result list*/
        insert_first(res_head, res_tail, diff);

        /*update link for tail1*/
        tail1 = tail1->prev;
    }

    return SUCCESS;
}

/*APC Multiplication operation using DLL*/
int APC_Multiplication(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, 
                       Dlist **res_head, Dlist **res_tail, char sign1, char sign2, 
                       char *res_sign)
{
    /*update result list as NULL*/
    *res_head = NULL;
    *res_tail = NULL;

    /*for different sign*/
    if(sign1 != sign2)
        *res_sign = '-';//assign result sign as negative

    /*insert zero into result list*/
    insert_first(res_head, res_tail, 0);

    /*initialize Dlist ptr2 as tail2*/
    Dlist *ptr2 = tail2;
    /*initialize zeros as 0*/
    int zeros = 0;

    /*until ptr2 becames null, loop will run*/
    while(ptr2)
    {
        /*initialize Dlist temp list as null*/
        Dlist *temp_head = NULL;
        Dlist *temp_tail = NULL;

        /*initialize carry as 0*/
        int carry = 0;

        /*initialize Dlist ptr21 as tail1*/
        Dlist *ptr1 = tail1;

        /*until ptr1 becames null, loop will run*/
        while(ptr1)
        {
            /*product list1 data with list2 data*/
            int prod = ptr1->data * ptr2->data + carry;

            carry = prod / 10;//calculate carry from prod
            prod %= 10;//extract single digit value from prod

            /*insert first the prod in temp list*/
            insert_first(&temp_head, &temp_tail, prod);

            /*update ptr1 for traverse list*/
            ptr1 = ptr1->prev;
        }

        /*At last if carry present put it into list*/
        if(carry)
        {
            insert_first(&temp_head, &temp_tail, carry);
        }

        /* append zeros ,if zeros > 0*/
        for(int i = 0; i < zeros; i++)
        {
            /*create new list*/
            Dlist *new = malloc(sizeof(Dlist));

            /*insert last 0*/
            new->data = 0;
            new->next = NULL;
            new->prev = temp_tail;

            temp_tail->next = new;
            temp_tail = new;
        }

        /*update new list as null*/
        Dlist *new_head = NULL;
        Dlist *new_tail = NULL;
        char sign;

        /*call APC addition for add result list and temp list and store result in new list*/
        APC_Addition(*res_head, *res_tail, temp_head, temp_tail,
                     &new_head, &new_tail,'+', '+', &sign);

        /* free old result */
        Dlist *tmp = *res_head;

        while(tmp)
        {
            Dlist *next = tmp->next;
            free(tmp);
            tmp = next;
        }

        /*store new list into result list*/
        *res_head = new_head;
        *res_tail = new_tail;

        /* free temp list */
        tmp = temp_head;

        while(tmp)
        {
            Dlist *next = tmp->next;
            free(tmp);
            tmp = next;
        }

        /*increament zero*/
        zeros++;
        /*update ptr2 for traverse*/
        ptr2 = ptr2->prev;
    }

    /* remove leading zeros */
    while(*res_head &&
          (*res_head)->data == 0 &&
          *res_head != *res_tail)
    {
        Dlist *tmp = *res_head;

        *res_head = (*res_head)->next;
        (*res_head)->prev = NULL;

        free(tmp);
    }

    return SUCCESS;

}

/*APC Division operation using DLL*/
int APC_Division(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2,
                 Dlist **res_head, Dlist **res_tail, char sign1,char sign2, 
                 char *res_sign)

{
    /*update result list as null*/
    *res_head = NULL;
    *res_tail = NULL;

    /*for different sign*/
    if(sign1 != sign2)
        *res_sign = '-';

    /* divide by zero */
    if(head2 && head2 == tail2 && head2->data == 0)
        return FAILURE;

    /*initialize current list as empty*/
    Dlist *curr_head = NULL;
    Dlist *curr_tail = NULL;

    /*asiign list1 to ptr list*/
    Dlist *ptr = head1;

    /*until null,loop runs*/
    while(ptr)
    {
        /*insert last ptr first  data into current list*/
        insert_last(&curr_head,&curr_tail,ptr->data);

        /*delete leading zero node from current list*/
        while(curr_head &&
              curr_head->data == 0 &&
              curr_head != curr_tail)
        {
            Dlist *tmp = curr_head;
            curr_head = curr_head->next;
            curr_head->prev = NULL;
            free(tmp);
        }

        int q_digit = 0;

        /*repeated until curent list data > or = to list2 data */
        while(compare_lists(curr_head,head2) >= 0)
        {
            /*for store subtract result*/
            Dlist *new_head = NULL;
            Dlist *new_tail = NULL;
            char sign;

            /*subtract list2 data from current list data*/
            APC_Subtraction(curr_head, curr_tail, head2,tail2, 
                            &new_head, &new_tail,'+', '+', &sign);

            /*delete current list*/
            free_list(&curr_head,&curr_tail);

            /*update current list with subtract result list*/
            curr_head = new_head;
            curr_tail = new_tail;

            /*increament q_digit for each iteration*/
            q_digit++;
        }

        /*insert q_digit value into result list*/
        insert_last(res_head,res_tail,q_digit);

        /*update ptr for traverse*/
        ptr = ptr->next;
    }

    /*delete leading zero nodes in result list*/
    while(*res_head &&
          (*res_head)->data == 0 &&
          *res_head != *res_tail)
    {
        Dlist *tmp = *res_head;

        *res_head = (*res_head)->next;
        (*res_head)->prev = NULL;

        free(tmp);
    }

    /*if result list is empty, insert 0 into result list*/
    if(*res_head == NULL)
        insert_first(res_head,res_tail,0);

    /*Delete current list*/
    free_list(&curr_head,&curr_tail);

    return SUCCESS;

}

/*compare two list data*/
int compare_lists(Dlist *head1, Dlist *head2)
{
    int len1 = 0, len2 = 0;

    /*for trsverse list create temp*/
    Dlist *temp1 = head1;
    Dlist *temp2 = head2;

    /*calculate length of list1*/
    while(temp1)
    {
        len1++;
        temp1 = temp1->next;
    }

    /*calculate length of list2*/
    while(temp2)
    {
        len2++;
        temp2 = temp2->next;
    }

    /*if list1 > list2*/
    if(len1 > len2)
        return 1;

    /*if list 1 < list 2*/
    if(len1 < len2)
        return -1;

    /*if both are equal*/
    while(head1 && head2)
    {
        /*if list1 data > list2 data*/
        if(head1->data > head2->data)
            return 1;

        /*if list1 data < list2 data*/
        if(head1->data < head2->data)
            return -1;

        /*update link for traverse */
        head1 = head1->next;
        head2 = head2->next;
    }

    return 0;
}

/*insert first in DLL*/
int insert_first(Dlist **head, Dlist **tail, int data)
{
    /*create new list*/
    Dlist *new = malloc(sizeof(Dlist));

    /*validate*/
    if(new == NULL)
        return FAILURE;

    /*update data and link*/
    new->data = data;
    new->prev = NULL;
    new->next = *head;

    /*if empty list, insert directly*/
    if(*head == NULL)
    {
        *head = *tail = new;
    }
    /*if non empty, insert first*/
    else
    {
        /*establish connection*/
        (*head)->prev = new;
        *head = new;
    }

    return SUCCESS;
}