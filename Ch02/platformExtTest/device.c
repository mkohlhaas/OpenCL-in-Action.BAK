#include "error.h"
#include <CL/cl.h>
#include <glib.h>
#include <stdio.h>

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

static cl_uint getDeviceUint(cl_device_id device, cl_device_info paramName, char *errorMsg) {
  size_t paramSize;
  cl_int err = clGetDeviceInfo(device, paramName, 0, NULL, &paramSize);
  handleError(err, errorMsg);
  cl_uint retValue;
  err = clGetDeviceInfo(device, paramName, paramSize, &retValue, NULL);
  handleError(err, errorMsg);
  return retValue;
}

// TODO: write macro
static size_t getDeviceSizeT(cl_device_id device, cl_device_info paramName, char *errorMsg) {
  size_t paramSize;
  cl_int err = clGetDeviceInfo(device, paramName, 0, NULL, &paramSize);
  handleError(err, errorMsg);
  size_t retValue;
  err = clGetDeviceInfo(device, paramName, paramSize, &retValue, NULL);
  handleError(err, errorMsg);
  return retValue;
}

static char *getDeviceStr(cl_device_id device, cl_device_info paramName, char *errorMsg) {
  size_t paramSize;
  cl_int err = clGetDeviceInfo(device, paramName, 0, NULL, &paramSize);
  handleError(err, errorMsg);
  char *retValue = malloc(sizeof(char) * paramSize);
  err = clGetDeviceInfo(device, paramName, paramSize, retValue, NULL);
  handleError(err, errorMsg);
  return retValue;
}

