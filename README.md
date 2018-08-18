# LL-1-ParserGenerator
Predictive Parsing 
Module -1 : Parse Table Construction:
Inputs : grammar.txt / grammar2.txt , first_follow.txt/ first_follow2.txt

The module creates a ParseTable with nonterminals along rows and terminals along columns in the following way:
i.   for each a in first(A) add the corresponding production in the entry,  ParseTable[A,a]
ii.  if first(A) has epsilon, for each b in follow(A) add the production A→epsilon at   
     ParseTable[A,b]

Module -2:
1. Lexical Analyser
 the lex.l file , adds tokens to any given input and stores it in input.txt
2.  Validation
this module reads from input.txt (appended with “$”) . Maintaing a stack and using the parse Table, this module validates the input and prints the result as “Accepted “ or “Rejected”

To run:
Give the inputString that you wish to parse, to lex.l and then run parser.c
