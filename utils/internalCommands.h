#ifndef INTERNAL_COMMANDS_H
#define INTERNAL_COMMANDS_H

#define MY_WAIT 1
#define CLEAN_DIE 2
#define PRINTME 3

void mywait_();
void cleanEdie_();

int eh_comando_interno(char* string);
void roda_comando_interno(int comando);

#endif //INTERNAL_COMMANDS_H