// clang-format off
char   *getDeviceBuiltInKernels(cl_device_id device)                      { return getDeviceStr(device,   CL_DEVICE_BUILT_IN_KERNELS,                        "Couldn't get built in kernels."); }
char   *getDeviceDriverVersion(cl_device_id device)                       { return getDeviceStr(device,   CL_DRIVER_VERSION,                                 "Couldn't get driver version."); }
char   *getDeviceIlVersion(cl_device_id device)                           { return getDeviceStr(device,   CL_DEVICE_IL_VERSION,                              "Couldn't get il version."); }
char   *getDeviceLatestConformanceVersionPassed(cl_device_id device)      { return getDeviceStr(device,   CL_DEVICE_LATEST_CONFORMANCE_VERSION_PASSED,       "Couldn't get latest conformance version passed."); }
char   *getDeviceName(cl_device_id device)                                { return getDeviceStr(device,   CL_DEVICE_NAME,                                    "Couldn't get name."); }
char   *getDeviceProfile(cl_device_id device)                             { return getDeviceStr(device,   CL_DEVICE_PROFILE,                                 "Couldn't get profile."); }
char   *getDeviceVendor(cl_device_id device)                              { return getDeviceStr(device,   CL_DEVICE_VENDOR,                                  "Couldn't get vendor."); }
char   *getDeviceVersion(cl_device_id device)                             { return getDeviceStr(device,   CL_DEVICE_VERSION,                                 "Couldn't get version."); }
cl_uint getDeviceAddressBits(cl_device_id device)                         { return getDeviceUint(device,  CL_DEVICE_ADDRESS_BITS,                            "Couldn't get address bits."); }
cl_uint getDeviceAvailable(cl_device_id device)                           { return getDeviceUint(device,  CL_DEVICE_AVAILABLE,                               "Couldn't get device available."); }
cl_uint getDeviceCompilerAvailable(cl_device_id device)                   { return getDeviceUint(device,  CL_DEVICE_COMPILER_AVAILABLE,                      "Couldn't get device compiler available."); }
cl_uint getDeviceEndianLittle(cl_device_id device)                        { return getDeviceUint(device,  CL_DEVICE_ENDIAN_LITTLE,                           "Couldn't get device endian little."); }
cl_uint getDeviceErrorCorrectionSupport(cl_device_id device)              { return getDeviceUint(device,  CL_DEVICE_ERROR_CORRECTION_SUPPORT,                "Couldn't get device error correction support."); }
cl_uint getDeviceGenericAddressSpaceSupport(cl_device_id device)          { return getDeviceUint(device,  CL_DEVICE_GENERIC_ADDRESS_SPACE_SUPPORT,           "Couldn't get device generic address space support."); }
cl_uint getDeviceGlobalMemCachelineSize(cl_device_id device)              { return getDeviceUint(device,  CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE,               "Couldn't get global mem cacheline size."); }
cl_uint getDeviceImageBaseAddressAlignment(cl_device_id device)           { return getDeviceUint(device,  CL_DEVICE_IMAGE_BASE_ADDRESS_ALIGNMENT,            "Couldn't get image base address alignment."); }
cl_uint getDeviceImagePitchAlignment(cl_device_id device)                 { return getDeviceUint(device,  CL_DEVICE_IMAGE_PITCH_ALIGNMENT,                   "Couldn't get image pitch alignment."); }
cl_uint getDeviceImageSupport(cl_device_id device)                        { return getDeviceUint(device,  CL_DEVICE_IMAGE_SUPPORT,                           "Couldn't get device image support."); }
cl_uint getDeviceLinkerAvailable(cl_device_id device)                     { return getDeviceUint(device,  CL_DEVICE_LINKER_AVAILABLE,                        "Couldn't get device linker available."); }
cl_uint getDeviceMaxClockFrequency(cl_device_id device)                   { return getDeviceUint(device,  CL_DEVICE_MAX_CLOCK_FREQUENCY,                     "Couldn't get max clock frequency."); }
cl_uint getDeviceMaxComputeUnits(cl_device_id device)                     { return getDeviceUint(device,  CL_DEVICE_MAX_COMPUTE_UNITS,                       "Couldn't get max compute units."); }
cl_uint getDeviceMaxConstantArgs(cl_device_id device)                     { return getDeviceUint(device,  CL_DEVICE_MAX_CONSTANT_ARGS,                       "Couldn't get max constant args."); }
cl_uint getDeviceMaxNumSubGroups(cl_device_id device)                     { return getDeviceUint(device,  CL_DEVICE_MAX_NUM_SUB_GROUPS,                      "Couldn't get max num sub groups."); }
cl_uint getDeviceMaxOnDeviceEvents(cl_device_id device)                   { return getDeviceUint(device,  CL_DEVICE_MAX_ON_DEVICE_EVENTS,                    "Couldn't get max on device events."); }
cl_uint getDeviceMaxOnDeviceQueues(cl_device_id device)                   { return getDeviceUint(device,  CL_DEVICE_MAX_ON_DEVICE_QUEUES,                    "Couldn't get max on device queues."); }
cl_uint getDeviceMaxPipeArgs(cl_device_id device)                         { return getDeviceUint(device,  CL_DEVICE_MAX_PIPE_ARGS,                           "Couldn't get max pipe args."); }
cl_uint getDeviceMaxReadImageArgs(cl_device_id device)                    { return getDeviceUint(device,  CL_DEVICE_MAX_READ_IMAGE_ARGS,                     "Couldn't get max read image args."); }
cl_uint getDeviceMaxReadWriteImageArgs(cl_device_id device)               { return getDeviceUint(device,  CL_DEVICE_MAX_READ_WRITE_IMAGE_ARGS,               "Couldn't get max read write image args."); }
cl_uint getDeviceMaxSamplers(cl_device_id device)                         { return getDeviceUint(device,  CL_DEVICE_MAX_SAMPLERS,                            "Couldn't get max samplers."); }
cl_uint getDeviceMaxWorkItemDimensions(cl_device_id device)               { return getDeviceUint(device,  CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,                "Couldn't get max work item dimensions."); }
cl_uint getDeviceMaxWriteImageArgs(cl_device_id device)                   { return getDeviceUint(device,  CL_DEVICE_MAX_WRITE_IMAGE_ARGS,                    "Couldn't get max write image args."); }
cl_uint getDeviceMemBaseAddrAlign(cl_device_id device)                    { return getDeviceUint(device,  CL_DEVICE_MAX_PIPE_ARGS,                           "Couldn't get mem base addr align."); }
cl_uint getDeviceNativeVectorWidthChar(cl_device_id device)               { return getDeviceUint(device,  CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR,                "Couldn't get native vector width char."); }
cl_uint getDeviceNativeVectorWidthDouble(cl_device_id device)             { return getDeviceUint(device,  CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE,              "Couldn't get native vector width double."); }
cl_uint getDeviceNativeVectorWidthFloat(cl_device_id device)              { return getDeviceUint(device,  CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT,               "Couldn't get native vector width float."); }
cl_uint getDeviceNativeVectorWidthHalf(cl_device_id device)               { return getDeviceUint(device,  CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF,                "Couldn't get native vector width half."); }
cl_uint getDeviceNativeVectorWidthInt(cl_device_id device)                { return getDeviceUint(device,  CL_DEVICE_NATIVE_VECTOR_WIDTH_INT,                 "Couldn't get native vector width int."); }
cl_uint getDeviceNativeVectorWidthLong(cl_device_id device)               { return getDeviceUint(device,  CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG,                "Couldn't get native vector width long."); }
cl_uint getDeviceNativeVectorWidthShort(cl_device_id device)              { return getDeviceUint(device,  CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT,               "Couldn't get native vector width short."); }
cl_uint getDeviceNonUniformWorkGroupSupport(cl_device_id device)          { return getDeviceUint(device,  CL_DEVICE_NON_UNIFORM_WORK_GROUP_SUPPORT,          "Couldn't get device non uniform work group support."); }
cl_uint getDevicePartitionMaxSubDevices(cl_device_id device)              { return getDeviceUint(device,  CL_DEVICE_PARTITION_MAX_SUB_DEVICES,               "Couldn't get partition max sub devices."); }
cl_uint getDevicePipeMaxActiveReservations(cl_device_id device)           { return getDeviceUint(device,  CL_DEVICE_MAX_PIPE_ARGS,                           "Couldn't get pipe max active reservations."); }
cl_uint getDevicePipeMaxPacketSize(cl_device_id device)                   { return getDeviceUint(device,  CL_DEVICE_MAX_PIPE_ARGS,                           "Couldn't get pipe max packet size."); }
cl_uint getDevicePipeSupport(cl_device_id device)                         { return getDeviceUint(device,  CL_DEVICE_PIPE_SUPPORT,                            "Couldn't get device pipe support."); }
cl_uint getDevicePreferredGlobalAtomicAlignment(cl_device_id device)      { return getDeviceUint(device,  CL_DEVICE_PREFERRED_GLOBAL_ATOMIC_ALIGNMENT,       "Couldn't get preferred global atomic alignment."); }
cl_uint getDevicePreferredInteropUserSync(cl_device_id device)            { return getDeviceUint(device,  CL_DEVICE_PREFERRED_INTEROP_USER_SYNC,             "Couldn't get device preferred interop user sync."); }
cl_uint getDevicePreferredLocalAtomicAlignment(cl_device_id device)       { return getDeviceUint(device,  CL_DEVICE_PREFERRED_LOCAL_ATOMIC_ALIGNMENT,        "Couldn't get preferred local atomic alignment."); }
cl_uint getDevicePreferredPlatformAtomicAlignment(cl_device_id device)    { return getDeviceUint(device,  CL_DEVICE_PREFERRED_PLATFORM_ATOMIC_ALIGNMENT,     "Couldn't get preferred platform atomic alignment."); }
cl_uint getDevicePreferredVectorWidthChar(cl_device_id device)            { return getDeviceUint(device,  CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR,             "Couldn't get preferred vector width char."); }
cl_uint getDevicePreferredVectorWidthDouble(cl_device_id device)          { return getDeviceUint(device,  CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE,           "Couldn't get preferred vector width double."); }
cl_uint getDevicePreferredVectorWidthFloat(cl_device_id device)           { return getDeviceUint(device,  CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT,            "Couldn't get preferred vector width float."); }
cl_uint getDevicePreferredVectorWidthHalf(cl_device_id device)            { return getDeviceUint(device,  CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF,             "Couldn't get preferred vector width half."); }
cl_uint getDevicePreferredVectorWidthInt(cl_device_id device)             { return getDeviceUint(device,  CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT,              "Couldn't get preferred vector width int."); }
cl_uint getDevicePreferredVectorWidthLong(cl_device_id device)            { return getDeviceUint(device,  CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG,             "Couldn't get preferred vector width long."); }
cl_uint getDevicePreferredVectorWidthShort(cl_device_id device)           { return getDeviceUint(device,  CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT,            "Couldn't get preferred vector width short."); }
cl_uint getDeviceQueueOnDeviceMaxSize(cl_device_id device)                { return getDeviceUint(device,  CL_DEVICE_QUEUE_ON_DEVICE_MAX_SIZE,                "Couldn't get queue on device max size."); }
cl_uint getDeviceQueueOnDevicePreferredSize(cl_device_id device)          { return getDeviceUint(device,  CL_DEVICE_QUEUE_ON_DEVICE_PREFERRED_SIZE,          "Couldn't get queue on device preferred size."); }
cl_uint getDeviceReferenceCount(cl_device_id device)                      { return getDeviceUint(device,  CL_DEVICE_REFERENCE_COUNT,                         "Couldn't get reference count."); }
cl_uint getDeviceSubGroupIndependentForwardProgress(cl_device_id device)  { return getDeviceUint(device,  CL_DEVICE_SUB_GROUP_INDEPENDENT_FORWARD_PROGRESS,  "Couldn't get device sub group independent forward progress."); }
cl_uint getDeviceVendorID(cl_device_id device)                            { return getDeviceUint(device,  CL_DEVICE_VENDOR_ID,                               "Couldn't get device vendor."); }
cl_uint getDeviceWorkGroupCollectiveFunctionsSupport(cl_device_id device) { return getDeviceUint(device,  CL_DEVICE_WORK_GROUP_COLLECTIVE_FUNCTIONS_SUPPORT, "Couldn't get device work group collective functions support."); }
size_t  getDeviceGlobalVariablePreferredTotalSize(cl_device_id device)    { return getDeviceSizeT(device, CL_DEVICE_GLOBAL_VARIABLE_PREFERRED_TOTAL_SIZE,    "Couldn't get global variable preferred total size."); }
size_t  getDeviceImage2dMaxHeight(cl_device_id device)                    { return getDeviceSizeT(device, CL_DEVICE_IMAGE2D_MAX_HEIGHT,                      "Couldn't get image2d max height."); }
size_t  getDeviceImage2dMaxWidth(cl_device_id device)                     { return getDeviceSizeT(device, CL_DEVICE_IMAGE2D_MAX_WIDTH,                       "Couldn't get image2d max width."); }
size_t  getDeviceImage3dMaxDepth(cl_device_id device)                     { return getDeviceSizeT(device, CL_DEVICE_IMAGE3D_MAX_DEPTH,                       "Couldn't get image3d max depth."); }
size_t  getDeviceImage3dMaxHeight(cl_device_id device)                    { return getDeviceSizeT(device, CL_DEVICE_IMAGE3D_MAX_HEIGHT,                      "Couldn't get image3d max height."); }
size_t  getDeviceImage3dmaxWidth(cl_device_id device)                     { return getDeviceSizeT(device, CL_DEVICE_IMAGE3D_MAX_WIDTH,                       "Couldn't get image3d max width."); }
size_t  getDeviceImageMaxArraySize(cl_device_id device)                   { return getDeviceSizeT(device, CL_DEVICE_IMAGE_MAX_ARRAY_SIZE,                    "Couldn't get image max array size."); }
size_t  getDeviceImageMaxBufferSize(cl_device_id device)                  { return getDeviceSizeT(device, CL_DEVICE_IMAGE_MAX_BUFFER_SIZE,                   "Couldn't get image max buffer size."); }
size_t  getDeviceMaxGlobalVariableSize(cl_device_id device)               { return getDeviceSizeT(device, CL_DEVICE_MAX_GLOBAL_VARIABLE_SIZE,                "Couldn't get max global variable size."); }
size_t  getDeviceMaxParameterSize(cl_device_id device)                    { return getDeviceSizeT(device, CL_DEVICE_MAX_PARAMETER_SIZE,                      "Couldn't get max parameter size."); }
size_t  getDeviceMaxWorkGroupSize(cl_device_id device)                    { return getDeviceSizeT(device, CL_DEVICE_MAX_WORK_GROUP_SIZE,                     "Couldn't get max work group size."); }
size_t  getDevicePreferredWorkGroupSizeMultiple(cl_device_id device)      { return getDeviceSizeT(device, CL_DEVICE_PREFERRED_WORK_GROUP_SIZE_MULTIPLE,      "Couldn't get preferred work group size multiple."); }
size_t  getDevicePrintfBufferSize(cl_device_id device)                    { return getDeviceSizeT(device, CL_DEVICE_PRINTF_BUFFER_SIZE,                      "Couldn't get printf buffer size."); }
size_t  getDeviceProfilingTimerResolution(cl_device_id device)            { return getDeviceSizeT(device, CL_DEVICE_PROFILING_TIMER_RESOLUTION,              "Couldn't get profiling timer resolution."); }
// char *getDeviceExtensions(cl_device_id device)                     { return getDeviceStr(device,CL_DEVICE_EXTENSIONS ,                        "Couldn't get extensions."); }
// clang-format on

