grammar TuringMachine;

program : ALPHABET (NEWLINE+ (instruction | COMMENT))* EOF;

lsymbol : IDENTIFIER;

instruction : state_def (instr_body NEWLINE)+;

instr_body : (match_)? actions state_;

match_ : IDENTIFIER;

actions : ACTIONS | IDENTIFIER;

state_def : IDENTIFIER (OPAREN symargs CPAREN)?;

symargs : IDENTIFIER (COMMA IDENTIFIER)*;

// That same dumbassery also forces us to change this name, as "state" is an
// internal parser variable, so it cannot deal with creating the proper hook
// (though it doesn't even care to warn us about it when generating the python
// code).
state_ : state_name2 (OPAREN args CPAREN)?;

state_name2 : state_name;
state_name : IDENTIFIER;

args : arg (COMMA arg)*;

arg : state_ | lsymbol;


//
// Lexer rules:
//

COMMA                     : ',';
OPAREN                    : '(';
CPAREN                    : ')';

fragment ANY              : '*';
fragment EMPTYCELL        : '#';
fragment NSSYMBOL         : [;:_!@%^&'] | ANY | EMPTYCELL;
fragment ALPHABET_CHAR    : [a-zA-Z0-9] | NSSYMBOL;
ALPHABET                  : ALPHABET_CHAR+ '.';

IDENTIFIER                : ALPHABET_CHAR+;

fragment ACTION           : [LRHE] | 'P' ALPHABET_CHAR;
fragment WS               : (' ' | '\t');
ACTIONS                   : ACTION (COMMA ACTION)*;

COMMENT                   : '//' ~[\r\n]*;

NEWLINE                   : ('\r'? '\n' | '\r') ;
WHITESPACE                : ' ' -> skip ;
