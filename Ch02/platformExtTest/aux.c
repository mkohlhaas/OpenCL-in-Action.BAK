#include "aux.h"
#include <stdio.h>

typedef struct {
  cl_uint major;
  cl_uint minor;
  cl_uint patch;
} unpackedVersion;

void handleError(cl_int err, char *message) {
  if (err) {
    // TODO; proper error message for err
    // CL_SUCCESS
    // CL_DEVICE_NOT_FOUND
    // CL_DEVICE_NOT_AVAILABLE
    // CL_COMPILER_NOT_AVAILABLE
    // CL_MEM_OBJECT_ALLOCATION_FAILURE
    // CL_OUT_OF_RESOURCES
    // CL_OUT_OF_HOST_MEMORY
    // CL_PROFILING_INFO_NOT_AVAILABLE
    // CL_MEM_COPY_OVERLAP
    // CL_IMAGE_FORMAT_MISMATCH
    // CL_IMAGE_FORMAT_NOT_SUPPORTED
    // CL_BUILD_PROGRAM_FAILURE
    // CL_MAP_FAILURE
    // CL_MISALIGNED_SUB_BUFFER_OFFSET
    // CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST
    // CL_COMPILE_PROGRAM_FAILURE
    // CL_LINKER_NOT_AVAILABLE
    // CL_LINK_PROGRAM_FAILURE
    // CL_DEVICE_PARTITION_FAILED
    // CL_KERNEL_ARG_INFO_NOT_AVAILABLE
    // CL_INVALID_VALUE
    // CL_INVALID_DEVICE_TYPE
    // CL_INVALID_PLATFORM
    // CL_INVALID_DEVICE
    // CL_INVALID_CONTEXT
    // CL_INVALID_QUEUE_PROPERTIES
    // CL_INVALID_COMMAND_QUEUE
    // CL_INVALID_HOST_PTR
    // CL_INVALID_MEM_OBJECT
    // CL_INVALID_IMAGE_FORMAT_DESCRIPTOR
    // CL_INVALID_IMAGE_SIZE
    // CL_INVALID_SAMPLER
    // CL_INVALID_BINARY
    // CL_INVALID_BUILD_OPTIONS
    // CL_INVALID_PROGRAM
    // CL_INVALID_PROGRAM_EXECUTABLE
    // CL_INVALID_KERNEL_NAME
    // CL_INVALID_KERNEL_DEFINITION
    // CL_INVALID_KERNEL
    // CL_INVALID_ARG_INDEX
    // CL_INVALID_ARG_VALUE
    // CL_INVALID_ARG_SIZE
    // CL_INVALID_KERNEL_ARGS
    // CL_INVALID_WORK_DIMENSION
    // CL_INVALID_WORK_GROUP_SIZE
    // CL_INVALID_WORK_ITEM_SIZE
    // CL_INVALID_GLOBAL_OFFSET
    // CL_INVALID_EVENT_WAIT_LIST
    // CL_INVALID_EVENT
    // CL_INVALID_OPERATION
    // CL_INVALID_GL_OBJECT
    // CL_INVALID_BUFFER_SIZE
    // CL_INVALID_MIP_LEVEL
    // CL_INVALID_GLOBAL_WORK_SIZE
    // CL_INVALID_PROPERTY
    // CL_INVALID_IMAGE_DESCRIPTOR
    // CL_INVALID_COMPILER_OPTIONS
    // CL_INVALID_LINKER_OPTIONS
    // CL_INVALID_DEVICE_PARTITION_COUNT
    // CL_INVALID_PIPE_SIZE
    // CL_INVALID_DEVICE_QUEUE
    // CL_INVALID_SPEC_ID
    // CL_MAX_SIZE_RESTRICTION_EXCEEDED
    fprintf(stderr, "%s\nError: %d\n", message, err);
    exit(EXIT_FAILURE);
  }
}

cl_platform_id *getPlatforms(cl_uint *numPlatforms) {
  cl_int err = clGetPlatformIDs(0, NULL, numPlatforms);
  handleError(err, "Error getting platforms.");
  cl_platform_id *platforms = malloc(sizeof(cl_platform_id) * (*numPlatforms));
  err = clGetPlatformIDs(*numPlatforms, platforms, NULL);
  handleError(err, "Couldn't get any platforms.");
  return platforms;
}

