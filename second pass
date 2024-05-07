#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <map>
#include <sstream>

//define global variables

int startAddress,locctr = 0,length, baseReg = 0;
char line[70],label[9],opcode[8],operand[18],programName[9], LC[8];
FILE *file, *symTab;

// struct for use in OPTAB vector
struct instructionInfo {
    std::string code;
    int format;
};

// struct for use in SymbolTable vector
struct SYMTAB{
    char symbol[10];
    int addr;
    int base;
};

// struct for use in LiteralTable vector
struct LITTAB{
    char literal[10];
    int address;
    int length = 0;
};

// define vectors for opTab, SymbolTable, and LiteralTable
typedef std::map<std::string, instructionInfo> OPTAB;
std::vector<SYMTAB> SymbolTable;
std::vector<LITTAB> LiteralTable;
OPTAB opTab;

// method to generate the opcode table
OPTAB generateOPTAB() {
    OPTAB opcodeTable;
    // opcode table contains valid opcodes, as well as their opcode number
    // formatted by format 3 or 4 depending on the presense of the '+' char for ease of processing during passes
    opcodeTable["ADD"] = {"18", 3};
    opcodeTable["+ADD"] = {"18", 4};
    opcodeTable["ADDF"] = {"58", 3};
    opcodeTable["+ADDF"] = {"58", 4};
    opcodeTable["ADDR"] = {"90", 2};
    opcodeTable["AND"] = {"40", 3};
    opcodeTable["+AND"] = {"40", 4};
    opcodeTable["CLEAR"] = {"B4", 2};
    opcodeTable["COMP"] = {"28", 3};
    opcodeTable["+COMP"] = {"28", 4};
    opcodeTable["COMPR"] = {"A0", 2};
    opcodeTable["DIV"] = {"24", 3};
    opcodeTable["+DIV"] = {"24", 4};
    opcodeTable["DIVR"] = {"9C", 2};
    opcodeTable["FIX"] = {"C4", 1};
    opcodeTable["FLOAT"] = {"C0", 1};
    opcodeTable["HIO"] = {"F4", 1};
    opcodeTable["J"] = {"3C", 3};
    opcodeTable["+J"] = {"3C", 4};
    opcodeTable["JEQ"] = {"30", 3};
    opcodeTable["+JEQ"] = {"30", 4};
    opcodeTable["JGT"] = {"34", 3};
    opcodeTable["+JGT"] = {"34", 4};
    opcodeTable["JLT"] = {"38", 3};
    opcodeTable["+JLT"] = {"38", 4};
    opcodeTable["JSUB"] = {"48", 3};
    opcodeTable["+JSUB"] = {"48", 4};
    opcodeTable["LDA"] = {"00", 3};
    opcodeTable["+LDA"] = {"00", 4};
    opcodeTable["LDB"] = {"68", 3};
    opcodeTable["+LDB"] = {"68", 4};
    opcodeTable["LDCH"] = {"50", 3};
    opcodeTable["+LDCH"] = {"50", 4};
    opcodeTable["LDF"] = {"70", 3};
    opcodeTable["+LDF"] = {"70", 4};
    opcodeTable["LDL"] = {"08", 3};
    opcodeTable["+LDL"] = {"08", 4};
    opcodeTable["LDS"] = {"6C", 3};
    opcodeTable["+LDS"] = {"6C", 4};
    opcodeTable["LDT"] = {"74", 3};
    opcodeTable["+LDT"] = {"74", 4};
    opcodeTable["LDX"] = {"04", 3};
    opcodeTable["+LDX"] = {"04", 4};
    opcodeTable["LPS"] = {"D0", 3};
    opcodeTable["+LPS"] = {"D0", 4};
    opcodeTable["MUL"] = {"20", 3};
    opcodeTable["+MUL"] = {"20", 4};
    opcodeTable["MULF"] = {"60", 3};
    opcodeTable["+MULF"] = {"60", 4};
    opcodeTable["MULR"] = {"98", 2};
    opcodeTable["NORM"] = {"C8", 1};
    opcodeTable["OR"] = {"44", 3};
    opcodeTable["+OR"] = {"44", 4};
    opcodeTable["RD"] = {"D8", 3};
    opcodeTable["+RD"] = {"D8", 4};
    opcodeTable["RMO"] = {"AC", 2};
    opcodeTable["RSUB"] = {"4C", 3};
    opcodeTable["+RSUB"] = {"4C", 4};
    opcodeTable["SHIFTL"] = {"A4", 2};
    opcodeTable["SHIFTR"] = {"A8", 2};
    opcodeTable["SIO"] = {"F0", 1};
    opcodeTable["SSK"] = {"EC", 3};
    opcodeTable["+SSK"] = {"EC", 4};
    opcodeTable["STA"] = {"0C", 3};
    opcodeTable["+STA"] = {"0C", 4};
    opcodeTable["STB"] = {"78", 3};
    opcodeTable["+STB"] = {"78", 4};
    opcodeTable["STCH"] = {"54", 3};
    opcodeTable["+STCH"] = {"54", 4};
    opcodeTable["STF"] = {"80", 3};
    opcodeTable["+STF"] = {"80", 4};
    opcodeTable["STI"] = {"D4", 3};
    opcodeTable["+STI"] = {"D4", 4};
    opcodeTable["STL"] = {"14", 3};
    opcodeTable["+STL"] = {"14", 4};
    opcodeTable["STS"] = {"7C", 3};
    opcodeTable["+STS"] = {"7C", 4};
    opcodeTable["STSW"] = {"E8", 3};
    opcodeTable["+STSW"] = {"E8", 4};
    opcodeTable["STT"] = {"84", 3};
    opcodeTable["+STT"] = {"84", 4};
    opcodeTable["STX"] = {"10", 3};
    opcodeTable["+STX"] = {"10", 4};
    opcodeTable["SUB"] = {"1C", 3};
    opcodeTable["+SUB"] = {"1C", 4};
    opcodeTable["SUBF"] = {"5C", 3};
    opcodeTable["+SUBF"] = {"5C", 4};
    opcodeTable["SUBR"] = {"94", 2};
    opcodeTable["SVC"] = {"B0", 2};
    opcodeTable["TD"] = {"E0", 3};
    opcodeTable["+TD"] = {"E0", 4};
    opcodeTable["TIO"] = {"F8", 1};
    opcodeTable["TIX"] = {"2C", 3};
    opcodeTable["+TIX"] = {"2C", 4};
    opcodeTable["TIXR"] = {"B8", 2};
    opcodeTable["WD"] = {"DC", 3};
    opcodeTable["+WD"] = {"DC", 4};

    return opcodeTable;
}

