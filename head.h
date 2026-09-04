#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*Structure of Double linked list*/
typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
} Dlist;

/*Macros*/
#define SUCCESS 1
#define FAILURE 0

/* Command Line Argument Validation */
int CLA_validation(char **argv);

int validate_number(char *str);

/* Convert strings to doubly linked lists */
int Convert_str_list(char *num1, char *num2, Dlist **head1, Dlist **tail1, 
                    Dlist **head2, Dlist **tail2, char *sign1, char *sign2);

/*Insert last to double linked list*/
int insert_last(Dlist **head, Dlist **tail, int data);

/*APC Addition operation using DLL*/
int APC_Addition(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, 
                Dlist **res_head, Dlist **res_tail, char sign1, char sign2, 
                char *res_sign);

/*Insert first to double linked list*/
int insert_first(Dlist **head, Dlist **tail, int data);

/*Compare two list*/
int compare_lists(Dlist *head1, Dlist *head2);

/*APC Subtraction operation using DLL*/
int APC_Subtraction(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, 
                    Dlist **res_head, Dlist **res_tail, char sign1, char sign2, 
                    char *res_sign);

/*APC Multiplication operation using DLL*/
int APC_Multiplication(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, 
                      Dlist **res_head, Dlist **res_tail, char sign1, char sign2, 
                      char *res_sign);

/*APC Division operation using DLL*/
int APC_Division(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, 
                Dlist **res_head, Dlist **res_tail, char sign1, char sign2, 
                char *res_sign);


/*Display the result list*/
void print_list(Dlist *res_head, char res_sign);

/*Delete result list*/
void free_list(Dlist **head, Dlist **tail);

#endif