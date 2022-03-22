parser grammar TParser;

options {
	tokenVocab = TLexer;
}

// Actual grammar start.
main: statement EOF;

statement : select | insert | createClass | createProperty;

classDefinition : Identifier;

select : 'select' tuple=tupleDefinition 'from' sources+=source (',' sources+=source)? 'where' expression;

source : name=Identifier ':' type=classDefinition;

tupleDefinition: expressions+=expression (',' expressions+=expression)*;

expression: disjunction;

disjunction: left=conjunction ('||' right=disjunction)?;

conjunction: left=equality ('&&' right=conjunction)?;

equality: left=comparison (op=equalityOperator right=equality)?;

equalityOperator: '=' | '!=';

comparison: left=additiveExpression (op=comparisonOperator right=comparison)?;

comparisonOperator: '<' | '>' | '<=' | '>=';

additiveExpression: left=multiplicativeExpression (op=additiveOperator right=additiveExpression)?;

additiveOperator: '+' | '-';

multiplicativeExpression:  left=primaryExpression (op=multiplicativeOperator right=multiplicativeExpression)?;

multiplicativeOperator: '*' | '/' | '%';

primaryExpression: memberAccess;

memberAccess:  variable=Identifier '.' property=Identifier;

insert: 'insert' type=classDefinition '(' ( pairs+=pair ( ',' pairs+=pair )* )? ')';

pair: name=Identifier '=' value=Number;

createClass: 'create' name=Identifier;

createProperty: 'create' type=Identifier '.' name=Identifier;


//'class'
// 'property'