// // function to calculate byte size for "BYTE" opcode
int calcByteSize(const std::string& op) {
    if (op.empty()) {
        return 0;
    }
    if (op[1] == 'C' || op[1] == 'c') {
        return op.length() - 3;
    } else {
        return (op.length() - 3) / 2;
    }
}

// function to update the location counter based on the opcode
void calcLocationCounter(){

    int found=0;
    if (opTab.find(opcode) != opTab.end()) { // if opcode is found
        locctr += opTab[opcode].format; // update location counter by format number (which is equivalent to the number of bytes)
        found = 1; // mark as found
    }
    if(!found){ // if not found
        if(!strcmp(opcode,"WORD")) locctr+=3; // check if it is "WORD", and add 3
        else if (!strcmp(opcode,"RESW"))locctr+=(3*atoi(operand)); // else, check if it is "RESW" and update by 3 times the number in the operand
        else if (!strcmp(opcode,"RESB"))locctr+=atoi(operand); // // else, check if it is "RESB" and update by the operand
        else if (!strcmp(opcode, "BYTE")) { // // if its "BYTE"
            length = calcByteSize(operand); // calculate the byte size and add to location counter
            locctr += length;
        }
    }
}

// function to read in values for label, opcode, and operand of the source file
void processLine() {
    label[0]='\0'; // reset label in case there is no label
    int i; // int i to keep track of index of the char of the line being processed
    int indx = 0; // int index to keep track of indexing for label, opcode, and operand
    bool endOfLine = false; // boolean to determine if end of line has been reached at any point of processing
    // set label, ignoring any whitespaces
    for (i = 0; i < 9; i++) {
        if (line[i] == '\n') {
            endOfLine = true;
            break;
        }
        if (line[i] != ' '){ //read in values
            label[indx] = line[i];
            indx++;
        }
        else if (line[i] == ' ') {

            break;
        }
    }
    label[indx] = '\0'; // null terminate label

    // set opcode, ignoring any whitespaces

    for (indx = 0; i < 17 && endOfLine == false; i++) {
        if (line[i] == '\n') {
            endOfLine = true;
            break;
        }
        if (line[i] != ' '){ //read in values
            opcode[indx] = line[i];
            indx++;
        }
    }
    opcode[indx] = '\0'; // null terminate opcode

    // set operand, ignoring any whitespaces
    for (indx = 0; (i < 69) && (endOfLine == false); i++) {
        if (line[i] == '\n') {
            break;
        }

        if (line[i] != ' '){ //read in values
            operand[indx] = line[i];
            indx++;
        }
    }
    operand[indx] = '\0'; // null terminate operand

}

