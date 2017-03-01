// Benjamin Steenkamer
// CPEG 324-010
// Lab 1 - 8 Bit ISA Simulator
// 3/3/17

#include <string.h>
#include <stdio.h>

//Global Variables
char lineBuffer[16]; //Each line should be only 8 character + new line + end line, but adding extra space for safety
char opCode[2];
int linesToSkip = 0;

//Registers
char r0 = 0;
char r1 = 0;
char r2 = 0;
char r3 = 0;

void ISA_add(){

}

void ISA_sub(){

}

void ISA_li(){

}

void ISA_prnt(){

}

void ISA_cmp(){
    // linesToSkip = 1;
    // linesToSkip = 2;
}


int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Simulator usage is: ./simulator FILENAME\n");
    }
    else{
        FILE *file = fopen(argv[1], "r");//Open file entered from command line in read mode

        if(file == NULL){
            printf("File \"%s\" not found!\n", argv[1]);
            return 0;
        }

        while(fgets(lineBuffer, sizeof(lineBuffer), file)){
            opCode[0] = lineBuffer[0];
            opCode[1] = lineBuffer[1];

            if(linesToSkip == 0){
                if(strcmp(opCode,"00") == 0){
                    if(lineBuffer[3] == '0'){
                        ISA_prnt();
                    }
                    else{
                        ISA_cmp();
                    }
                }
                else if((strcmp(opCode,"01") == 0)){
                    ISA_add();
                }
                else if((strcmp(opCode,"10") == 0)){
                    ISA_sub();
                }
                else{ // opCode is "11"
                    ISA_li();
                }
            }
            else{
                linesToSkip--;
            }
        }

        fclose(file);
    }

    return 0;
}
