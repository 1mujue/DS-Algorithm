#include <stdio.h>

// this program is used to convert the input text into a 
// C program that can print the input text.
// Generally speaking, you need to handle these situations:
// '\\' '\'' '\"' '%' and '\n'.
int main()
{
    char ch;
    printf("#include <stdio.h>\n\n"
           "int main()\n"
           "{\n"
           "\tprintf(\"");

    while((ch = getchar()) != EOF)
    {
        if(ch == '\\' || ch == '\'' || ch == '\"')
        {
            putchar('\\');
            putchar(ch);
        }
        else if(ch == '%')
        {
            printf("%%%%");
        }
        else if(ch == '\n')
        {
            printf("\\n\"\n\t\t\"");
        }
        else
        {
            putchar(ch);
        }
    }

    printf("\");\n"
           "\treturn 0;\n"
           "}\n");
    return 0;
}
