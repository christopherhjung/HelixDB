parser grammar TParser;

options {
	tokenVocab = TLexer;
}

// Actual grammar start.
main: statement EOF;

statement : select | insert | createClass | createProperty;

classDefinition : Identifier;

select : 'select' expression=expr 'from' name=Identifier ':' type=classDefinition 'where' id=Number;

expr: variable=Identifier '.' property=Identifier;

insert: 'insert' type=classDefinition '(' ( pairs+=pair ( ',' pairs+=pair )* )? ')';

pair: name=Identifier '=' value=Number;

createClass: 'create' name=Identifier;

createProperty: 'create' type=Identifier '.' name=Identifier;


//'class'
// 'property'

