#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    const unsigned char BOM[3] = { '\xEF', '\xBB', '\xBF' };
    char file_name[64] = { "target.csv" };
    if (argc > 1) strcpy(file_name, argv[1]);
    FILE* one = fopen(file_name, "r+b");
    if (!one) return -1;
    unsigned char buffer[64];
    int n = fread(buffer, 1, 3, one);
    if (n != 3)return -2;
    if (memcmp(buffer, BOM, 3) != 0)
    {   printf("file '%s' has no BOM\n", file_name);
        fclose(one);
        return 0;
    };
    n = fseek(one, 0, SEEK_SET);
    if (n != 0) return -3;
    buffer[0] = buffer[1] = buffer[2] = '*';
    n = fwrite(buffer, 1, 3, one);
    if (n == 3)
        printf("Byte Order Mark changed to '***'\n");
    else
        printf("Error writing to file\n");
    fclose(one);
    return 0;
}