char *getPlatformInfoParam(cl_platform_id platform, cl_platform_info paramName) {
  size_t paramSize;
  cl_int err = clGetPlatformInfo(platform, paramName, 0, NULL, &paramSize);
  char *str = malloc(sizeof(char) * paramSize);
  err = clGetPlatformInfo(platform, paramName, paramSize, str, NULL);
  handleError(err, "Couldn't get platform info.");
  return str;
}

char *getPlatformName(cl_platform_id platform) { return getPlatformInfoParam(platform, CL_PLATFORM_NAME); }
char *getPlatformProfile(cl_platform_id platform) { return getPlatformInfoParam(platform, CL_PLATFORM_PROFILE); }
char *getPlatformVersion(cl_platform_id platform) { return getPlatformInfoParam(platform, CL_PLATFORM_VERSION); }
char *getPlatformVendor(cl_platform_id platform) { return getPlatformInfoParam(platform, CL_PLATFORM_VENDOR); }

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
  GString *retValue = g_string_new(NULL);
  g_string_append_printf(retValue, "%u.%u.%u", unpacked.major, unpacked.minor, unpacked.patch);
  return g_string_free(retValue, FALSE);
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

void _prtArray(GArray *arr) {
  printf("Array holds:\n");
  for (int i = 0; i < arr->len; i++)
    printf("%s\n", g_array_index(arr, char *, i));
  printf("\n");
}

GArray *getDeviceTypes(cl_device_id device) {
  GArray *deviceTypes = g_array_new(FALSE, FALSE, sizeof(char *));
  size_t paramSize;
  cl_int err = clGetDeviceInfo(device, CL_DEVICE_TYPE, 0, NULL, &paramSize);
  handleError(err, "Couldn't get device type.");
  cl_device_type deviceType;
  err = clGetDeviceInfo(device, CL_DEVICE_TYPE, paramSize, &deviceType, NULL);
  handleError(err, "Couldn't get device type.");

  char *defaultType = "Default";
  char *cpuType = "CPU";
  char *gpuType = "GPU";
  char *acceleratorType = "Accelerator";

  if (deviceType & CL_DEVICE_TYPE_DEFAULT)
    g_array_append_val(deviceTypes, defaultType);
  else if (deviceType & CL_DEVICE_TYPE_CPU)
    g_array_append_val(deviceTypes, cpuType);
  else if (deviceType & CL_DEVICE_TYPE_GPU)
    g_array_append_val(deviceTypes, gpuType);
  else if (deviceType & CL_DEVICE_TYPE_ACCELERATOR)
    g_array_append_val(deviceTypes, acceleratorType);

  return deviceTypes;
}

cl_uint getDeviceUint(cl_device_id device, cl_device_info paramName, char *errorMsg) {
  cl_uint retValue;
  size_t paramSize;
  cl_int err = clGetDeviceInfo(device, paramName, 0, NULL, &paramSize);
  handleError(err, errorMsg);
  err = clGetDeviceInfo(device, paramName, paramSize, &retValue, NULL);
  handleError(err, errorMsg);
  return retValue;
}

cl_uint getDeviceVendorID(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_VENDOR_ID, "Couldn't get device vendor.");
}

cl_uint getDeviceMaxComputeUnits(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_MAX_COMPUTE_UNITS, "Couldn't get max compute units.");
}

cl_uint getDeviceMaxWorkItemDimensions(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, "Couldn't get max work item dimensions.");
}

cl_uint getPreferredVectorWidthChar(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR, "Couldn't get preferred vector width char.");
}

cl_uint getPreferredVectorWidthShort(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT, "Couldn't get preferred vector width short.");
}

cl_uint getPreferredVectorWidthInt(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT, "Couldn't get preferred vector width int.");
}

cl_uint getPreferredVectorWidthLong(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG, "Couldn't get preferred vector width long.");
}

cl_uint getPreferredVectorWidthFloat(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT, "Couldn't get preferred vector width float.");
}

cl_uint getPreferredVectorWidthDouble(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE, "Couldn't get preferred vector width double.");
}

cl_uint getNativeVectorWidthChar(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR, "Couldn't get native vector width char.");
}

cl_uint getNativeVectorWidthShort(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT, "Couldn't get native vector width short.");
}

cl_uint getNativeVectorWidthInt(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_NATIVE_VECTOR_WIDTH_INT, "Couldn't get native vector width int.");
}

cl_uint getNativeVectorWidthLong(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG, "Couldn't get native vector width long.");
}

cl_uint getNativeVectorWidthFloat(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT, "Couldn't get native vector width float.");
}

cl_uint getNativeVectorWidthDouble(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE, "Couldn't get native vector width double.");
}

