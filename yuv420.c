#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int simplest_yuv420_split(char *, int, int);

int simplest_yuv420_gray(char *, int, int, int);

int simplest_yuv420_halfy(char *, int ,int , int);

int main(int argc, char const *argv[])
{

    // simplest_yuv420_split("lena_256x256_yuv420p.yuv", 256, 256);

    // simplest_yuv420_gray("lena_256x256_yuv420p.yuv", 256, 256, 1);

    simplest_yuv420_halfy("lena_256x256_yuv420p.yuv", 256, 256, 1);

    return 0;
}

// 让图片变成灰色；
int simplest_yuv420_gray(char *url, int w, int h, int num)
{
    FILE *fp = fopen(url, "rb+");
    FILE *fp1 = fopen("output_gray.yuv", "wb+");
    char *pic = (char *)malloc(w * h * 3 / 2);

    for (int i = 0; i < num; i++)
    {
        fread(pic, 1, w * h * 3 / 2, fp);
        // Gray
        memset(pic + w * h, 128, w * h / 2);
        fwrite(pic, 1, w * h * 3 / 2, fp1);
    }

    free(pic);
    fclose(fp);
    fclose(fp1);
    return 0;
}

// 分离图片的y, u, v数据;
int simplest_yuv420_split(char *path, int w, int h)
{

    FILE *fp = fopen(path, "rb+");
    FILE *fp1 = fopen("output_420_y.yuv", "wb+");
    FILE *fp2 = fopen("output_420_u.yuv", "wb+");
    FILE *fp3 = fopen("output_420_v.yuv", "wb+");

    unsigned char *pic = (unsigned char *)malloc(w * h * 3 / 2);

    fread(pic, 1, w * h * 3 / 2, fp);

    // y
    fwrite(pic, 1, w * h, fp1);
    // u
    fwrite(pic + w * h, 1, w * h / 4, fp2);
    // v
    fwrite(pic + w * h * 5 / 4, 1, w * h / 4, fp3);

    free(pic);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    // fclose(fp1);
}

//图片亮度减半；
int simplest_yuv420_halfy(char *url, int w, int h, int num)
{
    FILE *fp = fopen(url, "rb+");
    FILE *fp1 = fopen("output_half.yuv", "wb+");

    unsigned char *pic = (unsigned char *)malloc(w * h * 3 / 2);

    for (int i = 0; i < num; i++)
    {
        fread(pic, 1, w * h * 3 / 2, fp);
        // Half
        for (int j = 0; j < w * h; j++)
        {
            unsigned char temp = pic[j] / 2;
            // printf("%d,\n",temp);
            pic[j] = temp;
        }
        fwrite(pic, 1, w * h * 3 / 2, fp1);
    }

    free(pic);
    fclose(fp);
    fclose(fp1);

    return 0;
}