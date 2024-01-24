#include <iostream>
#include <conio.h>
#include <stdlib.h>
using namespace std;
//normal kuyruk islemleri...
struct normalKuyruk
{
    int musteriNo;
    int islemSuresi;
    normalKuyruk* sonraki;
    normalKuyruk* sonrakiSure;
};
normalKuyruk* SureDugum = new normalKuyruk;
normalKuyruk* son = new normalKuyruk;
normalKuyruk* oncekiBeklemeSuresi = new normalKuyruk;
int kuyrukBoyutu = 0;
int kuyrukSirasi = 0;

void normalKuyrugaEkle(int no,int sure)
{
    normalKuyruk* yeniNo = new normalKuyruk;
    yeniNo->musteriNo = no;
    normalKuyruk* yeniSure = new normalKuyruk;
    yeniSure->islemSuresi = sure;
    if (kuyrukBoyutu == 0)
    {
        yeniNo->sonraki = NULL;
        yeniSure->sonrakiSure = NULL;
    }
    else
    {
        yeniNo->sonraki = son;
        yeniSure->sonrakiSure = SureDugum;
    }
    oncekiBeklemeSuresi->islemSuresi += SureDugum->islemSuresi;
    son = yeniNo;
    SureDugum = yeniSure;
    kuyrukBoyutu++;
}
int toplamSure=0;
void normalKuyruktanSil()
{
    kuyrukSirasi++;
    if (kuyrukBoyutu > 0)
    {
        normalKuyruk* yeniSon = son;
        normalKuyruk* yeniSure = SureDugum;
        toplamSure = toplamSure + yeniSure->islemSuresi;
        for (int i = 1; i < kuyrukBoyutu; i++)
        {
            yeniSon = yeniSon->sonraki;
            yeniSure = yeniSure->sonrakiSure;
        }
        if (kuyrukSirasi == 1) { oncekiBeklemeSuresi->islemSuresi = 0; }
        cout <<kuyrukSirasi<<". sirada kuyruktan cikan " << yeniSon->musteriNo << "'no lu musterinin islemi ";
        cout << yeniSure->islemSuresi << "sn. surdu ve islem suresi ile birlikte " << (yeniSure->islemSuresi + oncekiBeklemeSuresi->islemSuresi) << "sn. kuyrukta bekledi. " << endl << endl;
        yeniSon->sonraki = NULL;
        yeniSure->sonrakiSure = NULL;
        kuyrukBoyutu--;
    }
    else
    {
        cout <<"Musterilerin ortalama islem suresi: " << toplamSure/(kuyrukSirasi-1) <<"sn. dir." << endl<<endl;
    }
}

struct listeYigin
{
    int musteriNo;
    int musteriSure;
    listeYigin* sonraki;
    listeYigin* sonrakiSure;
};

listeYigin* yiginTepesi = new listeYigin;
listeYigin* yiginSureTepesi = new listeYigin;
int yiginUzunlugu = 0;

void listeYiginaEkle(int no,int sure)
{
    listeYigin* yeniNo = new listeYigin;
    listeYigin* yeniSure = new listeYigin;
    yeniNo->musteriNo = no;
    yeniSure->musteriSure = sure;
    yeniNo->sonraki = yiginTepesi;
    yeniSure->sonrakiSure = yiginSureTepesi;
    yiginTepesi = yeniNo;
    yiginSureTepesi = yeniSure;
    yiginUzunlugu++;
}
int listeYigindanCikar()
{
    if (yiginUzunlugu != 0)
    {
        normalKuyrugaEkle(yiginTepesi->musteriNo, yiginSureTepesi->musteriSure);
        yiginTepesi = yiginTepesi->sonraki;
        yiginSureTepesi = yiginSureTepesi->sonrakiSure;
        yiginUzunlugu--;
        return 0;
    }
}

//Onlelikli kuyruk islemleri...

#define oncelikliKuyrukUzunlugu 10
struct oncelikliKuyruk
{
    int musteriNumaralari[oncelikliKuyrukUzunlugu];
    int musteriSayisi = 0;
    int kuyrukBasi = 0;
    int kuyrukSonu = -1;
    int islemSureleri[oncelikliKuyrukUzunlugu];
    int toplamSure = 0, ortalamaSure = 0;
};

