#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;
struct dugum
{
	int plakaNo;
	string sehir;
	struct dugum* solDügüm;
	struct dugum* sagDügüm;
	dugum(int no,string isim) :plakaNo(no),sehir(isim), solDügüm(nullptr), sagDügüm(nullptr) {}
};

dugum* kokArama(dugum* agacKok, int no)
{
	if (agacKok == nullptr || agacKok->plakaNo == no) { return agacKok; }
	if (no < agacKok->plakaNo) { return kokArama(agacKok->solDügüm, no); }
	else { return kokArama(agacKok->sagDügüm, no); }	
}

void agacaEkle(dugum*& agacKok, int no , string isim)
{
	if (agacKok == nullptr) { agacKok = new dugum(no, isim);}
	if (no < agacKok->plakaNo) { agacaEkle(agacKok->solDügüm, no, isim);}
	else if (no > agacKok->plakaNo) { agacaEkle(agacKok->sagDügüm, no, isim);}
}

int derinlikHesap(dugum* agacKok)
{
	if (agacKok == nullptr) { return 0; }
	int solDerinlik = derinlikHesap(agacKok->solDügüm);
	int sagDerinlik = derinlikHesap(agacKok->sagDügüm);
	return 1 + max(solDerinlik, sagDerinlik);
}

bool dengeliMi(dugum* agacKok)
{
	int solDerinlik = derinlikHesap(agacKok->solDügüm);
	int sagDerinlik = derinlikHesap(agacKok->sagDügüm);
	if (abs(solDerinlik - sagDerinlik) > 1) { return false; }
	else { return true; }
	return dengeliMi(agacKok->solDügüm) && dengeliMi(agacKok->sagDügüm);
}

void sehirIsmiYazma(dugum* agacKok, int no)
{
	dugum* dugum = kokArama(agacKok, no);
	if (dugum == nullptr) { cout << "Plaka kodu bulunamadi." << endl; }
	else { cout << "Sehir: " << dugum->sehir << endl; }
}

int agacDuzeyFarki(dugum* agacKok, int plaka1, int plaka2)
{
	dugum* dugum1 = kokArama(agacKok, plaka1);
	dugum* dugum2 = kokArama(agacKok, plaka2);
	if (dugum1 == nullptr || dugum2 == nullptr) { return -1; }
	int duzey1 = 0, duzey2 = 0;
	dugum* sonDugum = agacKok;
	while (sonDugum != nullptr && sonDugum->plakaNo != plaka1)
	{
		if (plaka1 < sonDugum->plakaNo)
		{
			sonDugum = sonDugum->solDügüm;
			duzey1++;
		}
		else
		{
			sonDugum = sonDugum->sagDügüm;
			duzey1++;
		}
	}
	sonDugum = agacKok;
	while (sonDugum != nullptr && sonDugum->plakaNo != plaka2)
	{
		if (plaka2 < sonDugum->plakaNo)
		{
			sonDugum = sonDugum->solDügüm;
			duzey2++;
		}
		else 
		{
			sonDugum = sonDugum->sagDügüm;
			duzey2++;
		}
	}
	return abs(duzey1 - duzey2);
}

void agacıYaz()
{
	int bosluk = 28;
	int index = 0;
	int okunaneleman = 1;
	int plakalar[] = { 55,29,69,19,52,60,78,8,28,37,53,57,67,74,81,5,14,61 };
	for (int i = 0; i < 18; i++)
	{
		cout << setw(bosluk) << plakalar[i];
		index++;
		if (index == okunaneleman)
		{
			cout << endl ;
			okunaneleman *= 2;
			index = 0;
			bosluk -= 8;
		}
		if (i == 6) { bosluk += 3; }
		if (i == 10) { bosluk -= 1; }
		if (i == 14) { bosluk += 7; }
		if (i == 16) { bosluk += 23; }
	}
}

void preOrder(struct dugum* agacKok)
{
	if (agacKok == nullptr) return;
	cout << agacKok->plakaNo << "-";
	preOrder(agacKok->solDügüm);
	preOrder(agacKok->sagDügüm);
}
void inOrder(dugum* agacKok)
{
	if (agacKok == nullptr) return;	
	inOrder(agacKok->solDügüm);
	cout << agacKok->plakaNo << "-";
	inOrder(agacKok->sagDügüm);
}
void postOrder(struct dugum* agacKok)
{
	if (agacKok == nullptr) return;
	postOrder(agacKok->solDügüm);
	postOrder(agacKok->sagDügüm);
	cout << agacKok->plakaNo << "-";
}

int main()
{
	ifstream dosyaOku("sehir_plaka_kodlari.txt");
	string harf = "";
	string plakaVeSehir[18][18];
	int harfSayaci = 0;
	dugum* agacKok = nullptr;
	if (dosyaOku.is_open())
	{
		while (getline(dosyaOku, harf) && harfSayaci < 18)
		{
			if (harf.length() >= 2)
			{
				plakaVeSehir[harfSayaci][0] = harf.substr(0, 2);
				plakaVeSehir[harfSayaci][1] = harf.substr(3, 9);
				harfSayaci++;
			}
		}
		dosyaOku.close();
	}
	for (int i = 0; i < 18; i++)
	{
		agacaEkle(agacKok, stoi(plakaVeSehir[i][0]), plakaVeSehir[i][1]);
	}

	int derinlik = derinlikHesap(agacKok);
	cout << "Agacin derinligi: " << derinlik << endl;
	bool denge = dengeliMi(agacKok);
	cout << "Agac dengeli mi?" << (denge ? " Dengeli" : " Dengesiz") << endl<<endl;
	agacıYaz();
	cout << endl<<"---------------------------------------------------------"<<endl<<endl;
	
	int plakaNo1, plakaNo2;
	cout << "Birinci plaka kodu girin: ";
	cin >> plakaNo1;
	cout << "Ikinci plaka kodu girin: ";
	cin >> plakaNo2;

	sehirIsmiYazma(agacKok, plakaNo1);
	sehirIsmiYazma(agacKok, plakaNo2);
	int seviyeFarki = agacDuzeyFarki(agacKok, plakaNo1, plakaNo2);
	if (seviyeFarki != -1) { cout << "Duzey farki: " << seviyeFarki << endl << endl; }
	else { cout << "2 plaka kodundan en az biri agacta yok ise duzey farklarni gösteremiyoruz." << endl<< endl; }

	cout << "inorder: ";
	inOrder(agacKok);
	cout << endl;
	cout << "preorder: ";
	preOrder(agacKok);
	cout << endl;
	cout << "postorder: ";
	postOrder(agacKok);
	cout << endl;

	return 0;

}
