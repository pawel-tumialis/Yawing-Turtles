
#include <fstream>
#include <string.h>
#include <iostream>
using namespace std;

struct BITMAPFILEHEADER {
	int bfType;
	int bfSize;
	int bfReserved1;
	int bfReserved2;
	int bfOffBits;
};

struct BITMAPINFOHEADER {
	int biSize;
	int biWidth;
	int biHeight;
	int biPlanes;
	int biBitCount;
	int biCompression;
	int biSizeImage;
	int biXpelsPerMeter;
	int biYpelsPerMeter;
	int biCrlUses;
	int biCrlImportant;
};

void czytaj_BITMAPFILEHEADER(ifstream& plik_wejsciowy, BITMAPFILEHEADER& bfh) {
	plik_wejsciowy.read(reinterpret_cast<char*>(&bfh.bfType), 2);
	plik_wejsciowy.read(reinterpret_cast<char*>(&bfh.bfSize), 4);
	plik_wejsciowy.read(reinterpret_cast<char*>(&bfh.bfReserved1), 2);
	plik_wejsciowy.read(reinterpret_cast<char*>(&bfh.bfReserved2), 2);
	plik_wejsciowy.read(reinterpret_cast<char*>(&bfh.bfOffBits), 4);
	cout << bfh.bfType<<endl;
	cout << bfh.bfSize << endl;
	cout << bfh.bfReserved1<< endl;
	cout << bfh.bfReserved2<< endl;
	cout << bfh.bfOffBits<< endl<<endl;
}
void czytaj_BITMAPINFOHEADER(ifstream& plik_wejsciowy, BITMAPINFOHEADER& bih) {
	plik_wejsciowy.read(reinterpret_cast<char*>(&bih.biSize), 4);
	plik_wejsciowy.read(reinterpret_cast<char*>(&bih.biWidth), 4);
	plik_wejsciowy.read(reinterpret_cast<char*>(&bih.biHeight), 4);
	plik_wejsciowy.read(reinterpret_cast<char*>(&bih.biPlanes), 2);
	plik_wejsciowy.read(reinterpret_cast<char*>(&bih.biBitCount), 2);
	plik_wejsciowy.read(reinterpret_cast<char*>(&bih.biCompression), 4);
	plik_wejsciowy.read(reinterpret_cast<char*>(&bih.biSizeImage), 4);
	plik_wejsciowy.read(reinterpret_cast<char*>(&bih.biXpelsPerMeter), 4);
	plik_wejsciowy.read(reinterpret_cast<char*>(&bih.biYpelsPerMeter), 4);
	plik_wejsciowy.read(reinterpret_cast<char*>(&bih.biCrlUses), 4);
	plik_wejsciowy.read(reinterpret_cast<char*>(&bih.biCrlImportant), 4);
	cout << bih.biSize<< endl;
	cout << bih.biWidth<< endl;
	cout << bih.biHeight<< endl;
	cout << bih.biPlanes<< endl;
	cout << bih.biBitCount<< endl;
	cout << bih.biCompression<< endl;
	cout << bih.biSizeImage<< endl;
	cout << bih.biXpelsPerMeter<< endl;
	cout << bih.biYpelsPerMeter<< endl;
	cout << bih.biCrlUses<< endl;
	cout << bih.biCrlImportant<< endl;
}

void zapisuj_BITMAPFILEHEADER(ofstream& plik_wyjsciowy, BITMAPFILEHEADER& bfh) {
	plik_wyjsciowy.write(reinterpret_cast<char*>(&bfh.bfType), 2);
	plik_wyjsciowy.write(reinterpret_cast<char*>(&bfh.bfSize), 4);
	plik_wyjsciowy.write(reinterpret_cast<char*>(&bfh.bfReserved1), 2);
	plik_wyjsciowy.write(reinterpret_cast<char*>(&bfh.bfReserved2), 2);
	plik_wyjsciowy.write(reinterpret_cast<char*>(&bfh.bfOffBits), 4);
}

void zapisuj_BITMAPINFOHEADER(ofstream& plik_wyjsciowy, BITMAPINFOHEADER& bih) {
	plik_wyjsciowy.write(reinterpret_cast<char*>(&bih.biSize), 4);
	plik_wyjsciowy.write(reinterpret_cast<char*>(&bih.biWidth), 4);
	plik_wyjsciowy.write(reinterpret_cast<char*>(&bih.biHeight), 4);
	plik_wyjsciowy.write(reinterpret_cast<char*>(&bih.biPlanes), 2);
	plik_wyjsciowy.write(reinterpret_cast<char*>(&bih.biBitCount), 2);
	plik_wyjsciowy.write(reinterpret_cast<char*>(&bih.biCompression), 4);
	plik_wyjsciowy.write(reinterpret_cast<char*>(&bih.biSizeImage), 4);
	plik_wyjsciowy.write(reinterpret_cast<char*>(&bih.biXpelsPerMeter), 4);
	plik_wyjsciowy.write(reinterpret_cast<char*>(&bih.biYpelsPerMeter), 4);
	plik_wyjsciowy.write(reinterpret_cast<char*>(&bih.biCrlUses), 4);
	plik_wyjsciowy.write(reinterpret_cast<char*>(&bih.biCrlImportant), 4);
}

void dodanie_zer(BITMAPINFOHEADER bih, ofstream& plik_wyjsciowy) {
	int ilezer;
	ilezer = bih.biWidth % 4;
	while (ilezer) {
		int zero = 0;
		plik_wyjsciowy.write(reinterpret_cast<char*>(&zero), 1);
		ilezer--;
	}
}

int main()
{//jak na razie kopiuje jeden do jednego obraz wejsciowy 
	ifstream plik_wejsciowy;
	ofstream plik_wyjsciowy;

	plik_wejsciowy.open("obraz.bmp", ios::binary);
	if (!plik_wejsciowy) {
		cout << "Plik wejsciowy nie zosta³ otwarty.";
		return 0;
	}

	plik_wyjsciowy.open("obrazwyjœciowy.bmp", ios::binary);
	if (!plik_wyjsciowy) {
		cout << "Plik wyjsciowy nie zosta³ otwarty.";
		return 0;
	}
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;

	czytaj_BITMAPFILEHEADER(plik_wejsciowy, bfh);
	czytaj_BITMAPINFOHEADER(plik_wejsciowy, bih);
	zapisuj_BITMAPFILEHEADER(plik_wyjsciowy, bfh);
	zapisuj_BITMAPINFOHEADER(plik_wyjsciowy, bih);

	int p = 0;
	int r = 0;
	int g = 0;
	int b = 0;
	for (int i = 0; i < bih.biHeight; i++) {
		for (int i = 0; i < bih.biWidth; i++) {
			plik_wejsciowy.read(reinterpret_cast<char*>(&b), 1);
		
		
			plik_wejsciowy.read(reinterpret_cast<char*>(&g), 1);
		
			plik_wejsciowy.read(reinterpret_cast<char*>(&r), 1);
		
			plik_wyjsciowy.write(reinterpret_cast<char*>(&b), 1);
			plik_wyjsciowy.write(reinterpret_cast<char*>(&g), 1);
			plik_wyjsciowy.write(reinterpret_cast<char*>(&r), 1);
		}
		dodanie_zer(bih, plik_wyjsciowy);
		
		
	}

	

		plik_wejsciowy.close();
		plik_wyjsciowy.close();
		return 0;
}