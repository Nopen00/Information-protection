/////*
////
//// * des.c	v1.0
////
//// *
////
//// * Copyleft 2001 Jinius. All Rights Unreserved.
////
//// *
////
//// * Permission to use, copy, modify, and distribute this software
////
//// * for NON-COMMERCIAL purpose is hereby granted.
////
//// *
////
//// * http://kuls.korea.ac.kr/~jinius/
////
//// * http://jin.wo.to/
////
//// *
////
//// * email : jiniuskorea@hanmail.net
////
//// */
////
////
////#include <string.h>
////
////#include <stdlib.h>
////
////#include "des.h"
////
////#include "bit.h"
////
////
////
////void permute(const unsigned char *input, unsigned char *output, const int *mapping, const int mapsize)
////
////{
////
////	unsigned char *buffer;
////
////	int i;
////
////
////
////	buffer = (unsigned char *)malloc((mapsize+7) / 8);		/* buffer allocate */
////
////
////
////	for(i = 0; i < mapsize; i++)
////
////		set_bit(buffer, i, get_bit(input, mapping[i] - 1));
////
////
////
////	memcpy(output, buffer, (mapsize+7) / 8);
////
////
////
////	free(buffer);
////
////}
////
////
////
/////* key generator */
////
////void set_subkey(unsigned char subkey[16][6], const unsigned char *key)
////
////{
////
////	unsigned char buffer[7];
////
////	unsigned char lkey[4], rkey[4];
////
////	int i,j;
////
////	memset(lkey, 0, 4);		/* fill with 0 */
////
////	memset(rkey, 0, 4);
////
////
////
////	permute(key, buffer, pc1, 56);
////
////
////
////	/* Devide 56-bit block to two 28-bit block */
////
////	for(i = 0; i < 28; i++) {
////
////		set_bit(lkey, i, get_bit(buffer, i));
////
////		set_bit(rkey, i, get_bit(buffer, i + 28));
////
////	}
////
////
////
////	/* generate 16 subkey */
////
////	for(i = 0; i < 16; i++) {
////
////		left_rotate(lkey, rotate[i], 28);
////
////		left_rotate(rkey, rotate[i], 28);
////
////
////
////		for(j = 0; j < 28; j++) {
////
////			set_bit(buffer, j, get_bit(lkey, j));
////
////			set_bit(buffer, j + 28, get_bit(rkey, j));
////
////		}
////
////
////
////		/* export 'i'th subkey */
////
////		permute(buffer, subkey[i], pc2, 48);
////
////	}
////
////}
////
////
////
/////* One of 16 round in DES main function */
////
////void round(unsigned char *lblock, unsigned char *rblock, const unsigned char *subkey)
////
////{
////
////	unsigned char buffer[6];
////
////	int i;
////
////
////
////	permute(rblock, buffer, e, 48);
////
////	xor_bit(buffer, subkey, buffer, 48);
////
////	sbox(buffer);
////
////	permute(buffer, buffer, p32, 32);
////
////	xor_bit(buffer, lblock, buffer, 32);
////
////
////
////	memcpy(lblock, rblock, 4);
////
////	memcpy(rblock, buffer, 4);
////
////}
////
////
////
/////* S-box */
////
////void sbox(unsigned char *data)
////
////{
////
////	unsigned char buffer[4];
////
////	unsigned char temp;
////
////	int i, j;
////
////	int row, col;
////
////
////
////	for(i = 0; i < 8; i++) {
////
////		row = (get_bit(data, i * 6) << 1) + get_bit(data, i * 6 + 5);
////
////		// 잘못된 예
////		//col = (get_bit(data, i * 6 + 2) << 3) + (get_bit(data, i * 6 + 2) << 2) ...
////			// 올바른 예
////			col = (get_bit(data, i * 6 + 1) << 3)
////			| (get_bit(data, i * 6 + 2) << 2)
////			| (get_bit(data, i * 6 + 3) << 1)
////			| get_bit(data, i * 6 + 4);
////
////		temp = s_box[row][col];
////
////
////
////		for(j = 0; j < 4; j++)
////
////			set_bit(buffer, i * 4 + j, get_bit(&temp, j + 4));
////
////	}
////
////
////
////	memcpy(data, buffer, 4);
////
////
////
////	return;
////
////}
////
////
////
////void des_encipher(const unsigned char *plaintext, unsigned char *ciphertext, const unsigned char *key)
////
////{
////
////	des_main(plaintext, ciphertext, key, encipher);
////
////}
////
////
////
////void des_decipher(const unsigned char *ciphertext, unsigned char *plaintext, const unsigned char *key)
////
////{
////
////	des_main(ciphertext, plaintext, key, decipher);
////
////}
////
////
////
////static int des_main(const unsigned char *input, unsigned char *output, const unsigned char *key, DesOrder direction)
////
////{
////
////	static unsigned char subkey[16][6];
////
////	unsigned char buffer[8];
////
////	int i;
////
////
////
////	if(key != NULL) set_subkey(subkey, key);
////
////	permute(input, buffer, ip, 64);
////
////
////
////	for(i = 0; i < 16; i++) {
////
////		if(direction == encipher)
////
////			round(buffer, buffer + 4, subkey[i]);
////
////		else round(buffer, buffer + 4, subkey[15 - i]);
////
////	}
////
////
////
////	memcpy(output, buffer + 4, 4);
////
////	memcpy(output + 4, buffer, 4);
////
////
////
////	permute(output, output, fp, 64);
////
////
////
////	return 0;
////
////}
////
////int main() {
////
////	unsigned char input[8] = { 'a','b','c','d','a','b','c','d' };
////	unsigned char key[7] = { 'a','b','c','d','a','b','c' };
////
////	//const unsigned char input[8] = { "abcdabcd" }; //평문
////	unsigned char output[8] = { 0 }; //암호문
////	unsigned char output2[8] = { 0 }; //복호문
////	//unsigned char key[7] = { "abcdabc" };
////	
////	des_encipher(input, output, key);
////	des_decipher(output, output2, key);
////
////	//des_main(input, output, key, encipher);
////	//des_main(output, output2, key, decipher);
////
////	return 0;
////
////}
//
//
//// des_debug.c
//// DES debug version with verbose round-by-round printing and bug fixes.
//// (기본 DES 테이블들은 des.h 에 정의되어 있다고 가정)
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include "des.h"
//#include "bit.h"
//
//#define DEBUG 1   // 0: disable debug prints, 1: enable
//
//static void print_bytes_hex(const unsigned char* b, int n) {
//    for (int i = 0; i < n; ++i) printf("%02X ", b[i]);
//}
//
//static void print_block_hex(const char* label, const unsigned char* b, int n) {
//    if (!DEBUG) return;
//    printf("%s:", label);
//    for (int i = 0; i < n; ++i) printf(" %02X", b[i]);
//    printf("\n");
//}
//
///* permute: mapping에 따라 input의 비트를 재배치 -> output */
//void permute(const unsigned char* input, unsigned char* output, const int* mapping, const int mapsize)
//{
//    unsigned char buffer[8]; // mapsize <= 64이면 충분
//    int i;
//
//    memset(buffer, 0, sizeof(buffer));
//
//    for (i = 0; i < mapsize; i++)
//        set_bit(buffer, i, get_bit(input, mapping[i] - 1));
//
//    memcpy(output, buffer, (mapsize + 7) / 8);
//}
//
///* key generator
//   subkey[16][6] : 16개의 서브키(각 48비트 -> 6바이트) */
//void set_subkey(unsigned char subkey[16][6], const unsigned char* key)
//{
//    unsigned char buffer[7];
//    unsigned char lkey[4], rkey[4];
//    int i, j;
//
//    memset(lkey, 0, 4);
//    memset(rkey, 0, 4);
//    memset(buffer, 0, sizeof(buffer));
//
//    permute(key, buffer, pc1, 56);
//
//    /* divide 56-bit block to two 28-bit blocks */
//    for (i = 0; i < 28; i++) {
//        set_bit(lkey, i, get_bit(buffer, i));
//        set_bit(rkey, i, get_bit(buffer, i + 28));
//    }
//
//    /* generate 16 subkeys */
//    for (i = 0; i < 16; i++) {
//        left_rotate(lkey, rotate[i], 28);
//        left_rotate(rkey, rotate[i], 28);
//
//        /* merge L and R into buffer (56bit) */
//        for (j = 0; j < 28; j++) {
//            set_bit(buffer, j, get_bit(lkey, j));
//            set_bit(buffer, j + 28, get_bit(rkey, j));
//        }
//
//        /* export i'th subkey (48bit) */
//        permute(buffer, subkey[i], pc2, 48);
//
//        if (DEBUG) {
//            printf("Subkey %2d: ", i + 1);
//            print_bytes_hex(subkey[i], 6);
//            printf("\n");
//        }
//    }
//}
//
///* S-box substitution (48bit -> 32bit)
//   NOTE: 기존 코드의 col 계산 오류 수정:
//   col은 6비트 블록의 비트[1..4]를 사용해야 함.
//*/
//void sbox(unsigned char* data)
//{
//    unsigned char buffer[4];
//    unsigned char temp;
//    int i, j;
//    int row, col;
//
//    memset(buffer, 0, 4);
//
//    for (i = 0; i < 8; i++) {
//        /* 각 6비트 블록: 비트 인덱스 = i*6 ... i*6+5 */
//        row = (get_bit(data, i * 6) << 1) + get_bit(data, i * 6 + 5);
//
//        /* col: 비트 i*6+1 .. i*6+4 (MSB->LSB 순서로 가정) */
//        col = (get_bit(data, i * 6 + 1) << 3)
//            + (get_bit(data, i * 6 + 2) << 2)
//            + (get_bit(data, i * 6 + 3) << 1)
//            + get_bit(data, i * 6 + 4);
//
//        temp = s_box[i][row * 16 + col]; // 일부 구현은 s_box[row][col] 대신 flat 배열을 사용
//
//        /* temp의 하위 4비트를 buffer의 4비트로 채움 (j=0..3) */
//        for (j = 0; j < 4; j++)
//            set_bit(buffer, i * 4 + j, (temp >> (3 - j)) & 0x01);
//    }
//
//    memcpy(data, buffer, 4);
//}
//
///* 한 라운드 수행: L,R, subkey(48bit) */
//void round_func(unsigned char* lblock, unsigned char* rblock, const unsigned char* subkey)
//{
//    unsigned char buffer[6];
//    memset(buffer, 0, 6);
//
//    permute(rblock, buffer, e, 48);        // E 확장(32->48)
//    xor_bit(buffer, subkey, buffer, 48);   // XOR with subkey
//    sbox(buffer);                          // S-box (48->32)
//    permute(buffer, buffer, p32, 32);      // P-box (32->32)
//    xor_bit(buffer, lblock, buffer, 32);   // XOR with L
//
//    /* L <- R, R <- buffer */
//    memcpy(lblock, rblock, 4);
//    memcpy(rblock, buffer, 4);
//}
//
///* 래퍼: 암/복호화용 */
//void des_encipher(const unsigned char* plaintext, unsigned char* ciphertext, const unsigned char* key)
//{
//    des_main(plaintext, ciphertext, key, encipher);
//}
//
//void des_decipher(const unsigned char* ciphertext, unsigned char* plaintext, const unsigned char* key)
//{
//    des_main(ciphertext, plaintext, key, decipher);
//}
//
///* DES main - 입력/출력/키, direction(encipher/decipher) */
//static int des_main(const unsigned char* input, unsigned char* output, const unsigned char* key, DesOrder direction)
//{
//    static unsigned char subkey[16][6];
//    unsigned char buffer[8];
//    unsigned char L[4], R[4];
//    int i;
//
//    if (key != NULL) set_subkey(subkey, key);
//
//    permute(input, buffer, ip, 64);   // Initial Permutation
//    if (DEBUG) {
//        printf("After IP: ");
//        print_bytes_hex(buffer, 8);
//        printf("\n");
//    }
//
//    /* buffer: 8바이트 (L||R) */
//    memcpy(L, buffer, 4);
//    memcpy(R, buffer + 4, 4);
//
//    for (i = 0; i < 16; i++) {
//        if (direction == encipher) {
//            if (DEBUG) {
//                printf("Round %2d start: L=", i + 1); print_bytes_hex(L, 4); printf(" R="); print_bytes_hex(R, 4); printf("\n");
//            }
//            round_func(L, R, subkey[i]);
//        }
//        else {
//            if (DEBUG) {
//                printf("Round %2d start (dec): L=", i + 1); print_bytes_hex(L, 4); printf(" R="); print_bytes_hex(R, 4); printf("\n");
//            }
//            round_func(L, R, subkey[15 - i]);
//        }
//        if (DEBUG) {
//            printf("Round %2d end  : L=", i + 1); print_bytes_hex(L, 4); printf(" R="); print_bytes_hex(R, 4); printf("\n\n");
//        }
//    }
//
//    /* 최종 스왑 (L<->R) 후 결합 */
//    memcpy(buffer, R, 4);
//    memcpy(buffer + 4, L, 4);
//
//    /* Final Permutation */
//    permute(buffer, output, fp, 64);
//
//    if (DEBUG) {
//        printf("After FP (output): ");
//        print_bytes_hex(output, 8);
//        printf("\n");
//    }
//
//    return 0;
//}
//
//int main()
//{
//    /* 테스트용 입력/키 (8바이트) */
//    unsigned char input[8] = "abcdabcd";   // 평문(8바이트)
//    unsigned char key[8] = "ABCDEFGH";   // 키(8바이트) - 실제 DES는 패리티 등 고려
//    unsigned char out_enc[8] = { 0 };
//    unsigned char out_dec[8] = { 0 };
//
//    printf("Plaintext : ");
//    print_bytes_hex(input, 8); printf("  \"%s\"\n", input);
//    printf("Key       : ");
//    print_bytes_hex(key, 8); printf("\n\n");
//
//    /* 암호화 */
//    des_encipher(input, out_enc, key);
//
//    printf("\nCiphertext (hex): ");
//    print_bytes_hex(out_enc, 8); printf("\n");
//
//    /* 복호화 */
//    des_decipher(out_enc, out_dec, key);
//
//    printf("Decrypted (hex): ");
//    print_bytes_hex(out_dec, 8); printf("\n");
//    printf("Decrypted (str): \"%.*s\"\n", 8, out_dec);
//
//    return 0;
//}
