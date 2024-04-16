#include <iostream>
#include <map>
#include <string>
# include <fstream>

char opcode[10], operand[10], label[10], ch, temp1[10], temp2[20], temp3[20];
int LC, start, length, s = -1, o = -1, i, j = 0, flag, size = 0, opd;
FILE *file, *symTab;


struct instructionInfo {
    std::string code;
    int format;
};

struct SYMTAB {
    char label[10];
    int addr;
}ST[30];

typedef std::map<std::string, instructionInfo> OPTAB;
typedef std::map<std::string, int> SymbolTable;

OPTAB generateOPTAB() {
    OPTAB opcodeTable;
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


int calculateByteSize(const std::string& operand) {
    if (operand.empty()) {
        return 0;
    }
    if (operand[0] == 'C' || operand[0] == 'c') {
        return operand.length() - 3;
    } else {
        return (operand.length() - 3) / 2;
    }
}

/*void readLine() {
    strcpy(temp1,"");
    strcpy(temp2,"");
    strcpy(temp3,"");
    fscanf(file, "%s", temp1);
    if (getc(file) != '\n') {
        fscanf(file, "%s", temp2);
        if (getc(file) != '\n') {
            fscanf(file, "%s", temp3);
        }
    }
    if (strcmp(temp1, "") != 0 && strcmp(temp2, "") == 0 && strcmp(temp3, "") == 0) {
        strcpy(label, "");
        strcpy(opcode, temp2);
        strcpy(operand, "");
    }
    else if (strcmp(temp1, "") != 0 && strcmp(temp2, "") != 0 && strcmp(temp3, "") == 0) {
        strcpy(label, "");
        strcpy(opcode, temp2);
        strcpy(operand, temp3);
    }
    else if (strcmp(temp1, "") != 0 && strcmp(temp2, "") != 0 && strcmp(temp3, "") != 0) {
        strcpy(label, temp1);
        strcpy(opcode, temp2);
        strcpy(operand, temp3);
    }
}
*/

void readLine() {
    strcpy(label, "");
    strcpy(opcode, "");
    strcpy(operand, "");
    fscanf(file, "%9s", label); // Read the label field
    if (feof(file)) return; // Check for end-of-file
    if (getc(file) != '\n') {
        fscanf(file, "%9s", opcode); // Read the opcode field
        if (feof(file)) return; // Check for end-of-file
        if (getc(file) != '\n') {
            fscanf(file, " %[^\n]s", operand); // Read the rest of the line as the operand field
        }
    }
}





void firstPass(FILE* file, SymbolTable& SYMTAB, OPTAB opcodeTable) {


    std::string sourceFilename = "sourcefile"; // Replace with actual source file name

        FILE* intermediateFile = fopen((sourceFilename + ".int").c_str(), "w");
        if (intermediateFile == nullptr) {
            std::cerr << "Error: Unable to create intermediate code file " << sourceFilename + ".int" << std::endl;
            return;
        }

        // Open listing file for writing
        FILE* listingFile = fopen((sourceFilename + ".lst").c_str(), "w");
        if (listingFile == nullptr) {
            std::cerr << "Error: Unable to create listing file " << sourceFilename + ".lst" << std::endl;
            fclose(intermediateFile); // Close intermediate file before returning
            return;
        }

    fscanf(file, "%s%s%x", label, opcode, &opd);
    if (strcmp(opcode, "START") == 0) {
        start = opd;
        LC = start;
        fprintf(intermediateFile, "%s\t%s\t%x\n", label, opcode,opd);
        //readLine();
    }
    else {
        LC = 0;
    }
    readLine(); // cahnged
    while (strcmp(opcode, "END") != 0) {
        fprintf(intermediateFile, "%x\t%s\t%s\t%s\n", LC, label, opcode, operand);
        if (strcmp(label, "") != 0) {
            for (i = 0; i <= s; i++) {
                if (strcmp(label, "") != 0) { // Added condition to check if label is not empty
                    for (i = 0; i <= s; i++) {
                        if (strcmp(ST[i].label, label) == 0) {
                            printf("Error, duplicate Symbol");
                            exit(0);
                        }
                    }
                }
            }
            s++;
            strcpy(ST[s].label, label);
            ST[s].addr = LC;
        }
        flag = 0;
        if (opcodeTable.find(opcode) != opcodeTable.end()) {
            LC += opcodeTable[opcode].format;
            size += opcodeTable[opcode].format;
            flag = 1;
        }
        if (flag == 0) {
            if (strcmp(opcode, "WORD") == 0) {
                LC += 0x3;
                size += 3;
            } else if (strcmp(opcode, "RESW") == 0) {
                LC += (0x3 * (atoi(operand)));
            } else if (strcmp(opcode, "RESB") == 0) {
                LC += (atoi(operand));
            } else if (strcmp(opcode, "BYTE") == 0) {
                length = calculateByteSize(operand);
                LC += length;
                size += length;
            }
        }
        readLine();
    }
    fprintf(intermediateFile, "\t%s\t%s\t%s\n", label, opcode, operand);
    for (i = 0; i <=s; i++) {
        fprintf(symTab, "%s\t%x", ST[i].label, ST[i].addr);
        if (i != s)
            fprintf(symTab, "\n");
    }
    //TODO change this to fprintf(listingfile, "%x\n%x", LC - start, size);
    fclose(intermediateFile);
}


int main(int argc, char* argv[]) {
    OPTAB opcodeTab = generateOPTAB();
    for (i = 1; i < argc; ++i) {
        SymbolTable  symTab;
        file = fopen(argv[i], "r");
        if (file == nullptr) {
            std::cerr << "Error: Unable to open file " << argv[i] << std::endl;
            continue; // Skip to the next file if unable to open
        }
        firstPass(file, symTab, opcodeTab);
        fclose(file);
    }
    return 0;
}
