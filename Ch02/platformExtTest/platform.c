#include "error.h"
#include <CL/cl.h>

// Platform

cl_platform_id *getPlatforms(cl_uint *numPlatforms) {
  cl_int err = clGetPlatformIDs(0, NULL, numPlatforms);
  handleError(err, "Error getting platforms.");
  cl_platform_id *platforms = malloc(sizeof(cl_platform_id) * (*numPlatforms));
  err = clGetPlatformIDs(*numPlatforms, platforms, NULL);
  handleError(err, "Couldn't get any platforms.");
  return platforms;
}

static char *getPlatformInfoStr(cl_platform_id platform, cl_platform_info paramName) {
  size_t paramSize;
  cl_int err = clGetPlatformInfo(platform, paramName, 0, NULL, &paramSize);
  char *str = malloc(sizeof(char) * paramSize);
  err = clGetPlatformInfo(platform, paramName, paramSize, str, NULL);
  handleError(err, "Couldn't get platform info.");
  return str;
}

// clang-format off
char *getPlatformName(cl_platform_id platform)    { return getPlatformInfoStr(platform, CL_PLATFORM_NAME); }
char *getPlatformProfile(cl_platform_id platform) { return getPlatformInfoStr(platform, CL_PLATFORM_PROFILE); }
char *getPlatformVersion(cl_platform_id platform) { return getPlatformInfoStr(platform, CL_PLATFORM_VERSION); }
char *getPlatformVendor(cl_platform_id platform)  { return getPlatformInfoStr(platform, CL_PLATFORM_VENDOR); }
// clang-format on

cl_name_version *getPlatformExtensions(cl_platform_id platform, size_t *numExtensions) {
  cl_int err = clGetPlatformInfo(platform, CL_PLATFORM_EXTENSIONS_WITH_VERSION, 0, NULL, numExtensions);
  handleError(err, "Couldn't get number of extensions.");
  cl_name_version *extensions = malloc(*numExtensions);
  err = clGetPlatformInfo(platform, CL_PLATFORM_EXTENSIONS_WITH_VERSION, (*numExtensions), extensions, NULL);
  handleError(err, "Couldn't get platform extensions info.");
  *numExtensions /= (CL_NAME_VERSION_MAX_NAME_SIZE + sizeof(cl_version));
  return extensions;
}

cl_ulong getPlatformHostTimerResolution(cl_platform_id platform) {
  size_t paramSize;
  cl_ulong timerResolution;
  cl_int err = clGetPlatformInfo(platform, CL_PLATFORM_HOST_TIMER_RESOLUTION, 0, NULL, &paramSize);
  err = clGetPlatformInfo(platform, CL_PLATFORM_HOST_TIMER_RESOLUTION, paramSize, &timerResolution, NULL);
  handleError(err, "Couldn't get platform host timer resolution.");
  return timerResolution;
}

cl_device_id *getDeviceIDs(cl_platform_id platform, cl_uint *numDevices) {
  *numDevices = 0;
  cl_int err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, NULL, numDevices);
  if (err)
    return NULL;
  cl_device_id *devices = malloc(sizeof(cl_device_id) * (*numDevices));
  err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, *numDevices, devices, NULL);
  if (err)
    return NULL;
  return devices;
}
