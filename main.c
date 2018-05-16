#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pdi.h"

/*============================================================================*/

//#define INPUT_IMAGE "img/7.bmp"
#define OVERLAY_IMAGE "./img/Wind Waker GC.bmp"

/*============================================================================*/

void binarizaLocal(Imagem *in, Imagem *out, int altura, int largura);

/*============================================================================*/

int main()
{
	int i, j;
	float r, g, b;
	char *files[9] = {"./img/0.BMP", "./img/1.bmp", "./img/2.bmp", "./img/3.bmp", "./img/4.bmp",
					   "./img/5.bmp", "./img/6.bmp", "./img/7.bmp", "./img/8.bmp"};
	char fileName[20];

	for (int idx = 0; idx < 9; idx++)
	{
		Imagem *img = abreImagem(files[idx], 3);
		if (!img)
		{
			printf("Erro abrindo a imagem.\n");
			exit(1);
		}
		Imagem *overlay = abreImagem(OVERLAY_IMAGE, 3);

		Imagem *overlay2 = criaImagem(img->largura, img->altura, 3);

		redimensionaNN(overlay, overlay2);

		Imagem *img_out = criaImagem(img->largura, img->altura, 3);

		for (i = 0; i < img->altura; i++)
		{
			for (j = 0; j < img->largura; j++)
			{
				r = img->dados[0][i][j];
				g = img->dados[1][i][j];
				b = img->dados[2][i][j];

				if (g - r > 0.1 && g - b > 0.1)
				{
					img_out->dados[0][i][j] = overlay2->dados[0][i][j];
					img_out->dados[1][i][j] = overlay2->dados[1][i][j];
					img_out->dados[2][i][j] = overlay2->dados[2][i][j];
				}
				else
				{
					img_out->dados[0][i][j] = img->dados[0][i][j];
					img_out->dados[1][i][j] = img->dados[1][i][j];
					img_out->dados[2][i][j] = img->dados[2][i][j];
				}
			}
		}

		Imagem *img_buffer = criaImagem(img->largura, img->altura, 3);

		filtroGaussiano(img_out, img_buffer,(float)1.4,(float)1.4, NULL);

		sprintf(fileName, "./resultados/%d-final.bmp", idx);
		salvaImagem(img_buffer, fileName);
		salvaImagem(overlay2, "resize.bmp");

		destroiImagem(img_out);
		destroiImagem(img);
	}
	return (0);
}
