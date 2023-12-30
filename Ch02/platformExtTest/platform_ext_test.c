#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

cl_int err;

void handleError(char *message) {
  if (err) {
    perror(message);
    exit(EXIT_FAILURE);
  }
}

int main(void) {

  /* Extension data */
  char *ext_data;
  size_t ext_size;
  const char icd_ext[] = "cl_khr_icd";

  /* Find number of platforms */
  cl_uint num_platforms;
  err = clGetPlatformIDs(1, NULL, &num_platforms);
  handleError("Couldn't find any platforms.");

  /* Access all installed platforms */
  cl_platform_id *platforms = (cl_platform_id *)malloc(sizeof(cl_platform_id) * num_platforms);
  clGetPlatformIDs(num_platforms, platforms, NULL);

  /* Find extensions of all platforms */
  cl_int platform_index = -1;
  for (cl_int i = 0; i < num_platforms; i++) {
    /* Find size of extension data */
    err = clGetPlatformInfo(platforms[i], CL_PLATFORM_EXTENSIONS, 0, NULL, &ext_size);
    handleError("Couldn't read extension data.");

    /* Access extension data */
    ext_data = (char *)malloc(ext_size);
    err = clGetPlatformInfo(platforms[i], CL_PLATFORM_EXTENSIONS, ext_size, ext_data, NULL);
    handleError("Couldn't access extension data.");
    printf("Platform %d supports extensions: %s\n", i, ext_data);

    /* Look for ICD extension */
    if (strstr(ext_data, icd_ext)) {
      free(ext_data);
      platform_index = i;
      break;
    }
    free(ext_data);
  }

  /* Display whether ICD extension is supported */
  if (platform_index > -1) {
    printf("Platform %d supports the %s extension.\n", platform_index, icd_ext);
  } else {
    printf("No platforms support the %s extension.\n", icd_ext);
  }

  /* Deallocate resources */
  free(platforms);
}
