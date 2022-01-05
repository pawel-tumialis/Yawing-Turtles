#include "lodepng.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

std::vector<unsigned char> image;
unsigned width, height;

void decodeOneStep(const char* filename) {
	unsigned error = lodepng::decode(image, width, height, filename);
	if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height) {
	unsigned error = lodepng::encode(filename, image, width, height);
	if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

int Index(int w, int h) {
	if (h > 0) {
		return 4 * (h * width + w);
	}
	else {
		return w * 4;
	}
}

void Image1() {
	char File[] = "szyfr_1.png";
	decodeOneStep(File);
	int freshhold = 4;
	std::vector<unsigned char> newimage;
	char lastpixel;
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width - 1; w++) {
			if (w == 0) {
				lastpixel = image[Index(w, h)];
				newimage.push_back((char)0);
				newimage.push_back((char)0);
				newimage.push_back((char)0);
				newimage.push_back((char)255);
			}
			else if (image[Index(w + 1, h)] == lastpixel) {
				newimage.push_back((char)0);
				newimage.push_back((char)0);
				newimage.push_back((char)0);
				newimage.push_back((char)255);
			}
			else {
				lastpixel = image[Index(w + 1, h)];
				newimage.push_back((char)255);
				newimage.push_back((char)255);
				newimage.push_back((char)255);
				newimage.push_back((char)255);
			}
		}
		newimage.push_back((char)0);
		newimage.push_back((char)0);
		newimage.push_back((char)0);
		newimage.push_back((char)255);
	}

	for (int w = 0; w < width; w++) {
		for (int h = 0; h < height - 1; h++) {
			if (h == 0) {
				lastpixel = image[Index(w, h)];
			}
			else if (image[Index(w, h + 1)] != lastpixel) {
				lastpixel = image[Index(w, h + 1)];
				newimage[Index(w, h)] = (char)255;
				newimage[Index(w, h) + 1] = (char)255;
				newimage[Index(w, h) + 2] = (char)255;
			}
		}
	}
	char Name[] = "test1.png";
	encodeOneStep(Name, newimage, width, height);
	image.clear();
}

void Image2() {
	char File[] = "test2.png";
	decodeOneStep(File);
	int freshhold = 4;
	std::vector<unsigned char> newimage;
	char lastpixel;
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width - 1; w++) {
			if (w == 0) {
				lastpixel = image[Index(w, h)];
				newimage.push_back((char)0);
				newimage.push_back((char)0);
				newimage.push_back((char)0);
				newimage.push_back((char)255);
			}
			else if (image[Index(w + 1, h)] == lastpixel) {
				newimage.push_back((char)0);
				newimage.push_back((char)0);
				newimage.push_back((char)0);
				newimage.push_back((char)255);
			}
			else {
				lastpixel = image[Index(w + 1, h)];
				newimage.push_back((char)255);
				newimage.push_back((char)255);
				newimage.push_back((char)255);
				newimage.push_back((char)255);
			}
		}
		newimage.push_back((char)0);
		newimage.push_back((char)0);
		newimage.push_back((char)0);
		newimage.push_back((char)255);
	}

	for (int w = 0; w < width; w++) {
		for (int h = 0; h < height - 1; h++) {
			if (h == 0) {
				lastpixel = image[Index(w, h)];
			}
			else if (image[Index(w, h + 1)] != lastpixel) {
				lastpixel = image[Index(w, h + 1)];
				newimage[Index(w, h)] = (char)255;
				newimage[Index(w, h) + 1] = (char)255;
				newimage[Index(w, h) + 2] = (char)255;
			}
		}
	}
	char Name[] = "test2.png";
	encodeOneStep(Name, newimage, width, height);
	image.clear();
}

