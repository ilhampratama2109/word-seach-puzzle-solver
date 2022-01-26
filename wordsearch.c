#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<time.h>

#define ROWS 100
#define COLS 100
#define MAXWORD 100

void InitMatched(int match[ROWS][COLS]){
    /*digunakan untuk inisialisasi matrik untuk matched, elemen diisi dengan 0 */
    int i, j;
    for(i = 0 ; i < ROWS ; i++){
        for(j = 0 ; j < COLS; j++){
            match[i][j] = 0;
        }
    }
}

void Max(int current, int *max){
    // menentukan bilangan yang terbesar antara 2 bilangan
    if(current > *max){
        *max = current;
    }
}

int WordLen(char *word){
    // mencari panjang dari Word
    int i;
    for (i = 0 ; word[i] != '\0'; i++){}
    i--;
    return i;
}


void Strip(char* word){
    // mengupas string di word
    int i;
    for(i = 0 ; word[i] != '\0'; i++){
        if(word[i] == '\n'){
            word[i] = '\0';
        }
    }
}


int main(){
    char puzzle[ROWS][COLS];
    int match[ROWS][COLS];
    char words[MAXWORD][COLS];
    char cc;
    int row = 0;
    int col = 0;
    int maxcol = 0;
    int numword = 0;
    int i,j,k,l;
    FILE *puzzlefile;
    FILE *keysearch;
    double time_spend = 0.0;
    int jumlah_banding_kata = 0;
    
    // perhitungan waktu dimulai
    clock_t begin = clock();
    /*inisialisasi matcher*/
    InitMatched(match);
    puzzlefile = fopen("puzzle9.txt", "r");
    if (puzzlefile == NULL){
        printf("gagal membuka file, periksa dulu apakah file yang anda masukkan benar \n");
        return 0;
    }

    while(!feof(puzzlefile)){
        cc = fgetc(puzzlefile);
        if(cc == '\n'){
            row++;
            col = 0;
        }else if(isalnum(cc)){
            puzzle[col][row] = toupper(cc);
            col++;
            Max(col,&maxcol);
        }
    }

    keysearch = fopen("key9.txt", "r");
    if(keysearch == NULL){
        printf("tidak ada kata yang akan dicari\n");
        return 0;
    }
    while(!feof(keysearch)){
        fgets(words[numword], 100, keysearch);
        Strip(words[numword]);
        numword++;
    }
    numword--;

    /*algoritma matching */
    for(i = 0 ; i < numword; i++){
        for(k = 0 ; k < row; k++){
            for(j = 0; j < maxcol; j++){
                if(puzzle[j][k] == words[i][0]){
                    if(maxcol > (WordLen(words[i])+ j)){
                        for(l = 0; words[i][l] == puzzle[j+l][k]; l++){
                            if(words[i][l+1] == '\0'){
                                for(l = 0; words[i][l] == puzzle[j+l][k]; l++){
                                    match[j+l][k] = 1;
                                    jumlah_banding_kata++;
                                }
                                break;
                            }else{
                                jumlah_banding_kata++;
                            }
                        }
                        if (row > (WordLen(words[i]) + k)) {	
                            for(l=0; words[i][l] == puzzle[j+l][k+l]; l++) {
                                if(words[i][l+1]=='\0') {
                                    for(l=0; words[i][l] == puzzle[j+l][k+l]; l++)
                                        match[j+l][k+l] = 1;
                                        jumlah_banding_kata++;
                                    break;
                                }else{
                                    jumlah_banding_kata++;
                                }
                            }
                        }
                        if (0 <= (k - WordLen(words[i]))) {
                            for(l=0; words[i][l] == puzzle[j+l][k-l]; l++){
                                if(words[i][l+1]=='\0') {
                                    for(l=0; words[i][l] == puzzle[j+l][k-l]; l++)
                                        match[j+l][k-l] = 1;
                                        jumlah_banding_kata++;
                                    break;
                                }else{
                                    jumlah_banding_kata++;
                                }
                            }
                        }
                    }
                    if (0 <= (j - WordLen(words[i]))){
                        for(l=0; words[i][l] == puzzle[j-l][k]; l++) {
                            if(words[i][l+1]=='\0') {
                                for(l=0; words[i][l] == puzzle[j-l][k]; l++)
                                    match[j-l][k] = 1;
                                    jumlah_banding_kata++;
                                break;
                            }else{
                                jumlah_banding_kata++;
                            }
                        }
                        if (row > (WordLen(words[i]) + k)) {
                            for(l=0; words[i][l] == puzzle[j-l][k+l]; l++) {
                                if(words[i][l+1]=='\0') {
                                    for(l=0; words[i][l] == puzzle[j-l][k+l]; l++)
                                        match[j-l][k+l] = 1;
                                        jumlah_banding_kata++;
                                    break;
                                }else{
                                    jumlah_banding_kata++;
                                }
                            }
                        }
                        if (0 <= (k - WordLen(words[i]))) {
                            for(l=0; words[i][l] == puzzle[j-l][k-l]; l++) {
                                if(words[i][l+1]=='\0') {
                                    for(l=0; words[i][l] == puzzle[j-l][k-l]; l++)
                                        match[j-l][k-l] = 1;
                                        jumlah_banding_kata++;
                                    break;
                                }else{
                                    jumlah_banding_kata++;
                                }
                            }
                        }
                    }
                    if (row > (WordLen(words[i]) + k)) {
                        for(l=0; words[i][l] == puzzle[j][k+l]; l++) {
                            if(words[i][l+1]=='\0') {
                                for(l=0; words[i][l] == puzzle[j][k+l]; l++)
                                    match[j][k+l] = 1;
                                    jumlah_banding_kata++;
                                break;
                            }else{
                                jumlah_banding_kata++;
                            }
                        }
                    }
                    if (0 <= (k - WordLen(words[i]))){
                    for(l=0; words[i][l] == puzzle[j][k-l]; l++) {
                            if(words[i][l+1]=='\0') {
                                for(l=0; words[i][l] == puzzle[j][k-l]; l++)
                                    match[j][k-l] = 1;
                                    jumlah_banding_kata++;
                                break;
                            }else{
                                jumlah_banding_kata++;
                            }
                        }
                    }
                }
            }
        }
    }

    clock_t end = clock();

    for (k = 0; k < row; k++) {
        for (j = 0; j < maxcol; j++){
            if (match[j][k] == 1){
                printf("%c ", puzzle[j][k]);
            }else {
                printf("- ");
            }
        }
        printf("\n");
    }

    time_spend = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("waktu yang dibutuhkan untuk pencarian kata adalah:\n%f detik\n", time_spend );
    printf("jumlah kata yang dibandingkan adalah : %d", jumlah_banding_kata);
    return 0;
}