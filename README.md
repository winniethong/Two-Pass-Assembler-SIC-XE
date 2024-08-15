README

- Name: Chloe Kershner, Winnie Thong
- User: cssc4063
- Class: CS530, Spring 2024
- Assignment 2
- Filename: README

File Manifest:
- Makefile, README.md, asxe.cpp, ourTestFile.sic

Compile Instruction:
- make clean
- make
- ./asxe P2sample.sic

Operating Instruction:
- listing file and symtab: ./asxe <filename>
- must include at least one file to process, and it can process multiple if more than one are provided in the command line
- We used the P2sample.sic, the example input provided in the assignment description, for filename
- We also created our own file for testing with different test cases the P2sample.sic did not test such as using BYTE and having the start address set to a non zero number
- When defining literals in source code file, use =C' ' or =X' ' unless using "BYTE". In that case only use C' ' or X' '
- Must use the same formatting and spacing as P2samle.sic and ourTestFile.sic for any input files

Design Decisions:
- To ensure readability, we were prompted to have user friendly output. This means using readable output tables such as symtab, littab, and a listing file. Each column will have a title and their respective contents which the user understand the logic.
- The lines of the source code are processed depending on the placement of the characters. So any source code file inputted must have the same spacing as P2sample.sic and ourTestFile.sic
- We unfortunately have the entire code in just one file (asxe.cpp) which is not ideal and does is not using best practices.

Extras:
- Functionality: N/A
- Algorithm: N/A

Known Deficiencies:
- Since the program cannot handle larger files, its potential is capped. Bigger files can cause it to perform slower or even crash. Not only that, but this is a very simple two pass aseembler code, meaning the input cannot be too complicated.
- Additionally, the assembler can only handle format 3 or 4 instructions, we did not have time to implement the additional functionality of format 1 and 2
- Cannot handle comments after first line

Lessons Learned:
- Although we were able to learn and understand how to do the listing file and symtabs by hand from the exam, we did not consider how this logic could be implemented in code until this assignment. We referred to the textbook pseudocode for the two passes. We were able to understand the ins and outs of creating simple symtabs and listing files. We realized that there were many little steps along the way, meaning we needed a lot of helper functions to help ease this implmentation.