// function to check if a label exists, and add it to the Symbol Table if not
void checkLabel() {
    bool labelExists = false;
    // iterate through Symbol Table
    for (auto& symTabObj : SymbolTable) {
        if (std::strcmp(symTabObj.symbol, label) == 0) { // if symbol is found,
            symTabObj.addr = -1; // set address to -1
            printf("Duplicate Symbol");
            labelExists = true; // print message for duplicate symbol
            break;
        }
    }
    // if it does not exist, add it to the Symbol Table
    if (!labelExists) {
        SYMTAB symTabObj;
        std::strcpy(symTabObj.symbol, label);
        symTabObj.addr = locctr; // set the address as the locctr
        symTabObj.base = 0; // base relative is 0 for now
        SymbolTable.push_back(symTabObj);
    }
}

// function to check if literal exists, and add it to the LiteralTable if not
void checkLiteral() {
    char temp[8];
    int i;
    int literalLength = 0;
    // create a temp variable in order to extract and store just the value of the literal
    // opcodes are read in with full name ex:  =C'EOF' so start at 4th index and read until another ' is encountered
    for (i = 0; i < strlen(opcode); i++) {
        if (opcode[i + 3] == '\'') {
            break;
        }
        temp[i] = opcode[i + 3];
        literalLength++;
    }
    temp[i] = '\0';

    bool literalExists = false;

    // search for literal in LiteralTable
    for (auto& litTabObj : LiteralTable) {
        if (std::strcmp(litTabObj.literal, temp) == 0) {
            litTabObj.address = -1;
            literalExists = true;
            break;
        }
    }

    // if it does not exist, add it to the table
    if (!literalExists) {
        LITTAB litTabObj;
        std::strcpy(litTabObj.literal, temp);
        litTabObj.address = locctr;
        litTabObj.length = literalLength;
        LiteralTable.push_back(litTabObj);
    }
}

// function to implement pass 1
void PASS1(FILE *input, FILE *inter) {

    bool flag = false;
    fgets(line,70,input);  // read in first lines and check for comment
    if (line[0] == '.') { // if comment, print line to intermediate file
        fprintf(inter,"%s", line);
        fgets(line,70,input); // read and process next line
        processLine();
    }
    else {
        // just process the line
        processLine();
    }
    // start formatting for symbol table
    fprintf(symTab, "CSect   Symbol  Value   LENGTH    Flags:\n");
    fprintf(symTab, "----------------------------------------\n");

    // if opcode is "START" set location counter to operand and print the line to the intermediate file
    if(!strcmp(opcode,"START")) {
        startAddress=atoi(operand);
        locctr=startAddress;
        strcpy(programName, label);
        fprintf(symTab, "%-*s          ", 14, label);  // add to symbol table
        flag = true; // set flag to true (used to determine if symbol table length needs to be calculated at the end)
        fprintf(inter,"%04X    %s",locctr, line); // print the line to the intermediate file
        fgets(line,28,input); // read and process the next line
        processLine();
    }
    else { // else
        programName[0]='\0'; // no program name
        startAddress=0; // start address and location counter will be 0
        locctr=0;
    }

    // while the opcode is not "END"
    while(strcmp(opcode,"END")!=0)
    {
        // process the line
        processLine();
        if(opcode[0]=='=')checkLiteral(); // check for literals
        else if(label[0]!='\0')checkLabel(); // check for symbols
        fprintf(inter,"%04X    %s",locctr, line); // print line to intermediate file
        calcLocationCounter(); // update locctr (done after processing in order to print correctly)
        fgets(line,28,input); // read and proccess next line
        processLine();
    }

    fprintf(inter,"        %s",line); // print last line
    if (flag) { // if "START" at beginning, calculate length to add to symTab
        length = locctr - startAddress;
        fprintf(symTab, "%06X\n", length);
    }

    // write SymbolTable to file
    for (int i = 0; i < SymbolTable.size(); ++i) {
        fprintf(symTab, "        %-*s%06X              R\n", 8, SymbolTable[i].symbol, SymbolTable[i].addr);
    }
    // TODO add to pass 2
    fprintf(symTab, "\nLiteralTable\n");
    fprintf(symTab, "Name    Operand Address Length:\n");
    fprintf(symTab, "---------------------------------------\n");
    for (int i = 0; i < LiteralTable.size(); ++i) {
        fprintf(symTab, "%-*s------  %06X  %i\n", 8, LiteralTable[i].literal, LiteralTable[i].address, LiteralTable[i].length);
    }

    fclose(inter);
    fclose(input);
}

