#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define PROGRAM_FILE "test.cl"

cl_int err;

void handleError(char *message) {
  if (err) {
    perror(message);
    exit(EXIT_FAILURE);
  }
}

void printProgramLog(cl_program program, cl_device_id device) {
  size_t log_size;
  clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
  char *program_log = (char *)malloc(log_size + 1);
  program_log[log_size] = '\0';
  clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size + 1, program_log, NULL);
  printf("%s\n", program_log);
  free(program_log);
  exit(EXIT_FAILURE);
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

  /* Create a context */
  cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
  handleError("Couldn't create a context");

  /* Read program file and place content into buffer */
  FILE *program_handle = fopen(PROGRAM_FILE, "r");
  err = !program_handle;
  handleError("Couldn't find the program file");

  fseek(program_handle, 0, SEEK_END);
  size_t program_size = ftell(program_handle);
  rewind(program_handle);
  char *program_buffer = (char *)malloc(program_size + 1);
  program_buffer[program_size] = '\0';
  fread(program_buffer, sizeof(char), program_size, program_handle);
  fclose(program_handle);

  /* Create program from file */
  cl_program program = clCreateProgramWithSource(context, 1, (const char **)&program_buffer, &program_size, &err);
  handleError("Couldn't create the program");
  free(program_buffer);

  /* Build program */
  err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
  if (err) {
    printProgramLog(program, device);
  }

  /* Find out how many kernels are in the source file */
  cl_uint num_kernels;
  err = clCreateKernelsInProgram(program, 0, NULL, &num_kernels);
  handleError("Couldn't find any kernels");

  /* Create a kernel for each function */
  cl_kernel *kernels = (cl_kernel *)malloc(num_kernels * sizeof(cl_kernel));
  err = clCreateKernelsInProgram(program, num_kernels, kernels, NULL);
  handleError("Couldn't create kernel.");

  /* Search for the named kernel */
  char kernel_name[20];
  for (cl_uint i = 0; i < num_kernels; i++) {
    err = clGetKernelInfo(kernels[i], CL_KERNEL_FUNCTION_NAME, sizeof(kernel_name), kernel_name, NULL);
    handleError("Couldn't kernel function name.");
    if (!strcmp(kernel_name, "mult")) {
      printf("Found mult kernel at index %u.\n", i);
      break;
    }
  }

  for (cl_int i = 0; i < num_kernels; i++) {
    clReleaseKernel(kernels[i]);
  }
  free(kernels);
  clReleaseProgram(program);
  clReleaseContext(context);
}
