README

- Names: Winnie Thong, Chloe Kershner

File Manifest:
- Makefile, README.md, asxe.cpp, ourTestFile.sic

Compile Instruction:
- make clean
- make
- ./asxe P2sample.sic

Operating Instruction:
- listing file and symtab: ./asxe <filename>
- must include at least one file to process, and it can process multiple if more than one is provided in the command line
- We used the P2sample.sic, the example input provided in the assignment description, for filename
- We also created our file for testing with different test cases the P2sample.sic did not test such as using BYTE and having the start address set to a nonzero number
- When defining literals in source code file, use =C' ' or =X' ' unless using "BYTE". In that case, only use C' ' or X' '
- Must use the same formatting and spacing as P2samle.sic and ourTestFile.sic for any input files

Design Decisions:
- To ensure readability, we were prompted to have user-friendly output. This means using readable output tables such as symtab, littab, and a listing file. Each column will have a title and their respective contents which the user understands the logic.
- The lines of the source code are processed depending on the placement of the characters. So any source code file inputted must have the same spacing as P2sample.sic and ourTestFile.sic
- We have the entire code in just one file (asxe.cpp) which is not ideal and does not use best practices.



Known Deficiencies:
- Since the program cannot handle larger files, its potential is capped. Bigger files can cause it to perform slower or even crash. Not only that, but this is a very simple two-pass assembler code, meaning the input cannot be too complicated.
- Additionally, the assembler can only handle format 3 or 4 instructions, we did not have time to implement the additional functionality of format 1 and 2
- Cannot handle comments after the first line

Lessons Learned:
- Although we learned and understood how to do the listing file and symtabs by hand from the exam, we did not consider how this logic could be implemented in code until this assignment. We referred to the textbook pseudocode for the two passes. We were able to understand the ins and outs of creating simple symtabs and listing files. We realized that there were many little steps along the way, meaning we needed a lot of helper functions to help ease this implementation.
