/*
Name: Mohamed ihushan
Date: 18/06/2026
Description: DS_Project 1 - APC(Arbitrary precision calculator) using double linked list
Sample input:./a.out 40 "*" 10
             Validated the APC arguments successfully
             Convert string to double linked list successfully done
             =====================================================================
                        ARBITRARY PRECISION CALCULATOR (APC)                     
             =====================================================================
             1.Addition
             2.Subtraction
             3.Multiplication
             4.Division
             5.Exit
             Enter your choice: 3 

Sample output:400
              APC multiplication operation is successfully executed
              
*/

#include "head.h"

/*APC project main function*/
int main(int argc, char **argv)
{
    /*sign variable fot hold sign of num1, num2 and result sign*/
    char sign1 = 0;
    char sign2 = 0;
    char res_sign;

    /*Node declaration of DLL for operand1,operand2 and result list*/
    Dlist *res_head = NULL;
    Dlist *res_tail = NULL;
    Dlist *head1 = NULL;
    Dlist *tail1 = NULL;
    Dlist *head2 = NULL;
    Dlist *tail2 = NULL;

    int option;

    /*validate command line argument count*/
    if(argc != 4)
    {
        printf("Command line arguments must be four, please refer below\n");
        printf("Input: ./a.out <operand1> <operator> <operand2>\n");
        return 1;
    }

    /*Validation of command line arguments*/
    if(CLA_validation(argv) == SUCCESS)
    {
        printf("Validated the APC arguments successfully\n");

        /*Convert string to list function*/
        if(Convert_str_list(argv[1], argv[3], &head1, &tail1, 
                           &head2, &tail2, &sign1, &sign2) == SUCCESS)
        {
            printf("Convert string to double linked list successfully done\n");
        }
        else
        {
            printf("Failed to convert string to double linked list\n");
            return 1;
        }
    }
    else
    {
        printf("Failed to validate APC arguments\n");
        return 1;
    }

    /*choosing desired operation by entering option*/
    do
    {
        printf("=====================================================================\n");
        printf("            ARBITRARY PRECISION CALCULATOR (APC)                     \n");
        printf("=====================================================================\n");
        printf("1.Addition\n");
        printf("2.Subtraction\n");
        printf("3.Multiplication\n");
        printf("4.Division\n");
        printf("5.Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &option);

        /*Based on option ,Arithmetic operation will execute*/
        switch(option)
        {
            /*Addition operation*/
            case 1:
               if(APC_Addition(head1, tail1, head2, tail2, &res_head, 
                              &res_tail, sign1, sign2, &res_sign) == SUCCESS)
                {
                    /*After execution display result and free result list*/
                   print_list(res_head, res_sign);
                   free_list(&res_head, &res_tail);
                   res_sign = 0;
                   printf("APC Addition operation is successfully executed\n");
                   break;
                }
                else
                {
                    printf("Failed to execute APC addition operation\n");
                    return 1;
                }
            
            /*Subtraction operation*/
            case 2:
                if(APC_Subtraction(head1, tail1, head2, tail2, &res_head, 
                                  &res_tail, sign1, sign2, &res_sign) == SUCCESS)
                {
                    /*After execution display result and free result list*/
                    print_list(res_head, res_sign);
                    free_list(&res_head, &res_tail);
                    res_sign = 0;
                    printf("APC subtraction operation is successfully executed\n");
                    break;
                }
                else
                {
                    printf("failed to execute APC subtraction operation\n");
                    return 1;
                }

            /*Multiplication operation*/
            case 3:
                if(APC_Multiplication(head1, tail1, head2, tail2, &res_head, 
                                     &res_tail, sign1, sign2, &res_sign) == SUCCESS)
                {
                    /*After execution display result and free result list*/
                    print_list(res_head, res_sign);
                    free_list(&res_head, &res_tail);
                    res_sign = 0;
                    printf("APC multiplication operation is successfully executed\n");
                    break;
                }
                else
                {
                    printf("Failed to execute APC multiplication operation\n");
                    return 1;
                }
            
            /*Division operation*/
            case 4:
                if(APC_Division(head1, tail1, head2, tail2, &res_head, 
                               &res_tail, sign1, sign2, &res_sign) == SUCCESS)
                {
                    /*After execution display result and free result list*/
                    print_list(res_head, res_sign);
                    free_list(&res_head, &res_tail);
                    res_sign = 0;
                    printf("APC division operation is successfully executed\n");
                    break;
                }
                else
                {
                    printf("Failed to execute APC division operation\n");
                }
            /*Exit option*/
            default:
                printf("Invalid option\n");
        }

    } while(option != 5);

    return 0;
}