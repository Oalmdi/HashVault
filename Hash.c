#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

#define DATA_SIZE 31
#define KEY 7

struct FileBlock {
    unsigned char folder_name;
    unsigned char data[DATA_SIZE];
};

void xorData(unsigned char data[]) {
    for (int i = 0; i < DATA_SIZE; i++) {
        data[i] = data[i] ^ KEY;
    }
}

void createFile() {
    struct FileBlock block;
    int hash;
    char folder[20];
    char path[100];

    block.folder_name = 'A';

    strcpy((char *)block.data, "This is secret file data");

    xorData(block.data);

    srand(time(NULL));
    hash = rand() % 900000 + 100000;

    sprintf(folder, "storage%c", block.folder_name);
    mkdir(folder, 0777);

    sprintf(path, "%s/%d.txt", folder, hash);

    FILE *fp = fopen(path, "wb");

    fwrite(&block, sizeof(block), 1, fp);

    fclose(fp);

    printf("File created and encrypted.\n");
    printf("Hash Key: %d\n", hash);
    printf("Saved in: %s\n", path);
}

void readFile() {
    struct FileBlock block;
    int hash;
    char folder[20];
    char path[100];

    printf("Enter Hash Key: ");
    scanf("%d", &hash);

    sprintf(folder, "storageA");
    sprintf(path, "%s/%d.txt", folder, hash);

    FILE *fp = fopen(path, "rb");

    if (fp == NULL) {
        printf("File not found.\n");
        return;
    }

    fread(&block, sizeof(block), 1, fp);

    fclose(fp);

    xorData(block.data);

    printf("Folder Name: %c\n", block.folder_name);
    printf("File Data: %s\n", block.data);
}

int main() {
    int choice;

    printf("1. Create encrypted file\n");
    printf("2. Read file by Hash Key\n");
    printf("Choose: ");
    scanf("%d", &choice);

    if (choice == 1) {
        createFile();
    }
    else if (choice == 2) {
        readFile();
    }
    else {
        printf("Wrong choice.\n");
    }

    return 0;
}