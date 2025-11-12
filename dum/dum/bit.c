///*
// * bit.c
// *
// * Copyleft 2001 Jinius. All Rights Unreserved.
// *
// * Permission to use, copy, modify, and distribute this software
// * for NON-COMMERCIAL purpose is hereby granted.
// *
// * http://kuls.korea.ac.kr/~jinius/
// * http://jin.wo.to/
// *
// * email : jiniuskorea@hanmail.net
// */
//#include <stdlib.h>
//#include <string.h>
//#include "bit.h"
//
//int get_bit(const unsigned char *data, const int position)
//{
//	unsigned char mask;
//	int state;
//
//	mask = 0x80 >> (position % 8);		/* 0x80 : 10000000 */
//	state = ((data[position / 8] & mask) == mask) ? 1 : 0;
//
//	return state;
//}
//
//void set_bit(unsigned char *data, const int position, const int state)
//{
//	unsigned char mask;
//
//	mask = 0x80 >> (position % 8);		/* 0x80 : 10000000 */
//
//	if(state) data[position / 8] = data[position / 8] | mask;
//	else data[position / 8] = data[position / 8] & (~mask);
//
//	return;
//}
//
//void xor_bit(const unsigned char *input1, const unsigned char *input2, unsigned char *output, const int size)
//{
//	int i;
//
//	for(i = 0; i < (size+7) / 8; i++)		/* (size+7) / 8 : ceil(size / 8) */
//		output[i] = (input1[i] | input2[i]) & ~(input1[i] & input2[i]);
//
//	for(i *= 8; i < size; i++) {
//		if(get_bit(input1, i) != get_bit(input2, i)) set_bit(output, i, 1);
//		else set_bit(output, i, 0);
//	}
//
//	return;
//}
//
//void right_rotate(unsigned char *data, const int count, const int size)
//{
//	unsigned char *buffer;
//	int i;
//
//	if(count > 0) {
//		buffer = (unsigned char *)malloc((size+7) / 8);		/* (size+7) / 8 : ceil(size / 8) */
//
//		memcpy(buffer, data, (size+7) / 8);
//
//		for(i = 0; i < size; i++)
//			set_bit(buffer, (i + count) % size, get_bit(data, i));
//
//		memcpy(data, buffer, (size+7) / 8);
//
//		free(buffer);
//	}
//	else if(count < 0) right_rotate(data, size - (-count) % size, size);
//
//	return;
//}
//
//void left_rotate(unsigned char *data, const int count, const int size)
//{
//	right_rotate(data, size - (count % size), size);
//}
