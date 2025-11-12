///*
//
//스트림 암호 RC4
//
//
//*/
//
//
//
//
//
//#define _CRT_SECURE_NO_WARNINGS
//
//#include <cstdio>
//#include <cstring>
//#include <iostream>
//
//int file_size = 0; // File_Read / File_write에서 사용
//
//// (선택) 디버깅용 상태 보관 구조체 — 필요 없으면 제거해도 됩니다.
//struct rc4_byte {
//    unsigned char Byte = 0;
//    int i = 0;
//    int j = 0;
//};
//
//// ----------- 유틸: swap (C++) -----------
//inline void swap(unsigned char& a, unsigned char& b) {
//    unsigned char t = a;
//    a = b;
//    b = t;                 //  원본 이미지의 버그(j=i)를 수정
//}
//
//// ----------- 파일 쓰기 -----------
//char* File_write(char* Out, char fn[256]) {
//    std::FILE* fp = std::fopen(fn, "wb");
//    if (!fp) {
//        std::perror("fopen (write) failed");
//        return nullptr;
//    }
//    std::fwrite(Out, sizeof(char), static_cast<size_t>(file_size), fp);
//    std::fclose(fp);
//    return Out;
//}
//
//// ----------- 파일 읽기 -----------
//char* File_Read(char* In, char fn[256]) {
//    std::FILE* fp = std::fopen(fn, "rb");
//    if (!fp) {
//        std::perror("fopen (read) failed");
//        return nullptr;
//    }
//    std::fseek(fp, 0, SEEK_END);
//    long sz = std::ftell(fp);
//    std::fseek(fp, 0, SEEK_SET);
//
//    if (sz < 0) {
//        std::fclose(fp);
//        return nullptr;
//    }
//
//    file_size = static_cast<int>(sz);
//    In = new char[static_cast<size_t>(file_size) + 1] {0}; // C++ 스타일 new
//    std::fread(In, 1, static_cast<size_t>(file_size), fp);
//    In[file_size] = '\0';
//    std::fclose(fp);
//    return In;
//}
//
//// ----------- RC4 KSA -----------
//void RC4_init(unsigned char S[256], const char key[256]) {
//    unsigned char K[256] = { 0 };
//    int keylen = static_cast<int>(std::strlen(key));
//
//    for (int i = 0; i < 256; ++i) {
//        S[i] = static_cast<unsigned char>(i);
//        K[i] = static_cast<unsigned char>(key[i % keylen]);
//    }
//
//    int j = 0;
//    for (int i = 0; i < 256; ++i) {
//        j = (j + S[i] + K[i]) & 0xFF;     // %256
//        swap(S[i], S[j]);
//    }
//}
//
//// ----------- RC4 PRGA -----------
//char* RC4_crypto(const char* In, const char key[256], char* Out) {
//    unsigned char S[256];
//    RC4_init(S, key);
//
//    int i = 0, j = 0;
//    Out = new char[static_cast<size_t>(file_size) + 1] {0};
//
//    for (int n = 0; n < file_size; ++n) {
//        i = (i + 1) & 0xFF;
//        j = (j + S[i]) & 0xFF;
//        swap(S[i], S[j]);
//        unsigned char rnd = S[(S[i] + S[j]) & 0xFF];
//        Out[n] = static_cast<char>(static_cast<unsigned char>(In[n]) ^ rnd);
//    }
//    Out[file_size] = '\0';
//    return Out;
//}
//
//int main() {
//    char key[256] = { "thank" };
//    char fread_plain[256] = { "plaintext.txt" };
//    char fread_cipher[256] = { "ciphertext.txt" };
//    char fwrite_cipher[256] = { "ciphertext.txt" };
//    char fwrite_decipher[256] = { "deciphertext.txt" };
//
//    char* plain = nullptr;
//    char* cipher = nullptr;
//    char* decipher = nullptr;
//
//    // 암호화
//    plain = File_Read(plain, fread_plain);
//    if (!plain) { std::cerr << "Failed to read plaintext\n"; return 1; }
//    cipher = RC4_crypto(plain, key, cipher);
//    File_write(cipher, fwrite_cipher);
//
//    // 복호화
//    delete[] plain; plain = nullptr; // 깔끔하게 정리
//    cipher = File_Read(cipher, fread_cipher);
//    if (!cipher) { std::cerr << "Failed to read ciphertext\n"; return 1; }
//    decipher = RC4_crypto(cipher, key, decipher);
//    File_write(decipher, fwrite_decipher);
//
//    // 메모리 정리
//    delete[] cipher;
//    delete[] decipher;
//
//    return 0;
//}
