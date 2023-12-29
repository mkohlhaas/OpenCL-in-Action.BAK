#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define PROGRAM_FILE "matvec.cl"
#define KERNEL_FUNC "matvec_mult"

void handleError(cl_int err, char *message) {
  if (err) {
    fprintf(stderr, "%s\nError: %d\n", message, err);
    exit(EXIT_FAILURE);
  }
}

cl_platform_id getFirstPlatform() {
  cl_platform_id platform;
  cl_int err = clGetPlatformIDs(1, &platform, NULL);
  handleError(err, "Couldn't find any platforms.");
  return platform;
}

cl_device_id getFirstGPUDevice(cl_platform_id platform) {
  cl_int err;
  cl_device_id device;
  err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
  handleError(err, "Couldn't find any devices.");
  return device;
}

cl_context createContext(cl_device_id device) {
  cl_int err;
  cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
  handleError(err, "Couldn't create a context.");
  return context;
}

void printProgramBuildLog(cl_program program, cl_device_id device) {
  // get size of build log
  size_t log_size;
  clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
  // load build log
  char *program_log = (char *)malloc(log_size + 1);
  program_log[log_size] = '\0';
  clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size + 1, program_log, NULL);
  // print build log
  printf("%s\n", program_log);
  free(program_log);
  exit(EXIT_FAILURE);
}

cl_program createProgram(cl_context context, cl_device_id device) { // device necessary for build log
  cl_int err;

  // open file
  FILE *program_handle = fopen(PROGRAM_FILE, "r");
  handleError(!program_handle, "Couldn't find the program file.");

  // read file content
  fseek(program_handle, 0, SEEK_END);
  size_t program_size = ftell(program_handle);
  rewind(program_handle);
  char *program_buffer = (char *)malloc(program_size + 1);
  program_buffer[program_size] = '\0';
  fread(program_buffer, sizeof(char), program_size, program_handle);
  fclose(program_handle);

  // create program from source
  cl_program program = clCreateProgramWithSource(context, 1, (const char **)&program_buffer, &program_size, &err);
  handleError(err, "Couldn't create the program.");
  free(program_buffer);

  // build program
  err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
  if (err) {
    printProgramBuildLog(program, device);
  }
  return program;
}

cl_kernel createKernel(cl_program program) {
  cl_int err;
  cl_kernel kernel = clCreateKernel(program, KERNEL_FUNC, &err);
  handleError(err, "Couldn't create the kernel.");
  return kernel;
}

cl_command_queue createCommandQueue(cl_context context, cl_device_id device) {
  cl_int err;
  cl_command_queue queue = clCreateCommandQueueWithProperties(context, device, NULL, &err);
  handleError(err, "Couldn't create the command queue.");
  return queue;
}

cl_mem createInputBuffer(cl_context context, float *in, size_t size) {
  cl_int err;
  cl_mem mat_buff = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * size, in, &err);
  handleError(err, "Couldn't create buffer object.");
  return mat_buff;
}

cl_mem createMatrixBuffer(cl_context context, float *mat) { return createInputBuffer(context, mat, 16); }

cl_mem createVectorBuffer(cl_context context, float *vec) { return createInputBuffer(context, vec, 4); }

cl_mem createResultBuffer(cl_context context) {
  cl_int err;
  cl_mem res_buff = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * 4, NULL, &err);
  handleError(err, "Couldn't create result buffer object.");
  return res_buff;
}

void runKernel(cl_kernel kernel, cl_command_queue queue, cl_mem mat_buff, cl_mem vec_buff, cl_mem res_buff) {
  cl_int err;

  // set arguments
  err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &mat_buff);
  err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &vec_buff);
  err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &res_buff);
  handleError(err, "Couldn't set kernel arguments.");

  // enqueue kernel
  size_t work_units_per_kernel = 4;
  err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &work_units_per_kernel, NULL, 0, NULL, NULL);
  handleError(err, "Couldn't enqueue the kernel execution command.");
}

void readResult(cl_command_queue queue, cl_mem res_buff, float *result) {
  cl_int err = clEnqueueReadBuffer(queue, res_buff, CL_BLOCKING, 0, sizeof(float) * 4, result, 0, NULL, NULL);
  handleError(err, "Couldn't enqueue the read buffer command.");
}

void testResult(float *mat, float *vec, float *result) {
  float expected[] = {0, 0, 0, 0};
  for (cl_int i = 0; i < 4; i++) {
    expected[0] += mat[i] * vec[i];      // 84.000000
    expected[1] += mat[i + 4] * vec[i];  // 228.000000
    expected[2] += mat[i + 8] * vec[i];  // 372.000000
    expected[3] += mat[i + 12] * vec[i]; // 516.000000
  }

  // clang-format off
  if (result[0] == expected[0] &&
      result[1] == expected[1] &&
      result[2] == expected[2] &&
      result[3] == expected[3])
  { // clang-format on
    printf("Matrix-vector multiplication successful!\n");
  } else {
    printf("Matrix-vector multiplication NOT successful!\n");
  }
}

void releaseResources(cl_platform_id platform, cl_context context, cl_device_id device, cl_command_queue queue,
                      cl_program program, cl_kernel kernel, cl_mem res_buff, cl_mem vec_buff, cl_mem mat_buff) {
  clReleaseMemObject(mat_buff);
  clReleaseMemObject(vec_buff);
  clReleaseMemObject(res_buff);
  clReleaseKernel(kernel);
  clReleaseProgram(program);
  clReleaseCommandQueue(queue);
  clReleaseDevice(device);
  clReleaseContext(context);
}