void oncelikliKuyrugaEkle(oncelikliKuyruk* k, int musteriNo, int musteriSuresi)
{
    k->kuyrukSonu++;
    if (k->kuyrukSonu == oncelikliKuyrukUzunlugu)
    {
        k->kuyrukSonu = 0;
    }
    k->musteriNumaralari[k->kuyrukSonu] = musteriNo;
    k->islemSureleri[k->kuyrukSonu] = musteriSuresi;
    k->musteriSayisi++;
}
int beklenensureler = 0;
int sayac = 0;
void oncelikliKuyruktanCikar(oncelikliKuyruk* k)
{
    int sureDegisimi;
    int musteriNoDegisimi;
    for (int i = 1; i < k->musteriSayisi; i++)
    {
        for (int j = 0; j < (k->musteriSayisi - i); j++)
        {
            if (k->islemSureleri[j] > k->islemSureleri[j + 1])
            {
                sureDegisimi = k->islemSureleri[j];
                k->islemSureleri[j] = k->islemSureleri[j + 1];
                k->islemSureleri[j + 1] = sureDegisimi;

                musteriNoDegisimi = k->musteriNumaralari[j];
                k->musteriNumaralari[j] = k->musteriNumaralari[j + 1];
                k->musteriNumaralari[j + 1] = musteriNoDegisimi;
            }
        }
    }
    beklenensureler += k->islemSureleri[sayac];
    sayac++;
    cout << k->musteriNumaralari[k->kuyrukBasi] << "no'lu musterinin islemi ";
    cout << k->islemSureleri[k->kuyrukBasi] << "sn. surdu ve islem suresi ile birlikte " << beklenensureler << "sn. kuyrukta bekledi." << endl;
    k->kuyrukBasi++;
    if (k->kuyrukBasi == oncelikliKuyrukUzunlugu)
    {
        k->kuyrukBasi = 0;
    }
    k->musteriSayisi--;
}

void ortalamaSureHesap(oncelikliKuyruk* k, int diziBuyuklugu)
{
    for (int i = 0; i < diziBuyuklugu; i++)
    {
        k->toplamSure += k->islemSureleri[i];
    }
    k->ortalamaSure = k->toplamSure / diziBuyuklugu;
    cout << endl << "Musterilerin bekleme sure ortalamasi:  " << k->ortalamaSure <<"sn. dir." << endl;
}

#define ikinciYiginBuyuklugu 100
struct diziYigin
{
    int musteriNumaralari[ikinciYiginBuyuklugu];
    int islemSureleri[ikinciYiginBuyuklugu];
    int yiginTepesi = -1;
    oncelikliKuyruk kuyrukIsareti;
};
void diziYiginaEkle(diziYigin* y, int no,int sure)
{
    y->yiginTepesi++;
    y->musteriNumaralari[y->yiginTepesi] = no;
    y->islemSureleri[y->yiginTepesi] = sure;
}
void diziYigindanCikar(diziYigin* y)
{
    oncelikliKuyrugaEkle(&y->kuyrukIsareti, y->musteriNumaralari[y->yiginTepesi], y->islemSureleri[y->yiginTepesi]);
    y->yiginTepesi--;
}



int main()
{
    diziYigin* yiginIsareti = new diziYigin;
    int secim, musteriNo, normalKuyrukMusteriSayisi = 0, oncelikliKuyrukMusteriSayisi = 0;
    int  randomSayi=0, maxSure = 300, minSure = 30;
    bool ilkMi = true;
    do
    {
        cout << "0-Eklenecek musteri kalmadi. " << " 1-Musteri Ekle." << endl;
        cin >> secim;
        if (secim == 1)
        {
            srand(time(0));
            cout << "Musteri no'su gir: " << endl;
            cin >> musteriNo;
            cout << musteriNo << " no'lu musteri siraya girdi." << endl;
            for (int i = 0; i < (oncelikliKuyrukMusteriSayisi+1); i++)
            {
                randomSayi = rand() % (maxSure - minSure + 1) + minSure;
            }
            listeYiginaEkle(musteriNo, randomSayi);
            diziYiginaEkle(yiginIsareti, musteriNo, randomSayi);
            ilkMi = false;
            normalKuyrukMusteriSayisi++;
            oncelikliKuyrukMusteriSayisi++;
        }
        if (secim != 0 && secim != 1) { cout << "Yanlis deger girdiniz..." << endl; secim = 1; }
        if (ilkMi) { cout << "En az 1 secim yapilmali." << endl; secim = 1; }
    } while (secim == 1);
    for (int i = 0; i < oncelikliKuyrukMusteriSayisi; i++)
    {
        diziYigindanCikar(yiginIsareti);
    }
    cout << "-------------" << endl << endl;
    cout << "Normal kuyruk ile Musterilerin islemleri yapiliyor..." << endl << endl;
    cout << "-------------" << endl << endl;
    do
    {
        listeYigindanCikar();
        normalKuyruktanSil();
        normalKuyrukMusteriSayisi--;

    } while (normalKuyrukMusteriSayisi !=-1);
    cout << "-------------" << endl << endl;
    cout << "Oncelikli kuyruk ile Musterilerin islemleri yapiliyor..." << endl << endl;
    cout << "-------------" << endl;

    for (int i = 0; i < oncelikliKuyrukMusteriSayisi; i++)
    {
        cout << endl << (i + 1) << ". sirada kuyruktan cikan ";
        oncelikliKuyruktanCikar(&yiginIsareti->kuyrukIsareti);
    }

    ortalamaSureHesap(&yiginIsareti->kuyrukIsareti, oncelikliKuyrukMusteriSayisi);
}