// function used in pass 2 to calculate the object code
std::string calculateObjectCode() {
    int i;
    // nixbpe flags for determining object code
    int nFlag = -1, iFlag = -1, xFlag = -1, bFlag = -1, pFlag = -1, eFlag = -1;
    //  SYMTAB object used later in oder to track the found symbol
    SYMTAB symb;
    // variables to hold objCode, and changed versions of operand that is read in
    char objCode[9], operand3[8], operand2[8];
    // start by resetting each first char
    objCode[0] = '\0';
    operand3[0] = '\0';
    operand2[0] = '\0';
    // check if operand contains a # or @
    if (operand[0] == '#' || operand[0] == '@') { // if so,
        for (i = 1; i < strlen(operand); i++) {
            operand2[i - 1] = operand[i]; // use operand2 to store operand without this char
        }
        // null terminate operand2
        operand2[i -1] = '\0';
        if (operand[0] == '#') { // set flags accordingly for immediate adressing mode
            nFlag = 0;
            iFlag = 1;
            xFlag = 0;
        }
        else if (operand[0] == '@') { // set flags accordingly for indirect adressing mode
            nFlag = 1;
            iFlag = 0;
            xFlag = 0;
        }
    }
        // will be using operand2 from now on, so if neither # or @ found, just copy the original operand into operand2
    else {
        strcpy(operand2, operand);
        // set flags accordingly for simple addressing mode
        nFlag = 1;
        iFlag = 1;
    }

    // find opcode in opTab
    bool opcodeFound = false;
    char opcodeValue[2];
    int format;
    for (const auto& op : opTab) {
        if (op.first == opcode) { // if opcode found
            opcodeFound = true;
            opcodeValue[0] = op.second.code[0]; // save first digit of opcode value
            opcodeValue[1] = op.second.code[1]; // save second digit of opcode value
            format = op.second.format; // save format
            break;
        }
    }
    // if format 3, set flags accordingly
    if (format == 3) {
        eFlag = 0;
    }
    // if format 4, set flags accordingly
    else if (format == 4) {
        eFlag = 1;
        bFlag = 0;
        pFlag = 0;
    }

    objCode[0] = opcodeValue[0]; // set first number of object code
    int number;
    // calculate the second number of the object code depending on second number of opcode value and the n and i flags
    // change the opcode value to a hexadecimal number
    std::istringstream(opcodeValue + 1) >> std::hex >> number;
    // save as binary and pad with up to 3 zeros
    std::string binaryString = std::bitset<4>(number).to_string();
    // save the last two bits as the n and i flags
    binaryString[binaryString.size() - 2] = '0' + nFlag;
    binaryString[binaryString.size() - 1] = '0' + iFlag;
    // change the binary number to a hex number
    int modifiedNumber = std::stoi(binaryString, nullptr, 2);
    std::stringstream ss;
    ss << std::hex << modifiedNumber;
    std::string hexString = ss.str();
    // change the letter values of hex to uppercase
    for (char& c : hexString) {
        c = std::toupper(c);
    }
    // save the value to the objCode's second digit
    objCode[1] = hexString[0];
    // set the res of the objCode to zero for now
    // TA will be zero unless there is a symbol found
    if (format == 3) { // set number of zeros for format 3
        for (int i = 2; i < 6; i++) {
            objCode[i] = '0';
        }
        // null terminate the objCode
        objCode[6] = '\0';
    }
    else if (format == 4) { // set number of zeros for format 4
        for (int i = 2; i < 6; i++) {
            objCode[i] = '0';
        }
        // null terminate the objCode
        objCode[6] = '\0';
    }


    // check if there is no operand
    if (operand2[0] == '\0'){
        // return objCode as is
        return objCode;
    }
    // check if there is only numbers in the operand
    int isOnlyDigits = 1;
    for (i = 0; operand2[i] != '\0'; i++) {
        if (!isdigit(operand2[i])) {
            isOnlyDigits = 0; // found a non-digit character
            break;
        }
    }
    // if there is only digits in the operand
    if (isOnlyDigits) {
        // return objCode as is
        return objCode;
    }

    /* check for comma
    the actual assembler would check which register follows
    for testing, we are only using register X, so I only implemented with register X
    Professor Leonard told me this was ok to do */
    bool commaEncountered = false;
    int operandIndex = 0;
    for (int i = 0; operand2[i] != '\0'; ++i) {
        if (operand2[i] != ',') { // if comma is not encountered, copy value to operand3
            operand3[operandIndex++] = operand2[i];
        } else { // else, comma is encountered, break and stop reading in
            commaEncountered = true;
            break;
        }
    }
    // null terminate operand3
    operand3[operandIndex] = '\0';

    // if comma was encountered, we are assuming it is register X, so set xFlag to true for indexed adressing
    if (commaEncountered) {
        xFlag = 1;
    }
    else { // else we are not using indexed addressing
        xFlag = 0;
    }

    // if the opcode was found
    if (opcodeFound) {
        // check for a symbol in the operand field (now using operand3 variation that now excludes any read in comma or # or @)
        bool symbolFound = false;
        // search the symbol table
        for (int i = 0; i < SymbolTable.size(); ++i) {
            if (std::strcmp(SymbolTable[i].symbol, operand3) == 0) { // if found
                symb = SymbolTable[i]; // save the symbol for later use
                symbolFound = true;
                if (bFlag == -1) { // if the b flag has not yet been set,
                    // set it to whatever the symbol indicates it should be set to
                    bFlag = symb.base;
                    // if b is 1, p is 0 and vice versa
                    if (bFlag == 1) {
                        pFlag = 0;
                    }
                    else {
                        pFlag = 1;
                    }
                }
                break;
            }
        }

        // if the symbol was found, calculate the TA
        if (symbolFound) {
            // if using base relative addressing
            if (bFlag == 1) {
                // calculate TA displacement using the value in the base register
                int difference = symb.addr - baseReg;
                // format the difference with padded zeros up to 3 spaces
                char formattedValue[4]; // 3 digits + '\0'
                snprintf(formattedValue, sizeof(formattedValue), "%03X", difference);
                // store the formatted value into objCode at indexes 3, 4, and 5
                // format 3 since format 4 cannot use base relative or pc relative
                objCode[3] = formattedValue[0];
                objCode[4] = formattedValue[1];
                objCode[5] = formattedValue[2];
                // null terminate objCode
                objCode[6] = '\0';
            }
            // else if using pc relative addressing
            else if (pFlag == 1) {
                int locctrDecimal = locctr;
                char locctrHex[4];
                snprintf(locctrHex, sizeof(locctrHex), "%03X", locctrDecimal);

                // calculate the difference using the location counter
                int difference = symb.addr - locctrDecimal;
                // if the difference is a negative number, use 2's complement
                if (difference < 0) {
                    // calculate the absolute value of the difference
                    difference = -difference;
                    // convert the absolute value to 2's complement
                    difference = (1 << 12) - difference;
                }

                // format the difference with padded zeros up to 3 spaces
                char formattedValue[4]; // 3 digits + '\0'
                snprintf(formattedValue, sizeof(formattedValue), "%03X", difference);

                // store the formatted value into objCode at indexes 3, 4, and 5
                // format 3 since format 4 cannot use base relative or pc relative
                objCode[3] = formattedValue[0];
                objCode[4] = formattedValue[1];
                objCode[5] = formattedValue[2];
                // null terminate objCode
                objCode[6] = '\0';
            }
            // else, use the direct address provided for simple addressing
            else {
                // change the address in symbol to be padded with up to 5 zeros
                char formattedValue[6];
                snprintf(formattedValue, sizeof(formattedValue), "%05X", symb.addr);

                // store the formatted value into objCode at indexes 3, 4, 5, 6, and 7
                objCode[3] = formattedValue[0];
                objCode[4] = formattedValue[1];
                objCode[5] = formattedValue[2];
                objCode[6] = formattedValue[3];
                objCode[7] = formattedValue[4];
                // null terminate objCode
                objCode[8] = '\0';
            }

        }
        // if not a symbol, check for a literal
        else if (operand[0] == '=') {
            char temp[8];
            int i;
            // extract just the value of the literal into a temp variable
            for (i = 0; i < strlen(operand); i++) {
                if (operand[i + 3] == '\'') {
                    break;
                }
                temp[i] = operand[i + 3];
            }
            temp[i] = '\0';

            // check the LiteralTable
            for (auto& litTabObj : LiteralTable) {
                if (std::strcmp(litTabObj.literal, temp) == 0) { // if a literal is found, calculate the objCode using its adress
                    char formattedValue[6]; // pad with up to 5 zeros
                    snprintf(formattedValue, sizeof(formattedValue), "%05X", litTabObj.address);

                    // store the formatted value into objCode at indexes 3, 4, and 5
                    objCode[3] = formattedValue[0];
                    objCode[4] = formattedValue[1];
                    objCode[5] = formattedValue[2];
                    objCode[6] = formattedValue[3];
                    objCode[7] = formattedValue[4];
                    // null terminate objCode
                    objCode[8] = '\0';
                }
            }
        }
        else { // if symbol was not found, print out error and set the TA to zero
            printf("Error: Symbol not found\n");
            objCode[3] = '0';
            objCode[4] = '0';
            objCode[5] = '0';
            objCode[6] = '\0';
        }
    }
    // if opcode wasn't found
    // check for "BASE"
    else if (strcmp(opcode, "BASE") == 0){
        for (int i = 0; i < SymbolTable.size(); ++i) {
            if (std::strcmp(SymbolTable[i].symbol, operand3) == 0) {
                SymbolTable[i].base = 1; // set the symbol to be base relative
                baseReg = SymbolTable[i].addr;
                objCode[0] = '\0'; // no object code needed
                return objCode;
            }
        }
    }
    // else, check for "NOBASE"
    else if (strcmp(opcode, "NOBASE") == 0){
        for (int i = 0; i < SymbolTable.size(); ++i) {
            if (std::strcmp(SymbolTable[i].symbol, operand3) == 0) {
                SymbolTable[i].base = 0; // set the symbol to no longer be base relative
                objCode[0] = '\0'; // no object code needed
                return objCode;
            }
        }
    }
    else if (strcmp(opcode, "WORD")){
        //TODO implement later
    }
    else if (strcmp(opcode, "BYTE")){
        //TODO implement later
    }

    // calculate the third number of the objCode
    int binaryNumber = (xFlag << 3) | (bFlag << 2) | (pFlag << 1) | eFlag;
    // convert the binary number to hexadecimal
    char hexValue;
    if (binaryNumber < 10)
        hexValue = binaryNumber + '0';
    else
        hexValue = binaryNumber - 10 + 'A';
    // store the hexadecimal value into objCode at index 2
    objCode[2] = hexValue;


    return objCode;
}

