#include "aux.h"

int main(void) {

  // set up OpenCL
  cl_platform_id platform = getFirstPlatform();
  cl_device_id device = getFirstGPUDevice(platform);
  cl_context context = createContext(device);
  cl_program program = createProgram(context, device);
  cl_kernel kernel = createKernel(program);
  cl_command_queue queue = createCommandQueue(context, device);

  // data to be processed by the kernel
  float mat[16];
  for (cl_int i = 0; i < 16; i++) {
    mat[i] = i * 2.0f;
  }

  float vec[4];
  for (cl_int i = 0; i < 4; i++) {
    vec[i] = i * 3.0f;
  }

  // write to device
  cl_mem mat_buff = createMatrixBuffer(context, mat);
  cl_mem vec_buff = createVectorBuffer(context, vec);
  cl_mem res_buff = createResultBuffer(context);

  runKernel(kernel, queue, mat_buff, vec_buff, res_buff);

  // read from device
  float result[4];
  readResult(queue, res_buff, result);

  testResult(mat, vec, result);

  releaseResources(platform, context, device, queue, program, kernel, mat_buff, vec_buff, res_buff);
}
