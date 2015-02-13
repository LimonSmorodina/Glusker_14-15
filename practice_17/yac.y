%{
#include <stdio.h>
#include <string.h>

void yyerror(const char *str) {
    fprintf(stderr, "error: %s\n", str);
}

int yywrap () {
    return 1;
}

main () {
    yyparse();
}

%}

%token WHILE BOOL_VAL _BEGIN _END VARIBLE INT_CONST INT_OPERATION ASSIGNMENT LOG_OPERATION SEMICOLON S_SCOPE E_SCOPE NOT DO

%%
command: is_while

bool_state: BOOL_VAL
          | VARIBLE
          ;

bool_expr: NOT bool_expr
         | S_SCOPE bool_expr E_SCOPE
         | bool_expr LOG_OPERATION bool_expr 
         | bool_state

int_expr: VARIBLE
        | INT_CONST
        | S_SCOPE int_expr E_SCOPE
        | int_expr INT_OPERATION int_expr

int_ass: VARIBLE ASSIGNMENT int_expr SEMICOLON

loop_body: _BEGIN int_ass _END
         | int_ass

is_while: WHILE bool_expr DO loop_body
        {
            printf ("\tyes\n");
        }

