# Study Questions

1. Suppose you want to add unary operations (i.e.m ones requiring only one operand) to the calculator. For example, we might add "M" to indicate unary minus (i.e., change the sign of the old value) and "A" to indicate absolute value. What changes would need to be made to the program?
	- To make these changes in the program, we'd have to, in addition to checking for '+', '-', and '*', check for each unary operator. Then we'd have to not stop to accept user input, as we won't need a second value for the operation to work. So we do the operation, and then we can just print it back out and be done.

2. Suppose that words rather than single character symbols are to be used for the operators (e.g., the user types "times" instead of "*"). Where in the program would the necessary changes occur?
	- The changes would occur wherever we're checking the user's input. Instead of simply doing a logical equate on two chars, we'll have to loop through strings and make sure each char at each index is the same as our keyword.

3. Suppose that the calculator is to be converted to use C++ double values rather than integers. Where would changes need to be made?
	- We'd likely have to add support for decimals if we used C++ double values. And we'd have to parse the user's input to try and find a '.', and when one is found then note that all the rest of the numbers are a decimal.
