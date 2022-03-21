lexer grammar TLexer;

DelimitedComment
    : '/*' ( DelimitedComment | . )*? '*/'
      -> channel(HIDDEN)
    ;

LineComment
    : '//' ~[\u000A\u000D]*
      -> channel(HIDDEN)
    ;

WS
    : [\u0020\u0009\u000C]
      -> skip
    ;

NL: ('\u000A' | '\u000D' '\u000A') -> skip;

Select: 'select';
From: 'from';
Insert: 'insert';
Create: 'create';
Class: 'class';
Property: 'property';
Where: 'where';
OpenBracket: '[';
CloseBracket: ']';
OpenParenthesis: '(';
CloseParenthesis: ')';
OpenBrace : '{';
CloseBrace : '}';
Comma: ',';
Dot: '.';
Colon: ':';
Equals: '=';
Identifier: [a-zA-Z][a-zA-Z_]*;
Number:[0-9]+;
