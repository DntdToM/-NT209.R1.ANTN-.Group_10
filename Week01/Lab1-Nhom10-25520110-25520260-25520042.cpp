#include <stdio.h>
// 1.1
int negative(int x) {
  x = ~x + 1;
  return x;
}

// 1.2
int cal100x(int x) {
  x = (x << 6) + (x << 5) + (x << 2);
  return x;
}

// 1.3
int flipByte(int x, int n) {
  x = x ^ (0xff << (n << 3));
  return x;
}

// 1.4
unsigned int getnbit(unsigned int x, int n) {
  x = x & ((1 << n) + (~1 + 1));
  return x;
}

// 1.5
int round2n(int x, int n) {
  int mask = (1 << n) + ~0;
  x = x & ~mask;
  return x;
}

// 2.1
int isSameSign(int x, int y) {
  int signX = x >> 31;
  int signY = y >> 31;
  x = !(signX ^ signY);
  return x;
}

// 2.2
int isPositive(int x) {
  x = !(x >> 31) & !!x;
  return x;
}

// 2.3
/**
 * @brief 2.3: Kiểm tra xem số nguyên x có chia hết cho 2^n hay không (x % 2^n == 0).
 * @param x Số nguyên bất kỳ (32-bit int).
 * @param n Số nguyên không âm (n >= 0).
 * @return 1 nếu x chia hết cho 2^n, ngược lại trả về 0.
 * @note Giới hạn: Tối đa 15 toán tử (Max Ops: 15).
 * 
 * Ý tưởng & Giải thuật:
 * - Trong hệ bù 2, số x chia hết cho 2^n khi và chỉ khi phần dư x % 2^n = 0.
 *   Phần dư này tương ứng chính xác với n bit thấp nhất (LSB) của x.
 * - Bước 1 (Tạo mask): Cần mask có n bit cuối bằng 1 (giá trị 2^n - 1).
 *   Do không được dùng toán tử '-', ta dùng biểu diễn bù hai: 
 *   2^n - 1 = (1 << n) + ~0 (vì ~0 = -1).
 * - Bước 2 (Trích xuất n bit cuối): Thực hiện x & mask để lấy n bit thấp nhất.
 * - Bước 3 (Chuẩn hóa kết quả): Dùng toán tử '!' để kiểm tra:
 *   + Nếu x & mask == 0 (chia hết) => !(0) = 1.
 *   + Nếu x & mask != 0 (không chia hết) => !(khác 0) = 0.
 */
int isMulpw2(int x, int n) {
  int mask = (1 << n) + ~0;
  x = !(x & mask);
  return x;
}

// 2.4
/**
 * @brief 2.4: Kiểm tra số nguyên dương x có nhỏ hơn 2^n hay không (x < 2^n).
 * @param x Số nguyên dương (x > 0).
 * @param n Số nguyên (0 <= n <= 30).
 * @return 1 nếu x < 2^n, ngược lại trả về 0.
 * @note Giới hạn: Tối đa 15 toán tử (Max Ops: 15).
 * 
 * Ý tưởng & Giải thuật:
 * Cách tiếp cận 1 (Xét dấu hiệu số - Đang áp dụng):
 * - x < 2^n tương đương với hiệu x - 2^n < 0.
 * - Do cấm toán tử '-', ta biểu diễn -2^n qua số đối bù hai: ~powerOfTwo + 1
 *   (với powerOfTwo = 1 << n).
 * - Tính hiệu: tmp = x + ~powerOfTwo + 1.
 *   Do x > 0 và 0 <= n <= 30, hiệu không bao giờ bị tràn số 32-bit có dấu.
 * - Dịch phải số học tmp >> 31 để đưa bit dấu về vị trí thấp nhất:
 *   + Nếu x < 2^n => tmp < 0, bit dấu là 1 => tmp >> 31 = -1 (0xFFFFFFFF) => (-1) & 1 = 1.
 *   + Nếu x >= 2^n => tmp >= 0, bit dấu là 0 => tmp >> 31 = 0 => 0 & 1 = 0.
 * 
 * Cách tiếp cận 2 (Kiểm tra tiền tố bit - Tham khảo):
 * - Vì x > 0, nếu x < 2^n thì toàn bộ các bit từ vị trí n trở lên đều bằng 0.
 *   Do đó phép dịch phải x >> n chắc chắn bằng 0 => !(x >> n) = 1.
 * - Ngược lại, nếu x >= 2^n thì có ít nhất 1 bit từ vị trí n trở lên bằng 1 => !(x >> n) = 0.
 */
int isLess2n(int x, int n) {
  // Cách 1: Xét dấu hiệu số (x - 2^n)
  int powerOfTwo = 1 << n;
  int tmp = x + ~powerOfTwo + 1;
  x = (tmp >> 31) & 1;
  return x;
  /*
  Cách 2: Kiểm tra tiền tố bit
  x = x >> n;
  x = !x;
  return x;
  */
}