cl_uint getNativeVectorWidthHalf(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF, "Couldn't get native vector width half.");
}

cl_uint getMaxClockFrequency(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, "Couldn't get max clock frequency.");
}

cl_uint getAddressBits(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_ADDRESS_BITS, "Couldn't get address bits.");
}

cl_uint getMaxReadImageArgs(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_MAX_READ_IMAGE_ARGS, "Couldn't get max read image args.");
}

cl_uint getMaxWriteImageArgs(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_MAX_WRITE_IMAGE_ARGS, "Couldn't get max write image args.");
}

cl_uint getMaxReadWriteImageArgs(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_MAX_READ_WRITE_IMAGE_ARGS, "Couldn't get max read write image args.");
}

cl_uint getMaxSamplers(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_MAX_SAMPLERS, "Couldn't get max samplers.");
}

cl_uint getImagePitchAlignment(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_IMAGE_PITCH_ALIGNMENT, "Couldn't get image pitch alignment.");
}

cl_uint getImageBaseAddressAlignment(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_IMAGE_BASE_ADDRESS_ALIGNMENT, "Couldn't get image base address alignment.");
}

cl_uint getMaxPipeArgs(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_MAX_PIPE_ARGS, "Couldn't get max pipe args.");
}

cl_uint getPipeMaxActiveReservations(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_MAX_PIPE_ARGS, "Couldn't get pipe max active reservations.");
}

cl_uint getPipeMaxPacketSize(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_MAX_PIPE_ARGS, "Couldn't get pipe max packet size.");
}

cl_uint getMemBaseAddrAlign(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_MAX_PIPE_ARGS, "Couldn't get mem base addr align.");
}

cl_uint getGlobalMemCachelineSize(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE, "Couldn't get global mem cacheline size.");
}

cl_uint getMaxConstantArgs(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_MAX_CONSTANT_ARGS, "Couldn't get max constant args.");
}

cl_uint getQueueOnDevicePreferredSize(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_QUEUE_ON_DEVICE_PREFERRED_SIZE, "Couldn't get queue on device preferred size.");
}

cl_uint getQueueOnDeviceMaxSize(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_QUEUE_ON_DEVICE_MAX_SIZE, "Couldn't get queue on device max size.");
}

cl_uint getMaxOnDeviceQueues(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_MAX_ON_DEVICE_QUEUES, "Couldn't get max on device queues.");
}

cl_uint getMaxOnDeviceEvents(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_MAX_ON_DEVICE_EVENTS, "Couldn't get max on device events.");
}

cl_uint getPartitionMaxSubDevices(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_PARTITION_MAX_SUB_DEVICES, "Couldn't get partition max sub devices.");
}

cl_uint getReferenceCount(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_REFERENCE_COUNT, "Couldn't get reference count.");
}

cl_uint getPreferredPlatformAtomicAlignment(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_PREFERRED_PLATFORM_ATOMIC_ALIGNMENT, "Couldn't get preferred platform atomic alignment.");
}

cl_uint getPreferredGlobalAtomicAlignment(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_PREFERRED_GLOBAL_ATOMIC_ALIGNMENT, "Couldn't get preferred global atomic alignment.");
}

cl_uint getPreferredLocalAtomicAlignment(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_PREFERRED_LOCAL_ATOMIC_ALIGNMENT, "Couldn't get preferred local atomic alignment.");
}

cl_uint getMaxNumSubGroups(cl_device_id device) {
  return getDeviceUint(device, CL_DEVICE_MAX_NUM_SUB_GROUPS, "Couldn't get max num sub groups.");
}

// cl_bool 13
// size_t  18
// char[]  10

