/*
@file
Veri yapıları ve Algoritma 2. Ödevi
txt dosyasında sıralı bulunan (1,2,3...) listenin Binary Search Tree ile oluşturulup yazdırılması
@author
Name: Emre Çelik
Student No: 15011902
Date: 01/04/2018
E-mail: emrecelikk97@gmail.com
Complier Used: GCC 4.2.1 Apple LLVM Version 9.0.0 
IDE:
Operating System: MacOS Sierra
CPU: 1.6 GHz Intel Core i5
RAM: 8 GB 1600 MHz DDR3
Video Card: Intel HD Graphics 6000 1536 MB*
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct NODE{
	int value;
	struct NODE *left;
 	struct NODE *right;
}NODE;

//File Open İşlemleri
FILE *fileOpen(const char *name, const char *type){
	FILE *tmp;
	tmp = fopen(name, type);
	if(tmp == NULL){
		exit(1);
	}
	return tmp;
}

//Yeni bir Node oluşturulup return olarak döndürülmesi
NODE *CreateNode(int value){
	struct NODE *node = (NODE*)malloc(sizeof(NODE));
	node -> value = value;
	node -> left = NULL;
	node -> right = NULL;
	return node;
}

/*
arrayi git gide küçük parçalar haline bölüp işlem yapıyoruz.
.........................
            ^
            |
Buradan böldük mid ini bulduk, sonra kalan 2 parçayı da elimizde 1 eleman kalana kadar böldük
tek parça kalınca da malloc ile yeni bir NODE oluşturup birbirine ekledik
@array: txt dosyasından çekilmiş integer arrayimiz
@start: arrayimizin ilk elemanı
@end: arrayimizin sonunu tutan değişken
*/
NODE *sortedArrayToBST(int *array, int start, int end){
	if (start > end)
	{
		return NULL;
	}
	int mid = (start + end) / 2;
	NODE *root = CreateNode(array[mid]);

	root -> left = sortedArrayToBST(array, start, mid - 1);
	root -> right = sortedArrayToBST(array, mid + 1, end);

	return root;
}

//İnorder olarak yazdırılma 
void inOrder(NODE *root){
	if(root){
		inOrder(root -> left);
		printf("%d ", root -> value);
		inOrder(root -> right);
	}
}

//Preorder olarak yazdırılma
void preOrder(NODE *root){
	if(root){
		printf("%d ", root -> value);
		preOrder(root -> left);
		preOrder(root -> right);
	}
}

//Postorder olarak yazdırılma
void postOrder(NODE *root){
	if(root){
		postOrder(root -> left);
		postOrder(root -> right);
		printf("%d ", root -> value);
	}
}

/*
@tmp: txtden veri çekerken anlık olarak kullandığımız dizi
@seps: tmpde bulunan veriyi ',' lerden parçalamak istedik
@token: strtok fonksiyonu için kullanılan değişken
@sayac: dizimize kaç eleman eklediğimizi sayan sayac
@input: ','lerden ayrılmış dizimiz
*/
int main(){
	setlocale(LC_ALL, "Turkish"); 
	FILE *file;
	char fileName[] = "input1.txt";
	char tmp[100];
	NODE *node = malloc(sizeof(NODE));

	char seps[] = ",";
	char* token;
	int var;
	int input[100];
	int i = 0;
	int sayac = 0;

	file = fileOpen("input1.txt", "r");
	fscanf(file, "%s", tmp);
	printf("%s\n", tmp);

	token = strtok  (tmp, seps);
	while (token != NULL){
    	sscanf (token, "%d", &var);
    	input[i++] = var;
    	token = strtok (NULL, seps);
    	sayac++;
	}

	node = sortedArrayToBST(input, 0, sayac-1);
	printf("(LNR)inorder:   ");
	inOrder(node);
	//printf("\n");

	printf("\n(LRN)postorder: ");
	postOrder(node);
	//printf("\n");

	printf("\n(NLR)preorder:  ");
	preOrder(node);
	printf("\n");

	fclose(file);
	return 0;
}