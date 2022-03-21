parser grammar TParser;

options {
	tokenVocab = TLexer;
}

// Actual grammar start.
main: statement EOF;

statement : select | insert | createClass | createProperty;

classDefinition : Identifier;

select : 'select' name=Identifier ':' type=classDefinition 'from' source=classDefinition;

insert: 'insert' type=classDefinition '(' ( pairs+=pair ( ',' pairs+=pair )* )? ')';

createClass: 'create' name=Identifier;

createProperty: 'create' type=Identifier '.' name=Identifier;
//'class'
// 'property'
pair: name=Identifier '=' value=Number;

