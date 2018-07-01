/*
@file
Veri yapıları ve Algoritma 4. Ödevi
Txt dosyasından alınan matrixde Depth First Search Algoritması kullanarak en kısa yolu bulma
@author
Name: Emre Çelik
Student No: 15011902
Date: 20/05/2018
E-mail: emrecelikk97@gmail.com
Complier Used: GCC 4.2.1 Apple LLVM Version 9.0.0 
IDE:
Operating System: MacOS Sierra
CPU: 1.6 GHz Intel Core i5
RAM: 8 GB 1600 MHz DDR3
Video Card: Intel HD Graphics 6000 1536 MB€
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>

//eğer gideceğimiz yere ulaşım bulabildik mi onu saklarız
bool found = false;
//Kullanıcıdan başlangıç konumu alırız, başlangıç konumunu saklarız
int xStart = 1;
int yStart = 1;

FILE *fileOpen(const char *name, const char *type){
    FILE *tmp;
    tmp = fopen(name, type);
    if(tmp==NULL){
        exit(-1);
    }
    return tmp;
}

/*
matrixi oluşturduğumuz fonksiyon
*/
char **mallocMatrix2(char **matrix, int size) {
    matrix = (char **)malloc(size * sizeof(char*));
    for (int row = 0; row < size; row++){
        matrix[row] = (char *)malloc(size * sizeof(char));
    }
    return matrix;
} 

/*
matrixi oluşturduğumuz fonksiyon
*/
int **mallocMatrix(int **matrix, int size){
    matrix = (int **)malloc(size * sizeof(int*));
    for (int row = 0; row < size; row++){
        matrix[row] = (int *)malloc(size * sizeof(int));
    }
    return matrix;
}

/*
Txt dosyasından çektiğimiz matrisi yazdıran fonksiyon
*/
void printMatrix(int **matrix, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

/*
Ekrana yazılacak matrisi yazdıran fonksiyon
*/
void printMatrix2(char **matrix, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

/*
Ekrana yazılacak matrisin oluşturulduğu bölüm
*/
char **createMatrix2(int **matrix, char **matrix2, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (i % 2 == 0){
                if (j % 2 == 0){
                    if (matrix[i][j] != 0){
                        matrix2[i][j] = ' ';
                    }else{
                        matrix2[i][j] = '+';
                    }
                }
                else{
                    if (matrix[i][j] != 0){
                        matrix2[i][j] = ' ';
                    }else{
                        matrix2[i][j] = '-';
                    }
                }
            }
            else{
                if (j % 2 == 0){
                    if (matrix[i][j] != 0){
                        matrix2[i][j] = ' ';
                    }else{
                        matrix2[i][j] = '|';
                    }
                }
                else{
                    matrix2[i][j] = ' ';
                }
            }
        }
    }
    return matrix2;
}
/*
Depth First Search Algoritması kullanıldı.
Sırasıyla komşulara bakıldı, eğer gidilebiliyorsa fonskiyon yinelemeli olarak 
kendini çağırdı ve hedeflenen noktaya gitmeye çalışıldı
Eğer ulaşıldıysa found değişkeni true oldu ve fonksyon rekürsif olarak en kısa yolu I ile işaretledi
input dosyasında duvarlar 0 ile
yollar 1 ile
odacıklar 2 ile
gidilecek yer ise 5 ile işaretlenmiştir.
*/
char **DFSMatrix(int **matrix, char **matrix2, int x, int y){
    matrix2[x][y] = 'x';
    printf("[%d][%d]\n", x, y);

    if (matrix[x][y] == 5){
        found = true;
    }
    if ( (found != true) && (matrix[x][y-1] == 1 ) ){ //Yukarı
        if ((matrix2[x][y-2] != 'x' )){
            DFSMatrix(matrix, matrix2, x, y-2); 
        }
    }
    if ( (found != true) && (matrix[x+1][y] == 1 ) ){ //Sağ
        if ((matrix2[x+2][y] != 'x' )){
            DFSMatrix(matrix, matrix2, x+2, y); 
        }
    }
    if ( (found != true) && (matrix[x][y+1] == 1 ) ){ //Aşağı
        if ((matrix2[x][y+2] != 'x' )){
            DFSMatrix(matrix, matrix2, x, y+2); 
        }
    }
    if ( (found != true) && (matrix[x-1][y] == 1 ) ){ //Sola
        if ((matrix2[x-2][y] != 'x' )){
            DFSMatrix(matrix, matrix2, x-2, y); 
        } 
    }
    
    
    if (found){
        matrix2[x][y] = 'I'; 
        printf("{%d}{%d}\n", x, y);
    }
    if (matrix[x][y] == 5){
        found = true;
        matrix2[x][y] = 'X'; 
    }
    return matrix2;
} 

/*
Txt dosyasında olan matrix virgüllerden ayrılarak **matrix e aktarılır
*/
int **createMatrix(FILE *file, int **matrix,int size){
    char tmp[100];
    int input[100];
    char *token;
    char seps[] = ",";
    int var, i = 0, j;

    for (j = 0; j < size; j++){
        fscanf(file, "%s", tmp);
        token = strtok  (tmp, seps);
        while (token != NULL){
            sscanf (token, "%d", &var);
            input[i++] = var;
            token = strtok (NULL, seps);
        }
        for (i = 0; i < size; i++){
            matrix[j][i] = input[i];
        }
        i = 0;
    }
    return matrix;
}

/*
Depth First Search ile oluşturduğumuz matrisde x ile taradığımız alan işaretlenmiştir
eğer sadece en kısa yolu görmek istiyorsak matrixi x lerden temizlemeliyiz.
Matrix i x lerden temizlemek için kullanırız.
*/
char **clearXFromMatrix(char **matrix, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if ( matrix[i][j] == 'x' ){
                matrix[i][j] = ' ';
            }
        }
    }
    return matrix;
}

int main(int argc, char const *argv[]){
    FILE *file;
    int **matrix;
    char **matrix2;
    int size = 11;
    printf("Size = ");
    scanf("%d", &size);
    printf("X Ekseni = ");
    scanf("%d", &xStart);
    printf("Y Ekseni = ");
    scanf("%d", &yStart);
    file = fileOpen("input.txt", "r");

    matrix = mallocMatrix(matrix, size);

    matrix = createMatrix(file, matrix, size);

    //printMatrix(matrix, size);

    matrix2 = mallocMatrix2(matrix2, size);
    
    matrix2 = createMatrix2(matrix, matrix2, size);

    matrix2 = DFSMatrix(matrix, matrix2, xStart, yStart);

    //matrix2 = clearXFromMatrix(matrix2, size);

    matrix2[xStart][yStart] = '*';

    printMatrix2(matrix2, size);
    
    return 0;
}