// 2.5
/**
 * @brief 2.5: Mô phỏng toán tử logic !x mà không sử dụng '!'.
 * @param x Số nguyên 32-bit bất kỳ.
 * @return 1 nếu x == 0, 0 nếu x != 0.
 * @note Giới hạn: Tối đa 25 toán tử (Max Ops: 25).
 * 
 * Ý tưởng & Giải thuật:
 * - Theo bảng chân trị logic: x == 0 trả về 1, x != 0 trả về 0.
 * - Đặc trưng bit dấu trong biểu diễn bù hai:
 *   + Với x == 0: Số đối -x = 0. Cả x và -x đều có bit dấu (bit 31) bằng 0.
 *   + Với x > 0: Số đối -x < 0 nên bit dấu của -x luôn là 1.
 *   + Với x < 0 (kể cả biên TMin = -2147483648): Bản thân x đã có bit dấu là 1.
 * - Xây dựng thuật toán:
 *   + Biểu diễn số đối: -x = ~x + 1.
 *   + Phép OR bitwise: x | (~x + 1)
 *     Nếu x != 0: bit dấu (bit 31) luôn bằng 1.
 *     Nếu x == 0: bit dấu bằng 0.
 *   + Dịch phải số học 31 bit: (x | (~x + 1)) >> 31
 *     Khi x != 0: bit dấu là 1 => dịch phải số học cho ra -1 (0xFFFFFFFF).
 *     Khi x == 0: bit dấu là 0 => dịch phải cho ra 0.
 *   + Cộng thêm 1 để thu được kết quả logic:
 *     Khi x != 0: -1 + 1 = 0.
 *     Khi x == 0: 0 + 1 = 1.
 */
int logicNot(int x) {
  x = (x | (~x + 1)) >> 31;
  x = x + 1;
  return x;
}

int main() {
  int score = 0;
  // 1.1
  printf("1.1 negative");
  if (negative(0) == 0 && negative(9) == -9 && negative(-5) == 5) {
    printf("\t\tPass.");
    score += 1;
  } else
    printf("\t\tFailed.");

  // 1.2
  printf("\n1.2 cal100x");
  if (cal100x(0) == 0 && cal100x(9) == 900 && cal100x(-5) == -500) {
    printf("\t\t\tPass.");
    score += 1;
  } else
    printf("\t\t\tFailed.");

  // 1.3
  printf("\n1.3 flipByte");
  if (flipByte(10, 0) == 245 && flipByte(0, 1) == 65280 &&
      flipByte(0x5501, 1) == 0xaa01) {
    printf("\t\tPass.");
    score += 2;
  } else
    printf("\t\tFailed.");

  // 1.4
  printf("\n1.4 getnbit");
  if (getnbit(15, 3) == 7 && getnbit(63, 6) == 63 && getnbit(30, 2) == 2) {
    if (getnbit(10, 32) == 10 && getnbit(-50, 35) == -50) {
      printf("\t\t\tAdvanced Pass.");
      score += 3;
    } else {
      printf("\t\t\tPass.");
      score += 2;
    }
  } else
    printf("\t\t\tFailed.");

  // 1.5
  printf("\n1.5 round2n");
  if (round2n(10, 3) == 8 && round2n(16, 2) == 16 && round2n(70, 6) == 64) {
    if (round2n(15, 3) == 16 && round2n(20, 5) == 32) {
      printf("\t\t\tAdvanced Pass.");
      score += 3;
    } else {
      printf("\t\t\tPass.");
      score += 2;
    }
  } else
    printf("\t\t\tFailed.");

  // 2.1
  printf("\n2.1 isSameSign");
  if (isSameSign(2, -2) == 0 && isSameSign(-5, 10) == 0 &&
      isSameSign(0, 16) == 1 && isSameSign(-4, -20) == 1) {
    printf("\t\tPass.");
    score += 1;
  } else
    printf("\t\tFailed.");

  // 2.2
  printf("\n2.2 isPositive");
  if (isPositive(10) == 1 && isPositive(-105) == 0 && isPositive(0) == 0) {
    printf("\t\tPass.");
    score += 2;
  } else
    printf("\t\tFailed.");

  // 2.3
  printf("\n2.3 isMulpw2");
  if (isMulpw2(16, 4) == 1 && isMulpw2(10, 2) == 0 && isMulpw2(48, 3) == 1) {
    printf("\t\tPass.");
    score += 2;
  } else
    printf("\t\tFailed.");

  // 2.4
  printf("\n2.4 isLess2n");
  if (isLess2n(15, 1) == 0 && isLess2n(8, 3) == 0 && isLess2n(12, 4) == 1 &&
      isLess2n(63, 6) == 1) {
    printf("\t\tPass.");
    score += 2;
  } else
    printf("\t\tFailed.");

  // 2.5
  printf("\n2.5 logicNot");
  if (logicNot(0) == 1 && logicNot(1) == 0 && logicNot(-15) == 0 &&
      logicNot(-2147483648) == 0) {
    printf("\t\tPass.");
    score += 3;
  } else
    printf("\t\tFailed.");

  printf("\n------\nYour score: %.1f", (float)score / 2);
  return 0;
}