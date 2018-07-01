/*
@file
Veri yapıları ve Algoritma 1. Ödevi
Linkli liste yapısıyla oluşturulmuş 2 listenin birleşimi ve kesişiminin yazdırılması
@author
Name: Emre Çelik
Student No: 15011902
Date: 04/03/2018
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
#define clear() printf("\033[H\033[J")

typedef struct{
	int value;
	struct NODE *next;
}NODE;

/*
Yeni bir node oluşturur, val ile alınan değeri node'un value değerine yazar.
@val: fonksiyona verilen değer
@pnew: anlık oluşturulan node
*/
NODE *createN(int val){
	NODE *pnew;
	pnew = (NODE*)malloc(sizeof(NODE));
	if(pnew != NULL){
		pnew -> next = NULL;
		pnew -> value = val;
		return pnew;
	}
	else{
		printf("Yer Tutulamadı..\n");
		exit(-1);
	}
}

/*
Attribute olarak verilen listenin sonuna bir node oluşturup onu ekler.
@head: fonksiyona verilen listenin adresi
@val: listenin sonuna gelecek node'un alacağı değer
*/
void add(NODE *head, int val){
	NODE *current = head;

	//Listenin en sonuna gitmek için kullanılan while
	while(current -> next != NULL){
		current = current -> next;
	}
	current -> next = createN(val);
}

/*
Kesişim Listesinin oluşturulduğu fonksiyon
ilk while a ve b listesinde ortak eleman olup olmadığını kontrol eder, var ise createN fonksiyonu
ile C listesini oluşturup ilk değer olarak a ve b listesindeki ortak elemanı değer olarak atarız.
Eğer ortak eleman yoksa "Kesişim Yoktur" denir ve fonksiyondan çıkılır.
Kesişim var ise ve diğer while ile başka kesişim var mı diye A ve B listelerinin sonuna kadar kontrol edilir.
@headATmp: A listesinin başlangıç adresini saklayan geçici değişken
@headBTmp: B listesinin başlangıç adresini saklayan geçici değişken
@tmp: ilk while ın 1 kere dönmesini istiyoruz, onu kontrol etmemizi sağlar
*/
NODE *createListC(NODE *headA, NODE *headB, NODE *headC){
	NODE *headATmp = headA;
	NODE *headBTmp = headB;
	int tmp = 0;

	//a ve b listesinde kesişim var mı kontrol edilir, var ise c listesi oluşturulup değer verilir
	while( (headATmp != NULL) && (headBTmp != NULL) && (tmp == 0) ){
		if(headATmp -> value > headBTmp -> value){
			headBTmp = headBTmp -> next;
		}
		else if(headATmp -> value == headBTmp -> value){
			headC = createN(headATmp -> value);
			headATmp = headATmp -> next;
			headBTmp = headBTmp -> next;
			tmp++;
		}
		else{
			headATmp = headATmp -> next;
		}
	}

	//kesişim yok ise kesişim yoktur denir
	if(headC == NULL){
		printf("Kesişim Yoktur");
	}

	//bir kesişim görülmüşse başka kesişim var mı yok mu kontrol edilir.
	while( (headATmp != NULL) && (headBTmp != NULL) ){
		if(headATmp -> value > headBTmp -> value){
			headBTmp = headBTmp -> next;
		}
		else if(headBTmp -> value > headATmp -> value){
			headATmp = headATmp -> next;
		}
		else{
			add(headC, headATmp -> value);
			headATmp = headATmp -> next;
			headBTmp = headBTmp -> next;
		}
	}
	return headC;
}

