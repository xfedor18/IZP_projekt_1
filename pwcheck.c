#include <stdio.h>
#include <stdlib.h>
#define LENTH 100

int bigLetters(char *string){ //check for capital letters
        for (int i = 0; string[i] != '\0'; i++){
        if (string[i] >= 'A' && string[i] <= 'Z'){
            return 1;
        }      
    }
    return 0;
}

int smallLetters(char *string){ //checking for small letters
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] >= 'a' && string[i] <= 'z')
        {
            return 1;
        }
    }
    return 0;
}

int numbers(char *string){ // presence of numbers
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] >= 48 && string[i] <= 57)
        {
            return 1;
        }
    }
    return 0;
}

int specialSymbols (char* string){ // presence of numbers special symbols
    for (int i=0; string[i] != '\0'; i++){
        if (((string[i] >= 32) && (string[i] <= 47)) || ((string[i] >= 58) && (string[i] <= 64)) || ((string[i] >= 91) && (string[i] <= 96)) || ((string[i] >= 123) && (string[i] <= 126)))
            return 1;
    }
    return 0;
}

int Levl_1 (char *string){ // at least 1 uppercase and 1 lowercase letter
    if ((bigLetters(string) == 1) && (smallLetters(string) == 1))
    {
        return 1;
    }
    return 0; 
}

int Levl_2 (char *string, int parametr){ // output of parameter dependence on parameter
    if ((parametr == 1) && (Levl_1(string) == 1))
        return 1;
    if ((parametr == 2) && (Levl_1(string) == 1))
        return 1;
    if (((parametr == 3) && (Levl_1(string) == 1)) && ((numbers(string) == 1) || (specialSymbols(string) == 1)))
        return 1;
    if ((parametr > 3) && (Levl_1(string) == 1) && (numbers(string) == 1) && (specialSymbols(string) == 1))
        return 1;
    return 0;   
}

int Levl_3 (char *string, int parametr){ //inconsistency of characters of the same length.
    if (Levl_2(string, parametr) == 1){
        int repetitions = 1;
        int correctRepetitions = 0;
        for (int i=0; string[i] != '\0'; i++){
            if (string[i] == string[i+1]){ //matching signs
                repetitions++; 
                if (repetitions > correctRepetitions){ //pass the correct value of the repetitions
                    correctRepetitions = repetitions ;
                }
            }else{
                repetitions = 1;
            }
        }
        if (correctRepetitions >= parametr){ //are there any coincidences
            return 0;
        }else{
            return 1;
        }
    }else{
        return 0;
    }
}

int main(int argc, char *argv[]){
    argc  = 1;
    if(argc > 3)
        printf("as an argument can only be: Level from 0 to 4 inclusive, Parameter is not less than 0 and --status\n");
    char stroka[LENTH];
    int levevl = atoi(argv[1]); //translated the first argument from a string to a number
    int Parametr = atoi(argv[2]); //translated 2 argument from a string to a number
    if ((levevl < 0) || (levevl > 4)) //acceptable values
        printf("level can be from 0 to 4 inclusive\n");
    if (Parametr < 0) // acceptable values
        printf("parameter cannot be less than 0\n");
    while ((fgets(stroka, LENTH, stdin) != NULL)){  //got passwords from file (termenal)
        if (levevl == 1){
            if (Levl_1(stroka) == 1)
                printf("%s\n", stroka);
        }else if (levevl == 2){
            if (Levl_2(stroka, Parametr) == 1)
                printf("%s\n", stroka);
        }else if (levevl == 3){
            if (Levl_3(stroka, Parametr)==1)
                printf("%s", stroka);
        }
    }
    return 1;
}