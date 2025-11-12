//#pragma warning(disable:4996)
//
//#include <cstdio>
//#include <cstring>
//#include <iostream>
//
//// --------------------- Cipher ---------------------
//char* Cipher(const char* src, const char* key) {
//    size_t n = std::strlen(src);
//    char* des = new char[n + 1];
//
//    for (size_t i = 0; i < n; ++i) {
//        switch (src[i]) {
//        // a~z
//        case 'a': des[i] = key[0];  break;   case 'b': des[i] = key[1];  break;
//        case 'c': des[i] = key[2];  break;   case 'd': des[i] = key[3];  break;
//        case 'e': des[i] = key[4];  break;   case 'f': des[i] = key[5];  break;
//        case 'g': des[i] = key[6];  break;   case 'h': des[i] = key[7];  break;
//        case 'i': des[i] = key[8];  break;   case 'j': des[i] = key[9];  break;
//        case 'k': des[i] = key[10]; break;   case 'l': des[i] = key[11]; break;
//        case 'm': des[i] = key[12]; break;   case 'n': des[i] = key[13]; break;
//        case 'o': des[i] = key[14]; break;   case 'p': des[i] = key[15]; break;
//        case 'q': des[i] = key[16]; break;   case 'r': des[i] = key[17]; break;
//        case 's': des[i] = key[18]; break;   case 't': des[i] = key[19]; break;
//        case 'u': des[i] = key[20]; break;   case 'v': des[i] = key[21]; break;
//        case 'w': des[i] = key[22]; break;   case 'x': des[i] = key[23]; break;
//        case 'y': des[i] = key[24]; break;   case 'z': des[i] = key[25]; break;
//        // A~Z
//        case 'A': des[i] = key[26]; break;   case 'B': des[i] = key[27]; break;
//        case 'C': des[i] = key[28]; break;   case 'D': des[i] = key[29]; break;
//        case 'E': des[i] = key[30]; break;   case 'F': des[i] = key[31]; break;
//        case 'G': des[i] = key[32]; break;   case 'H': des[i] = key[33]; break;
//        case 'I': des[i] = key[34]; break;   case 'J': des[i] = key[35]; break;
//        case 'K': des[i] = key[36]; break;   case 'L': des[i] = key[37]; break;
//        case 'M': des[i] = key[38]; break;   case 'N': des[i] = key[39]; break;
//        case 'O': des[i] = key[40]; break;   case 'P': des[i] = key[41]; break;
//        case 'Q': des[i] = key[42]; break;   case 'R': des[i] = key[43]; break;
//        case 'S': des[i] = key[44]; break;   case 'T': des[i] = key[45]; break;
//        case 'U': des[i] = key[46]; break;   case 'V': des[i] = key[47]; break;
//        case 'W': des[i] = key[48]; break;   case 'X': des[i] = key[49]; break;
//        case 'Y': des[i] = key[50]; break;   case 'Z': des[i] = key[51]; break;
//        default:
//            des[i] = src[i];
//        }
//    }
//    des[n] = '\0';                  // ★ 널 종료!
//    return des;
//}
//
//// --------------------- Histogram (그대로) ---------------------
//void Alpha_Hist(const char* in) {
//    int hist[26] = { 0 };
//    size_t n = std::strlen(in);
//
//    for (size_t i = 0; i < n; ++i) {
//        if ('A' <= in[i] && in[i] <= 'Z') hist[in[i] - 'A']++;
//        if ('a' <= in[i] && in[i] <= 'z') hist[in[i] - 'a']++;
//    }
//    for (int i = 0; i < 26; ++i) std::printf("%c : %d\n", i + 'A', hist[i]);
//}
//
//// --------------------- File I/O (수정) ---------------------
//char* File_Read(const char* filename) {
//    FILE* fp = std::fopen(filename, "rb");   // 텍스트도 rb가 안전
//    if (!fp) {
//        std::perror("파일 열기 실패");
//        return nullptr;
//    }
//
//    std::fseek(fp, 0, SEEK_END);
//    long size = std::ftell(fp);
//    std::fseek(fp, 0, SEEK_SET);
//
//    if (size < 0) { std::fclose(fp); return nullptr; }
//
//    char* buf = new char[static_cast<size_t>(size) + 1];
//    std::memset(buf, 0, static_cast<size_t>(size) + 1);
//
//    // fread(ptr, size_per_item, item_count, fp)
//    size_t readn = std::fread(buf, 1, static_cast<size_t>(size), fp);
//    buf[readn] = '\0';                            // ★ 널 종료
//    std::fclose(fp);
//    return buf;
//}
//
//void File_Write(const char* out, const char* filename = "ciphertext.txt") {
//    FILE* fp = std::fopen(filename, "wb");
//    if (!fp) { std::perror("파일 쓰기 실패"); return; }
//    std::fwrite(out, 1, std::strlen(out), fp);    // ★ 전체 쓰기
//    std::fclose(fp);
//}
//
//// --------------------- Double Transpose (12단위) ---------------------
//char* double_transpose_cipher(const char* src) {
//    size_t n = std::strlen(src);
//    char* cipher = new char[n + 1];
//    std::memset(cipher, 0, n + 1);
//
//    size_t blocks = n / 12;
//    for (size_t i = 0; i < blocks; ++i) {
//        size_t b = i * 12;
//        cipher[b + 0]  = src[b + 11];
//        cipher[b + 1]  = src[b + 9];
//        cipher[b + 2]  = src[b + 8];
//        cipher[b + 3]  = src[b + 10];
//        cipher[b + 4]  = src[b + 7];
//        cipher[b + 5]  = src[b + 5];
//        cipher[b + 6]  = src[b + 4];
//        cipher[b + 7]  = src[b + 6];
//        cipher[b + 8]  = src[b + 3];
//        cipher[b + 9]  = src[b + 1];
//        cipher[b + 10] = src[b + 0];
//        cipher[b + 11] = src[b + 2];
//    }
//    // ★ 남는 글자는 그대로 복사
//    for (size_t i = blocks * 12; i < n; ++i) cipher[i] = src[i];
//
//    cipher[n] = '\0';
//    return cipher;
//}
//
//// --------------------- One-time XOR (키 길이 12) ---------------------
//char* onetime_cipher(const char* src, const char* key /*len=12*/) {
//    size_t n = std::strlen(src);
//    char* cipher = new char[n + 1];
//
//    for (size_t i = 0; i < n; ++i) {
//        cipher[i] = static_cast<char>(src[i] ^ key[i % 12]); // ★ 남는 부분도 처리
//    }
//    cipher[n] = '\0';
//    return cipher;
//}
//
//char* onetime_decipher(const char* src, const char* key /*len=12*/) {
//    size_t n = std::strlen(src);
//    char* plain = new char[n + 1];
//
//    for (size_t i = 0; i < n; ++i) {
//        plain[i] = static_cast<char>(src[i] ^ key[i % 12]);
//    }
//    plain[n] = '\0';
//    return plain;
//}
//
//
//// --------------------- main ---------------------
//int main() {
//    char key[53] = { 0 }; // 52 + '\0'
//    std::strcpy(key, "irstcnopfglqyzadejumkhvwxbIRSTCNOPFGLQYZADEJUMKHVWXB");
//
//    const char okey[12] = { 1,2,3,4,1,2,3,4,1,2,3,4 };
//
//    // 실행 폴더(보통 x64\\Debug)에 파일이 있어야 합니다.
//    char* plain = File_Read("onetime_cipher.txt");  // 파일명/경로 정확히!
//    if (!plain) return 1;
//
//    char* cipher  = Cipher(plain, key);
//    char* cipher3 = onetime_decipher(cipher, okey);
//   // char* cipher2 = double_transpose_cipher(cipher);
//    //char* cipher3 = onetime_cipher(cipher2, okey);
//
//    File_Write(cipher3, "ciphertext.txt");
//
//    // 메모리 해제
//    delete[] plain;
//    delete[] cipher;
//    //delete[] cipher2;
//    delete[] cipher3;
//
//    std::cout << "완료: ciphertext.txt 생성" << std::endl;
//    return 0;
//}
