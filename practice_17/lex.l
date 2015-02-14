%{
#include <stdio.h>
#include "y.tab.h"
%}

%%
(?i:while)                   return WHILE;
(?i:do)                      return DO;
(?i:true|false)              return BOOL_VAL;
(?i:begin)                   return _BEGIN;
(?i:end;)                    return _END;
(?i:not)                     return NOT;
(?i:=|and|or)                return LOG_OPERATION;
(?i:[a-zA-Z_][a-zA-Z_0-9]*)  return VARIBLE;
[0-9]+                       return INT_CONST;
[\*\+\-\/]                   return INT_OPERATION;
:=                           return ASSIGNMENT;
;                            return SEMICOLON;
\(                           return S_SCOPE;
\)                           return E_SCOPE;
\n                      /*igonre*/
[ \t]                   /*ignore*/
%%
