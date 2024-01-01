#include <glib.h>
#include <stdio.h>

void prtArray(GArray *arr) {
  fprintf(stderr, "Array holds:\n");
  for (int i = 0; i < arr->len; i++)
    printf("%s\n", g_array_index(arr, char *, i));
  printf("\n");
}
