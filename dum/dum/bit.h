/*
 * bit.h
 *
 * Copyleft 2001 Jinius. All Rights Unreserved.
 *
 * Permission to use, copy, modify, and distribute this software
 * for NON-COMMERCIAL purpose is hereby granted.
 *
 * http://kuls.korea.ac.kr/~jinius/
 * http://jin.wo.to/
 *
 * email : jiniuskorea@hanmail.net
 */

int get_bit(const unsigned char *data, const int position);
void set_bit(unsigned char *data, const int position, const int state);
void xor_bit(const unsigned char *input1, const unsigned char *input2, unsigned char *output, const int size);
void right_rotate(unsigned char *data, const int count, const int size);
void left_rotate(unsigned char *data, const int count, const int size);
