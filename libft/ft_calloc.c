#include "libft.h"

    void *ft_calloc(size_t nmemb, size_t size) {
  void *ptr;
  size_t i;
  size_t bytes;

  i = 0;
  if (nmemb <= 0 || size <= 0)
    return (malloc(1));
  bytes = nmemb * size;
  if (bytes / nmemb != size)
    return (NULL);
  ptr = malloc(nmemb * size);
  if (!ptr)
    return (NULL);
  while (i < bytes) {
    *(char *)(ptr + i) = 0;
    i++;
  }
  return (ptr);
}

/*
int main(void) {
  int *arr;
  int *arr2;

  int n;

  n = 5;
  arr = calloc(10, sizeof(int));
  arr2 = ft_calloc(10, sizeof(int));
  if (!arr)
    printf("Memory allocation failed!\n");
  if (!arr2)
    printf("Memory allocation failed!\n");
  while (n--)
	  printf("%d\n", arr[n - 1]);
  return (0);
}
*/
