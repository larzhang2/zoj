#include <stdio.h>
#include <stdbool.h>

bool is_small_honest;

bool check(int big, int small, int n) {
  int i;

  for (i = n; i > 1; i--) {
    if (small % i == 0)
      if (check(big, small / i, i - 1))
        return true;

    if (big % i == 0)
      if (check(big / i, small, i - 1))
        return true;
  }

  if (small == 1)
    is_small_honest = true;
  else if (is_small_honest == false)
    return true;

  if (big == 1 && small == 1)
    return true;

   return false;
}

int get_winner(int big, int small, int n) {
  int winner = big;

  is_small_honest = false;

  if (!check(big, small, n))
    winner = small;

  return winner;
}

int main() {
  int a, b;
  int big, small;

  while (scanf("%d%d", &a, &b) != EOF) {
    big = (a > b) ? a : b;
    small = a + b - big;
    printf("%d\n", get_winner(a, b, 100));
  }
  return 0;
}
