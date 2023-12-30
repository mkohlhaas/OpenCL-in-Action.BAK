#include "aux.h"
#include <stdio.h>

void handleError(cl_int err, char *message) {
  if (err) {
    fprintf(stderr, "%s\nError: %d\n", message, err);
    exit(EXIT_FAILURE);
  }
}

cl_platform_id *getPlatforms(cl_uint *numPlatforms) {
  cl_int err = clGetPlatformIDs(0, NULL, numPlatforms);
  handleError(err, "Error getting platforms.");
  handleError(!numPlatforms, "There are no platform SDKs installed.");
  cl_platform_id *platforms = malloc(sizeof(cl_platform_id) * (*numPlatforms));
  err = clGetPlatformIDs(*numPlatforms, platforms, NULL);
  handleError(err, "Couldn't get any platforms.");
  return platforms;
}

char *getPlatformInfoChar(cl_platform_id platform, cl_platform_info paramName) {
  size_t length;
  cl_int err = clGetPlatformInfo(platform, paramName, 0, NULL, &length);
  char *str = malloc(sizeof(char) * length);
  err = clGetPlatformInfo(platform, paramName, length, str, NULL);
  handleError(err, "Couldn't get platform info.");
  return str;
}

char *getPlatformName(cl_platform_id platform) { return getPlatformInfoChar(platform, CL_PLATFORM_NAME); }
char *getPlatformProfile(cl_platform_id platform) { return getPlatformInfoChar(platform, CL_PLATFORM_PROFILE); }
char *getPlatformVersion(cl_platform_id platform) { return getPlatformInfoChar(platform, CL_PLATFORM_VERSION); }
char *getPlatformVendor(cl_platform_id platform) { return getPlatformInfoChar(platform, CL_PLATFORM_VENDOR); }

cl_name_version *getPlatformExtensions(cl_platform_id platform, size_t *numExtensions) {
  cl_int err = clGetPlatformInfo(platform, CL_PLATFORM_EXTENSIONS_WITH_VERSION, 0, NULL, numExtensions);
  handleError(err, "Couldn't get number of extensions.");
  cl_name_version *extensions = malloc(*numExtensions);
  err = clGetPlatformInfo(platform, CL_PLATFORM_EXTENSIONS_WITH_VERSION, (*numExtensions), extensions, NULL);
  handleError(err, "Couldn't get platform extensions info.");
  *numExtensions /= (CL_NAME_VERSION_MAX_NAME_SIZE + sizeof(cl_version));
  return extensions;
}

unpackedVersion _unpackVersion(cl_uint version) {
  unpackedVersion ret;
  ret.major = (version >> 22);
  ret.minor = (version >> 12) & ((1 << 10) - 1);
  ret.patch = version & ((1 << 12) - 1);
  return ret;
}

char *versionToStr(cl_uint version) {
  unpackedVersion unpacked = _unpackVersion(version);
  char *retValue = malloc(50);
  sprintf(retValue, "%u.%u.%u", unpacked.major, unpacked.minor, unpacked.patch);
  return retValue;
}

cl_ulong getPlatformHostTimerResolution(cl_platform_id platform) {
  size_t length;
  cl_ulong timerResolution;
  cl_int err = clGetPlatformInfo(platform, CL_PLATFORM_HOST_TIMER_RESOLUTION, 0, NULL, &length);
  err = clGetPlatformInfo(platform, CL_PLATFORM_HOST_TIMER_RESOLUTION, length, &timerResolution, NULL);
  handleError(err, "Couldn't get platform host timer resolution.");
  return timerResolution;
}
