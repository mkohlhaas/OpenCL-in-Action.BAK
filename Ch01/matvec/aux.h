#include <CL/cl.h>

void handleError(cl_int, char *);
cl_platform_id getFirstPlatform();
cl_device_id getFirstGPUDevice(cl_platform_id);
cl_context createContext(cl_device_id);
void printProgramBuildLog(cl_program, cl_device_id);
cl_program createProgram(cl_context, cl_device_id);
cl_kernel createKernel(cl_program);
cl_command_queue createCommandQueue(cl_context, cl_device_id);
cl_mem createMatrixBuffer(cl_context, float *);
cl_mem createVectorBuffer(cl_context , float *);
cl_mem createResultBuffer(cl_context);
void runKernel(cl_kernel, cl_command_queue, cl_mem, cl_mem, cl_mem);
void readResult(cl_command_queue, cl_mem, float *);
void testResult(float *, float *, float *);
void releaseResources(cl_platform_id, cl_context, cl_device_id, cl_command_queue, cl_program, cl_kernel, cl_mem, cl_mem, cl_mem);
