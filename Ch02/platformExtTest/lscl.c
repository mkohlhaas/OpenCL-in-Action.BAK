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

    // Devices
    cl_uint numDevices;
    cl_device_id *devices = getDeviceIDs(platforms[i], &numDevices);
    json_object *Devices = json_object_new_array();
    for (int i = 0; i < numDevices; i++) {
      json_object *Device = json_object_new_object();

      // Types
      json_object *Types = json_object_new_array();
      GArray *deviceTypes = getDeviceTypes(devices[i]);
      for (int i = 0; i < deviceTypes->len; i++) {
        json_object_array_add(Types, json_object_new_string(g_array_index(deviceTypes, char *, i)));
      }
      json_object_object_add(Device, "types", Types);

      // Vendor ID
      cl_uint vendorID = getDeviceVendorID(devices[i]);
      json_object_object_add(Device, "vendor_id", json_object_new_uint64(vendorID));

      // Max Compute Units
      cl_uint maxComputeUnits = getDeviceMaxComputeUnits(devices[i]);
      json_object_object_add(Device, "max_compute_units", json_object_new_uint64(maxComputeUnits));

      // Max Work Item Dimensions
      cl_uint maxWorkItemDimensions = getDeviceMaxComputeUnits(devices[i]);
      json_object_object_add(Device, "max_work_item_dimensions", json_object_new_uint64(maxWorkItemDimensions));

      // Preferred Vector Width Char
      cl_uint preferredVectorWidthChar = getPreferredVectorWidthChar(devices[i]);
      json_object_object_add(Device, "preferred_vector_width_char", json_object_new_uint64(preferredVectorWidthChar));

      // Preferred Vector Width Short
      cl_uint preferredVectorWidthShort = getPreferredVectorWidthChar(devices[i]);
      json_object_object_add(Device, "preferred_vector_width_short", json_object_new_uint64(preferredVectorWidthShort));

      // Preferred Vector Width Int
      cl_uint preferredVectorWidthInt = getPreferredVectorWidthChar(devices[i]);
      json_object_object_add(Device, "preferred_vector_width_int", json_object_new_uint64(preferredVectorWidthInt));

      // Preferred Vector Width Long
      cl_uint preferredVectorWidthLong = getPreferredVectorWidthChar(devices[i]);
      json_object_object_add(Device, "preferred_vector_width_long", json_object_new_uint64(preferredVectorWidthLong));

      // Preferred Vector Width Float
      cl_uint preferredVectorWidthFloat = getPreferredVectorWidthChar(devices[i]);
      json_object_object_add(Device, "preferred_vector_width_float", json_object_new_uint64(preferredVectorWidthFloat));

      // Preferred Vector Width Double
      cl_uint preferredVectorWidthDouble = getPreferredVectorWidthChar(devices[i]);
      json_object_object_add(Device, "preferred_vector_width_double", json_object_new_uint64(preferredVectorWidthDouble));

      // Native Vector Width Char
      cl_uint nativeVectorWidthChar = getNativeVectorWidthChar(devices[i]);
      json_object_object_add(Device, "native_vector_width_char", json_object_new_uint64(preferredVectorWidthChar));

      // Native Vector Width Short
      cl_uint nativeVectorWidthShort = getNativeVectorWidthShort(devices[i]);
      json_object_object_add(Device, "native_vector_width_short", json_object_new_uint64(nativeVectorWidthShort));

      // Native Vector Width Int
      cl_uint nativeVectorWidthInt = getNativeVectorWidthInt(devices[i]);
      json_object_object_add(Device, "native_vector_width_int", json_object_new_uint64(nativeVectorWidthInt));

      // Native Vector Width Long
      cl_uint nativeVectorWidthLong = getNativeVectorWidthLong(devices[i]);
      json_object_object_add(Device, "native_vector_width_long", json_object_new_uint64(nativeVectorWidthLong));

      // Native Vector Width Float
      cl_uint nativeVectorWidthFloat = getNativeVectorWidthFloat(devices[i]);
      json_object_object_add(Device, "native_vector_width_float", json_object_new_uint64(nativeVectorWidthFloat));

      // Native Vector Width Double
      cl_uint nativeVectorWidthDouble = getNativeVectorWidthDouble(devices[i]);
      json_object_object_add(Device, "native_vector_width_double", json_object_new_uint64(nativeVectorWidthDouble));

      // Native Vector Width Half
      cl_uint nativeVectorWidthHalf = getNativeVectorWidthHalf(devices[i]);
      json_object_object_add(Device, "native_vector_width_half", json_object_new_uint64(nativeVectorWidthHalf));

      // Max Clock Frequency
      cl_uint maxClockFrequency = getMaxClockFrequency(devices[i]);
      json_object_object_add(Device, "max_clock_frequency", json_object_new_uint64(maxClockFrequency));

      // Address Bits
      cl_uint addressBits = getAddressBits(devices[i]);
      json_object_object_add(Device, "address_bits", json_object_new_uint64(addressBits));

      // Max Read Image Args
      cl_uint maxReadImageArgs = getMaxReadImageArgs(devices[i]);
      json_object_object_add(Device, "max_read_image_args", json_object_new_uint64(maxReadImageArgs));

      // Max Write Image Args
      cl_uint maxWriteImageArgs = getMaxWriteImageArgs(devices[i]);
      json_object_object_add(Device, "max_write_image_args", json_object_new_uint64(maxWriteImageArgs));

      // Max Read Write Image Args
      cl_uint maxReadWriteImageArgs = getMaxReadWriteImageArgs(devices[i]);
      json_object_object_add(Device, "max_read_write_image_args", json_object_new_uint64(maxReadWriteImageArgs));

      // Max Samplers
      cl_uint maxSamplers = getMaxSamplers(devices[i]);
      json_object_object_add(Device, "max_samplers", json_object_new_uint64(maxSamplers));

      // Image Pitch Alignment
      cl_uint imagePitchAlignment = getImagePitchAlignment(devices[i]);
      json_object_object_add(Device, "image_pitch_alignment", json_object_new_uint64(imagePitchAlignment));

      // Image Base Address Alignment
      cl_uint imageBaseAddressAlignment = getImageBaseAddressAlignment(devices[i]);
      json_object_object_add(Device, "image_base_address_alignment", json_object_new_uint64(imageBaseAddressAlignment));

      // Max Pipe Args
      cl_uint maxPipeArgs = getMaxPipeArgs(devices[i]);
      json_object_object_add(Device, "max_pipe_args", json_object_new_uint64(maxPipeArgs));

      // Pipe Max Active Reservations
      cl_uint pipeMaxActiveReservations = getPipeMaxActiveReservations(devices[i]);
      json_object_object_add(Device, "pipe_max_active_reservations", json_object_new_uint64(pipeMaxActiveReservations));

      // PipeMaxPacketSize
      cl_uint pipeMaxPacketSize = getPipeMaxPacketSize(devices[i]);
      json_object_object_add(Device, "pipe_max_packet_size ", json_object_new_uint64(pipeMaxPacketSize));

      // Mem Base AddrA lign
      cl_uint memBaseAddrAlign = getMemBaseAddrAlign(devices[i]);
      json_object_object_add(Device, "mem_base_addr_align ", json_object_new_uint64(memBaseAddrAlign));

      // Global Mem Cacheline Size
      cl_uint globalMemCachelineSize = getGlobalMemCachelineSize(devices[i]);
      json_object_object_add(Device, "global_mem_cacheline_size", json_object_new_uint64(globalMemCachelineSize));

      // Max Constant Args
      cl_uint maxConstantArgs = getMaxConstantArgs(devices[i]);
      json_object_object_add(Device, "max_constant_args", json_object_new_uint64(maxConstantArgs));

      // Queue On Device Preferred Size
      cl_uint queueOnDevicePreferredSize = getQueueOnDevicePreferredSize(devices[i]);
      json_object_object_add(Device, "queue_on_device_preferred_size", json_object_new_uint64(queueOnDevicePreferredSize));

      // Queue On Device MaxSize
      cl_uint queueOnDeviceMaxSize = getQueueOnDeviceMaxSize(devices[i]);
      json_object_object_add(Device, "queue_on_device_max_size", json_object_new_uint64(queueOnDeviceMaxSize));

      // Max On Device Queues
      cl_uint maxOnDeviceQueues = getMaxOnDeviceQueues(devices[i]);
      json_object_object_add(Device, "max_on_device_queues", json_object_new_uint64(maxOnDeviceQueues));

      // Max On Device Events
      cl_uint maxOnDeviceEvents = getMaxOnDeviceEvents(devices[i]);
      json_object_object_add(Device, "max_on_device_events", json_object_new_uint64(maxOnDeviceEvents));

      // Partition Max SubDevices
      cl_uint partitionMaxSubDevices = getPartitionMaxSubDevices(devices[i]);
      json_object_object_add(Device, "partition_max_sub_devices", json_object_new_uint64(partitionMaxSubDevices));

      // Reference Count
      cl_uint referenceCount = getReferenceCount(devices[i]);
      json_object_object_add(Device, "reference_count", json_object_new_uint64(referenceCount));

      // Preferred Platform Atomic Alignment
      cl_uint preferredPlatformAtomicAlignment = getPreferredPlatformAtomicAlignment(devices[i]);
      json_object_object_add(Device, "preferred_platform_atomic_alignment", json_object_new_uint64(preferredPlatformAtomicAlignment));

      // Preferred Global Atomic Alignment
      cl_uint preferredGlobalAtomicAlignment = getPreferredGlobalAtomicAlignment(devices[i]);
      json_object_object_add(Device, "preferred_global_atomic_alignment", json_object_new_uint64(preferredGlobalAtomicAlignment));

      // Preferred Local Atomic Alignment
      cl_uint preferredLocalAtomicAlignment = getPreferredLocalAtomicAlignment(devices[i]);
      json_object_object_add(Device, "preferred_local_atomic_alignment", json_object_new_uint64(preferredLocalAtomicAlignment));

      // Max Num Sub Groups
      cl_uint maxNumSubGroups = getMaxNumSubGroups(devices[i]);
      json_object_object_add(Device, "max_num_sub_groups", json_object_new_uint64(maxNumSubGroups));

      json_object_array_add(Devices, Device);
    }
    json_object_object_add(Platform, "devices", Devices);
  }
  printf("%s\n", json_object_to_json_string_ext(Root, JSON_C_TO_STRING_PRETTY));
}
