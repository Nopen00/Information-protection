#pragma warning(disable:4996)

#include <stdio.h>

#include <iostream>







char* Cipher(char* src, char* key) {



    char* des = new char[strlen(src) + 1];



    for (int i = 0; i < strlen(src); i++)

    switch (src[i]) {

    case 'a':

    des[i] = key[0];

    break;

    case 'b':

    des[i] = key[1];

    break;

    case 'c':

    des[i] = key[2];

    break;

    case 'd':

    des[i] = key[3];

    break;

    case 'e':

    des[i] = key[4];

    break;

    case 'f':

    des[i] = key[5];

    break;

    case 'g':

    des[i] = key[6];

    break;

    case 'h':

    des[i] = key[7];

    break;

    case 'i':

    des[i] = key[8];

    break;

    case 'j':

    des[i] = key[9];

    break;

    case 'k':

    des[i] = key[10];

    break;

    case 'l':

    des[i] = key[11];

    break;

    case 'm':

    des[i] = key[12];

    break;

    case 'n':

    des[i] = key[13];

    break;

    case 'o':

    des[i] = key[14];

    break;

    case 'p':

    des[i] = key[15];

    break;

    case 'q':

    des[i] = key[16];

    break;

    case 'r':

    des[i] = key[17];

    break;

    case 's':

    des[i] = key[18];

    break;

    case 't':

    des[i] = key[19];

    break;

    case 'u':

    des[i] = key[20];

    break;

    case 'v':

    des[i] = key[21];

    break;

    case 'w':

    des[i] = key[22];

    break;

    case 'x':

    des[i] = key[23];

    break;

    case 'y':

    des[i] = key[24];

    break;

    case 'z':

    des[i] = key[25];

    break;

    case 'A':

    des[i] = key[26];

    break;

    case 'B':

    des[i] = key[27];

    break;

    case 'C':

    des[i] = key[28];

    break;

    case 'D':

    des[i] = key[29];

    break;

    case 'E':

    des[i] = key[30];

    break;

    case 'F':

    des[i] = key[31];

    break;

    case 'G':

    des[i] = key[32];

    break;

    case 'H':

    des[i] = key[33];

    break;

    case 'I':

    des[i] = key[34];

    break;

    case 'J':

    des[i] = key[35];

    break;

    case 'K':

    des[i] = key[36];

    break;

    case 'L':

    des[i] = key[37];

    break;

    case 'M':

    des[i] = key[38];

    break;

    case 'N':

    des[i] = key[39];

    break;

    case 'O':

    des[i] = key[40];

    break;

    case 'P':

    des[i] = key[41];

    break;

    case 'Q':

    des[i] = key[42];

    break;

    case 'R':

    des[i] = key[43];

    break;

    case 'S':

    des[i] = key[44];

    break;

    case 'T':

    des[i] = key[45];

    break;

    case 'U':

    des[i] = key[46];

    break;

    case 'V':

    des[i] = key[47];

    break;

    case 'W':

    des[i] = key[48];

    break;

    case 'X':

    des[i] = key[49];

    break;

    case 'Y':

    des[i] = key[50];

    break;

    case 'Z':

    des[i] = key[51];

    break;

    default:

    des[i] = src[i];

    }





    return des;



}



void Alpha_Hist(char* in) {

    int hist[26] = { 0 };

    for (int i = 0; i < strlen(in); i++) {

        if (65 <= in[i] && in[i] <= 90)

        hist[in[i] - 65]++;

        if (97 <= in[i] && in[i] <= 122)

        hist[in[i] - 97]++;

    }



    for (int i = 0; i < 26; i++) {

        printf("%c : %d\n", i + 65, hist[i]);

    }

}



char* File_Read(char* In) {



    FILE* fp = NULL;



    fp = fopen("plaintxt.txt", "rt");

    fseek(fp, 0, SEEK_END);    // 파일 포인터를 파일의 끝으로 이동시킴

    int size = ftell(fp);          // 파일 포인터의 현재 위치를 얻음

    fseek(fp, 0, SEEK_SET);    // 파일 포인터를 파일의 끝으로 이동시킴

    In = new char[size + 1];

    memset(In, 0, size + 1);

    fread(In, size, sizeof(char), fp);

    fclose(fp);

    return In;

}



char* File_write(char* Out) {



    FILE* fp = NULL;



    fp = fopen("ciphertext.txt", "wt");

    int size = strlen(Out) - 5;

    fwrite(Out, sizeof(char), size, fp);

    fclose(fp);

    return Out;

}



char* double_transpose_cipher(char* src) {



    char* cipher = new char[strlen(src) + 1];

    memset(cipher, 0, strlen(src) + 1);



    for (int i = 0; i < strlen(src) /12; i++) {

        cipher[i * 12] = src[i * 12 + 11];

        cipher[i * 12 + 1] = src[i * 12 + 9];

        cipher[i * 12 + 2] = src[i * 12 + 8];

        cipher[i * 12 + 3] = src[i * 12 + 10];

        cipher[i * 12 + 4] = src[i * 12 + 7];

        cipher[i * 12 + 5] = src[i * 12 + 5];

        cipher[i * 12 + 6] = src[i * 12 + 4];

        cipher[i * 12 + 7] = src[i * 12 + 6];

        cipher[i * 12 + 8] = src[i * 12 + 3];

        cipher[i * 12 + 9] = src[i * 12 + 1];

        cipher[i * 12 + 10] = src[i * 12];

        cipher[i * 12 + 11] = src[i * 12 + 2];

    }



return cipher;

}



char* onetime_cipher(char* src, char * key) {



    char* cipher = new char[strlen(src) + 1];

    memset(cipher, 0, strlen(src) + 1);



    for (int i = 0; i < strlen(src) / 12; i++) {

        cipher[i * 12] = src[i * 12] ^ key[0];

        cipher[i * 12 + 1] = src[i * 12 + 1] ^ key[1];

        cipher[i * 12 + 2] = src[i * 12 + 2] ^ key[2];

        cipher[i * 12 + 3] = src[i * 12 + 3] ^ key[3];

        cipher[i * 12 + 4] = src[i * 12 + 4] ^ key[4];

        cipher[i * 12 + 5] = src[i * 12 + 5] ^ key[5];

        cipher[i * 12 + 6] = src[i * 12 + 6] ^ key[6];

        cipher[i * 12 + 7] = src[i * 12 + 7] ^ key[7];

        cipher[i * 12 + 8] = src[i * 12 + 8] ^ key[8];

        cipher[i * 12 + 9] = src[i * 12 + 9] ^ key[9];

        cipher[i * 12 + 10] = src[i * 12 + 10] ^ key[10];

        cipher[i * 12 + 11] = src[i * 12 + 11] ^ key[11];

    }



    return cipher;

}



int main()

{



    char key[53] = { 0 };

    char okey[12] = {1,2,3,4,1,2,3,4,1,2,3,4 };

    strcpy(key, "irstcnopfglqyzadejumkhvwxbIRSTCNOPFGLQYZADEJUMKHVWXB");




    char* plain = NULL;

    char* cipher = NULL;

    char* cipher2 = NULL;

    char* cipher3 = NULL;



    plain = File_Read(plain);

    cipher = Cipher(plain, key);

    cipher2 = double_transpose_cipher(cipher); // key : 123->321, 1234->4213

    cipher3 = onetime_cipher(cipher2, okey);

    File_write(cipher3);

    return 0;

}