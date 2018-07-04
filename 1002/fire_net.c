#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"
#include "string.h"

char g_map[4][4];
uint8_t result[10000];

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

  for (i = x + 1; i < size; i++) {
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

  for (i = y + 1; i < size; i++) {
    if (g_map[x][i] == '!')
      return true;
    else if (g_map[x][i] == 'X')
      break;
  }

  g_map[x][y] = '!';
  return false;
}

bool is_blockhouses(uint32_t size, uint32_t x, uint32_t y) {
  if (x >= size || y >= size)
    return false;

  if (g_map[x][y] != '.')
    return false;

  return (find_enemy(size, x, y) == false);
}

uint32_t get_max(uint32_t size, uint32_t x, uint32_t y) {
  int i, j;
  uint32_t max = 0;

  if (is_blockhouses(size, x, y) == false)
    return max;

  max++;
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      if (is_blockhouses(size, i, j))
        max++;
    }
  }

  return max;
}

void recover_map(uint32_t size) {
  int i, j;

  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      if (g_map[i][j] == '!')
        g_map[i][j] = '.';
    }
  }
}

int main() {
  uint32_t map_size;
  int i, j;
  uint32_t max = 0;
  uint32_t cur;
  uint32_t cnt = 0;

  do {
    max = 0;
    map_size = get_map_size();
    if (map_size == 0 || map_size > 4)
      break;

    get_map(map_size);
    for (i = 0; i < map_size; i++) {
      for (j = 0; j < map_size; j++) {
        cur = get_max(map_size, i, j);
        if (max < cur) {
          max = cur;
        }
        recover_map(map_size);
      }
    }
    result[cnt++] = max;
  } while(true);

  for (i = 0; i < cnt; i++)
    printf("%d\n", result[i]);
}