// CL_DEVICE_MAX_WORK_GROUP_SIZE
// CL_DEVICE_MAX_WORK_ITEM_SIZES
// CL_DEVICE_MAX_MEM_ALLOC_SIZE
// CL_DEVICE_IMAGE2D_MAX_WIDTH
// CL_DEVICE_IMAGE2D_MAX_HEIGHT
// CL_DEVICE_IMAGE3D_MAX_WIDTH
// CL_DEVICE_IMAGE3D_MAX_HEIGHT
// CL_DEVICE_IMAGE3D_MAX_DEPTH
// CL_DEVICE_IMAGE_SUPPORT
// CL_DEVICE_MAX_PARAMETER_SIZE
// CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE
// CL_DEVICE_SINGLE_FP_CONFIG
// CL_DEVICE_GLOBAL_MEM_CACHE_TYPE
// CL_DEVICE_GLOBAL_MEM_CACHE_SIZE
// CL_DEVICE_GLOBAL_MEM_SIZE
// CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE
// CL_DEVICE_MAX_CONSTANT_ARGS
// CL_DEVICE_LOCAL_MEM_TYPE
// CL_DEVICE_LOCAL_MEM_SIZE
// CL_DEVICE_ERROR_CORRECTION_SUPPORT
// CL_DEVICE_PROFILING_TIMER_RESOLUTION
// CL_DEVICE_ENDIAN_LITTLE
// CL_DEVICE_AVAILABLE
// CL_DEVICE_COMPILER_AVAILABLE
// CL_DEVICE_EXECUTION_CAPABILITIES
// CL_DEVICE_QUEUE_PROPERTIES
// CL_DEVICE_QUEUE_ON_HOST_PROPERTIES
// CL_DEVICE_NAME
// CL_DEVICE_VENDOR
// CL_DRIVER_VERSION
// CL_DEVICE_PROFILE
// CL_DEVICE_VERSION
// CL_DEVICE_EXTENSIONS
// CL_DEVICE_PLATFORM
// CL_DEVICE_DOUBLE_FP_CONFIG
// CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF
// CL_DEVICE_HOST_UNIFIED_MEMORY
// CL_DEVICE_OPENCL_C_VERSION
// CL_DEVICE_LINKER_AVAILABLE
// CL_DEVICE_BUILT_IN_KERNELS
// CL_DEVICE_IMAGE_MAX_BUFFER_SIZE
// CL_DEVICE_IMAGE_MAX_ARRAY_SIZE
// CL_DEVICE_PARENT_DEVICE
// CL_DEVICE_PARTITION_MAX_SUB_DEVICES
// CL_DEVICE_PARTITION_PROPERTIES
// CL_DEVICE_PARTITION_AFFINITY_DOMAIN
// CL_DEVICE_PARTITION_TYPE
// CL_DEVICE_REFERENCE_COUNT
// CL_DEVICE_PREFERRED_INTEROP_USER_SYNC
// CL_DEVICE_PRINTF_BUFFER_SIZE
// CL_DEVICE_MAX_GLOBAL_VARIABLE_SIZE
// CL_DEVICE_QUEUE_ON_DEVICE_PROPERTIES
// CL_DEVICE_QUEUE_ON_DEVICE_PREFERRED_SIZE
// CL_DEVICE_QUEUE_ON_DEVICE_MAX_SIZE
// CL_DEVICE_MAX_ON_DEVICE_QUEUES
// CL_DEVICE_MAX_ON_DEVICE_EVENTS
// CL_DEVICE_SVM_CAPABILITIES
// CL_DEVICE_GLOBAL_VARIABLE_PREFERRED_TOTAL_SIZE
// CL_DEVICE_PREFERRED_PLATFORM_ATOMIC_ALIGNMENT
// CL_DEVICE_PREFERRED_GLOBAL_ATOMIC_ALIGNMENT
// CL_DEVICE_PREFERRED_LOCAL_ATOMIC_ALIGNMENT
// CL_DEVICE_IL_VERSION
// CL_DEVICE_MAX_NUM_SUB_GROUPS
// CL_DEVICE_SUB_GROUP_INDEPENDENT_FORWARD_PROGRESS
// CL_DEVICE_NUMERIC_VERSION
// CL_DEVICE_EXTENSIONS_WITH_VERSION
// CL_DEVICE_ILS_WITH_VERSION
// CL_DEVICE_BUILT_IN_KERNELS_WITH_VERSION
// CL_DEVICE_ATOMIC_MEMORY_CAPABILITIES
// CL_DEVICE_ATOMIC_FENCE_CAPABILITIES
// CL_DEVICE_NON_UNIFORM_WORK_GROUP_SUPPORT
// CL_DEVICE_OPENCL_C_ALL_VERSIONS
// CL_DEVICE_PREFERRED_WORK_GROUP_SIZE_MULTIPLE
// CL_DEVICE_WORK_GROUP_COLLECTIVE_FUNCTIONS_SUPPORT
// CL_DEVICE_GENERIC_ADDRESS_SPACE_SUPPORT
// CL_DEVICE_OPENCL_C_FEATURES
// CL_DEVICE_DEVICE_ENQUEUE_CAPABILITIES
// CL_DEVICE_PIPE_SUPPORT
// CL_DEVICE_LATEST_CONFORMANCE_VERSION_PASSED