// cl_ulong
// CL_DEVICE_MAX_MEM_ALLOC_SIZE
// CL_DEVICE_GLOBAL_MEM_CACHE_SIZE
// CL_DEVICE_GLOBAL_MEM_SIZE
// CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE
// CL_DEVICE_LOCAL_MEM_SIZE

// cl_version                             CL_DEVICE_NUMERIC_VERSION
// cl_command_queue_properties            CL_DEVICE_QUEUE_ON_DEVICE_PROPERTIES            CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE
// cl_command_queue_properties            CL_DEVICE_QUEUE_ON_HOST_PROPERTIES
// cl_device_affinity_domain              CL_DEVICE_PARTITION_AFFINITY_DOMAIN             CL_DEVICE_AFFINITY_DOMAIN_NUMA
// cl_device_atomic_capabilities          CL_DEVICE_ATOMIC_FENCE_CAPABILITIES             CL_DEVICE_ATOMIC_ORDER_RELAXED
// cl_device_atomic_capabilities          CL_DEVICE_ATOMIC_MEMORY_CAPABILITIES
// cl_device_device_enqueue_capabilities  CL_DEVICE_DEVICE_ENQUEUE_CAPABILITIES           CL_DEVICE_QUEUE_SUPPORTED
// cl_device_exec_capabilities            CL_DEVICE_EXECUTION_CAPABILITIES                CL_EXEC_KERNEL
// cl_device_fp_config                    CL_DEVICE_SINGLE_FP_CONFIG                      CL_FP_DENORM
// cl_device_fp_config                    CL_DEVICE_DOUBLE_FP_CONFIG
// cl_device_id                           CL_DEVICE_PARENT_DEVICE
// cl_device_local_mem_type               CL_DEVICE_LOCAL_MEM_TYPE                        CL_GLOBAL
// cl_device_mem_cache_type               CL_DEVICE_GLOBAL_MEM_CACHE_TYPE                 CL_READ_ONLY_CACHE (NOT a bit-field)
// cl_device_partition_property[]         CL_DEVICE_PARTITION_PROPERTIES                  CL_DEVICE_PARTITION_EQUALLY (NOT a bit-field)
// cl_device_partition_property[]         CL_DEVICE_PARTITION_TYPE
// cl_device_svm_capabilities             CL_DEVICE_SVM_CAPABILITIES                      CL_DEVICE_SVM_COARSE_GRAIN_BUFFER
// cl_name_version[]                      CL_DEVICE_BUILT_IN_KERNELS_WITH_VERSION         see. getPlatformExtensions
// cl_name_version[]                      CL_DEVICE_EXTENSIONS_WITH_VERSION
// cl_name_version[]                      CL_DEVICE_ILS_WITH_VERSION
// cl_name_version[]                      CL_DEVICE_OPENCL_C_ALL_VERSIONS
// cl_name_version[]                      CL_DEVICE_OPENCL_C_FEATURES
// cl_platform_id                         CL_DEVICE_PLATFORM
// size_t[]                               CL_DEVICE_MAX_WORK_ITEM_SIZES                   0, 1, 2 (max.)
