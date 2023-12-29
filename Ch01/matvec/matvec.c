#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define PROGRAM_FILE "matvec.cl"
#define KERNEL_FUNC "matvec_mult"

void handleError(cl_int err, char *message) {
  if (err) {
    perror(message);
    exit(EXIT_FAILURE);
  }
}

void printProgramLog(cl_program program, cl_device_id device) {
  /* Find size of log and print to std output */
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

  /* Initialize data to be processed by the kernel */
  float mat[16];
  for (cl_int i = 0; i < 16; i++) {
    mat[i] = i * 2.0f;
  }

  float vec[4];
  float correct[] = {0.0f, 0.0f, 0.0f, 0.0f};
  for (cl_int i = 0; i < 4; i++) {
    vec[i] = i * 3.0f;
    correct[0] += mat[i] * vec[i];
    correct[1] += mat[i + 4] * vec[i];
    correct[2] += mat[i + 8] * vec[i];
    correct[3] += mat[i + 12] * vec[i];
  }

  /* Identify a platform */
  cl_platform_id platform;
  cl_int err = clGetPlatformIDs(1, &platform, NULL);
  handleError(err, "Couldn't find any platforms");

  /* Access a device */
  cl_device_id device;
  err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
  handleError(err, "Couldn't find any devices");

  /* Create the context */
  cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
  handleError(err, "Couldn't create a context");

  /* Read program file and place content into buffer */
  FILE *program_handle = fopen(PROGRAM_FILE, "r");
  handleError(!program_handle, "Couldn't find the program file");

  fseek(program_handle, 0, SEEK_END);
  size_t program_size = ftell(program_handle);
  rewind(program_handle);
  char *program_buffer = (char *)malloc(program_size + 1);
  program_buffer[program_size] = '\0';
  fread(program_buffer, sizeof(char), program_size, program_handle);
  fclose(program_handle);

  /* Create program from file */
  cl_program program = clCreateProgramWithSource(context, 1, (const char **)&program_buffer, &program_size, &err);
  handleError(err, "Couldn't create the program");
  free(program_buffer);

  /* Build program */
  err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
  if (err) {
    printProgramLog(program, device);
  }

  /* Create kernel for the mat_vec_mult function */
  cl_kernel kernel = clCreateKernel(program, KERNEL_FUNC, &err);
  handleError(err, "Couldn't create the kernel");

  /* Create CL buffers to hold input and output data */
  cl_mem mat_buff = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * 16, mat, &err);
  handleError(err, "Couldn't create a buffer object");
  cl_mem vec_buff = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * 4, vec, &err);
  handleError(err, "Couldn't create a buffer object");
  cl_mem res_buff = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * 4, NULL, &err);
  handleError(err, "Couldn't create a buffer object");

  /* Create kernel arguments from the CL buffers */
  err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &mat_buff);
  handleError(err, "Couldn't set the kernel argument");
  err = clSetKernelArg(kernel, 1, sizeof(cl_mem), &vec_buff);
  handleError(err, "Couldn't set the kernel argument");
  err = clSetKernelArg(kernel, 2, sizeof(cl_mem), &res_buff);
  handleError(err, "Couldn't set the kernel argument");

  /* Create a CL command queue for the device*/
  cl_command_queue queue = clCreateCommandQueueWithProperties(context, device, NULL, &err);
  handleError(err, "Couldn't create the command queue");

  /* Enqueue the command queue to the device */
  size_t work_units_per_kernel = 4; /* 4 work-units per kernel */
  err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &work_units_per_kernel, NULL, 0, NULL, NULL);
  handleError(err, "Couldn't enqueue the kernel execution command");

  /* Read the result */
  float result[4];
  err = clEnqueueReadBuffer(queue, res_buff, CL_TRUE, 0, sizeof(float) * 4, result, 0, NULL, NULL);
  handleError(err, "Couldn't enqueue the read buffer command");

  /* Test the result */
  // clang-format off
  if (result[0] == correct[0] &&
      result[1] == correct[1] &&
      result[2] == correct[2] &&
      result[3] == correct[3]) {
    printf("Matrix-vector multiplication successful.\n");
  } else {
    printf("Matrix-vector multiplication unsuccessful.\n");
  }
  // clang-format on

  /* Deallocate resources */
  clReleaseMemObject(mat_buff);
  clReleaseMemObject(vec_buff);
  clReleaseMemObject(res_buff);
  clReleaseKernel(kernel);
  clReleaseCommandQueue(queue);
  clReleaseProgram(program);
  clReleaseContext(context);
}
