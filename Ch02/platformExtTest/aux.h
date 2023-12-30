#include <CL/cl.h>

typedef struct {
  cl_uint major;
  cl_uint minor;
  cl_uint patch;
} unpackedVersion;

char *getPlatformName(cl_platform_id);
char *getPlatformProfile(cl_platform_id);
char *getPlatformVendor(cl_platform_id);
char *getPlatformVersion(cl_platform_id);
char *versionToStr(cl_uint version);
cl_name_version *getPlatformExtensions(cl_platform_id, size_t *);
cl_platform_id *getPlatforms(cl_uint *);
cl_ulong getPlatformHostTimerResolution(cl_platform_id);
