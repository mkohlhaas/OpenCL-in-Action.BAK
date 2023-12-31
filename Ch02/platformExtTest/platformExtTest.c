#include "aux.h"
#include "json_object.h"
#include <stdio.h>

int main(void) {

  // set up OpenCL
  cl_uint numPlatforms;
  cl_platform_id *platforms = getPlatforms(&numPlatforms);

  json_object *Root = json_object_new_object();
  json_object *Platforms = json_object_new_array();
  json_object_object_add(Root, "platforms", Platforms);

  for (int i = 0; i < numPlatforms; i++) {
    json_object *Platform = json_object_new_object();
    json_object_array_add(Platforms, Platform);

    // Name
    char *platformName = getPlatformName(platforms[i]);
    json_object_object_add(Platform, "name", json_object_new_string(platformName));

    // Profile
    char *platformProfile = getPlatformProfile(platforms[i]);
    json_object_object_add(Platform, "profile", json_object_new_string(platformProfile));

    // Version
    char *platformVersion = getPlatformVersion(platforms[i]);
    json_object_object_add(Platform, "version", json_object_new_string(platformVersion));

    // Vendor
    char *platformVendor = getPlatformVendor(platforms[i]);
    json_object_object_add(Platform, "vendor", json_object_new_string(platformVendor));

    // Host Timer Resolution
    cl_ulong htr = getPlatformHostTimerResolution(platforms[i]);
    json_object_object_add(Platform, "host_timer_resolution", json_object_new_uint64(htr));

    // Extensions
    size_t numExtensions;
    cl_name_version *extensions = getPlatformExtensions(platforms[i], &numExtensions);
    json_object *Extensions = json_object_new_array();
    for (int i = 0; i < numExtensions; i++) {
      json_object *Extension = json_object_new_object();
      json_object_object_add(Extension, "name", json_object_new_string(extensions[i].name));
      json_object_object_add(Extension, "version", json_object_new_string(versionToStr(extensions[i].version)));
      json_object_array_add(Extensions, Extension);
    }
    json_object_object_add(Platform, "extensions", Extensions);
  }
  printf("%s\n", json_object_to_json_string_ext(Root, JSON_C_TO_STRING_PLAIN));
}
