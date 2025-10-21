//Author: Erkan Altundal
//Purpose: A virtual machine for Pascal programming language

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 500

typedef struct {    //a struct to easily parse the text segment
    int op;
    int l;
    int m;
}In;

int is_base_pointer(int, int);
void printproperly(int);
int base(int BP, int L);

// global variables for easier operations through data
int pas[ARRAY_SIZE] = {0};  // all set to zero
int sp = 500;
int bp = 499;
int pc = 10;
In ir;
int eop = 1;
int base_links[100]; // stores all active base pointers
int link_count = 0;

int main(int argc, char* argv[]){
    FILE *file;
    char line[100];

    if (argc < 2) { // make sure arguement count is two
        printf("Usage: ./a input.txt\n");
        return 1;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: could not open file\n");
        return 1;
    }

    int op, l, m;
    int idx = 10;   // a pc imitator to assign corresponding elements of text to the bottom memory of pas
    while (fscanf(file, "%d %d %d", &op, &l, &m) == 3) {    //fscanf returns the amount of fetch (3)
        pas[idx++] = op;    
        pas[idx++] = l;
        pas[idx++] = m;
        if (idx >= ARRAY_SIZE - 2) {    
            printf("too many instructions. aborting.\n");
        break;
        }
    }

    fclose(file);

    if (idx == 10) {    // just a checker
        printf("no instructions loaded check the input file\n");
    }    
    
    /*for (int i = 10; i < ARRAY_SIZE - 2; i += 3) {        // another checker to see the text segment of pas
        if (pas[i] == 0 && pas[i+1] == 0 && pas[i+2] == 0)
            break; 
        printf("%3d\t%2d\t%1d\t%2d\n", i, pas[i], pas[i+1], pas[i+2]);
    }*/

    printf("                 PC  BP  SP  stack\n");
    printf("Initial values:  %d  %d %d\n", pc, bp, sp);
    while(eop){
        //fetch
        char opname[4]; //a string that we will need to specify what code implemented with each ISA inside switch
        ir.op = pas[pc];  // assign the values of instructions according to pc  
        ir.l = pas[pc+1];
        ir.m = pas[pc+2];    
        pc = pc + 3;        //increment pc with 3 to reach the next elements of instructions

        //execute
        switch(ir.op){
            case 1: //INC
                sp = sp-ir.m;
                strcpy(opname, "INC");
                break;
            case 2: 
                switch(ir.m){
                    case 0: //RTN
                        sp = bp+1;
                        bp = pas[sp-2];
                        pc = pas[sp-3];
                        strcpy(opname, "RTN");
                        break;
                    case 1: //ADD
                        pas[sp+1] = pas[sp+1] + pas[sp];
                        sp = sp+1;
                        strcpy(opname, "ADD");
                        break;
                    case 2: //SUB
                        pas[sp+1] = pas[sp+1] - pas[sp];
                        sp = sp+1;
                        strcpy(opname, "SUB");
                        break;
                    case 3: //MUL
                        pas[sp+1] = pas[sp+1] * pas[sp];
                        sp = sp+1;
                        strcpy(opname, "MUL");
                        break;
                    case 4: //DIV
                        pas[sp+1] = pas[sp+1] / pas[sp];
                        sp = sp+1;
                        strcpy(opname, "DIV");
                        break;
                    case 5: //EQL
                        pas[sp+1] = pas[sp+1]==pas[sp];
                        sp = sp+1;
                        strcpy(opname, "EQL");
                        break;
                    case 6: //NEQ
                        pas[sp+1] = pas[sp+1]!=pas[sp];
                        sp = sp+1;
                        strcpy(opname, "NEQ");
                        break;
                    case 7: //LSS
                        pas[sp+1] = pas[sp+1]<pas[sp];
                        sp++;
                        strcpy(opname, "LSS");
                        break;
                    case 8: //LEQ
                        pas[sp+1] = pas[sp+1]<=pas[sp];
                        sp++;
                        strcpy(opname, "LEQ");
                        break;
                    case 9: //GTR
                        pas[sp+1] = pas[sp+1]>pas[sp];
                        sp++;
                        strcpy(opname, "GTR");
                        break;
                    case 10: //GEQ
                        pas[sp+1] = pas[sp+1]>=pas[sp];
                        sp++;
                        strcpy(opname, "GEQ");
                        break;
                    case 11:    //MOD  --- UPDATE FOR HW4 ---
                        pas[sp+1] = pas[sp+1] % pas[sp];
                        sp++;
                        strcpy(opname, "MOD");
                    default:
                        printf("ERROR1");
                        break;
                }
                break;
            case 3: //LOD
                sp = sp-1;
                pas[sp] = pas[base(bp,ir.l)-ir.m];
                strcpy(opname, "LOD");
                break;
            case 4: //STO
                pas[base(bp,ir.l)-ir.m] = pas[sp];
                sp = sp+1;
                strcpy(opname, "STO");
                break;
            case 5: //CAL
                pas[sp-1] = base(bp,ir.l);  //SL
                pas[sp-2] = bp;             //DL
                pas[sp-3] = pc;             //RA
                bp = sp-1;
                pc = ir.m;
                strcpy(opname, "CAL");
                break;
            case 6: //LIT
                sp =sp-1;
                pas[sp] = ir.m;
                strcpy(opname, "LIT");
                break;
            case 7: //JMP
                pc = ir.m;
                strcpy(opname, "JMP");
                break;
            case 8: // JPC
                if(pas[sp]==0){
                    pc = ir.m;
                }
                sp = sp +1;
                strcpy(opname, "JPC");
                break;
            case 9: //SYS
                switch(ir.m){  
                    case 1: //for printing the bottom of the stack
                        printf("Output result is: %d\n",pas[sp]);
                        sp = sp+1;
                        strcpy(opname, "SYS");
                        break;
                    case 2: //for getting user input, incrementing 1 to the stack
                        printf("Please Enter an Integer : ");
                        sp = sp-1;
                        scanf("%d", &pas[sp]);
                        strcpy(opname, "SYS");
                        break;
                    case 3: //halt
                        eop = 0;
                        strcpy(opname, "SYS");
                        break;
                    default:
                        printf("ERROR2");
                        break;  
                }
                break;
            default:
                printf("ERROR3: Invalid opcode %d at PC = %d\n", ir.op, pc - 3);
                eop = 0; // halt the program
                break;
        }

        // printer for each line of code, specifiers adjusted to look like the sample
        printf("    %-4s %-2d %-2d   %2d  %3d %3d   ", opname, ir.l, ir.m, pc, bp, sp);
        printproperly(499);

        //stack printer (old attempt)
        /*int printedVertical = 0;    // flag for printing the "|" after the numbers
        for (int i = 499; i >= sp; i--) {
            if (printedVertical && i == bp) {//basically prints "|" when i meets the bp value
                printf("| ");
            }
            printf("%d ", pas[i]);// print from top to bottom of stack
            printedVertical = 1;
        }
        printf("\n");*/
    }
    return 0;
}

//auxiliary function to see all dynamic link, to print | behind every AR
int is_base_pointer(int SP, int BP) {   
    for (int l = 0; ; l++) {
        int b = base(BP, l);
        if (b == SP)
            return 1; // SP matches a base pointer
        if (b == 0 || b == 1 || b == pas[b]) // hit the top or invalid
            break;
    }
    return 0;
}

//stack printer function
void printproperly(int SP){
    if(SP < sp){    // base step, print new line when done
        printf("\n");
        return;
    }
    if (is_base_pointer(SP, bp)&& SP != 499) {  // check every time sp hits bp
        printf("| "); 
    }

    printf("%d ", pas[SP]); //print the stack

    printproperly(SP-1);    //recursive call to go downwards
}

int base(int BP, int L){
    int arb = BP; // arb = activation record base
    while (L > 0){ //find base L levels down
        arb = pas[arb];
        L--;
    }
    return arb;
}
