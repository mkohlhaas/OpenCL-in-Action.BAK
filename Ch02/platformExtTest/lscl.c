#include "device.h"
#include "json_object.h"
#include "platform.h"
#include "version.h"
#include <stdio.h>

int main(void) {

  // set up OpenCL
  cl_uint numPlatforms;
  cl_platform_id *platforms = getPlatforms(&numPlatforms);

  json_object *Root = json_object_new_object();
  json_object *Platforms = json_object_new_array();
  json_object_object_add(Root, "platforms", Platforms);

  // Platforms
  for (int i = 0; i < numPlatforms; i++) {
    json_object *Platform = json_object_new_object();
    json_object_array_add(Platforms, Platform);

    // Name
    char *platformName = getPlatformName(platforms[i]);
    json_object_object_add(Platform, "name", json_object_new_string(platformName));

    // Profile
    char *platformProfile = getPlatformProfile(platforms[i]);
    json_object_object_add(Platform, "profile", json_object_new_string(platformProfile));

    // Vendor
    char *platformVendor = getPlatformVendor(platforms[i]);
    json_object_object_add(Platform, "vendor", json_object_new_string(platformVendor));

    // Version
    char *platformVersion = getPlatformVersion(platforms[i]);
    json_object_object_add(Platform, "version", json_object_new_string(platformVersion));

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
      json_object_object_add(Extension, "version", json_object_new_string(versionStr(extensions[i].version)));
      json_object_array_add(Extensions, Extension);
    }
    json_object_object_add(Platform, "extensions", Extensions);

    // Devices
    cl_uint numDevices;
    cl_device_id *devices = getDeviceIDs(platforms[i], &numDevices);
    json_object *Devices = json_object_new_array();
    for (int i = 0; i < numDevices; i++) {
      json_object *Device = json_object_new_object();

      // Name
      char *name = getDeviceName(devices[i]);
      json_object_object_add(Device, "name", json_object_new_string(name));

      // Vendor
      char *vendor = getDeviceVendor(devices[i]);
      json_object_object_add(Device, "vendor", json_object_new_string(vendor));

      // Version
      char *version = getDeviceVersion(devices[i]);
      json_object_object_add(Device, "version", json_object_new_string(version));

      // Driver Version
      char *driverVersion = getDeviceDriverVersion(devices[i]);
      json_object_object_add(Device, "driver_version", json_object_new_string(driverVersion));

      // Profile
      char *profile = getDeviceProfile(devices[i]);
      json_object_object_add(Device, "profile", json_object_new_string(profile));

      // Extensions
      // json_object *Extensions = json_object_new_array();
      // char *extensions = getDeviceExtensions(devices[i]);
      // char **vecExtensions = g_strsplit(extensions, " ", 0);
      // for (char **ext = vecExtensions; *ext; ext++) {
      //   json_object_array_add(Extensions, json_object_new_string(*ext));
      // }
      // json_object_object_add(Device, "extensions", Extensions);

      // Types
      json_object *Types = json_object_new_array();
      GArray *deviceTypes = getDeviceTypes(devices[i]);
      for (int i = 0; i < deviceTypes->len; i++) {
        json_object_array_add(Types, json_object_new_string(g_array_index(deviceTypes, char *, i)));
      }
      json_object_object_add(Device, "types", Types);

      // Address Bits
      cl_uint addressBits = getDeviceAddressBits(devices[i]);
      json_object_object_add(Device, "address_bits", json_object_new_uint64(addressBits));

      // Available
      cl_uint available = getDeviceAvailable(devices[i]);
      json_object_object_add(Device, "available", json_object_new_boolean(available));

      // Built-In Kernels
      char *builtInKernels = getDeviceBuiltInKernels(devices[i]);
      json_object_object_add(Device, "built_in_kernels", json_object_new_string(builtInKernels));

      // Compiler Available
      cl_uint compilerAvailable = getDeviceCompilerAvailable(devices[i]);
      json_object_object_add(Device, "compiler_available", json_object_new_boolean(compilerAvailable));

      // Endian Little
      cl_uint endianLittle = getDeviceEndianLittle(devices[i]);
      json_object_object_add(Device, "endian_little", json_object_new_boolean(endianLittle));

      // Error Correction Support
      cl_uint errorCorrectionSupport = getDeviceErrorCorrectionSupport(devices[i]);
      json_object_object_add(Device, "error_correction_support", json_object_new_boolean(errorCorrectionSupport));

      // Generic Address Space Support
      cl_uint genericAddressSpaceSupport = getDeviceGenericAddressSpaceSupport(devices[i]);
      json_object_object_add(Device, "generic_address_space_support", json_object_new_boolean(genericAddressSpaceSupport));

      // Global Mem Cacheline Size
      cl_uint globalMemCachelineSize = getDeviceGlobalMemCachelineSize(devices[i]);
      json_object_object_add(Device, "global_mem_cacheline_size", json_object_new_uint64(globalMemCachelineSize));

      // Global Variable Preferred Total Size
      size_t globalVariablePreferredTotalSize = getDeviceGlobalVariablePreferredTotalSize(devices[i]);
      json_object_object_add(Device, "global_variable_preferred_total_size", json_object_new_uint64(globalVariablePreferredTotalSize));

      // Il Version
      char *ilVersion = getDeviceIlVersion(devices[i]);
      json_object_object_add(Device, "il_version", json_object_new_string(ilVersion));

      // Image Base Address Alignment
      cl_uint imageBaseAddressAlignment = getDeviceImageBaseAddressAlignment(devices[i]);
      json_object_object_add(Device, "image_base_address_alignment", json_object_new_uint64(imageBaseAddressAlignment));

      // Image Max Array Size
      size_t imageMaxArraySize = getDeviceImageMaxArraySize(devices[i]);
      json_object_object_add(Device, "image_max_array_size", json_object_new_uint64(imageMaxArraySize));

      // Image Max Buffer Size
      size_t imageMaxBufferSize = getDeviceImageMaxBufferSize(devices[i]);
      json_object_object_add(Device, "image_max_buffer_size", json_object_new_uint64(imageMaxBufferSize));

      // Image Pitch Alignment
      cl_uint imagePitchAlignment = getDeviceImagePitchAlignment(devices[i]);
      json_object_object_add(Device, "image_pitch_alignment", json_object_new_uint64(imagePitchAlignment));

      // Image Support
      cl_uint imageSupport = getDeviceImageSupport(devices[i]);
      json_object_object_add(Device, "image_support", json_object_new_boolean(imageSupport));

      // Image2d Max Height
      size_t image2dMaxHeight = getDeviceImage2dMaxHeight(devices[i]);
      json_object_object_add(Device, "image2d_max_height", json_object_new_uint64(image2dMaxHeight));

      // Image2d Max Width
      size_t image2dMaxWidth = getDeviceImage2dMaxWidth(devices[i]);
      json_object_object_add(Device, "image2d_max_width", json_object_new_uint64(image2dMaxWidth));

      // Image3d Max Depth
      size_t image3dMaxDepth = getDeviceImage3dMaxDepth(devices[i]);
      json_object_object_add(Device, "image3d_max_depth", json_object_new_uint64(image3dMaxDepth));

      // Image3d Max Height
      size_t image3dMaxHeight = getDeviceImage3dMaxHeight(devices[i]);
      json_object_object_add(Device, "image3d_max_height", json_object_new_uint64(image3dMaxHeight));

      // Image3d max Width
      size_t image3dmaxWidth = getDeviceImage3dmaxWidth(devices[i]);
      json_object_object_add(Device, "image3d_max_width", json_object_new_uint64(image3dmaxWidth));

      // Latest Conformance Version Passed
      char *latestConformanceVersionPassed = getDeviceLatestConformanceVersionPassed(devices[i]);
      json_object_object_add(Device, "latest_conformance_version_passed", json_object_new_string(latestConformanceVersionPassed));

      // Linker Available
      cl_uint linkerAvailable = getDeviceLinkerAvailable(devices[i]);
      json_object_object_add(Device, "linker_available", json_object_new_boolean(linkerAvailable));

      // Max Compute Units
      cl_uint maxComputeUnits = getDeviceMaxComputeUnits(devices[i]);
      json_object_object_add(Device, "max_compute_units", json_object_new_uint64(maxComputeUnits));

      // Max Constant Args
      cl_uint maxConstantArgs = getDeviceMaxConstantArgs(devices[i]);
      json_object_object_add(Device, "max_constant_args", json_object_new_uint64(maxConstantArgs));

      // Max Clock Frequency
      cl_uint maxClockFrequency = getDeviceMaxClockFrequency(devices[i]);
      json_object_object_add(Device, "max_clock_frequency", json_object_new_uint64(maxClockFrequency));

      // Max Global Variable Size
      size_t maxGlobalVariableSize = getDeviceMaxGlobalVariableSize(devices[i]);
      json_object_object_add(Device, "max_global_variable_size", json_object_new_uint64(maxGlobalVariableSize));

      // Max Num Sub Groups
      cl_uint maxNumSubGroups = getDeviceMaxNumSubGroups(devices[i]);
      json_object_object_add(Device, "max_num_sub_groups", json_object_new_uint64(maxNumSubGroups));

      // Max On Device Events
      cl_uint maxOnDeviceEvents = getDeviceMaxOnDeviceEvents(devices[i]);
      json_object_object_add(Device, "max_on_device_events", json_object_new_uint64(maxOnDeviceEvents));

      // Max On Device Queues
      cl_uint maxOnDeviceQueues = getDeviceMaxOnDeviceQueues(devices[i]);
      json_object_object_add(Device, "max_on_device_queues", json_object_new_uint64(maxOnDeviceQueues));

      // Max Parameter Size
      size_t maxParameterSize = getDeviceMaxParameterSize(devices[i]);
      json_object_object_add(Device, "max_parameter_size", json_object_new_uint64(maxParameterSize));

      // Max Pipe Args
      cl_uint maxPipeArgs = getDeviceMaxPipeArgs(devices[i]);
      json_object_object_add(Device, "max_pipe_args", json_object_new_uint64(maxPipeArgs));

      // Max Read Image Args
      cl_uint maxReadImageArgs = getDeviceMaxReadImageArgs(devices[i]);
      json_object_object_add(Device, "max_read_image_args", json_object_new_uint64(maxReadImageArgs));

      // Max Read Write Image Args
      cl_uint maxReadWriteImageArgs = getDeviceMaxReadWriteImageArgs(devices[i]);
      json_object_object_add(Device, "max_read_write_image_args", json_object_new_uint64(maxReadWriteImageArgs));

      // Max Samplers
      cl_uint maxSamplers = getDeviceMaxSamplers(devices[i]);
      json_object_object_add(Device, "max_samplers", json_object_new_uint64(maxSamplers));

      // Max Work Item Dimensions
      cl_uint maxWorkItemDimensions = getDeviceMaxComputeUnits(devices[i]);
      json_object_object_add(Device, "max_work_item_dimensions", json_object_new_uint64(maxWorkItemDimensions));

      // Max Work Item Sizes
      // size_t maxWorkItemSizes = getMaxWorkItemSizes(devices[i]);
      // json_object_object_add(Device, "max_work_item_sizes", json_object_new_uint64(maxWorkItemSizes));

      // Max Work Group Size
      size_t maxWorkGroupSize = getDeviceMaxWorkGroupSize(devices[i]);
      json_object_object_add(Device, "max_work_group_size", json_object_new_uint64(maxWorkGroupSize));

      // Max Write Image Args
      cl_uint maxWriteImageArgs = getDeviceMaxWriteImageArgs(devices[i]);
      json_object_object_add(Device, "max_write_image_args", json_object_new_uint64(maxWriteImageArgs));

      // Mem Base AddrA lign
      cl_uint memBaseAddrAlign = getDeviceMemBaseAddrAlign(devices[i]);
      json_object_object_add(Device, "mem_base_addr_align ", json_object_new_uint64(memBaseAddrAlign));

      // Native Vector Width Char
      cl_uint nativeVectorWidthChar = getDeviceNativeVectorWidthChar(devices[i]);
      json_object_object_add(Device, "native_vector_width_char", json_object_new_uint64(nativeVectorWidthChar));

      // Native Vector Width Double
      cl_uint nativeVectorWidthDouble = getDeviceNativeVectorWidthDouble(devices[i]);
      json_object_object_add(Device, "native_vector_width_double", json_object_new_uint64(nativeVectorWidthDouble));

      // Native Vector Width Float
      cl_uint nativeVectorWidthFloat = getDeviceNativeVectorWidthFloat(devices[i]);
      json_object_object_add(Device, "native_vector_width_float", json_object_new_uint64(nativeVectorWidthFloat));

      // Native Vector Width Half
      cl_uint nativeVectorWidthHalf = getDeviceNativeVectorWidthHalf(devices[i]);
      json_object_object_add(Device, "native_vector_width_half", json_object_new_uint64(nativeVectorWidthHalf));

      // Native Vector Width Int
      cl_uint nativeVectorWidthInt = getDeviceNativeVectorWidthInt(devices[i]);
      json_object_object_add(Device, "native_vector_width_int", json_object_new_uint64(nativeVectorWidthInt));

      // Native Vector Width Long
      cl_uint nativeVectorWidthLong = getDeviceNativeVectorWidthLong(devices[i]);
      json_object_object_add(Device, "native_vector_width_long", json_object_new_uint64(nativeVectorWidthLong));

      // Native Vector Width Short
      cl_uint nativeVectorWidthShort = getDeviceNativeVectorWidthShort(devices[i]);
      json_object_object_add(Device, "native_vector_width_short", json_object_new_uint64(nativeVectorWidthShort));

      // Non Uniform Work Group Support
      cl_uint nonUniformWorkGroupSupport = getDeviceNonUniformWorkGroupSupport(devices[i]);
      json_object_object_add(Device, "non_uniform_work_group_support", json_object_new_boolean(nonUniformWorkGroupSupport));

      // Partition Max SubDevices
      cl_uint partitionMaxSubDevices = getDevicePartitionMaxSubDevices(devices[i]);
      json_object_object_add(Device, "partition_max_sub_devices", json_object_new_uint64(partitionMaxSubDevices));

      // Pipe Max Active Reservations
      cl_uint pipeMaxActiveReservations = getDevicePipeMaxActiveReservations(devices[i]);
      json_object_object_add(Device, "pipe_max_active_reservations", json_object_new_uint64(pipeMaxActiveReservations));

      // Pipe Max Packet Size
      cl_uint pipeMaxPacketSize = getDevicePipeMaxPacketSize(devices[i]);
      json_object_object_add(Device, "pipe_max_packet_size ", json_object_new_uint64(pipeMaxPacketSize));

      // Pipe Support
      cl_uint pipeSupport = getDevicePipeSupport(devices[i]);
      json_object_object_add(Device, "pipe_support", json_object_new_boolean(pipeSupport));

      // Preferred Global Atomic Alignment
      cl_uint preferredGlobalAtomicAlignment = getDevicePreferredGlobalAtomicAlignment(devices[i]);
      json_object_object_add(Device, "preferred_global_atomic_alignment", json_object_new_uint64(preferredGlobalAtomicAlignment));

      // Preferred Interop User Sync
      cl_uint preferredInteropUserSync = getDevicePreferredInteropUserSync(devices[i]);
      json_object_object_add(Device, "preferred_interop_user_sync", json_object_new_boolean(preferredInteropUserSync));

      // Preferred Local Atomic Alignment
      cl_uint preferredLocalAtomicAlignment = getDevicePreferredLocalAtomicAlignment(devices[i]);
      json_object_object_add(Device, "preferred_local_atomic_alignment", json_object_new_uint64(preferredLocalAtomicAlignment));

      // Preferred Platform Atomic Alignment
      cl_uint preferredPlatformAtomicAlignment = getDevicePreferredPlatformAtomicAlignment(devices[i]);
      json_object_object_add(Device, "preferred_platform_atomic_alignment", json_object_new_uint64(preferredPlatformAtomicAlignment));

      // Preferred Vector Width Char
      cl_uint preferredVectorWidthChar = getDevicePreferredVectorWidthChar(devices[i]);
      json_object_object_add(Device, "preferred_vector_width_char", json_object_new_uint64(preferredVectorWidthChar));

      // Preferred Vector Width Double
      cl_uint preferredVectorWidthDouble = getDevicePreferredVectorWidthChar(devices[i]);
      json_object_object_add(Device, "preferred_vector_width_double", json_object_new_uint64(preferredVectorWidthDouble));

      // Preferred Vector Width Float
      cl_uint preferredVectorWidthFloat = getDevicePreferredVectorWidthChar(devices[i]);
      json_object_object_add(Device, "preferred_vector_width_float", json_object_new_uint64(preferredVectorWidthFloat));

      // Preferred Vector Width Half
      cl_uint preferredVectorWidthHalf = getDevicePreferredVectorWidthHalf(devices[i]);
      json_object_object_add(Device, "preferred_vector_width_half", json_object_new_uint64(preferredVectorWidthHalf));

      // Preferred Vector Width Int
      cl_uint preferredVectorWidthInt = getDevicePreferredVectorWidthChar(devices[i]);
      json_object_object_add(Device, "preferred_vector_width_int", json_object_new_uint64(preferredVectorWidthInt));

      // Preferred Vector Width Long
      cl_uint preferredVectorWidthLong = getDevicePreferredVectorWidthChar(devices[i]);
      json_object_object_add(Device, "preferred_vector_width_long", json_object_new_uint64(preferredVectorWidthLong));

      // Preferred Vector Width Short
      cl_uint preferredVectorWidthShort = getDevicePreferredVectorWidthChar(devices[i]);
      json_object_object_add(Device, "preferred_vector_width_short", json_object_new_uint64(preferredVectorWidthShort));

      // Preferred Work Group Size Multiple
      size_t preferredWorkGroupSizeMultiple = getDevicePreferredWorkGroupSizeMultiple(devices[i]);
      json_object_object_add(Device, "preferred_work_group_size_multiple", json_object_new_uint64(preferredWorkGroupSizeMultiple));

      // Printf Buffer Size
      size_t printfBufferSize = getDevicePrintfBufferSize(devices[i]);
      json_object_object_add(Device, "printf_buffer_size", json_object_new_uint64(printfBufferSize));

      // Profiling Timer Resolution
      size_t profilingTimerResolution = getDeviceProfilingTimerResolution(devices[i]);
      json_object_object_add(Device, "profiling_timer_resolution", json_object_new_uint64(profilingTimerResolution));

      // Queue On Device MaxSize
      cl_uint queueOnDeviceMaxSize = getDeviceQueueOnDeviceMaxSize(devices[i]);
      json_object_object_add(Device, "queue_on_device_max_size", json_object_new_uint64(queueOnDeviceMaxSize));

      // Queue On Device Preferred Size
      cl_uint queueOnDevicePreferredSize = getDeviceQueueOnDevicePreferredSize(devices[i]);
      json_object_object_add(Device, "queue_on_device_preferred_size", json_object_new_uint64(queueOnDevicePreferredSize));

      // Reference Count
      cl_uint referenceCount = getDeviceReferenceCount(devices[i]);
      json_object_object_add(Device, "reference_count", json_object_new_uint64(referenceCount));

      // Sub Group Independent Forward Progress
      cl_uint subGroupIndependentForwardProgress = getDeviceSubGroupIndependentForwardProgress(devices[i]);
      json_object_object_add(Device, "sub_group_independent_forward_progress", json_object_new_boolean(subGroupIndependentForwardProgress));

      // Vendor ID
      cl_uint vendorID = getDeviceVendorID(devices[i]);
      json_object_object_add(Device, "vendor_id", json_object_new_uint64(vendorID));

      // Work Group Collective Functions Support
      cl_uint workGroupCollectiveFunctionsSupport = getDeviceWorkGroupCollectiveFunctionsSupport(devices[i]);
      json_object_object_add(Device, "work_group_collective_functions_support", json_object_new_boolean(workGroupCollectiveFunctionsSupport));

      json_object_array_add(Devices, Device);
    }
    json_object_object_add(Platform, "devices", Devices);
  }
  printf("%s\n", json_object_to_json_string_ext(Root, JSON_C_TO_STRING_PRETTY));
}
