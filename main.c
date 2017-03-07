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

//Registers, intiliazed to 0 before first write
char r0 = 0;
char r1 = 0;
char r2 = 0;
char r3 = 0;

char* decode_register(char a, char b){
    if(a == '0' && b == '0'){
        return &r0;
    }
    else if(a == '0' && b == '1'){
        return &r1;
    }
    else if(a == '1' && b == '0'){
        return &r2;
    }
    else{ //a == '1' && b == '1'
        return &r3;
    }
}

void ISA_add(){
    //Set operation reisgters
    char *dest_reg = decode_register(lineBuffer[2],lineBuffer[3]);
    char *src_reg = decode_register(lineBuffer[4],lineBuffer[5]);
    char *trg_reg = decode_register(lineBuffer[6],lineBuffer[7]);

    //Perform operation
    *dest_reg = *src_reg + *trg_reg;
}

void ISA_sub(){
    //Set operation reisgters
    char *dest_reg = decode_register(lineBuffer[2],lineBuffer[3]);
    char *src_reg = decode_register(lineBuffer[4],lineBuffer[5]);
    char *trg_reg = decode_register(lineBuffer[6],lineBuffer[7]);

    //Perform operation
    *dest_reg = *src_reg - *trg_reg;
}

//Load immediate value into register
void ISA_li(){
    char *dest_reg = decode_register(lineBuffer[2], lineBuffer[3]);
    char immediate_value = 0;
    char bit_value = 0;

    if(lineBuffer[4] == '1'){
        immediate_value = ~immediate_value;
    }

    for (int i = 7; i > 3; i--){
        //Convert ASCII "bit" to integer "bit" and set it as first bit of immediate_value
        bit_value = (lineBuffer[i] - 48);

        immediate_value ^= (-bit_value ^ immediate_value) & (1 << 7 - i); //Set the approatie bit of immediate_value
    }
    *dest_reg = immediate_value; //Load register with the immediate.
}

void ISA_prnt(){
    char *src_reg = decode_register(lineBuffer[3],lineBuffer[4]);

    if(lineBuffer[5] == '1'){ //Print as integer
        printf("%d\n",(*src_reg));
        fflush(stdout);
    }
    if(lineBuffer[6] == '1'){ //Print as 8 bit hexadecimal
        printf("%X\n",(*src_reg) & 0xFF);
        fflush(stdout);
    }
    if(lineBuffer[7] == '1'){ //Print as ASCII character
        printf("%c\n",(*src_reg));
        fflush(stdout);
    }
}

void ISA_cmp(){
    char *src_reg = decode_register(lineBuffer[4],lineBuffer[5]);
    char *trg_reg = decode_register(lineBuffer[6],lineBuffer[7]);

    if(*src_reg == *trg_reg){
        linesToSkip = lineBuffer[3] - 47 ; //Convert from ASCII to bit and add 1 to it so value is 1 or 2.
    }
}


int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Simulator usage is: ./simulator FILENAME\n");
        fflush(stdout);
    }
    else{
        FILE *file = fopen(argv[1], "r");//Open file entered from command line in read mode

        if(file == NULL){
            printf("File \"%s\" not found!\n", argv[1]);
            printf("\n---END OF SIMULATION---\n");
            fflush(stdout);
            return 0;
        }

        while(fgets(lineBuffer, sizeof(lineBuffer), file)){

            opCode[0] = lineBuffer[0];
            opCode[1] = lineBuffer[1];

            if(linesToSkip == 0){
                if(strcmp(opCode,"00") == 0){
                    if(lineBuffer[2] == '0'){
                        ISA_prnt();
                    }
                    else{  //lineBuffer[2] == '1'
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
                    fflush(stdout);
                }
            }
            else{
                linesToSkip--;
            }
        }

        fclose(file);
    }
    printf("\n---END OF SIMULATION---\n");
    fflush(stdout);

    return 0;
}
