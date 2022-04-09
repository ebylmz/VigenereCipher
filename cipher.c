/**
 * @author  Emirkan Burak Yilmaz
 * @brief   CSE108 LAB6 - Vigenère Cipher
 */

#include <stdio.h>

#define ALPHA_NUM 26
#define MAX_TEXT_LEN 100

void displayTable(char table[][ALPHA_NUM]);
void generateAlphaTable(char table[][ALPHA_NUM]);
void encryptAll(char table[][ALPHA_NUM], char plaintext[], char key[], char cipherText[]);
char encrypt(char table[][ALPHA_NUM], char alpa, char key);
void decryptAll(char table[][ALPHA_NUM], char plaintext[], char keystream[], char cipherText[]);
char decrypt(char table[][ALPHA_NUM], char alpa, char key);
void createKeyStream(char plaintext[], char key[], char keystream[]);
void read(char buffer[]);
void write(char buffer[]);
int length(char buffer[]);

int main(void) {
    char table[ALPHA_NUM][ALPHA_NUM];
    char plaintext[MAX_TEXT_LEN];
    char ciphertext[MAX_TEXT_LEN];
    char key[MAX_TEXT_LEN];
    char keystream[MAX_TEXT_LEN];
    
    // create and display the alpabet table
    generateAlphaTable(table);
    displayTable(table);

    printf("\n\n*** ENCRYPTION ***\n\n");
    // get the plain text and key from the user
    printf("Plaintext: ");
    read(plaintext);
    printf("Key: ");
    read(key);
    // create key stream and encrypt the plaintext
    createKeyStream(plaintext, key, keystream);
    encryptAll(table, plaintext, keystream, ciphertext);
    printf("Keystream:  ");
    write(keystream);
    printf("Ciphertext: ");
    write(ciphertext);

    printf("\n\n*** DECRYPTION ***\n\n");
    // get the ciphertext and key from the user
    printf("Ciphertext: ");
    read(plaintext);
    printf("Key: ");
    read(key);
    // create key stream and decrypt the encrypted text
    createKeyStream(plaintext, key, keystream);
    decryptAll(table, plaintext, keystream, ciphertext);
    printf("Keystream:  ");
    write(keystream);
    printf("Ciphertext: ");
    write(ciphertext);
}

void generateAlphaTable(char table[][ALPHA_NUM]) {
    int i, j;
    // fill the first column with letters from A to Z to use them fill the rest
    for (i = 0; i < ALPHA_NUM; ++i)
        table[0][i] = 'A' + i;
    // fill the rest of the table
    for (i = 1; i < ALPHA_NUM; ++i)
        for (j = 0; j < ALPHA_NUM; ++j)
            table[i][j] = table[0][(i + j) % ALPHA_NUM];
}

void displayTable(char table[][ALPHA_NUM]) {
    int i, j;
    for (i = 0; i < ALPHA_NUM; ++i) {
        for (j = 0; j < ALPHA_NUM; ++j)
            printf("%c ", table[i][j]);
        putchar('\n');
    }
}

void createKeyStream(char plaintext[], char key[], char keystream[]) {
    int i;
    int len = length(key); // used to take modules operation 
    for (i = 0; plaintext[i] != '\n'; ++i)
        keystream[i] = key[i % len];
    keystream[i] = '\n';
}

/* Assumes plaintext and keystream consist of only capital letters */
void encryptAll(char table[][ALPHA_NUM], char plaintext[], char keystream[], char cipherText[]) {
    int i;
    // encrypt each letter one by one
    for (i = 0; plaintext[i] != '\n'; ++i) 
        cipherText[i] = encrypt(table, plaintext[i], keystream[i]); 
    // add new line charachter at the end of the encrypted text
    cipherText[i] = '\n';   
}

char encrypt(char table[][ALPHA_NUM], char alpa, char key) {
    return table[key - 'A'][alpa - 'A'];
}

void decryptAll(char table[][ALPHA_NUM], char plaintext[], char keystream[], char cipherText[]) {
    int i;
    // encrypt each letter one by one
    for (i = 0; plaintext[i] != '\n'; ++i) 
        cipherText[i] = decrypt(table, plaintext[i], keystream[i]); 
    // add new line charachter at the end of the encrypted text
    cipherText[i] = '\n';   
}

char decrypt(char table[][ALPHA_NUM], char alpa, char key) {
    int r = key - 'A'; // decrypt the row
    int c = 0;
    // alpa (encrypted alphabetic char) was encrypted by using the key 
    // search encypted value to find its coloumn in alphabet table
    while (table[r][c] != alpa) 
        ++c;
    return table[0][c];
}

void read(char buffer[]) {
    // read all the charachters till new line (include the new line to buffer) 
    int i = -1;
    do {
        ++i;
        buffer[i] = getchar();
    } while(buffer[i] != '\n');
}

void write(char buffer[]) {
    int i = -1;
    do {
        putchar(buffer[++i]);
    } while (buffer[i] != '\n');
}

int length(char buffer[]) {
    int len = 0;
    while (buffer[len] != '\n')
        ++len;
    return len;
}