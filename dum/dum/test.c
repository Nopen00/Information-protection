///***************************************************************************
//* Copyright (c) 2000-2004, Future Systems, Inc. / Seoul, Republic of Korea *
//* All Rights Reserved.                                                     *
//*                                                                          *
//* This document contains proprietary and confidential information.  No     *
//* parts of this document or the computer program it embodies may be in     *
//* any way copied, duplicated, reproduced, translated into a different      *
//* programming language, or distributed to any person, company, or          *
//* corporation without the prior written consent of Future Systems, Inc.    *
//*                              Hyo Sun Hwang                               *
//*                372-2 YangJae B/D 6th Floor, Seoul, Korea                 *
//*                           +82-2-578-0581 (552)                           *
//***************************************************************************/
//
///*--------------------- [ Version/Command in detais] ---------------------*\
//Description : filename.? (CrypLib version 1.00)
//			(head file)	(C-source file)
//
//C0000 : Created by Hyo Sun Hwang (hyosun@future.co.kr) 2000/12/31
//
//C0001 : Modified by Hyo Sun Hwang (hyosun@future.co.kr) 2001/01/01
//
//\*------------------------------------------------------------------------*/
//
///*************** Header files *********************************************/
//#include <stdio.h>
//#include <time.h>
//#include "aes.h"
//#pragma warning(disable:4996)
//
///*************** Assertions ***********************************************/
//
///*************** Definitions / Macros  ************************************/
//#define KILO	1024
//#define MEGA	(KILO*KILO)
//
//////	Prine out BYTE data in ascending order and with no '0x'(hexa type)
//#undef PrintBYTE
//#define PrintBYTE(pfile, msg, Data, DataLen) {			\
//	int idx;											\
//	fprintf(pfile, "%5s =", msg);						\
//	for( idx=0; idx<(int)DataLen; idx++) {				\
//		if( (idx==0) || ((idx%16)!=0) )					\
//			fprintf(pfile, " %.2x", Data[idx]);			\
//		else											\
//			fprintf(pfile, "\n\t%.2x", Data[idx]);		\
//	}													\
//	fprintf(pfile, "\n");								\
//}
//
//////	한번에 'ByteLen'-bytes의 데이타를 처리하는 연산 'Oper'을
//////	'Iter'번 수행하고, 그 결과를 KByte/sec단위로 출력함.
//#define SPEED_TEST(str1, str2, Iter, ByteLen, Oper) {	\
//	unsigned idx;										\
//	clock_t start, finish;								\
//	double Sec, Mbps=0.0;								\
//	start = clock();									\
//	for( idx=0; idx<Iter; idx++)						\
//		{	Oper;	}									\
//	finish = clock();									\
//	Sec = (double)(finish-start) / CLOCKS_PER_SEC;		\
//	if( Sec!=0 )	Mbps = 8.0*ByteLen*idx/Sec/MEGA;	\
//	printf("%s%7.3fMbps(=%d*", str1, Mbps, Iter);		\
//	printf("%d", ByteLen);								\
//	printf("/%3.0f)%s", 1000.0*Sec, str2);				\
//}
//
///*************** New Data Types *******************************************/
//
///*************** Constant (Error Code) ************************************/
//#define CTR_USAGE_ERROR		0x2001
//#define CTR_KEYFILE_ERROR	0x2002
//
///*************** Global Variables *****************************************/
//char	Help[] = "\
//Usage1 : -[T/S]   (Test Value/Test Speed)\n\
//Usage2 : -[E/D] -[ECB/CBC/OFB/CFB/ECBPAD/CBCPAD/OFBPAD/CFBPAD] infile outfile\n\
//            (file 'key.dat' contains UserKey and IV)\n";
//
///*************** Prototypes ***********************************************/
//
////########################################################//
////######		Error Code 관리 함수				######//
////########################################################//
//
///*************************************************************************/
//typedef struct{
//	DWORD		ErrorCode;
//	BYTE		Message[32];
//} ERROR_MESSAGE;
//
//ERROR_MESSAGE	ErrorMessage[] = {
//	{CTR_FATAL_ERROR,		"CTR_FATAL_ERROR"},
//	{CTR_INVALID_USERKEYLEN,"CTR_INVALID_USERKEYLEN"},
//	{CTR_PAD_CHECK_ERROR,	"CTR_PAD_CHECK_ERROR"},
//	{CTR_DATA_LEN_ERROR,	"CTR_DATA_LEN_ERROR"},
//	{CTR_CIPHER_LEN_ERROR,	"CTR_CIPHER_LEN_ERROR"},
//	{CTR_USAGE_ERROR,		"CTR_USAGE_ERROR"},
//	{CTR_KEYFILE_ERROR,		"CTR_KEYFILE_ERROR"},
//	{0, ""},
//};
//
///**************************************************************************
//*
//*/
//void	Error(
//		DWORD	ErrorCode,
//		char	*Message)
//{
//	DWORD	i;
//
//	for( i=0; ErrorMessage[i].ErrorCode!=0; i++)
//		if( ErrorMessage[i].ErrorCode==ErrorCode )	break;
//
//	printf("ERROR(%s) :::: %s\n", ErrorMessage[i].Message, Message);
//	if( ErrorCode==CTR_USAGE_ERROR )	printf("\n%s", Help);
//	exit(1);
//}
//
////########################################################//
////######		Validity Test 관련 함수				######//
////########################################################//
//
///*************************************************************************/
//typedef struct{
//	DWORD		ModeType;
//	DWORD		PadType;
//	char		Description[32];
//	DWORD		UkLen;
//	BYTE		UK[56];
//	DWORD		IVLen;
//	BYTE		IV[16];
//	DWORD		PtLen;
//	BYTE		PT[48];
//	DWORD		EtLen;
//	BYTE		ET[48];
//} TEST_STRUCT;
//
//TEST_STRUCT		TestData[] = {
//	{	AI_ECB, AI_NO_PADDING, "ECB-NO_PADDING : ",
//		16,		{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//				 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
//		 0,		{0},
//		32,		{0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//				 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//				 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//				 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01},
//		32,		{0x3A,0xD7,0x8E,0x72,0x6C,0x1E,0xC0,0x2B,
//				 0x7E,0xBF,0xE9,0x2B,0x23,0xD9,0xEC,0x34,
//				 0x58,0xE2,0xFC,0xCE,0xFA,0x7E,0x30,0x61,
//				 0x36,0x7F,0x1D,0x57,0xA4,0xE7,0x45,0x5A}	},
//	{	AI_ECB, AI_NO_PADDING, "ECB-NO_PADDING : ",
//		24,		{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//				 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//				 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
//		 0,		{0},
//		32,		{0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//				 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//				 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//				 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01},
//		32,		{0x6C,0xD0,0x25,0x13,0xE8,0xD4,0xDC,0x98,
//				 0x6B,0x4A,0xFE,0x08,0x7A,0x60,0xBD,0x0C,
//				 0xCD,0x33,0xB2,0x8A,0xC7,0x73,0xF7,0x4B,
//				 0xA0,0x0E,0xD1,0xF3,0x12,0x57,0x24,0x35}	},
//	{	AI_ECB, AI_NO_PADDING, "ECB-NO_PADDING : ",
//		32,		{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//				 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//				 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//				 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
//		 0,		{0},
//		32,		{0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//				 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//				 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//				 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01},
//		32,		{0xDD,0xC6,0xBF,0x79,0x0C,0x15,0x76,0x0D,
//				 0x8D,0x9A,0xEB,0x6F,0x9A,0x75,0xFD,0x4E,
//				 0x53,0x0F,0x8A,0xFB,0xC7,0x45,0x36,0xB9,
//				 0xA9,0x63,0xB4,0xF1,0xC4,0xCB,0x73,0x8B}	},
//	{	AI_CBC, AI_NO_PADDING, "CBC-NO_PADDING",
//		16,		{0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,
//				 0x12,0x34,0x56,0x78,0x9A,0xBC,0xDE,0xF0},
//		16,		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//		32,		{0x37,0x36,0x35,0x34,0x33,0x32,0x31,0x20,
//				 0x4E,0x6F,0x77,0x20,0x69,0x73,0x20,0x74,
//				 0x68,0x65,0x20,0x74,0x69,0x6D,0x65,0x20,
//				 0x66,0x6F,0x72,0x20,0x00,0x00,0x00,0x00},
//		32,		{0x3E,0xBD,0x62,0x2A,0x06,0x58,0xE6,0x05,
//				 0x32,0x3E,0xC4,0x82,0xD6,0xD7,0x77,0xFF,
//				 0x5C,0x93,0x92,0x9A,0xD6,0xB1,0xF4,0x10,
//				 0x46,0x32,0xAA,0xE0,0x1C,0xA9,0x8B,0x3F}	},
//	{	AI_CBC, AI_PKCS_PADDING, "CBC-PKCS_PADDING",
//		16,		{0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,
//				 0x12,0x34,0x56,0x78,0x9A,0xBC,0xDE,0xF0},
//		16,		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//		28,		"7654321 Now is the time for ",
//		32,		{0x3e,0xbd,0x62,0x2a,0x06,0x58,0xe6,0x05,
//				 0x32,0x3e,0xc4,0x82,0xd6,0xd7,0x77,0xff,
//				 0xbd,0x38,0x68,0xe4,0xa9,0xa2,0x81,0xb8,
//				 0x61,0x95,0x2e,0xe1,0xb7,0x05,0xf9,0x5f}	},
//	{	AI_OFB, 0, "OFB",
//		16,		{0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
//				 0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F},
//		16,		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//		28,		"7654321 Now is the time for ",
//		28,		{0xf1,0x97,0x0e,0x03,0xb4,0xbd,0x6a,0xa2,
//				 0x21,0x20,0xf6,0x42,0xc8,0xbb,0xf8,0x0d,
//				 0xc7,0xf8,0xb9,0x52,0x9e,0xb7,0xad,0x51,
//				 0xf4,0xde,0xb6,0x34}	},
//	{	AI_CFB, 0, "CFB",
//		16,		{0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,
//				 0x12,0x34,0x56,0x78,0x9A,0xBC,0xDE,0xF0},
//		16,		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//		28,		"7654321 Now is the time for ",
//		28,		{0x75,0xf1,0x5a,0xb2,0x2f,0xa1,0xe2,0x0d,
//				 0x79,0x59,0xcd,0x19,0x35,0xbb,0x93,0xf4,
//				 0x7f,0x42,0x32,0xf3,0xb7,0x1a,0x0f,0xfd,
//				 0xb3,0x26,0xc6,0x46}	},
//	{	0, 0, ""},
//};
//
///**************************************************************************
//*
//*/
//void	ValidityTest()
//{
//	BYTE	EncText[2*AES_BLOCK_LEN], DecText[2*AES_BLOCK_LEN];
//	DWORD	i, tt, EncLen, DecLen;
//	RET_VAL	ret;
//	AES_ALG_INFO	EncAlgInfo, DecAlgInfo;
//
//	//
//	for( i=0; TestData[i].ModeType!=0; i++) {
//		AES_SetAlgInfo(TestData[i].ModeType, TestData[i].PadType,
//						TestData[i].IV, &EncAlgInfo);
//		AES_SetAlgInfo(TestData[i].ModeType, TestData[i].PadType,
//						TestData[i].IV, &DecAlgInfo);
//
//		//
//		ret = AES_EncKeySchedule(TestData[i].UK, TestData[i].UkLen, &EncAlgInfo);
//		if( ret!=CTR_SUCCESS )	Error(ret, "AES_EncKeySchedule() returns.");
//		if( (TestData[i].ModeType==AI_OFB) || (TestData[i].ModeType==AI_CFB) )
//			ret = AES_EncKeySchedule(TestData[i].UK, TestData[i].UkLen,
//							&DecAlgInfo);
//		else
//			ret = AES_DecKeySchedule(TestData[i].UK, TestData[i].UkLen,
//							&DecAlgInfo);
//		if( ret!=CTR_SUCCESS )	Error(ret, "AES_DecKeySchedule() returns.");
//
//		//
//		EncLen = tt = 0;
//		ret = AES_EncInit(&EncAlgInfo);
//		if( ret!=CTR_SUCCESS )	Error(ret, "AES_EncInit() returns.");
//		ret = AES_EncUpdate(&EncAlgInfo, TestData[i].PT, TestData[i].PtLen,
//							EncText, &EncLen);
//		if( ret!=CTR_SUCCESS )	Error(ret, "AES_EncUpdate() returns.");
//		ret = AES_EncFinal(&EncAlgInfo, EncText+EncLen, &tt);
//		if( ret!=CTR_SUCCESS )	Error(ret, "AES_EncFinal() returns.");
//		EncLen += tt;
//
//		//
//		DecLen = tt = 0;
//		ret = AES_DecInit(&DecAlgInfo);
//		if( ret!=CTR_SUCCESS )	Error(ret, "AES_DecInit() returns.");
//		ret = AES_DecUpdate(&DecAlgInfo, EncText, EncLen, DecText, &DecLen);
//		if( ret!=CTR_SUCCESS )	Error(ret, "AES_DecUpdate() returns.");
//		ret = AES_DecFinal(&DecAlgInfo, DecText+DecLen, &tt);
//		if( ret!=CTR_SUCCESS )	Error(ret, "AES_DecFinal() returns.");
//		DecLen += tt;
//
//		//
//		fprintf(stdout, "\n==== test %d : %s\n", i, TestData[i].Description);
//		PrintBYTE(stdout, "UK", TestData[i].UK, TestData[i].UkLen);
//		PrintBYTE(stdout, "PT", TestData[i].PT, TestData[i].PtLen);
//		PrintBYTE(stdout, "ET", EncText, EncLen);
//		if( memcmp(TestData[i].PT, DecText, TestData[i].PtLen)==0 )
//			printf("   DT = (OK)\n");
//		else
//			PrintBYTE(stdout, "DT", DecText, DecLen);
//	}
//}
//
///**************************************************************************
//*
//*/
//void	SpeedTest()
//{
//#define DATA_LEN	1024
//	BYTE	UserKey[AES_USER_KEY_LEN], IV[AES_BLOCK_LEN];
//	BYTE	PT[DATA_LEN+32], ET[DATA_LEN+32], DT[DATA_LEN+32];
//	DWORD	i, tt, Iter, EncLen=0, DecLen;
//	RET_VAL	ret;
//	AES_ALG_INFO	EncAlgInfo, DecAlgInfo;
//
//	//
//	for( tt=0; tt<AES_USER_KEY_LEN; tt++)	UserKey[tt] = 0;
//	for( tt=0; tt<AES_BLOCK_LEN; tt++)		IV[tt] = 0;
//	AES_SetAlgInfo(AI_CBC, AI_NO_PADDING, IV, &EncAlgInfo);
//	AES_SetAlgInfo(AI_CBC, AI_NO_PADDING, IV, &DecAlgInfo);
//
//	//
//	ret = AES_EncKeySchedule(UserKey, AES_USER_KEY_LEN, &EncAlgInfo);
//	if( ret!=CTR_SUCCESS )	Error(ret, "AES_EncKeySchedule() returns.");
//	ret = AES_DecKeySchedule(UserKey, AES_USER_KEY_LEN, &DecAlgInfo);
//	if( ret!=CTR_SUCCESS )	Error(ret, "AES_DecKeySchedule() returns.");
//
//	for( i=0; i<3; i++) {
//		fprintf(stdout, "\n==== test %d\n", i);
//		Iter = 2 * 18000;
//
//		//
//		for( tt=0; tt<DATA_LEN; tt++)	PT[tt] = 0;
//
//		//
//		SPEED_TEST("Enc:", " / ", Iter, DATA_LEN,
//			{	EncLen = tt = 0;
//				ret = AES_EncInit(&EncAlgInfo);
//				ret = AES_EncUpdate(&EncAlgInfo, PT, DATA_LEN,
//									ET, &EncLen);
//				ret = AES_EncFinal(&EncAlgInfo, ET+EncLen, &tt);
//				EncLen += tt;									}	);
//		//
//		SPEED_TEST("Dec:", " // ", Iter, DATA_LEN,
//			{	DecLen = tt = 0;
//				ret = AES_DecInit(&DecAlgInfo);
//				ret = AES_DecUpdate(&DecAlgInfo, ET, EncLen,
//									DT, &DecLen);
//				ret = AES_DecFinal(&DecAlgInfo, DT+DecLen, &tt);
//				DecLen += tt;									}	);
//
//		//
//		for( tt=0; tt<DATA_LEN; tt++)
//			if( DT[tt]!=0 )	break;
//		if( tt==DATA_LEN )	printf("OK");
//		else				printf("FAIL");
//	}
//#undef DATA_LEN
//}
//
///**************************************************************************
//*
//*/
//void	GetKeyIV(
//		BYTE	Key[AES_USER_KEY_LEN],
//		DWORD	*KeyLen,
//		BYTE	IV[AES_BLOCK_LEN],
//		DWORD	*IVLen)
//{
//	DWORD	ch, i, j;
//	FILE	*pfile;
//
//	if( (pfile=fopen("key.dat", "r"))==NULL ) {
//		printf( "The file 'key.dat' was not opened\n");
//		Error(0, "File(key.dat) Open Error");
//	}
//
//	fscanf(pfile, "%d", &j);
//	*KeyLen = j;
//	for( i=0; i<j; i++) {
//		fscanf(pfile, "%X", &ch);
//		Key[i] = (BYTE) ch;
//	}
//
//	fscanf(pfile, "%d", &j);
//	if( j!=AES_BLOCK_LEN ) {
//		*IVLen = 0;
//		for( i=0; i<AES_BLOCK_LEN; i++)
//			IV[i] = (BYTE) 0;
//	}
//	else {
//		*IVLen = AES_BLOCK_LEN;
//		for( i=0; i<AES_BLOCK_LEN; i++) {
//			fscanf(pfile, "%X", &ch);
//			IV[i] = (BYTE) ch;
//		}
//	}
//
//	fclose(pfile);
//}
//
///**************************************************************************
//*
//*/
//void	GeneralTest(
//		DWORD	EncType,
//		DWORD	ModeType,
//		DWORD	PadType,
//		char	*infile,
//		char	*outfile)
//{
//	FILE	*pIn, *pOut;
//	BYTE	UserKey[AES_USER_KEY_LEN];
//	BYTE	IV[AES_BLOCK_LEN];
//	BYTE	SrcData[1024+32], DstData[1024+32];
//	DWORD	UKLen, IVLen, SrcLen, DstLen;
//	RET_VAL	ret;
//	AES_ALG_INFO	AlgInfo;
//
//	//
//	GetKeyIV(UserKey, &UKLen, IV, &IVLen);
//
//	//
//	if( (pIn=fopen(infile, "rb"))==NULL ) {
//		printf( "The file '%s' was not opened\n", infile);
//		Error(0, "File(infile) Open Error");
//	}
//	if( (pOut=fopen(outfile, "wb"))==NULL ) {
//		printf( "The file '%s' was not opened\n", outfile);
//		Error(0, "File(outfile) Open Error");
//	}
//	//
//	AES_SetAlgInfo(ModeType, PadType, IV, &AlgInfo);
//
//	if( EncType==0 ) {		//	Encryption
//		ret = AES_EncKeySchedule(UserKey, UKLen, &AlgInfo);
//		if( ret!=CTR_SUCCESS )	Error(ret, "AES_EncKeySchedule() returns.");
//
//		ret = AES_EncInit(&AlgInfo);
//		if( ret!=CTR_SUCCESS )	Error(ret, "AES_EncInit() returns.");
//
//		for(  ;  ;  ) {
//			SrcLen = fread(SrcData, sizeof(BYTE), 1024, pIn);
//			if( SrcLen==0 )	break;
//
//			DstLen = 1024;
//			ret = AES_EncUpdate(&AlgInfo, SrcData, SrcLen, DstData, &DstLen);
//			if( ret!=CTR_SUCCESS )	Error(ret, "AES_EncUpdate() returns.");
//
//			fwrite(DstData, sizeof(BYTE), DstLen, pOut);
//		}
//
//		DstLen = 1024;
//		ret = AES_EncFinal(&AlgInfo, DstData, &DstLen);
//		if( ret!=CTR_SUCCESS )	Error(ret, "AES_EncFinal() returns.");
//		fwrite(DstData, sizeof(BYTE), DstLen, pOut);
//	}
//	else {					//	Decryption
//		ret = AES_DecKeySchedule(UserKey, UKLen, &AlgInfo);
//		if( ret!=CTR_SUCCESS )	Error(ret, "AES_DecKeySchedule() returns.");
//
//		ret = AES_DecInit(&AlgInfo);
//		if( ret!=CTR_SUCCESS )	Error(ret, "AES_DecInit() returns.");
//
//		for(  ;  ;  ) {
//			SrcLen = fread(SrcData, sizeof(BYTE), 1024, pIn);
//			if( SrcLen==0 )	break;
//
//			DstLen = 1024;
//			ret = AES_DecUpdate(&AlgInfo, SrcData, SrcLen, DstData, &DstLen);
//			if( ret!=CTR_SUCCESS )	Error(ret, "AES_DecUpdate() returns.");
//
//			fwrite(DstData, sizeof(BYTE), DstLen, pOut);
//		}
//
//		DstLen = 1024;
//		ret = AES_DecFinal(&AlgInfo, DstData, &DstLen);
//		if( ret!=CTR_SUCCESS )	Error(ret, "AES_DecFinal() returns.");
//		fwrite(DstData, sizeof(BYTE), DstLen, pOut);
//	}
//
//	fclose(pIn);
//	fclose(pOut);
//}
//
///**************************************************************************
//*
//*/
//void	ChangeToCapital(char *String)
//{
//	DWORD	i;
//
//	if( String[0]=='-' ) {
//		for( i=1;  ; i++) {
//			if( String[i]=='\0' )	break;
//			if( (String[i]>='a') && (String[i]<='z') )
//				String[i] += 'A' - 'a';
//		}
//	}
//}
//
///**************************************************************************
//*
//*/
//void	main(int argc, char **argv)
//{
//	DWORD	i;
//
//	//
//	for( i=1; i<(DWORD)argc; i++)
//		ChangeToCapital(argv[i]);
//
//	//
//	if( argc==2 ) {
//		if( strcmp(argv[1], "-T")==0 )		ValidityTest();
//		else if( strcmp(argv[1], "-S")==0 )	SpeedTest();
//		else	Error(CTR_USAGE_ERROR, "Invalid Use of Argument");
//	}
//	else if( argc==5 ) {
//		DWORD	EncType=0, ModeType=0, PadType=0;
//
//		//
//		if( strcmp(argv[1], "-E")==0 )		EncType = 0;
//		else if( strcmp(argv[1], "-D")==0 )	EncType = 1;
//		else	Error(CTR_USAGE_ERROR, "Invalid Use of Argument");
//
//		//
//		if( strcmp(argv[2], "-ECB")==0 ) {
//			ModeType = AI_ECB;
//			PadType = AI_NO_PADDING;
//		}
//		else if( strcmp(argv[2], "-CBC")==0 ) {
//			ModeType = AI_CBC;
//			PadType = AI_NO_PADDING;
//		}
//		else if( strcmp(argv[2], "-OFB")==0 ) {
//			ModeType = AI_OFB;
//			PadType = AI_NO_PADDING;
//		}
//		else if( strcmp(argv[2], "-CFB")==0 ) {
//			ModeType = AI_CFB;
//			PadType = AI_NO_PADDING;
//		}
//		else if( strcmp(argv[2], "-ECBPAD")==0 ) {
//			ModeType = AI_ECB;
//			PadType = AI_PKCS_PADDING;
//		}
//		else if( strcmp(argv[2], "-CBCPAD")==0 ) {
//			ModeType = AI_CBC;
//			PadType = AI_PKCS_PADDING;
//		}
//		else if( strcmp(argv[2], "-OFBPAD")==0 ) {
//			ModeType = AI_OFB;
//			PadType = AI_PKCS_PADDING;
//		}
//		else if( strcmp(argv[2], "-CFBPAD")==0 ) {
//			ModeType = AI_CFB;
//			PadType = AI_PKCS_PADDING;
//		}
//		else	Error(CTR_USAGE_ERROR, "Invalid Use of Argument");
//
//		GeneralTest(EncType, ModeType, PadType, argv[3], argv[4]);
//	}
//	else
//		Error(CTR_USAGE_ERROR, "Invalid Number of Argument");
//}
//
///*************** END OF FILE **********************************************/
