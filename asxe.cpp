

#include <iostream>
#include <map>
#include <string>
#include <vector>


int startAddress,locctr = 0,length;
char line[70],label[9],opcode[8],operand[9],programName[9];
FILE *file, *symTab;


struct instructionInfo {
    std::string code;
    int format;
};

struct SYMTAB{
    char symbol[10];
    int addr;
};
struct LITTAB{
    char literal[10];
    int operand = 0x000000;
    int address;
    int length = 0;
};

typedef std::map<std::string, instructionInfo> OPTAB;
std::vector<SYMTAB> SymbolTable;
std::vector<LITTAB> LiteralTable;

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

int calcByteSize(const std::string& op) {
    if (op.empty()) {
        return 0;
    }
    if (op[0] == 'C' || op[0] == 'c') {
        return op.length() - 3;
    } else {
        return (op.length() - 3) / 2;
    }
}

void checkOpcode(){
    OPTAB opTab = generateOPTAB();

    int found=0;
    if (opTab.find(opcode) != opTab.end()) {
        locctr += opTab[opcode].format;
        found = 1;
    }
    if(!found)
    {
        if(!strcmp(opcode,"WORD")) locctr+=3;
        else if (!strcmp(opcode,"RESW"))locctr+=(3*atoi(operand));
        else if (!strcmp(opcode,"RESB"))locctr+=atoi(operand);
        else if (!strcmp(opcode, "BYTE")) {
                    length = calcByteSize(operand);
                    locctr += length;
        }
    }
}

void processLine()
{
    label[0]='\0';
    int i;
    int indx = 0;
    bool endOfLine = false;
    for (i = 0; i < 9; i++) {
        if (line[i] == '\n') {
            endOfLine = true;
            break;
        }
        if (line[i] != ' '){
            label[indx] = line[i];
            indx++;
        }
        else if (line[i] == ' ') {

            break;
        }
    }
    label[indx] = '\0';

    for (indx = 0; i < 17 && endOfLine == false; i++) {
        if (line[i] == '\n') {
            endOfLine = true;
            break;
        }
        if (line[i] != ' '){
            opcode[indx] = line[i];
            indx++;
        }
    }
    opcode[indx] = '\0';

    for (indx = 0; i < 27 && endOfLine == false; i++) {
        if (line[i] == '\n') {
            break;
        }

        if (line[i] != ' '){
            operand[indx] = line[i];
            indx++;
        }
    }
    operand[indx] = '\0';

}

void checkLabel()
{
    bool labelExists = false;

    for (auto& symTabObj : SymbolTable) {
        if (std::strcmp(symTabObj.symbol, label) == 0) {
            symTabObj.addr = -1;
            labelExists = true;
            break;
        }
    }

    if (!labelExists) {
        SYMTAB symTabObj;
        std::strcpy(symTabObj.symbol, label);
        symTabObj.addr = locctr;
        SymbolTable.push_back(symTabObj);
    }
}

void checkLiteral() {
    char temp[8];
    int i;
    int literalLength = 0;
    for (i = 0; i < strlen(opcode); i++) {
        if (opcode[i + 3] == '\'') {
            break;
        }
        temp[i] = opcode[i + 3];
        literalLength++;
    }
    temp[i] = '\0';

    bool literalExists = false;

    for (auto& litTabObj : LiteralTable) {
        if (std::strcmp(litTabObj.literal, temp) == 0) {
            litTabObj.address = -1;
            literalExists = true;
            break;
        }
    }

    if (!literalExists) {
        LITTAB litTabObj;
        std::strcpy(litTabObj.literal, temp);
        litTabObj.address = locctr;
        litTabObj.length = literalLength;
        LiteralTable.push_back(litTabObj);
    }
}

void PASS1(FILE *input, FILE *inter) {

    bool flag = false;
    fgets(line,70,input);
    if (line[0] == '.') {
        fprintf(inter,"%s", line);
        fgets(line,70,input);
    }
    fprintf(symTab, "CSect   Symbol  Value   LENGTH  Flags:\n");
    fprintf(symTab, "--------------------------------------\n");

    processLine();

    if(!strcmp(opcode,"START")) {
        startAddress=atoi(operand);
        locctr=startAddress;
        strcpy(programName, label);
        fprintf(symTab, "%-*s          ", 8, label);
        flag = true;

        fprintf(inter,"%04X    %s",locctr, line);
        fgets(line,27,input);
    }
    else {
        programName[0]='\0';
        startAddress=0;
        locctr=0;
    }

    while(strcmp(opcode,"END")!=0)
    {
        processLine();
        if(label[0]=='*')checkLiteral();
        else if(label[0]!='\0')checkLabel();
        fprintf(inter,"%04X    %s",locctr, line);
        checkOpcode();
        fgets(line,27,input);
        processLine();
    }
    fprintf(inter,"%s",line);
    if (flag) {
        length = locctr - startAddress;
        fprintf(symTab, "%06X\n", length);
    }

    for (int i = 0; i < SymbolTable.size(); ++i) {
        fprintf(symTab, "        %-*s  %06X          R\n", 8, SymbolTable[i].symbol, SymbolTable[i].addr);
    }
    fprintf(symTab, "\nLiteralTable\n");
    fprintf(symTab, "Name     Operand   Address  Length:\n");
    fprintf(symTab, "---------------------------------------\n");
    for (int i = 0; i < LiteralTable.size(); ++i) {
        fprintf(symTab, "%-*s ------      %06X      %i\n", 8, LiteralTable[i].literal, LiteralTable[i].address, LiteralTable[i].length);
    }
    
    fclose(inter);
    fclose(input);
}

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        file = fopen(argv[i], "r");
        if (file == nullptr) {
            std::cerr << "Error: Unable to open file " << argv[i] << std::endl;
            continue;
        }
        std::string filename = std::string(argv[i]) + ".int";
        FILE* intermediateFile = fopen(filename.c_str(), "w");
        if (intermediateFile == nullptr) {
            std::cerr << "Error: Unable to create intermediate code file ";
        }

        filename = std::string(argv[i]) + ".l";
        FILE* listingFile = fopen(filename.c_str(), "w");
        if (listingFile == nullptr) {
            std::cerr << "Error: Unable to create listing file ";
            fclose(intermediateFile);
        }
        filename = std::string(argv[i]) + ".st";
        symTab = fopen(filename.c_str(), "w");
        if (listingFile == nullptr) {
            std::cerr << "Error: Unable to create listing file ";
            fclose(intermediateFile);
        }
        PASS1(file, intermediateFile);
        fclose(file);
    }
    length= locctr - startAddress;
}
