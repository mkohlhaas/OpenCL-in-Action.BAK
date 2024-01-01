#include "error.h"
#include <stdio.h>

static char *errors[] = {"Success",
                  "Device not found",
                  "Device not available",
                  "Compiler not available",
                  "Mem object allocation failure",
                  "Out of resources",
                  "Out of host memory",
                  "Profiling info not available",
                  "Mem copy overlap",
                  "Image format mismatch",
                  "Image format not supported",
                  "Build program failure",
                  "Map failure",
                  "Misaligned sub buffer offset",
                  "Exec status error for events in wait list",
                  "Compile program failure",
                  "Linker not available",
                  "Link program failure",
                  "Device partition failed",
                  "Kernel arg info not available",
                  "Invalid value",
                  "Invalid device type",
                  "Invalid platform",
                  "Invalid device",
                  "Invalid context",
                  "Invalid queue properties",
                  "Invalid command queue",
                  "Invalid host ptr",
                  "Invalid mem object",
                  "Invalid image format descriptor",
                  "Invalid image size",
                  "Invalid sampler",
                  "Invalid binary",
                  "Invalid build options",
                  "Invalid program",
                  "Invalid program executable",
                  "Invalid kernel name",
                  "Invalid kernel definition",
                  "Invalid kernel",
                  "Invalid arg index",
                  "Invalid arg value",
                  "Invalid arg size",
                  "Invalid kernel args",
                  "Invalid work dimension",
                  "Invalid work group size",
                  "Invalid work item size",
                  "Invalid global offset",
                  "Invalid event wait list",
                  "Invalid event",
                  "Invalid operation",
                  "Invalid gl object",
                  "Invalid buffer size",
                  "Invalid mip level",
                  "Invalid global work size",
                  "Invalid property",
                  "Invalid image descriptor",
                  "Invalid compiler options",
                  "Invalid linker options",
                  "Invalid device partition count",
                  "Invalid pipe size",
                  "Invalid device queue",
                  "Invalid spec id",
                  "Max size restriction exceeded"};

void handleError(cl_int err, char *message) {
  if (err) {
    fprintf(stderr, "%s\nError code: %d\nError message: %s.\n", message, err, errors[-err]);
    exit(EXIT_FAILURE);
  }
}