// function to process the lines of the intermediate file
// same process as reading in the source file, but accounting for the added addresses printed in the intermediate file
void processIntLine() {
    label[0] = '\0'; // reset label
    int i;
    int indx = 0;
    bool endOfLine = false;
    // read in the location address
    for (i = 0; i < 8; i++) {
        if (line[i] != ' ') { //read in values
            LC[indx] = line[i];
            indx++;
        } else if (LC[i] == ' ') {

            break;
        }
    }
    // set null terminator
    LC[indx] = '\0';

    // read in label
    for (indx = 0; i < 17; i++) {
        if (line[i] == '\n') { // check if end of line to stop processing values
            endOfLine = true;
            break;
        }
        if (line[i] != ' ') {
            label[indx] = line[i]; // read in values
            indx++;
        } else if (line[i] == ' ') {

            break;
        }
    }
    // set null terminator
    label[indx] = '\0';

    for (indx = 0; i < 25 && endOfLine == false; i++) {
        if (line[i] == '\n') { // check if end of line to stop processing values
            endOfLine = true;
            break;
        }
        if (line[i] != ' ') { //read in values
            opcode[indx] = line[i];
            indx++;
        }
    }
    // set null terminator
    opcode[indx] = '\0';

    for (indx = 0; (i < 36) && (endOfLine == false); i++) {
        if (line[i] == '\n') { // check if end of line to stop processing values
            break;
        }

        if (line[i] != ' ') { //read in values
            operand[indx] = line[i];
            indx++;
        }
    }
    // set null terminator
    operand[indx] = '\0';
}



