#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

cl_int err; // OpenCL errors

void handleError(char *message) {
  if (err) {
    perror(message);
    exit(EXIT_FAILURE);
  }
}

void releaseContext(cl_context context) {
  cl_uint ref_count;
  printf("Releasing context.\n");
  err = clReleaseContext(context);
  handleError("Couldn't release context.");
  err = clGetContextInfo(context, CL_CONTEXT_REFERENCE_COUNT, sizeof(ref_count), &ref_count, NULL);
  handleError("Couldn't read the reference count.");
  printf("Reference count: %u\n", ref_count);
}

int main(void) {

  /* Access the first installed platform */
  cl_platform_id platform;
  err = clGetPlatformIDs(1, &platform, NULL);
  handleError("Couldn't find any platforms");

  /* Access the first available device */
  cl_device_id device;
  err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
  if (err == CL_DEVICE_NOT_FOUND) {
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &device, NULL);
  }
  handleError("Couldn't find any devices");

  /* Create the context */
  cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
  handleError("Couldn't create a context");

  /* Determine the reference count */
  cl_uint ref_count;
  err = clGetContextInfo(context, CL_CONTEXT_REFERENCE_COUNT, sizeof(ref_count), &ref_count, NULL);
  handleError("Couldn't read the reference count.");
  printf("Initial reference count: %u\n", ref_count);

  // Add reference count.
  clRetainContext(context);
  // Decrease reference count.
  releaseContext(context);
  releaseContext(context); // will result in segmentation fault as context does not exist anymore
}
