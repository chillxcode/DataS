/*
@file
Veri yapıları ve Algoritma 3. Ödevi
Txt dosyasında bulunan matrisi k kadar gruplara ayırıp gruplar arası en kısa mesafeyi bulan program
@author
Name: Emre Çelik
Student No: 15011902
Date: 29/04/2018
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
/*
düğümleri sakladığımız struct
@a = 1. düğüm
@b = 2. düğüm
@weight = iki düğüm arası uzaklık
*/
typedef struct EDGE{
    int a;
    int b;
    int weight;
}EDGE;

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
int **mallocMatrix(int **matrix, int size){
    matrix = (int **)malloc(size * sizeof(int*));
    for (int row = 0; row < size; row++){
        matrix[row] = (int *)malloc(size * sizeof(int));
    }
    return matrix;
}

/*
Txt dosyasında bulunan matrisin ilk satırını alıp size ını bulan fonksiyon
matrix virgüllerle ayrıldığı için virgül sayısı + 1 dir boyutu deriz
*/
int matrixSize(FILE *file){
    int size = 1;
    int i = 0;
    char tmp[100];
    fscanf(file, "%s", tmp);
    while(tmp[i]){
        if(tmp[i] == ','){
            size++;
        }
        i++;
    }
    //fonksiyondan çıkmadan önce file pointer'ı sıfırlarız
    fseek(file, 0, SEEK_SET);
    return size;
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
verilen array'i realloc yapan fonksiyon
*/
EDGE *reallocArray(EDGE *edgeArray, int size){
    edgeArray = realloc(edgeArray, size);
    if(!edgeArray){
        exit(-1);
    }
    return edgeArray;
}

/*
Matrix in üst üçgenini tarar, 0'dan farklı uzaklığı ulan edgeleri edgeArray'e kaydeder.
@edgeArray = köşelerin tutulduğu array
@**matrix = txt dosyasından çekilen array
@size = matrix size'ı
@sizeArr = fonksiyondan 2 değer döndürmek için yapılmıştır. Edge sayısını saklar
*/
EDGE *createEdgeArray(EDGE *edgeArray, int **matrix, int size, int *sizeArr){
    int i, j;
    //ilk başta edge'miz yok
    int sizeArray = 0;
    //matrixin uzunluğu kadar
    for (i = 0; i < size; i++){ 
        //git dige üst üçgen olacak şekilde
        for (j = i; j < size; j++){ 
            //matrix[i][j] 0 dan farklıysa
            if ( !(i == j) && (matrix[i][j] != 0) ){
                //edgeArray e ilk değer eklerken realloc yapmamamız için gereken kontrol
                if (sizeArray != 0){
                    edgeArray = (EDGE *)realloc(edgeArray, sizeof(EDGE) * (sizeArray + 1) );
                }
                edgeArray[sizeArray].a = i;
                edgeArray[sizeArray].b = j;
                edgeArray[sizeArray].weight = matrix[i][j];
                sizeArray++;
            }
        }
    }
    //fonksiyondan 2 return yapıyoruz
    *sizeArr = sizeArray;
    return edgeArray;
}

//edgeArray'i boyutu kadar bastırıyoruz
//@sizeArray = edgeArray'in boyutu
void printEdgeArray(EDGE *edgeArray, int sizeArray){
    int i;
    for (i = 0; i < sizeArray; i++){
        printf("[%d %d] = %d\n", edgeArray[i].a, edgeArray[i].b, edgeArray[i].weight);
    }
}

//Grupların olduğu clusterArray'i yazdırdığımız fonksiyon, kullandığımız ifler düzgün yazdırmak amacıyla kullanıldı
void printClusterArray(int *clusterArray, int size){
    int i;
    printf("Cluster Array\n");
    for(i = 1; i < size; i++){
        if (i > 9){
            printf("%d ", i);
        }
        else{
            printf(" %d ", i);
        }
        
    }
    printf("\n");
    for (i = 0; i < size; i++){
            if (clusterArray[i] > 9){
                printf("%d ", clusterArray[i]);
            }
            else{
                printf(" %d ", clusterArray[i]);
            }
    }
    printf("\n");
}

/*
edgeArray'imizi nodeların birbirlerine olan uzaklığına göre küçükten büyüğe göre sıralayan fonksiyon
*/
void bubbleSort(EDGE *edgeArray, int sizeArray){
    EDGE tmp;
    int i, j;
    for (i = 0; i < sizeArray - 1; i++){
        for (j = 0; j < sizeArray - i - 1; j++){
            if (edgeArray[j].weight > edgeArray[j+1].weight){
                tmp.a = edgeArray[j].a;
                tmp.b = edgeArray[j].b;
                tmp.weight = edgeArray[j].weight;

                edgeArray[j].a = edgeArray[j+1].a;
                edgeArray[j].b = edgeArray[j+1].b;
                edgeArray[j].weight = edgeArray[j+1].weight;

                edgeArray[j+1].a = tmp.a;
                edgeArray[j+1].b = tmp.b;
                edgeArray[j+1].weight = tmp.weight;
            }
        }
    }
}

/*
Nodeların gruplandığı fonksiyon. Kullanıcıdan alınan k değeri kadar nodeları yakınlıklarına göre gruplar
@clusterArray = matrix size'ı kadar boyutu bulunan, nodeların grup isimlerini saklayan array
@edgeArray = edgelerin saklandığı array
@size = matrix boyutu
@totalEdge = toplam edge sayısı
@k = kullanıcıdan aldığımız grup sayısı
@clusterNumber = anlık grup sayısı
*/
int *kruskalAlg(int *clusterArray, EDGE *edgeArray, int size, int totalEdge, int k){
    int i = 0, clusterNumber = size, j, tmp;
    while( (clusterNumber >  k) && (i < totalEdge) ){
        //eğer edge[i] nin ilk nodu ve 2. nodu aynı ise
        if ( clusterArray[edgeArray[i].a] == clusterArray[edgeArray[i].b] ){
            //eğer edge[i] nin ilk nodu ve 2. nodu 0 ise; zaten aynı gruptaysalar işlem yapmayız zaten
            if ( ( clusterArray[edgeArray[i].a] == 0 ) && ( clusterArray[edgeArray[i].b] == 0) ){
                clusterArray[edgeArray[i].a] = edgeArray[i].a + 1;
                clusterArray[edgeArray[i].b] = edgeArray[i].a + 1;
                clusterNumber--;
            }
        }
        //eğer edge[i] nin ilk nodu ve 2. nodu farklı ise
        else{
            tmp = clusterArray[edgeArray[i].b];
            //ilk node bir sayı fakat 2. node 0; 2. nodu ilk nodun grubuna alıyoruz
            if (tmp == 0){
                clusterArray[edgeArray[i].b] = clusterArray[edgeArray[i].a];
                clusterNumber--;
            }
            //ilk node 0 fakat 2. node'un bir grubu var; ilk node'u 2. node'un grubuna alıyoruz
            else if( (tmp != 0) && (clusterArray[edgeArray[i].a] == 0) ){
                clusterArray[edgeArray[i].a] = clusterArray[edgeArray[i].b];
                clusterNumber--;
            }
            //iki node'un da kendi grupları var; 2. node'un grubunu ilk node'un grubuna dahil ediyoruz, for ile dönüyoruz
            else{
                for (j = 0; j < size; j++){
                    if ( ( clusterArray[j] != 0 ) && (clusterArray[j] == tmp ) ){
                        clusterArray[j] = clusterArray[edgeArray[i].a];
                    }
                }
                clusterNumber--;
            }
        }
        i++;
    }
    //kullanıcıdan alınan değer kadar grup oluşturduk ama açıkta kalan node'ların ileride karışmaması adına 0 olan değerlerini node ismi olarak değiştiriyoruz
    //eğer açıkta kalan node 0. node olma ihtimaline karşı node ismi +1 yapıyoruz
    for (i = 0; i < size; i++){
        if(clusterArray[i] == 0){
            clusterArray[i] = ( i + 1 );
        }
    }
    return clusterArray;
}

/*
clusterArray'de oluşturular gruplar arası en kısa mesafeyi bulurken kullanırız
bu fonksiyonun işi distanceArrayde hali hazırda en kısa mesafeyi bulmuş muyuz kontrol eden fonksiyon
eğer distanceArrayde gruplar zaten bağlanmışsa return 0 yapacaktır; aksi halde bulamazsa return 1
@distanceArray = clusterArrayde oluşturulan grupların birbirlerine olan uzaklıkları saklayan dizi
@sizeTmpArray = distance array in boyutu
@i = edge arrayden kontrol ederken hangi edge deyiz onu saklayan değişken
*/
int doesHave(EDGE *distanceArray, int *clusterArray, EDGE *edgeArray, int sizeTmpArray, int i){
    int j = 0;
    //ilk distanceArray değerini findDistance fonksiyonunda girdiğimiz için while a girer, sıkıntı yaşamayız
    while( j < sizeTmpArray ){
        //elimizde iki grup olsun 5 ve 12. grup, bu grup 2 şekilde bağlanabilir, (5 12) ve (12 5) diye
        //bu if de distanceArray de (5 12) var mı diye kontrol ediyoruz
        if( (distanceArray[j].a == clusterArray[edgeArray[i].a]) && (distanceArray[j].b == clusterArray[edgeArray[i].b]) ){
            return 0;
        }
        //burada ise distanceArray de (12 5) var mı diye kontrol ediyoruz
        else if((distanceArray[j].a == clusterArray[edgeArray[i].b]) && (distanceArray[j].b == clusterArray[edgeArray[i].a])){
            return 0;
        }
        j++;
    }
    return 1;
}

/*
clusterArrayde olan gruplanmış node ları, edgeArray de gruplarına göre kontrol edip en kısa mesafeyi bulan fonksiyon
@distanceArray = clusterArrayde oluşturulan grupların birbirlerine olan uzaklıkları saklayan dizi
@clusterarray = nodeların gruplara ayrılmış olduğu array
@edgeArray = edgelerin saklandığı array
@size = matrix size ı
@totalEdge = edgeArray'in boyutu
@k = kullanıcıdan alınan grup sayısı 
@maxSizeOfEdge = k kadar grubun en fazla k * (k - 1) / 2 adet bağlantısı olabilir
@sizeTmpArray = distanceArray indisini saklayan değişken
*/
EDGE *findDistance(EDGE *distanceArray, int *clusterArray, EDGE *edgeArray, int size,int totalEdge, int k){
    int i, j = 0;
    int maxSizeOfEdge = (k * (k - 1) / 2 );
    int sizeTmpArray = 0;
    //distanceArray'i mallocladık, en fazla olabilecek bağlantı sayısı kadar
    distanceArray = (EDGE *)malloc(maxSizeOfEdge * sizeof(EDGE));
    //mallocladığımız distanceArray'i sıfırlıyoruz; neden calloc yapmadım ?, sonradan aklıma geldi, kod çalışıyorken ellemek istemedim
    for (i = 0; i < maxSizeOfEdge; i++){
        distanceArray[i].a = 0;
        distanceArray[i].b = 0;
        distanceArray[i].weight = 0;
    }
    i = 0;
    //max bağlantı sayısına kadar ve toplam edge sayısına kadar döner
    while( (sizeTmpArray < maxSizeOfEdge) && (i < totalEdge) ){
        //nodelar aynı grupta değilseler true olur
        if( clusterArray[edgeArray[i].a] != clusterArray[edgeArray[i].b] ){
            //eğer ekleyeceğimiz değer distanceArray'in ilk değeriyse ilk değeri burada atarız
            if (sizeTmpArray == 0){
                distanceArray[sizeTmpArray].a = clusterArray[edgeArray[i].a];
                distanceArray[sizeTmpArray].b = clusterArray[edgeArray[i].b];
                distanceArray[sizeTmpArray].weight = edgeArray[i].weight;
                printf("Nodes = (%d %d), Clusters = {%d %d}, Distance = %d\n", edgeArray[i].a, edgeArray[i].b, clusterArray[edgeArray[i].a], clusterArray[edgeArray[i].b], edgeArray[i].weight);
                sizeTmpArray++;
            }
            //ilk değer değilse, doesHave fonksiyonuyla ekleyeceğimiz bağlantı distance arrayde var mı onu kontrol ederiz, yoksa ekleriz, varsa eklemeyiz
            if( doesHave(distanceArray, clusterArray, edgeArray, sizeTmpArray, i) ){
                distanceArray[sizeTmpArray].a = clusterArray[edgeArray[i].a];
                distanceArray[sizeTmpArray].b = clusterArray[edgeArray[i].b];
                distanceArray[sizeTmpArray].weight = edgeArray[i].weight;
                printf("Nodes = (%d %d), Clusters = {%d %d}, Distance = %d\n", edgeArray[i].a, edgeArray[i].b, distanceArray[sizeTmpArray].a, distanceArray[sizeTmpArray].b, distanceArray[sizeTmpArray].weight);
                sizeTmpArray++;
            }
        }
        j = 0;
        i++;
    }
    //en sonda distanceArray'i yazdırıyoruz
    printf("\nDistance Array\n");
    for (i = 0; i < sizeTmpArray; i++){
        printf("[%d %d] = %d\n", distanceArray[i].a, distanceArray[i].b, distanceArray[i].weight);
    }
    return distanceArray;
}



int main(int argc, const char * argv[]) {
    FILE *file;
    int **matrix;
    int size, k;
    int *clusterArray;
    EDGE *edgeArray = (EDGE *)malloc(sizeof(EDGE));
    EDGE *distanceArray;
    int totalEdge, i;

    printf("Cluster Size = ");
    scanf("%d", &k);

    file = fileOpen("data.txt", "r");

    //matrix'in boyutunu bulan fonksiyon
    size = matrixSize(file);

    //bulunan matrix boyutuna göre kümeleri tutan array'i mallocluyoruz
    clusterArray = (int *)malloc(size * sizeof(int));

    //clusterArray'i sıfırlıyoruz
    for (i = 0; i < size; i++){
        clusterArray[i] = 0;
    }

    //txtden alacağımız matrix i matrix değişkenine almak için mallocluyoruz
    matrix = mallocMatrix(matrix, size);

    //matrix i txtden alınan matrixe aktarıyoruz
    matrix = createMatrix(file, matrix, size);

    //aldığımız matrix'i yazdırıyoruz
    printMatrix(matrix, size); //                    

    printf("Matrix Size = %d\n", size);

    //matrixde bulunan edgeleri edgeArray e aktarıyoruz
    edgeArray = createEdgeArray(edgeArray, matrix, size, &totalEdge);

    printEdgeArray(edgeArray, totalEdge); //

    printf("----------------------------------------------------------\n"); //

    bubbleSort(edgeArray, totalEdge);

    //küçükten büyüğe sıralanmış edgeArray'i yazdırıyoruz
    printEdgeArray(edgeArray, totalEdge);

    printf("---Total Edge = %d---\n", totalEdge); //


    //kruskal yapılmamış grup arrayini yazdırıyoruz
    printClusterArray(clusterArray, size);

    printf("-------------------------------------------------------------------------------\n");

    //clusterArrayine gruplama yapıyoruz kruskal ile
    clusterArray = kruskalAlg(clusterArray, edgeArray, size, totalEdge, k);

    printClusterArray(clusterArray, size);

    printf("-------------------------------------------------------------------------------\n");

    //gruplar arası en kısa mesafeleri buluyoruz
    distanceArray =  findDistance(distanceArray, clusterArray, edgeArray, size, totalEdge, k);

    //freeleme işlemleri
    free(edgeArray);
    free(clusterArray);
    for (int i = 0; i < size; i++){
        free(matrix[i]);
    }
    free(matrix);
    fclose(file);
    return 0;
}