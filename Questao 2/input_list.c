#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    @shogunhirei
    Function to insert data more easily, because, seriously, element-wise its a pain in the ass

    Process:
    -> Input string;
    -> Read string;
    -> identify marker (",")
    -> Identify elements between markers (data)
    -> Create array with the length equal to the numbers of marks + 1
    ->         Problem: Converts string of text to number
    ->         Inicial solution: convert element-wise char and sum them up
    -> Do this for every markers + 1, 
    -> End: Return array
    sáb 10 nov 2018 12:39:52 -02
*/

int main(int argc, char** argv)
{
    int input[3];
    int m,j,k;

    printf("Insira coeff separados por virgula: ");
    for(int i = 0; i<3; i++)
    {
        scanf("%d,",&input[i]);
    }

    for (j = 0; j < 3; ++j) {
        printf("Input [%d] -> %d\n", j, input[j]);
    }

    /*char temp_str[strlen(input)];*/
    /*temp_str[0] = "0\0";*/


    /*for (j = 0; j < strlen(input); ++j) {*/
        /*if(&input[j] == ",")*/
        /*{*/
            /*m = 0;*/
            /*printf("Virgula em: %d\n",j);*/
            /*printf("Temp_str -> %s\n",temp_str);*/
        /*}*/
        /*else*/
        /*{*/
            /*if(m != 0)*/
            /*{*/
                /*strcat(temp_str, input[j]);*/
            /*}*/
            /*else*/
            /*{*/
                /*temp_str[0] = "0\0";*/
                /*temp_str[0] = input[j];*/
            /*}*/
        /*}*/
    /*}*/
    /*printf("Temp_str -> %s",temp_str);*/


    return(EXIT_SUCCESS);
}
