# ProjectExe
Expression Evaluator using C++


# To Compile Code

```g++ Executor.cpp parser.cpp validator.cpp test_cases.cpp -o Executor```


# Files Info

`Validator` - It will validate the expression string by following cases
   - Remove the ' ' empty spaces
   - Matching paranthesis
   - Invalid characters validation
   - Invalid operator usages

`Parser` - convert the infix expression into postfix expression
   - Ex. `1+(3-(2-0))` --> `1 3 2 0 - - +`
   - It will create linked nodes for each operands and operators.

`myNode.h` - Node structure for this evalution

`Executor` - Traverse into the linked list and evaluate the expression nodes.

`test_cases` - Holds test expressions with expected values.