void Image3() {
	char File[] = "szyfr_3.png";
	decodeOneStep(File);
	int freshhold = 4;
	std::vector<unsigned char> newimage;
	char lastpixel;
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width - 1; w++) {
			if (w == 0) {
				lastpixel = image[Index(w, h)];
				newimage.push_back((char)0);
				newimage.push_back((char)0);
				newimage.push_back((char)0);
				newimage.push_back((char)255);
			}
			else if (image[Index(w + 1, h)] == lastpixel) {
				newimage.push_back((char)0);
				newimage.push_back((char)0);
				newimage.push_back((char)0);
				newimage.push_back((char)255);
			}
			else {
				lastpixel = image[Index(w + 1, h)];
				newimage.push_back((char)255);
				newimage.push_back((char)255);
				newimage.push_back((char)255);
				newimage.push_back((char)255);
			}
		}
		newimage.push_back((char)0);
		newimage.push_back((char)0);
		newimage.push_back((char)0);
		newimage.push_back((char)255);
	}

	for (int w = 0; w < width; w++) {
		for (int h = 0; h < height - 1; h++) {
			if (h == 0) {
				lastpixel = image[Index(w, h)];
			}
			else if (image[Index(w, h + 1)] != lastpixel) {
				lastpixel = image[Index(w, h + 1)];
				newimage[Index(w, h)] = (char)255;
				newimage[Index(w, h) + 1] = (char)255;
				newimage[Index(w, h) + 2] = (char)255;
			}
		}
	}
	char Name[] = "test3.png";
	encodeOneStep(Name, newimage, width, height);
	image.clear();
}

struct Letter {
	Letter() {
		 xmin=0;
		 xmax=0;
		 ymin=0;
		 ymax=0;
	};
	int xmin;
	int xmax;
	int ymin;
	int ymax;
};

char chr(int num) {
	switch (num){
		case 1: return 'a';
		case 2: return 'ą';
		case 3: return 'b';
		case 4: return 'c';
		case 5: return 'ć';
		case 6: return 'd';
		case 7: return 'e';
		case 8: return 'ę';
		case 9: return 'f';
		case 10: return 'g';
		case 11: return 'h';
		case 12: return 'i';
		case 13: return 'j';
		case 14: return 'k';
		case 15: return 'l';
		case 16: return 'ł';
		case 17: return 'm';
		case 18: return 'n';
		case 19: return 'ń';
		case 20: return 'o';
		case 21: return 'ó';
		case 22: return 'p';
		case 23: return 'r';
		case 24: return 's';
		case 25: return 'ś';
		case 26: return 't';
		case 27: return 'u';
		case 28: return 'w';
		case 29: return 'y';
		case 30: return 'z';
		case 31: return 'ź';
		case 32: return 'ż';
	}

}

void Template() {
	char File[] = "Szablon.png";
	decodeOneStep(File);
	ofstream plik;
	plik.open("litery.txt");
	Letter letter;
	int letternumber = 1;
	bool white=0;
	for (int w = 0; w < width; w++) {
		bool find = 0;
		for (int h = 0; h < height; h++) {
			if (image[Index(w, h)] == (unsigned char)255) {
				if (!white) {
					letter.xmin = w;
					white = 1;
				}
				find = 1;
			}
		}
		if (!find && white) {
			letter.xmax = w-1;
			white = 0;
			//cout << letter.xmin << " " << letter.xmax<<" | ";
			bool y=0;
			bool yfind=0;
			for (int j = 0; j < height; j++) {
				bool yfind = 0;
				for (int i = 0; i < letter.xmax - letter.xmin; i++) {
					if (image[Index(letter.xmin+i, j)] == (unsigned char)255) {
						if (!y) {
							letter.ymin = j;
							y = 1;
						}
						yfind = 1;
					}
				}if (!yfind && y) {
					if (j > height / 2) {
						letter.ymax = j - 1;
						y = 0;
						//cout << letter.ymin << " " << letter.ymax << "\n"; //here letter size
						plik << chr(letternumber) << " ";
						letternumber++;
						for (int m = letter.ymin; m <= letter.ymax; m++) {
							float wt = 0;
							for (int n = letter.xmin; n <= letter.xmax; n++) {
								if (image[Index(n,m)] == (unsigned char)255) {
									wt++;
								}
							}
							plik << wt / (letter.xmax - letter.xmin) << " ";
						}
						plik << "\n";
					}
				}
			}
		}
	}
	plik.close();
	image.clear();
}

void Rotation() {
	char File[] = "szyfr_2.png";
	std::vector<unsigned char> newimage;
	decodeOneStep(File);
	//cout << image.size();
	char pixel[3];
	for(int i=0;i<image.size();i+=4){
		pixel[0] = image[image.size() - 4 - i];
		pixel[1] = image[image.size() - 3 - i];
		pixel[2] = image[image.size() - 2 - i];
		newimage.push_back(pixel[0]);
		newimage.push_back(pixel[1]);
		newimage.push_back(pixel[2]);
		newimage.push_back((char(255)));
	}
	char Name[] = "test2.png";
	encodeOneStep(Name, newimage, width, height);
	image.clear();
}
int main()
{
	Template();
	Image1();
	Rotation();
	Image2();
	Image3();
}

