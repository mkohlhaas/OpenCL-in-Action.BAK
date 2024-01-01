#include <CL/cl.h>

// clang-format off
char            *getPlatformName(cl_platform_id platform);
char            *getPlatformProfile(cl_platform_id platform);
char            *getPlatformVendor(cl_platform_id platform);
char            *getPlatformVersion(cl_platform_id platform);
cl_device_id    *getDeviceIDs(cl_platform_id platform, cl_uint *numDevices);
cl_name_version *getPlatformExtensions(cl_platform_id platform, size_t *);
cl_platform_id  *getPlatforms(cl_uint *numPlatforms);
cl_ulong         getPlatformHostTimerResolution(cl_platform_id platform);
