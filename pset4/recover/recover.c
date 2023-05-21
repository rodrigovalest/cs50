#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int check_jpeg(int byte1, int byte2, int byte3, int byte4);

int main(int argc, char *argv[])
{
    //Evitar escrever entrada errada no terminal
    if (argc != 2)
    {
        printf("Erro: tente usar o formato ./recover imagem\n");
        return 1;
    }

    //Criar arquivo e evitar abrir arquivo inválido
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Erro: digite o nome de um arquivo válido\n");
        return 2;
    }

    BYTE buffer[512];
    char *nomejpeg[4];
    FILE *img;

    int n = 0;

    while (1)
    {
        int check = fread(buffer, 1, 512, file);

        if (check != 512)
        {
            break;
        }

        if (check_jpeg(buffer[0], buffer[1], buffer[2], buffer[3]) == 1)
        {
            n++;
            printf("Achei o jpeg (%i)\n", n);

            if (n > 1)
            {
                fclose(img);
            }

            sprintf(nomejpeg[0], "%03i.jpg", n);
            img = fopen(nomejpeg[0], "w");
        }

        if (n > 0)
        {
            fwrite(buffer, 1, 512, img);
        }
    }

    fclose(file);
}


int check_jpeg(int byte1, int byte2, int byte3, int byte4)
{
    if (byte1 == 0xff && byte2 == 0xd8 && byte3 == 0xff && (byte4 & 0xf0) == 0xe0)
    {
        return 1;
    }

    return 0;
}