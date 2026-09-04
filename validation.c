#include "head.h"

int CLA_validation(char **argv)
{
    /* Validate first operand */
    if(validate_number(argv[1]) == FAILURE)
    {
        printf("Invalid first operand\n");
        return FAILURE;
    }

    /* Validate operator */
    if(argv[2][0] != '+' &&
       argv[2][0] != '-' &&
       argv[2][0] != '*' &&
       argv[2][0] != '/')
    {
        printf("Invalid operator\n");
        return FAILURE;
    }

    /* Validate second operand */
    if(validate_number(argv[3]) == FAILURE)
    {
        printf("Invalid second operand\n");
        return FAILURE;
    }

    return SUCCESS;
}

int validate_number(char *str)
{
    int i = 0;

    /* Check optional sign */
    if(str[0] == '+' || str[0] == '-')
    {
        /* Sign alone is invalid */
        if(str[1] == '\0')
            return FAILURE;

        i = 1;
    }

    /* Remaining characters must be digits */
    for(; str[i] != '\0'; i++)
    {
        if(!isdigit(str[i]))
            return FAILURE;
    }

    return SUCCESS;
}