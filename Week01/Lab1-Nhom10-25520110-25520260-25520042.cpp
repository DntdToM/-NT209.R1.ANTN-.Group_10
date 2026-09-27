#include <stdio.h>
// 1.1

/**
 * @brief Tính và trả về số nguyên là số đối của số một số nguyên nhập vào
 * @param x số nguyên cần tìm số đối
 * @return int số nguyên -x là số đối của x
 * @note Giải thích logic: Hàm sử dụng kỹ thuật bù 2 (Two's Complement) để
 * đảo dấu số nguyên theo từng bit của nó.
 * Cụ thể: ~x+1 thực hiện đảo bit, sau đó cộng 1 để chuyển thành số đối (bù 2)
 */
int negative(int x) {
  /*
  Hàm này trả về số đối của số nguyên x

  Args:
    x (int): số nguyên x đầu vào

  Return:
    int: số -x là số đối của x
  */
  x = ~x + 1;
  return x;
}

// 1.2
/**
 * @brief Tính và trả về số nguyên là tích của 100 với số nguyên nhập vào
 * @param x số nguyên cần tính
 * @return int số nguyên kết quả 100 * x
 * @note Giải thích logic: Hàm sử dụng left shift thay cho phép nhân. Vì phép
 * left shift là nhân với lũy thừa của 2, nên ta tách số 100 thành tổng các lũy
 * thừa của 2. Thực hiện left shift x với các số mũ lũy thừa đó rồi cộng các
 * kết quả lại
 * Cụ thể: 100 = 64 + 32 + 4 = 2^6 + 2^5 + 2^2
 */
int cal100x(int x) {
  x = (x << 6) + (x << 5) + (x << 2);
  return x;
}

// 1.3
/**
 * @brief Tính và trả về số nguyên là kết quả sau khi lật byte thứ n trong
 *  biểu diễn nhị phân của số nguyên x nhập vào
 * @param x số nguyên cần được lật byte
 * @param n số nguyên n (0 <= n <=3) chỉ định byte thứ n của x bị lật
 * @return int số nguyên là kết quả lật 1 byte thứ n của số nguyên x
 * @note Ý tưởng: tạo ra một mask (4byte) có dạng 0x0000FF00 với FF là
 * vị trí byte thứ n theo thứ tự tăng từ phải sang trái để thực hiện xor với x
 * trên cơ sở: x ^ 0 = x, x ^ 1 = ~x
 * Cụ thể: để FF bắt đầu ở vị trí byte thứ n nghĩa là ta đã left shift 8 * n bit
 * hay thực hiện left shift n << 3. Và ta có biểu thức mask = 0xff << (n << 3)
 */
int flipByte(int x, int n) {
  x = (0xff << (n << 3)) ^ x;
  return x;
}

//1.4
unsigned int getnbit(unsigned int x, int n) {
  /*
   * Ý TƯỞNG: Lấy n bit cuối của x bằng cách tạo mặt nạ (mask) gồm n bit 1 ở cuối rồi AND với x.
   *
   * - Cơ bản: Dịch 1 sang trái n bit (ví dụ n=3 ra 1000), sau đó trừ 1 (cộng với ~1+1) để ra n bit 1 (111).
   * - Nâng cao (Xử lý khi n >= 32 gây overflow):
   *   + Tính overflow_padd = ~(n >> 5) + 1 (tương đương n/32 rồi lấy số âm).
   *   + Nếu n < 32: overflow_padd là 0 (toàn bit 0).
   *   + Nếu n >= 32: overflow_padd là -1 (toàn bit 1).
   *   + Phép OR với overflow_padd giúp đảm bảo: khi n >= 32, mask tự động trở thành full 1 để lấy trọn vẹn số x.
   */
  int overflow_padd = 0 + ~(n >> 5) + 1;
  int one_big_num = (1 << n) ;

  int full_one = one_big_num + (~1+1) ;
  full_one = full_one | overflow_padd;

  x = x & full_one;
  return x;
}

//1.5

int round2n(int x, int n){
  /*
   * Ý TƯỞNG: Làm tròn x tới bội số gần nhất của 2^n.
   *
   * - Cơ bản: Chặt bỏ n bit cuối bằng cách dịch phải rồi dịch trái (tương đương chia lấy nguyên cho 2^n rồi nhân lại) giúp làm tròn XUỐNG bội số của 2^n.
   * - Mở rộng (Làm tròn GẦN NHẤT): Ta cộng thêm vào x một khoảng bằng đúng một nửa của 2^n trước khi "chặt bit".
   *   + boi_n = 1 << n (chính là 2^n).
   *   + pad_them = boi_n >> 1 (chính là một nửa của 2^n).
   *   + Nếu phần dư của x lớn hơn hoặc bằng một nửa, việc cộng này sẽ đẩy phần nguyên nhảy lên mức tiếp theo, tạo thành cơ chế làm tròn chính xác.
   */
  int boi_n = 1 << n;
  int pad_them = boi_n >>  1  ;

  x = x + pad_them;

  int chia_nguyen = x >> n ;
  x = chia_nguyen << n ;

  return x;
}

// 2.1
/**
 * @brief Kiểm tra 2 số x, y có cùng dấu (cùng âm hay cùng không âm). Trả về 1 nếu cùng dấu và 0 nếu ngược lại
 * @param x số nguyên thứ nhất
 * @param y số nguyên thứ hai
 * @return int Trả về 1 nếu x, y cùng dấu, trả về 0 nếu ngược lại
 * @note Ý tưởng: kiểm tra bit MSB của mỗi số để check dấu. Thực hiện điều đó bằng cách
 * (x >> 31) & 1 và (y >> 31) & 1 để đảm bảo có dạng 000...001 nếu âm hoặc 000...000 nếu không âm
 * Sau đó đem các bit MSB này xor với nhau và xor với 1. Việc xor với 1 là để đảm bảo kết quả trả về 1 khi cùng dấu,
 * trả về 0 nếu ngược lại (nếu không có xor 1 thì trả về bị đảo ngược với yêu cầu)
 * 
 */
int isSameSign(int x, int y) {
  return (((x >> 31) & 1) ^ ((y >> 31) & 1)) ^ 1;
}

// 2.2
/**
 * @brief Hàm kiểm tra số dương, trả về 1 nếu x nhập vào là số dương, 0 nếu x không dương
 * @param x số nguyên x nhập vào
 * @return int 1 nếu x là số dương, 0 nếu ngược lại
 * @note Ý tưởng: kiểm tra bit MSB của mỗi số, thực hiện bằng MSB(x) = (x >> 31) & 1
 * Vì số dương thì MSB = 0, số 0 thì MSB = 0, số âm thì MSB = 1 kết quả “hơi ngược” với mong muốn
 * là số dương trả về 1, số 0 thì trả về 0, số âm thì trả về 0.
 * Do đó ta lấy bù 2 của x, khi đó MSBbu2(x) = MSB(~x+1); MSBbu2(số dương) = 1, MSBbu2(số 0 và số âm) = 0.
 * Lợi dụng việc số 0 luôn bất biến qua phép lấy bù 2
 */
int isPositive(int x) {
  return ((~x+1) >> 31) & 1;
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
