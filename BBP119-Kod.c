/*

Proje

Ders: BBP119 - Programlama Temelleri - 1 

Ogrenci Isim: Emir Huseyin Zenginoglu
Ogrenci No: 220111565

ATM Programi
Icindekiler
-Hesap olusturma, giris, cikis
-Para Yatirma
-Para Cekme
-Bakiye Sorgulama
-Para transferi

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAKS_HESAP_SAYISI 10
#define MAKS_SIFRE_BOYUT 10

//Struct yapisini diziler gibi düsünebilirsiniz. Bir degiskene birden fazla ve farkli türde deger girilmesini saglar.
//Typedef yeni degisken olusturur. Hesap adinda bir veri turu olusuturup hesaplar adindaki 10 dizili degisken olusturuyoruz.
typedef struct {
  char isim[50];
  char sifre[MAKS_SIFRE_BOYUT + 1];
  float bakiye;
} Hesap;

Hesap hesaplar[MAKS_HESAP_SAYISI];
int hesapSayisi = 0;

int anaMenu() {
  int secim;
  printf("ATM'ye Hosgeldiniz!\n");
  printf("Hesap olusturmak icin (1)\n");
  printf("Giris yapmak icin (2)\n");
  printf("Cikis yapmak icin (3)\n");
  printf("Seciminizi girin: ");
  scanf("%d", &secim);
  return secim;
}

void hesapOlustur() {
	int i;
  	if (hesapSayisi == MAKS_HESAP_SAYISI) {
    	printf("Uzgunuz, hesap olusturma limitini astiniz.\n");
    	printf("Limit = %d\n", MAKS_HESAP_SAYISI);
    	return;
  	}

  	char isim[50];
  	printf("Isminizi girin: ");
  	scanf("%s", &isim);

  	for (i = 0; i < hesapSayisi; i++) {
  		//strcmp fonksiyonu otomatik olarak gosterilen degiskenleri ayni degere sahip olup olmadiklarini kontrol eder
    	if (strcmp(isim, hesaplar[i].isim) == 0) {
      		printf("Bu isim kullanimda lutfen farkli bir isim deneyin.\n");
      		sleep(2);
      		return;
    	}
  	}
  
  	//strcpy fonksiyonu, tam olarak olmasada "1. degisken = 2. degisken" olarak düsünebilirsiniz
  	//kisaca 2. degisken 1. degiskene esitleniyor
  	strcpy(hesaplar[hesapSayisi].isim, isim);

  	printf("Sifre girin (maksimum %d karakter): ", MAKS_SIFRE_BOYUT);
  	scanf("%s", hesaplar[hesapSayisi].sifre);

  	hesaplar[hesapSayisi].bakiye = 0;
  	hesapSayisi++;
	sleep(1);
  	printf("Hesabiniz basarili bir sekilde olusturuldu!\n");
  	sleep(2);
}

int hesapGiris() {
	int i;
  	char isim[50];
  	char sifre[MAKS_SIFRE_BOYUT + 1];

  	printf("Isminizi girin: ");
  	scanf("%s", isim);

  	printf("Sifrenizi girin: ");
  	scanf("%s", sifre);

  	for (i = 0; i < hesapSayisi; i++) {
    	if (strcmp(isim, hesaplar[i].isim) == 0 && strcmp(sifre, hesaplar[i].sifre) == 0) {
  			sleep(1);
  			printf("Hesaba giris yapildi.\n");
      		return i;
    	}	
  	}

  	printf("Yanlis isim veya sifre.\n");
  	sleep(2);
  	return -1;
}

int hesapGirisMenusu() {
  	int secim;
  	printf("Bakiye kontrol icin (1)\n");
  	printf("Para cekmek icin (2)\n");
  	printf("Para yatirmak icin (3)\n");
  	printf("Para transfer icin (4)\n");
  	printf("Hesaptan cikis yapmak icin (5)\n");
  	printf("Seciminizi girin: ");
  	scanf("%d", &secim);
  	return secim;
}

void bakiyeKontrol(int mevcutHesap) {
  	printf("Bakiyeniz: %.2f TL\n", hesaplar[mevcutHesap].bakiye);
  	sleep(3);
}

void paraCek(int mevcutHesap) {
  	float miktar;
  	printf("Cekmek istediginiz miktari girin: ");
  	scanf("%f", &miktar);
  	sleep(1);
  	if (miktar > hesaplar[mevcutHesap].bakiye) {
	  	sleep(1);
	    printf("Yetersiz bakiye.\n");
	  	sleep(2);   
	    return;
  	}

	hesaplar[mevcutHesap].bakiye -= miktar;
	printf("Cekilen miktar: %.2f TL\n", miktar);
  	sleep(2);
  	sleep(1);
	printf("Mevcut bakiyeniz: %.2f TL\n", hesaplar[mevcutHesap].bakiye);
	sleep(2);
}

void paraYatir(int mevcutHesap) {
  float miktar;
  printf("Yatirmak istediginiz miktari girin: ");
  scanf("%f", &miktar);
  sleep(1);
  hesaplar[mevcutHesap].bakiye += miktar;
  printf("Yatirilan miktar: %.2f TL\n", miktar);
  sleep(2);
  sleep(1);
  printf("Mevcut bakiyeniz: %.2f TL\n", hesaplar[mevcutHesap].bakiye);
  sleep(2);
}

void paraAktarma(int mevcutHesap) {
	int i;
  char alici[50];
  float miktar;

  printf("Gonderilecek hesabin ismini girin: ");
  scanf("%s", &alici);

  int aliciNo = -1;
  for (i = 0; i < hesapSayisi; i++) {
    if (strcmp(alici, hesaplar[i].isim) == 0) {
      aliciNo = i;
      break;
    }
  }

  if (aliciNo == -1) {
    printf("Boyle bir hesap bulunmamaktadir.\n");
    sleep(2);
    return;
  }

  printf("Gonderilecek miktari girin: ");
  scanf("%f", &miktar);

  if (miktar > hesaplar[mevcutHesap].bakiye) {
    printf("Yetersiz bakiye.\n");
    sleep(2);
    return;
  }

  hesaplar[mevcutHesap].bakiye -= miktar;
  hesaplar[aliciNo].bakiye += miktar;
  printf("Aktarilan hesap %s\n",hesaplar[aliciNo].isim);
  printf("Aktarilan miktar %.2f TL\n", miktar, hesaplar[aliciNo].isim);
  sleep(2);
  printf("Mevcut bakiyeniz %.2f TL\n", hesaplar[mevcutHesap].bakiye);
  sleep(2);
}


int main() {
  	while (1) {
    int secim = anaMenu();
	printf("\n");
    if (secim == 1) {
      	hesapOlustur();
      	printf("\n");
    } else if (secim == 2) {
      	int mevcutHesap = hesapGiris();
      	printf("\n");
      	if (mevcutHesap == -1) {
        	continue;
      	}

    while (1) {
    printf("\n");
    int secim = hesapGirisMenusu();
    printf("\n");
        if (secim == 1) {
          	bakiyeKontrol(mevcutHesap);
          	printf("\n");
        } else if (secim == 2) {
          	paraCek(mevcutHesap);     
			  printf("\n"); 	
        } else if (secim == 3) {
         	paraYatir(mevcutHesap);
         	printf("\n");
        } else if (secim == 4) {
          	paraAktarma(mevcutHesap);
          	printf("\n");
        } else if (secim == 5) {
        	printf("\n");
        	break;	
		} else {
          	printf("Gecersiz secim\n");
          	printf("\n");
        }
      }
    } else if (secim == 3) {
    	printf("\n");
      	break;
    } else {
      	printf("Gecersiz secim\n");
      	printf("\n");
    }
  }
  return 0;
}

