/*
 * Gregory Coolen - Décembre 2020
 * Examen d'OS Janvier 2016 (Q2 - C)
 * array_utils.h
 */


#ifndef Q2_C_ARRAY_UTILS_H
#define Q2_C_ARRAY_UTILS_H

#define ULL unsigned long long
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int** init_array(int N, int M){
    int **temp = (int**)malloc(N * sizeof(int*));
    for(int i = 0; i < N; i++) temp[i] = (int*)malloc(M*sizeof(int));

    return temp;
}

void dsp_mat(int N, int M, int** array){
    printf("---\n");
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
    printf("---");
}

void dsp_array(int M, int* array){
    for(int j = 0; j < M; j++){
        printf("%d ", array[j]);
    }
}

int** get_array(char* path, int* N, int* M){
    FILE* fp =fopen(path, "r");
    char* line = (char*)malloc(1024); size_t buffersize = 1024;

    getline(&line, &buffersize, fp); //getc() sinon
    *N = atoi((const char*)line);   //atoi s'occupe d'ignorer \n
    getline(&line, &buffersize, fp);
    *M = atoi((const char*)line);
    int m = *M, n= *N;

    int **temp = init_array(n, m);

    int size = 0;
    int i = 0, j;
    char* token;
    while(size != EOF && i < n) {
        j = 0;
        size = getline(&line, &buffersize, fp);
        token = strtok(line, " ");
        while (token != NULL && j < m) {
            temp[i][j] = atoi(token);
            token = strtok(NULL, " ");
            j++;
        }
        i++;
    }
    return temp;
}

int calcul_case(int** m1, int** m2, int new_array_lenght, int row_ind, int col_idx){
    int sum = 0;
    for(int i = 0; i < new_array_lenght; i ++) sum += m1[row_ind][i] * m2[i][col_idx];
    return sum;
}

#endif //Q2_C_ARRAY_UTILS_H
