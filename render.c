#include <stdio.h>
#include <stdlib.h>
#include <math.h>	
typedef struct VEC2 {float x;float y;} VEC2;
VEC2 player = {0.5,0.5};
unsigned char bitmapHeader[14] = {0x42,0x4d,0x46,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x00,0x00,0x00};
unsigned char bitmapCoreHeader[40] = {0x28,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x01,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
0x00,0x03,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

void imageGenerator(int size){
	char itt = 0;
	for(int i = size;i > 0;i/=256){
		bitmapCoreHeader[4 + itt] = i;
		bitmapCoreHeader[8 + itt] = i;
		itt++;
	}
	itt = 0;
	for(int i = size * size * 3;i > 0;i/=256){
		bitmapCoreHeader[20 + itt] = i;
		itt++;
	}
	unsigned char * texture = calloc(size * size * 3,1);
	itt = 0;
	for(int i = size;i > 0;i/=10){
		itt++;
	}
	char * str = malloc(itt + 3);
	str[itt] = 0x2E;
	str[itt + 1] = 0x62;
	str[itt + 2] = 0x6D;
	str[itt + 3] = 0x70;
	str[itt + 4] = 0x00;
	for(int i = size;i > 0;i/=10){
		str[itt - 1] = 0x30 + i % 10;
		itt--;
	}
	FILE * image = fopen(str,"wb");
	fwrite(&bitmapHeader,1,sizeof(bitmapHeader),image);
	fwrite(&bitmapCoreHeader,1,sizeof(bitmapCoreHeader),image);
	int itt2 = 0;
	int itt3 = 0;
	for(int i = 0;i < size * size * 3;i+=size * 3){
		for(int i2 = 0;i2 < size * 3;i2+=3){
			float rx = (float)itt2 / size - 0.5;
			float ry = (float)itt3 / size - 0.5;
			float x = 0;
			float y = 0;
			unsigned char itterations = 0;
			while(x + y < 256 && itterations < 255){
				float xtemp = x * x - y * y + rx;
				y = 2*x*y + ry;
				x = xtemp;
				itterations++;
			}
			texture[i + i2] = itterations;
			itt3++;
		}
		itt2++;
		itt3 = 0;
	}
	fwrite(texture,1,size * size * 3,image);
	fclose(image);
	free(texture);
	printf("%i",size);
	printf("%c",10);
}

int main(void){
	for(int i = 8;i < 20000;i*=2){
		imageGenerator(i);
	}
}
