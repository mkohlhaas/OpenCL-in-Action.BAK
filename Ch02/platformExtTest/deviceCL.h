#include <CL/cl.h>
#include <glib.h>

// char *getDeviceExtensions(cl_device_id device);
// size_t getMaxWorkItemSizes(cl_device_id device);

typedef struct property {
  gboolean enabled;
  char *property;
} property;

// clang-format off
GArray                  *getDeviceAffinityDomain(cl_device_id device);
GArray                  *getDeviceAtomicMemoryCapabilities(cl_device_id device);
GArray                  *getDeviceAtomicFenceCapabilities(cl_device_id device);
GArray                  *getDeviceDoubleFPConfig(cl_device_id device);
GArray                  *getDeviceEnqueueCapabilities(cl_device_id device);
GArray                  *getDeviceExecCapabilities(cl_device_id device);
GArray                  *getDeviceLocalMemType(cl_device_id device);
GArray                  *getDeviceMemCacheType(cl_device_id device);
GArray                  *getDeviceSingleFPConfig(cl_device_id device);
GArray                  *getDeviceSVMCapabilities(cl_device_id device);
GArray                  *getDeviceQueueOnDeviceProperties(cl_device_id device);
GArray                  *getDeviceQueueOnHostProperties(cl_device_id device);
GArray                  *getDeviceTypes(cl_device_id device);
// char                    *getDeviceBuiltInKernels(cl_device_id device);
char                    *getDeviceDriverVersion(cl_device_id device);
char                    *getDeviceIlVersion(cl_device_id device);
char                    *getDeviceLatestConformanceVersionPassed(cl_device_id device);
char                    *getDeviceName(cl_device_id device);
char                    *getDeviceProfile(cl_device_id device);
char                    *getDeviceVendor(cl_device_id device);
char                    *getDeviceVersion(cl_device_id device);
cl_device_id             getDeviceParentId(cl_device_id device);
cl_platform_id           getDevicePlatform(cl_device_id device);
cl_uint                  getDeviceAddressBits(cl_device_id device);
cl_uint                  getDeviceAvailable(cl_device_id device);
cl_uint                  getDeviceCompilerAvailable(cl_device_id device);
cl_uint                  getDeviceEndianLittle(cl_device_id device);
cl_uint                  getDeviceErrorCorrectionSupport(cl_device_id device);
cl_uint                  getDeviceGenericAddressSpaceSupport(cl_device_id device);
cl_uint                  getDeviceGlobalMemCachelineSize(cl_device_id device);
cl_uint                  getDeviceImageBaseAddressAlignment(cl_device_id device);
cl_uint                  getDeviceImagePitchAlignment(cl_device_id device);
cl_uint                  getDeviceImageSupport(cl_device_id device);
cl_uint                  getDeviceLinkerAvailable(cl_device_id device);
cl_uint                  getDeviceMaxClockFrequency(cl_device_id device);
cl_uint                  getDeviceMaxComputeUnits(cl_device_id device);
cl_uint                  getDeviceMaxConstantArgs(cl_device_id device);
cl_uint                  getDeviceMaxNumSubGroups(cl_device_id device);
cl_uint                  getDeviceMaxOnDeviceEvents(cl_device_id device);
cl_uint                  getDeviceMaxOnDeviceQueues(cl_device_id device);
cl_uint                  getDeviceMaxPipeArgs(cl_device_id device);
cl_uint                  getDeviceMaxReadImageArgs(cl_device_id device);
cl_uint                  getDeviceMaxReadWriteImageArgs(cl_device_id device);
cl_uint                  getDeviceMaxSamplers(cl_device_id device);
cl_uint                  getDeviceMaxWorkItemDimensions(cl_device_id device);
cl_uint                  getDeviceMaxWriteImageArgs(cl_device_id device);
cl_uint                  getDeviceMemBaseAddrAlign(cl_device_id device);
cl_uint                  getDeviceNativeVectorWidthChar(cl_device_id device);
cl_uint                  getDeviceNativeVectorWidthDouble(cl_device_id device);
cl_uint                  getDeviceNativeVectorWidthFloat(cl_device_id device);
cl_uint                  getDeviceNativeVectorWidthHalf(cl_device_id device);
cl_uint                  getDeviceNativeVectorWidthInt(cl_device_id device);
cl_uint                  getDeviceNativeVectorWidthLong(cl_device_id device);
cl_uint                  getDeviceNativeVectorWidthShort(cl_device_id device);
cl_uint                  getDeviceNonUniformWorkGroupSupport(cl_device_id device);
cl_uint                  getDeviceNumericVersion(cl_device_id device);
cl_uint                  getDevicePartitionMaxSubDevices(cl_device_id device);
cl_uint                  getDevicePipeMaxActiveReservations(cl_device_id device);
cl_uint                  getDevicePipeMaxPacketSize(cl_device_id device);
cl_uint                  getDevicePipeSupport(cl_device_id device);
cl_uint                  getDevicePreferredGlobalAtomicAlignment(cl_device_id device);
cl_uint                  getDevicePreferredInteropUserSync(cl_device_id device);
cl_uint                  getDevicePreferredLocalAtomicAlignment(cl_device_id device);
cl_uint                  getDevicePreferredPlatformAtomicAlignment(cl_device_id device);
cl_uint                  getDevicePreferredVectorWidthChar(cl_device_id device);
cl_uint                  getDevicePreferredVectorWidthDouble(cl_device_id device);
cl_uint                  getDevicePreferredVectorWidthFloat(cl_device_id device);
cl_uint                  getDevicePreferredVectorWidthHalf(cl_device_id device);
cl_uint                  getDevicePreferredVectorWidthInt(cl_device_id device);
cl_uint                  getDevicePreferredVectorWidthLong(cl_device_id device);
cl_uint                  getDevicePreferredVectorWidthShort(cl_device_id device);
cl_uint                  getDeviceQueueOnDeviceMaxSize(cl_device_id device);
cl_uint                  getDeviceQueueOnDevicePreferredSize(cl_device_id device);
cl_uint                  getDeviceReferenceCount(cl_device_id device);
cl_uint                  getDeviceSubGroupIndependentForwardProgress(cl_device_id device);
cl_uint                  getDeviceVendorID(cl_device_id device);
cl_uint                  getDeviceWorkGroupCollectiveFunctionsSupport(cl_device_id device);
size_t                   getDeviceGlobalVariablePreferredTotalSize(cl_device_id device);
size_t                   getDeviceImage2dMaxHeight(cl_device_id device);
size_t                   getDeviceImage2dMaxWidth(cl_device_id device);
size_t                   getDeviceImage3dMaxDepth(cl_device_id device);
size_t                   getDeviceImage3dMaxHeight(cl_device_id device);
size_t                   getDeviceImage3dmaxWidth(cl_device_id device);
size_t                   getDeviceImageMaxArraySize(cl_device_id device);
size_t                   getDeviceImageMaxBufferSize(cl_device_id device);
size_t                   getDeviceMaxGlobalVariableSize(cl_device_id device);
size_t                   getDeviceMaxParameterSize(cl_device_id device);
size_t                   getDeviceMaxWorkGroupSize(cl_device_id device);
size_t                   getDevicePreferredWorkGroupSizeMultiple(cl_device_id device);
size_t                   getDevicePrintfBufferSize(cl_device_id device);
size_t                   getDeviceProfilingTimerResolution(cl_device_id device);
cl_ulong                 getDeviceMaxMemAllocSize(cl_device_id device);
cl_ulong                 getDeviceGlobalMemCacheSize(cl_device_id device);
cl_ulong                 getDeviceGlobalMemSize(cl_device_id device);
cl_ulong                 getDeviceMaxConstantBufferSize(cl_device_id device);
cl_ulong                 getDeviceLocalMemSize(cl_device_id device);
