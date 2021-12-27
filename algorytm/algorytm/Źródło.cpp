
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
	cout << bfh.bfType << endl;
	cout << bfh.bfSize << endl;
	cout << bfh.bfReserved1 << endl;
	cout << bfh.bfReserved2 << endl;
	cout << bfh.bfOffBits << endl << endl;
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
	cout << bih.biSize << endl;
	cout << bih.biWidth << endl;
	cout << bih.biHeight << endl;
	cout << bih.biPlanes << endl;
	cout << bih.biBitCount << endl;
	cout << bih.biCompression << endl;
	cout << bih.biSizeImage << endl;
	cout << bih.biXpelsPerMeter << endl;
	cout << bih.biYpelsPerMeter << endl;
	cout << bih.biCrlUses << endl;
	cout << bih.biCrlImportant << endl;
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

void odcienie_szaroœci(int& rin, int& gin, int& bin) {

	rin = 0.299 * rin + 0.587 * gin + 0.114 * bin;
	gin = rin;
	bin = gin;
	//cout << endl << endl << rin << endl;
	//cout << gin << endl;
	//cout << bin << endl;
}

void wykrycie_krawedzi(int rin, int gin, int bin, int rin2, int gin2, int bin2, int rin3, int gin3, int bin3, int rin4, int gin4, int bin4, ofstream& plik_wyjsciowy) {
	int r = abs(rin - rin4) + abs(rin2 - rin3);
	int g = abs(gin - gin4) + abs(gin2 - gin3);
	int b = abs(bin - bin4) + abs(bin2 - bin3);
	plik_wyjsciowy.write(reinterpret_cast<char*>(&b), 1);
	plik_wyjsciowy.write(reinterpret_cast<char*>(&g), 1);
	plik_wyjsciowy.write(reinterpret_cast<char*>(&r), 1);

	//cout << endl << rin << endl;
	//cout << gin << endl;
	//cout << bin << endl;
}

int main()
{
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


	int a = 0;
	for (int j = 0; j < bih.biHeight; j++) {
		for (int i = 0; i < bih.biWidth; i++) {
			a++;
			int rin1 = 0;
			int gin1 = 0;
			int bin1 = 0;
			int rin2 = 0;
			int gin2 = 0;
			int bin2 = 0;
			int rin3 = 0;
			int gin3 = 0;
			int bin3 = 0;
			int rin4 = 0;
			int gin4 = 0;
			int bin4 = 0;
			plik_wejsciowy.read(reinterpret_cast<char*>(&bin1), 1);
			//cout << i << '.' << plik_wejsciowy.tellg()<<endl;
			plik_wejsciowy.read(reinterpret_cast<char*>(&gin1), 1);
			//cout << i +1 << '.' << plik_wejsciowy.tellg() << endl;
			plik_wejsciowy.read(reinterpret_cast<char*>(&rin1), 1);
			//cout << i + 2 << '.' << plik_wejsciowy.tellg() << endl;
			plik_wejsciowy.read(reinterpret_cast<char*>(&bin2), 1);
			//cout << i + 3 << '.' << plik_wejsciowy.tellg() << endl;
			plik_wejsciowy.read(reinterpret_cast<char*>(&gin2), 1);
			//cout << i + 4 << '.' << plik_wejsciowy.tellg() << endl;
			plik_wejsciowy.read(reinterpret_cast<char*>(&rin2), 1);
			//cout << i + 5 << '.' << plik_wejsciowy.tellg() << endl;
			if(a<(bih.biHeight*bih.biWidth )/2){
			plik_wejsciowy.seekg(bih.biWidth - 1, ios::cur);
			plik_wejsciowy.read(reinterpret_cast<char*>(&bin3), 1);
			//cout << i + bih.biWidth << '.' << plik_wejsciowy.tellg() << endl;
			plik_wejsciowy.read(reinterpret_cast<char*>(&gin3), 1);
			//cout << i + bih.biWidth+1 << '.' << plik_wejsciowy.tellg() << endl;
			plik_wejsciowy.read(reinterpret_cast<char*>(&rin3), 1);
			//cout << i + bih.biWidth+2 << '.' << plik_wejsciowy.tellg() << endl;
			plik_wejsciowy.read(reinterpret_cast<char*>(&bin4), 1);
			//cout << i + bih.biWidth+3 << '.' << plik_wejsciowy.tellg() << endl;
			plik_wejsciowy.read(reinterpret_cast<char*>(&gin4), 1);
			//cout << i + bih.biWidth+4 << '.' << plik_wejsciowy.tellg() << endl;
			plik_wejsciowy.read(reinterpret_cast<char*>(&rin4), 1);
			//cout << i + bih.biWidth+5 << '.' << plik_wejsciowy.tellg() << endl;
			plik_wejsciowy.seekg( 1 + i + (j * (bih.biWidth)), ios::beg);//dodaj i
			//cout << i + bih.biWidth+6 << '.' << plik_wejsciowy.tellg() << endl;
			}
			
			odcienie_szaroœci(rin1, gin1, bin1);
			odcienie_szaroœci(rin2, gin2, bin2);
			odcienie_szaroœci(rin3, gin3, bin3);
			odcienie_szaroœci(rin4, gin4, bin4);
			wykrycie_krawedzi(rin1, gin1, bin1, rin2, gin2, bin2, rin3, gin3, bin3, rin4, gin4, bin4, plik_wyjsciowy);
		}
		dodanie_zer(bih, plik_wyjsciowy);


	}


	cout << endl << a << endl;
	plik_wejsciowy.close();
	plik_wyjsciowy.close();
	return 0;
}