void PASS2(FILE *intFile, FILE *listFile) {
    std::string printCode = ""; // string to print out the opCode

    // get first line
    fgets(line, 70, intFile);
    if (line[0] == '.') { //check for comment
        fprintf(listFile, "%s", line); // if comment, print line to intermediate file
        fgets(line, 36, intFile); // read and process next line
    }

    // process the line
    processIntLine();

    // if opcode is "START" set location counter to operand and print to the intermediate file
    if (!strcmp(opcode, "START")) {
        startAddress = atoi(operand);
        locctr = startAddress;
        strcpy(programName, label);
        fprintf(listFile, "%s", line);
        fgets(line, 36, intFile); // read in next line
    } else { // else, set location counter to 0
        programName[0] = '\0';
        startAddress = 0;
        locctr = 0;
    }
    // while opcode is not equal to "END"
    while (strcmp(opcode, "END") != 0) {
        processIntLine(); // process the line
        calcLocationCounter(); // update the location counter
        // format the input to ignore the newline character
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';

        // print the line to the listing file without the newline character
        fprintf(listFile, "%-*s          ", 36,line);
        // check if line is a comment
        if (line[0] == '.') { // if it is get the next line and continue
            fgets(line, 36, intFile);
            continue;
        }
        // if opcode is "RESW" the object code does not need to be calculated
        if (strcmp(opcode, "RESW") == 0){
            // do nothing
            fprintf(listFile, "\n");

        }
        // if opcode is "RESW" the object code does not need to be calculated
        else if (strcmp(opcode, "RESB") == 0){
            // do nothing
            fprintf(listFile, "\n");
        }
        // if the opcode is a literal
        else if (opcode[0] == '=') {
            fprintf(listFile, " ");
            // check if it is a char literal
            if (opcode[1] == 'C') {
                int i;
                for (i = 3; opcode[i] != '\''; ++i) {
                    fprintf(listFile, "%02X", opcode[i]); // print the hexadecimal representation directly to listFile
                }
            }
            fprintf(listFile, "\n");
        }
        else {
            // calculate the object code and print it formatted with spaces and a newline character
            printCode = calculateObjectCode();
            fprintf(listFile, " ");
            for (int i = 0; printCode[i] != '\0'; i++) {
                fprintf(listFile, "%c", printCode[i]);
            }
            fprintf(listFile, "\n");
        }

        // get the next line and process it
        fgets(line, 36, intFile);
        processIntLine();
    }
    // print the last line
    fprintf(listFile, "%.*s", 35, line);

    // close the intermediate and listing file
    fclose(intFile);
    fclose(listFile);
}

