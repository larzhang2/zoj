#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"
#include "string.h"
#include "time.h"

char g_map[4][4];
uint32_t mmax;

uint32_t get_map_size() {
  uint32_t size;

  scanf("%d", &size);
  return size;
}

void get_map(uint32_t size) {
  int i, j;

  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++)
      scanf("%c", &g_map[i][j]);
  }
}

bool find_enemy(uint32_t size, uint32_t x, uint32_t y) {
  int i;

  for (i = x - 1; i >= 0; i--) {
    if (g_map[i][y] == '!')
      return true;
    else if (g_map[i][y] == 'X')
      break;
  }

  for (i = y - 1; i >= 0; i--) {
    if (g_map[x][i] == '!')
      return true;
    else if (g_map[x][i] == 'X')
      break;
  }

  return false;
}

bool can_put(uint32_t size, uint32_t x, uint32_t y) {
  if (x >= size || y >= size)
    return false;

  if (g_map[x][y] != '.')
    return false;

  return (find_enemy(size, x, y) == false);
}

void dfs(uint32_t x, uint32_t y, uint32_t size) {
  int i = x / size;
  int j = x % size;

  if (x >= size * size) {
    if (mmax < y)
      mmax = y;
    return;
  }

  if (can_put(size, i, j)) {
    g_map[i][j] = '!';
    dfs(x+1, y+1, size);
    g_map[i][j] = '.';
    dfs(x+1, y, size);
  } else {
    dfs(x+1, y, size);
  }
}

void calc(uint32_t size) {
  if (size == 1) {
    mmax = (g_map[0][0] == 'X') ? 0 : 1;
  } else {
  }
}

int main() {
  uint32_t map_size;
  uint32_t cnt = 0;

  do {
    mmax = 0;
    map_size = get_map_size();
    if (map_size == 0 || map_size > 4)
      break;

    get_map(map_size);
    if (map_size > 2)
      dfs(0, 0, map_size);
    else
      calc(map_size);
    printf("%d\n", mmax);
  } while(true);
}
