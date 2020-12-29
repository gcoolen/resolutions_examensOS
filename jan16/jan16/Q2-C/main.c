/*
 * Gregory Coolen - Décembre 2020
 * Examen d'OS Janvier 2016 (Q2 - C)
 * main.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "array_utils.h"
#include <sys/wait.h>
#include <semaphore.h>

#define M1 "matrix1.txt"
#define M2 "matrix2.txt"


#define R 0
#define W 1


int main() {
    int n_1, m_1, n_2, m_2;

    int **mat1 = get_array(M1, &n_1, &m_1);
    int **mat2 = get_array(M2, &n_2, &m_2);
    int **dest = init_array(n_1, m_2);

    for (int i = 0; i < n_1; i++) {
        int line[m_2];
        pid_t pids[m_2];
        int fd[2];
        pipe(fd);
        for (int j = 0; j < m_2; j++) {
            pids[j] = fork();
            if (pids[j] == 0) {
                close(fd[R]);
                int res = calcul_case(mat1, mat2, n_2, i, j);
                int msg[2] = {j, res};
                // transmettre l'indice de colonne car pas sûr que chaque résultat arrive dans l'ordre
                if (write(fd[W], &msg, sizeof(msg)) == -1) printf("writing error\n");
                close(fd[W]);
                exit(0);
            }
        }
        close(fd[W]);
        int x[2];   //reception du résultat
        for (int c = 0; c < m_2; c++) {
            if (read(fd[R], &x, sizeof(x)) == -1) printf("reading error\n");
            line[x[0]] = x[1];
        }
        for (int w = 0; w < m_2; w++) {wait(NULL);} //attendre toutes les cases de la ligne résultat
        memcpy(dest[i], line, m_2* sizeof(int));
        //deepcopy sinon modifie les liges précédentes dans la matrice résultat
        close(fd[R]);
    }
    dsp_mat(n_1, m_2, dest);
    /*
    323 449 262 438
    15 285 30 270
    291 315 230 310
    327 51 238 62
     */
}