int main(int argc, char* argv[]) {
    // generate the optab
    opTab = generateOPTAB();
    // process the command line arguments
    for (int i = 1; i < argc; ++i) {
        std::string filename = argv[i];
        // save the baseFilename in order to create files with different extensions
        size_t pos = filename.find_last_of(".");
        std::string baseFilename = filename.substr(0, pos);

        // open the file
        file = fopen(argv[i], "r");
        if (file == nullptr) {
            std::cerr << "Error: Unable to open file " << argv[i] << std::endl;
            continue;
        }

        // create an intermediate file
        filename = baseFilename + ".int";
        FILE* intermediateFile = fopen(filename.c_str(), "w");
        if (intermediateFile == nullptr) {
            continue;
        }

        // create a listing file
        filename = baseFilename + ".l";
        FILE* listingFile = fopen(filename.c_str(), "w");
        if (listingFile == nullptr) {
            std::cerr << "Error: Unable to create listing file " << filename << std::endl;
            fclose(intermediateFile);
            fclose(file);
            continue;
        }

        // create a symbol table file
        filename = baseFilename + ".st";
        symTab = fopen(filename.c_str(), "w");
        if (symTab == nullptr) {
            std::cerr << "Error: Unable to create symbol table file " << filename << std::endl;
            fclose(listingFile);
            fclose(intermediateFile);
            fclose(file);
            continue;
        }

        // run PASS1
        PASS1(file, intermediateFile);
        // create a new reference to the intermediate file to process from the beginning
        filename = baseFilename + ".int";
        FILE* intFile = fopen(filename.c_str(), "r");
        if (intFile == nullptr) {
            std::cerr << "Error: Unable to create intermediate code file ";
        }
        // run PASS2
        PASS2(intFile, listingFile);
        // close all the files
        fclose(file);
        fclose(listingFile);
        fclose(intermediateFile);
        fclose(file);

    }
    return 0;
}
