#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

std::vector<int> right_shift(std::vector<int>& lhs, int k) {
  int carry = 0;
  int n = lhs.size();
  std::vector<int> num(n);
  std::copy(&lhs[0], &lhs[0] + lhs.size(), &num[0]);
  for (int i = n - 1; i >= 0; i--) {
    int new_carry = num[i] & (1 << (k - 1));
    num[i] = (num[i] >> k) | (carry << (32 - k));
    carry = new_carry;
  }
  while (n > 1 && num.back() == 0) {
    num.pop_back();
    n--;
  }
  return num;
}

std::vector<int> left_shift(std::vector<int>& lhs, int k) {
  int carry = 0;
  int n = lhs.size();
  std::vector<int> num(n);
  std::copy(&lhs[0], &lhs[0] + lhs.size(), &num[0]);
  for (int i = 0; i < n; i++) {
    int new_carry = num[i] & (1 << (32 - k - 1));
    num[i] = (num[i] << k) | carry;
    carry = new_carry;
  }
  if (carry) {
    num.push_back(carry);
    n++;
  }
  return num;
}

int main()
{
    std::vector<int> a(4);
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(1000, 9999);
    std::generate(&a[0], &a[0] + a.size(), [&] { return distribution(generator); });
    for (auto v: a)
        std::cout<<v<<" ";
    std::cout<<std::endl;
    std::vector<int> m = left_shift(a, 1);
    for (auto v: m)
        std::cout<<v<<" ";
    std::cout<<std::endl;
    m = right_shift(m, 1);
    for (auto v: m)
        std::cout<<v<<" ";
    std::cout<<std::endl;
}
