#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int Global;
void *Thread1(void *x)
{
  Global = 42;
  return x;
}
void *Static(void *x)
{
  static int a = 0;
  a++;
  return x;
}
void *Malloc(void *x)
{
  char *a = (char *)malloc(100 * sizeof(char));
  a += 2;
  return x;
}
void *I(void *x)
{
  getchar();
  return x;
}
void *sub(void *x)
{
  I(NULL);
  return x;
}
void *normal(void *x)
{
  return x;
}
void *circle0(void *x);
void *circle2(void *x)
{
  circle0(x);
  return x;
}
void *circle1(void *x)
{
  circle2(x);
  normal(x);
  return x;
}
void *circle0(void *x)
{
  puts("hh");
  circle1(x);
  return x;
}
int Global1;
int main()
{
  pthread_t t;
  pthread_create(&t, NULL, Thread1, NULL);
  Global = 43;
  pthread_join(t, NULL);
  return Global;
}