/*
A ve B listelerinin Birleşiminin oluşturulduğu fonksiyon
İlk olarak A ya da B listesinden küçük elemanı kullanarak D listesini oluşturup ilk değeri veriyoruz.
A ve B fonksiyonlarının sonuna kadar gidiyoruz.
Eğer ikisinden birisinin sonuna gelmiş isek diğer listeyi sonuna kadar yazdırıyoruz.
@headATmp: A listesinin adresinin anlık olarak sakladığımız yer
@headBTmp: B listesinin adresinin anlık olarak sakladığımız yer
*/
NODE *createListD(NODE *headA, NODE *headB, NODE *headD){
	NODE *headATmp = headA;
	NODE *headBTmp = headB;

	//ilk en küçük değeri alır ve D Listesini oluşturup o değeri veririz
	if( headATmp -> value > headBTmp -> value ){
		headD = createN(headBTmp -> value);
		headBTmp = headBTmp -> next;
	}
	else if(headATmp -> value == headBTmp -> value){
		headD = createN(headATmp -> value);
		headATmp = headATmp -> next;
		headBTmp = headBTmp -> next;
	}
	else{
		headD = createN(headATmp -> value);
		headATmp = headATmp -> next;
	}

	//A ya da B listesinin sonunu görene kadar D listesine eleman atarız
	while( (headATmp != NULL) && (headBTmp != NULL) ){
		if(headATmp -> value > headBTmp -> value){
			add(headD, headBTmp -> value);
			headBTmp = headBTmp -> next;
		}
		else if(headATmp -> value == headBTmp -> value){
			add(headD, headATmp -> value);
			headATmp = headATmp -> next;
			headBTmp = headBTmp -> next;
		}
		else{
			add(headD, headATmp -> value);
			headATmp = headATmp -> next;
		}
	}

	//eğer A ya da B listesinden birisinin sonuna geldiysek diğer listeyi D listesine ekleriz
	if(headATmp == NULL){
		while(headBTmp != NULL){
			add(headD, headBTmp -> value);
			headBTmp = headBTmp -> next;
		}
	}
	else{
		while(headATmp != NULL){
			add(headD, headATmp -> value);
			headATmp = headATmp -> next;
		}
	}
	return headD;
}

//Listeyi bellekten sileriz
void freeList(NODE *head){
	if(head != NULL){
		freeList(head -> next);
		free(head);
	}
}

/*
Attribute den alınan listenin tüm elemanları recrusive olarak yazdıran fonskiyon
*/
void printList(NODE *head){
	if(head != NULL){
		printf("%d -> ", head -> value);
		printList(head -> next);
	}
}

int main(int argc, char const *argv[])
{	
	//Ne olur ne olmaz static tanımladık
	static NODE *headA, *headB, *headC, *headD;
	int choice, tmp, tmp2; 

	//A Dizisinin ilk elemanını alır A dizisini oluşturup ilk elemanını atarız
	printf("A Dizisinin İlk Elemanını Giriniz: ");
	scanf("%d", &tmp);
	headA = createN(tmp);

	//Aynı şekilde B için de yaparız
	printf("B Dizisinin İlk Elemanını Giriniz: ");
	scanf("%d", &tmp);
	headB = createN(tmp);

	clear();

	//Ana menü
	printf("1-) A Dizisine Eleman Ekle\n");
	printf("2-) B Dizisine Eleman Ekle\n");
	printf("3-) Kesişim ve Birleşim Görüntüle\n");
	scanf("%d", &choice);

	clear();
	while(1){
		switch(choice) {
			//A Listesine eleman ekleme bölümü, önce yazdırır sonra değer bekleriz ve ekleriz
      		case 1 :
      			printList(headA);
      			printf("\nValue: ");
      			scanf("%d", &tmp);
      			add(headA, tmp);

         		clear();
         	break;
         	//A Listesine eleman ekleme bölümü, önce yazdırır sonra değer bekleriz ve ekleriz
      		case 2 :
         		printList(headB);
      			printf("\nValue: ");
      			scanf("%d", &tmp);
      			add(headB, tmp);

         		clear();
         	break;
         	//A ve B Dizisini yazdırırız, C ve D Listesini oluşturup yazdırırız.
      		case 3 :
         		printf("A Dizisi: " );
         		printList(headA);
         		printf("\n");

         		printf("B Dizisi: " );
         		printList(headB);
         		printf("\n");

         		printf("C Dizisi: ");
         		printList(createListC(headA, headB, headC));
         		printf("\n");

         		printf("D Dizisi: ");
         		printList(createListD(headA, headB, headD));
         		printf("\n\n");

         		printf("Devam etmek için bir tuşa basınız..");
         		scanf("%d", &tmp2);
         		clear();
         	break;
      		default :
         		printf("Press 0 to Exit\n" );
   		}

   		//Tekrardan Menü yazdırılır.
		printf("1-) A Dizisine Eleman Ekle\n");
		printf("2-) B Dizisine Eleman Ekle\n");
		printf("3-) Kesişim ve Birleşim Görüntüle\n");
		printf("0-) Çıkış\n" );
		scanf("%d", &choice);
		clear();

		//Listeler Sıfırlanır ve Çıkış Yapılır.
		if(choice == 0){
			freeList(headA);
			freeList(headB);
			freeList(headC);
			freeList(headD);
			exit(-1);
		}
	}
	return 0;
}