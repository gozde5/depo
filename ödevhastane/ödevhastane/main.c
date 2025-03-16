//
//  main.c
//  ödevhastane
//
//  Created by gözde on 16.03.2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hasta bilgilerini tutan yapı burda struct ile hasta için girilmesi gereken özellikleri hasta adı altında topladık
typedef struct Hasta {
    int id;
    char isim[50];
    int yas;
    char durum[50]; // "Acil" veya "Normal"
    char receteNo[20];
    struct Hasta* sonraki;
} Hasta;

Hasta* bas = NULL; // Hasta kuyruğunun başlangıcı bunu sırayla veriyor

// Yeni bir hasta ekleme fonksiyonu
void hastaEkle(int id, char* isim, int yas, char* durum, char* receteNo) {
    Hasta* yeniHasta = (Hasta*)malloc(sizeof(Hasta));
    yeniHasta->id = id;
    strcpy(yeniHasta->isim, isim);
    yeniHasta->yas = yas;
    strcpy(yeniHasta->durum, durum);
    strcpy(yeniHasta->receteNo, receteNo);
    yeniHasta->sonraki = NULL;

    if (bas == NULL || strcmp(durum, "Acil") == 0) {
        yeniHasta->sonraki = bas;
        bas = yeniHasta;
    } else {
        Hasta* temp = bas;
        while (temp->sonraki != NULL) {
            temp = temp->sonraki;
        }
        temp->sonraki = yeniHasta;
    }
}

// Hastaları listeleme fonksiyonu burda başa hasta ekliyoruz
void hastalariListele(void) {
    Hasta* temp = bas;// temp nlık kaydeder
    printf("\nHastane Kuyruğu:\n");
    while (temp != NULL) {
        printf("ID: %d, Isim: %s, Yas: %d, Durum: %s, Recete No: %s\n", temp->id, temp->isim, temp->yas, temp->durum, temp->receteNo);
        temp = temp->sonraki;
    }
}

// İlk hastayı çıkartan fonksiyon
void hastaCikar(void) {
    if (bas == NULL) {
        printf("Kuyruk bos!\n");
        return;
    }
    Hasta* temp = bas;
    bas = bas->sonraki;
    printf("Hasta cikartildi: %s\n", temp->isim);
    free(temp);
}

// Reçete numarası oluşturma fonksiyonu
void receteOlustur(char* receteNo) {
    sprintf(receteNo, "RX-%d", rand() % 10000);
}

int main() {
    char recete[20];
    receteOlustur(recete);
    hastaEkle(1, "Ahmet Yilmaz", 45, "Acil", recete);
    
    receteOlustur(recete);
    hastaEkle(2, "Mehmet Kaya", 30, "Normal", recete);
    
    receteOlustur(recete);
    hastaEkle(3, "Fatma Demir", 60, "Acil", recete);
    
    hastalariListele();
    
    hastaCikar();
    
    hastalariListele();
    
    return 0;
}
// evet çıktı olarak isim yaş ve durum reçete no gibi çıktıları hasta sırasına göre sıralıyor
