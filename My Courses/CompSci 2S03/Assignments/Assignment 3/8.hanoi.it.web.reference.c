// This code was taken from the internet
// Does the Tower of Hanoi in C using iteration and stack & arrays
// Used merely as a reference
// Proves that recursion is better for specific cases

#include <stdio.h>
#include <time.h>

#define DISKS 4 // 10 max
int stacks[3][DISKS];
int sps[3];

void init(int from)
{
  int i;
  sps[2] = sps[1] = sps[0] = 0;
  for (i = 0; i < DISKS; i++)
    stacks[from][i] = DISKS - i; // disk radius
  sps[from] = DISKS;
}

void print(void)
{
  int i, j, k;
  for (i = DISKS - 1; i >= 0; i--)
  {
    for (j = 0; j < 3; j++)
    {
      if (sps[j] > i)
      {
        for (k = 0; k < 10 - stacks[j][i]; k++)
          printf(" ");
        for (k = 0; k < 2 * stacks[j][i]; k++)
          printf("x");
        for (k = 0; k < 10 - stacks[j][i]; k++)
          printf(" ");
      }
      else
      {
        printf("                    "); // 10 * 2
      }
      printf("  ");
    }
    printf("\n");
  }
  printf("_________/\\_________  _________/\\_________  _________/\\_________\n\n");
}

void solve(int to, int from, int cnt)
{
  int other = from ^ to ^ 3;

  if (!cnt) return;

  solve(other, from, cnt - 1);

  stacks[to][sps[to]++] = stacks[from][--sps[from]];
  print();

  solve(to, other, cnt - 1);
}

int main(void)
{
  init(0);
  print();
  clock_t begin = clock();
  solve(2, 0, DISKS);
  clock_t end = clock();

  double executionTime = (double)(end - begin) / CLOCKS_PER_SEC; // calculate execution time by stracting start time from finish time
  printf("\nThis took %lf seconds\n\n", executionTime); // print execution time to screen

  return 0;
}