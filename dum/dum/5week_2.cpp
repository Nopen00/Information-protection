//// des_all_in_one.cpp
//#include <cstdio>
//#include <cstring>
//#include <cstdlib>
//#include <iostream>
//
//// ====== 상수 테이블 ======
//static const int ip[64] = {
//    58,50,42,34,26,18,10, 2, 60,52,44,36,28,20,12, 4,
//    62,54,46,38,30,22,14, 6, 64,56,48,40,32,24,16, 8,
//    57,49,41,33,25,17, 9, 1, 59,51,43,35,27,19,11, 3,
//    61,53,45,37,29,21,13, 5, 63,55,47,39,31,23,15, 7
//};
//
//static const int fp[64] = {
//    40, 8,48,16,56,24,64,32, 39, 7,47,15,55,23,63,31,
//    38, 6,46,14,54,22,62,30, 37, 5,45,13,53,21,61,29,
//    36, 4,44,12,52,20,60,28, 35, 3,43,11,51,19,59,27,
//    34, 2,42,10,50,18,58,26, 33, 1,41, 9,49,17,57,25
//};
//
//static const int ebox[48] = {
//    32, 1, 2, 3, 4, 5,  4, 5, 6, 7, 8, 9,
//     8, 9,10,11,12,13, 12,13,14,15,16,17,
//    16,17,18,19,20,21, 20,21,22,23,24,25,
//    24,25,26,27,28,29, 28,29,30,31,32, 1
//};
//
//static const int p32[32] = {
//    16, 7,20,21, 29,12,28,17, 1,15,23,26, 5,18,31,10,
//     2, 8,24,14, 32,27, 3, 9,19,13,30, 6,22,11, 4,25
//};
//
//static const int pc1[56] = {
//    57,49,41,33,25,17, 9,  1,58,50,42,34,26,18,
//    10, 2,59,51,43,35,27, 19,11, 3,60,52,44,36,
//    63,55,47,39,31,23,15,  7,62,54,46,38,30,22,
//    14, 6,61,53,45,37,29, 21,13, 5,28,20,12, 4
//};
//
//static const int pc2[48] = {
//    14,17,11,24, 1, 5,  3,28,15, 6,21,10,
//    23,19,12, 4,26, 8, 16, 7,27,20,13, 2,
//    41,52,31,37,47,55, 30,40,51,45,33,48,
//    44,49,39,56,34,53, 46,42,50,36,29,32
//};
//
//static const int rotate_tab[16] = { 1,1,2,2, 2,2,2,2, 1,2,2,2, 2,2,2,1 };
//
//// S-box 8개
//static const unsigned char s_box[8][64] = {
//    {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7, 0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8, 4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0, 15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13},
//    {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10, 3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5, 0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15, 13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9},
//    {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8, 13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1, 13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7, 1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12},
//    {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15, 13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9, 10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4, 3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14},
//    {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9, 14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6, 4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14, 11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3},
//    {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11, 10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8, 9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6, 4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13},
//    {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1, 13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6, 1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2, 6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12},
//    {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7, 1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2, 7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8, 2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
//};
//
//// ====== 보조 비트 함수 ======
//inline int get_bit(const unsigned char* data, int pos) {
//    // pos: 0.. (MSB-first)
//    int byte = pos / 8;
//    int bit = 7 - (pos % 8);
//    return (data[byte] >> bit) & 1;
//}
//inline void set_bit(unsigned char* data, int pos, int v) {
//    int byte = pos / 8;
//    int bit = 7 - (pos % 8);
//    if (v) data[byte] |= (1u << bit);
//    else   data[byte] &= ~(1u << bit);
//}
//
//static void xor_bits(unsigned char* out,
//    const unsigned char* a,
//    const unsigned char* b,
//    int nbits) {
//    for (int i = 0; i < nbits; ++i)
//        set_bit(out, i, get_bit(a, i) ^ get_bit(b, i));
//}
//
//static void permute(const unsigned char* input,
//    unsigned char* output,
//    const int* mapping,
//    int mapsize) {
//    const int out_bytes = (mapsize + 7) / 8;
//    std::memset(output, 0, out_bytes);
//    for (int i = 0; i < mapsize; ++i)
//        set_bit(output, i, get_bit(input, mapping[i] - 1));
//}
//
//static void left_rotate28(unsigned char* half28, int r) {
//    // half28: 28비트(4바이트에 저장, 상위 4비트는 미사용)
//    unsigned char tmp[4]{ 0,0,0,0 };
//    for (int i = 0; i < 28; ++i) {
//        int v = get_bit(half28, (i + r) % 28);
//        set_bit(tmp, i, v);
//    }
//    std::memcpy(half28, tmp, 4);
//}
//
//// ====== S-box 처리 (48bit -> 32bit) ======
//static void sbox(unsigned char* data48 /*inout: 48bit, 결과는 하위 32bit에*/) {
//    unsigned char out32[4]{ 0,0,0,0 };
//    for (int i = 0; i < 8; ++i) {
//        int base = i * 6;
//        int row = (get_bit(data48, base) << 1) | get_bit(data48, base + 5);
//        int col = (get_bit(data48, base + 1) << 3)
//            | (get_bit(data48, base + 2) << 2)
//            | (get_bit(data48, base + 3) << 1)
//            | get_bit(data48, base + 4);
//        unsigned char val = s_box[i][row * 16 + col]; // 4bit
//        // val의 4비트를 MSB-first로 out32에 기록
//        for (int j = 0; j < 4; ++j)
//            set_bit(out32, i * 4 + j, (val >> (3 - j)) & 1);
//    }
//    std::memcpy(data48, out32, 4); // 앞 32비트만 유효
//}
//
//// ====== 키 스케줄 ======
//static void set_subkey(unsigned char subkey[16][6], const unsigned char* key56 /*7바이트*/) {
//    unsigned char perm56[7]{ 0,0,0,0,0,0,0 };
//    permute(key56, perm56, pc1, 56);
//
//    unsigned char L[4]{ 0,0,0,0 }, R[4]{ 0,0,0,0 };
//    for (int i = 0; i < 28; ++i) {
//        set_bit(L, i, get_bit(perm56, i));
//        set_bit(R, i, get_bit(perm56, i + 28));
//    }
//
//    unsigned char merged56[7]{ 0,0,0,0,0,0,0 };
//    for (int r = 0; r < 16; ++r) {
//        left_rotate28(L, rotate_tab[r]);
//        left_rotate28(R, rotate_tab[r]);
//
//        for (int i = 0; i < 28; ++i) {
//            set_bit(merged56, i, get_bit(L, i));
//            set_bit(merged56, i + 28, get_bit(R, i));
//        }
//        // 56 -> 48 (pc2)
//        std::memset(subkey[r], 0, 6);
//        permute(merged56, subkey[r], pc2, 48);
//    }
//}
//
//// ====== 라운드 함수 ======
//static void round_func(unsigned char* L /*4B*/, unsigned char* R /*4B*/, const unsigned char* k48) {
//    unsigned char exp48[6]{ 0,0,0,0,0,0 };
//    permute(R, exp48, ebox, 48);           // E 확장
//    xor_bits(exp48, exp48, k48, 48);       // 키 XOR
//    sbox(exp48);                           // S-box -> exp48 앞 32bit 사용
//    unsigned char p32out[4]{ 0,0,0,0 };
//    permute(exp48, p32out, p32, 32);       // P 박스
//
//    unsigned char newR[4]{ 0,0,0,0 };
//    xor_bits(newR, L, p32out, 32);         // L ⊕ f(R, K)
//
//    std::memcpy(L, R, 4);                  // 다음 라운드용 L <- 이전 R
//    std::memcpy(R, newR, 4);               // 다음 라운드용 R <- 계산값
//}
//
//// ====== DES 메인(블록 단위) ======
//enum DesOrder { ENCIPHER = 0, DECIPHER = 1 };
//
//static void des_main(const unsigned char* input8,
//    unsigned char* output8,
//    const unsigned char* key56 /*7B*/,
//    DesOrder dir) {
//    static unsigned char K[16][6]; // 서브키 캐시
//    if (key56) set_subkey(K, key56);
//
//    unsigned char buf[8]{ 0,0,0,0,0,0,0,0 };
//    permute(input8, buf, ip, 64);
//
//    unsigned char L[4]{ buf[0],buf[1],buf[2],buf[3] };
//    unsigned char R[4]{ buf[4],buf[5],buf[6],buf[7] };
//
//    for (int i = 0; i < 16; ++i) {
//        int r = (dir == ENCIPHER) ? i : (15 - i);
//        round_func(L, R, K[r]);
//    }
//
//    // 스왑 후 FP
//    unsigned char preout[8]{ R[0],R[1],R[2],R[3], L[0],L[1],L[2],L[3] };
//    permute(preout, output8, fp, 64);
//}
//
//// ====== 외부 인터페이스 ======
//static void des_encipher(const unsigned char* pt8, unsigned char* ct8, const unsigned char* key7) {
//    des_main(pt8, ct8, key7, ENCIPHER);
//}
//static void des_decipher(const unsigned char* ct8, unsigned char* pt8, const unsigned char* key7) {
//    des_main(ct8, pt8, nullptr, DECIPHER); // set_subkey 재사용 시 key7=nullptr 가능
//}
//
//// ====== 데모 ======
//int main() {
//    const unsigned char input[8] = { 'a','b','c','d','a','b','c','d' }; // 8B 평문 블록
//    unsigned char output[8]{ 0 }, output2[8]{ 0 };
//    const unsigned char key7[7] = { 'a','b','c','d','a','b','c' };     // 56bit 키(예시)
//
//    des_encipher(input, output, key7);
//    des_decipher(output, output2, key7);
//
//    std::cout << "Plain : ";
//    for (auto c : input)  std::printf("%02X ", c);   std::cout << "\n";
//    std::cout << "Cipher: ";
//    for (auto c : output) std::printf("%02X ", c);   std::cout << "\n";
//    std::cout << "Decryp: ";
//    for (auto c : output2)std::printf("%02X ", c);   std::cout << "\n";
//    return 0;
//}
//
//
//
