# Programming Perls Notes

## Chapter 1 : Cracking the oyster

## Chapter 2 : Aha! algorithms

## Chapter 3 : Data structures programs
- Proper view of data does indeed structure code - Program can be made smaller by restructuring their internal data
- small programs were more efficient in run time and space than the big programs
- _identify conceptul blocks against using data structures_
- separating data from control will pay handsomely
- Error messages : Dirty systems have hundreds of error messages scattered throughout the code, mixed with other output statements; clean systems have them accesed through a single function.
- _don't write a big program when a little one will do_
- The more general problems may be easier to solve
- Representation is essense of programming

## Chapter 4 : Writing correct programs
- Majorty of task of writing programming is covered by Problem definition, Algorithm design and data structure seleciton
### Principles
- __Assertions:__ The relationshio among input, program variables, and outpus describes the _state_ of program. Assertion allows programmers to enunciate those relationships precisely.
- __sequential control structures:__ do this and do that - in between it can change prrogram state and hence should have assertion
- __selection control structures:__ These structures include conditional statements {if, switch}. During execution we select one of the choice and this choice allows us to make an relevant assertion.
- __iteration control structure:__ Here we extablish invariant before getting in to loop, followed by preserving the truth (hence maintaining assertion) on each iteration. Second items to consider is if this loop terminates. Most likely certain condition where assertion is not true ?
- __Function:__ where we state two assertion one "precodition" whish should be true before entering to function and "postcondition" which should help exiting it with desired results.
- __Debuging__: When you debug and fix bot h code and "false assertion(wrong logic ?)" , understand the code all the time and resist foul urge to "just change it untill it works"