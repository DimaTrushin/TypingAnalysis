#include "CudaGate.h"

#include <cassert>

#include <QDebug>

namespace NSApplication {
namespace NSCompute {
namespace NSCudaGateDetail {

CCudaDevices::CCudaDevices() {
  initializeDevicesInfo();
}

int CCudaDevices::getDevicesCount() {
  int device_count;
  cudaError_t result = cudaGetDeviceCount(&device_count);
  if (result != cudaSuccess)
    throw std::runtime_error("");
  return device_count;
}

CCudaDevices::CCudaInfo CCudaDevices::getCudaDeviceInfo(int devID) {
  assert(devID >= 0);
  assert(devID < int(Devices_.size()));
  CCudaInfo Data;
  if (cudaDeviceGetAttribute(&Data.ComputeMode, cudaDevAttrComputeMode,
                             devID) != cudaSuccess)
    throw std::runtime_error("");

  if (cudaDeviceGetAttribute(&Data.Major, cudaDevAttrComputeCapabilityMajor,
                             devID) != cudaSuccess)
    throw std::runtime_error("");

  if (cudaDeviceGetAttribute(&Data.Minor, cudaDevAttrComputeCapabilityMinor,
                             devID) != cudaSuccess)
    throw std::runtime_error("");
  return Data;
}

void CCudaDevices::initializeDevicesInfo() {
  for (int device = 0; device < int(Devices_.size()); ++device) {
    Devices_[device] = getCudaDeviceInfo(device);
  }
}

CCudaGateImpl::CCudaGateImpl() {
  setMaxGflopsDevice();
  setCudaContext();
}

void CCudaGateImpl::gpuDeviceInit(int devID) {
  assert(devID >= 0);
  assert(devID < int(Devices_.size()));
  if (Devices_[devID].ComputeMode == cudaComputeModeProhibited)
    throw std::runtime_error("");
  if (Devices_[devID].Major < 1)
    throw std::runtime_error("");
  if (cudaSetDevice(devID) != cudaSuccess)
    throw std::runtime_error("");

  CurrentDevice_ = devID;
}

void CCudaGateImpl::setMaxGflopsDevice() {
  uint64_t max_performance = 0;
  int best_device = -1;
  for (int device = 0; device < int(Devices_.size()); ++device) {
    uint64_t performance = getPerformance(device);
    if (max_performance < performance) {
      max_performance = performance;
      best_device = device;
    }
  }
  gpuDeviceInit(best_device);
}

uint64_t CCudaGateImpl::getPerformance(int devID) {
  assert(devID >= 0);
  assert(devID < int(Devices_.size()));

  if (Devices_[devID].ComputeMode == cudaComputeModeProhibited)
    return 0;
  return getMultiProcessorCount(devID) * getSmPerMultiproc(devID) *
         getClockRate(devID);
}

uint64_t CCudaGateImpl::getClockRate(int devID) {
  assert(devID >= 0);
  assert(devID < int(Devices_.size()));

  int clockRate = 0;
  cudaError_t result =
      cudaDeviceGetAttribute(&clockRate, cudaDevAttrClockRate, devID);
  switch (result) {
  case cudaErrorInvalidValue:
    return 1;
  case cudaSuccess:
    return clockRate;
  default:
    throw std::runtime_error("");
  }
}

uint64_t CCudaGateImpl::getSmPerMultiproc(int devID) {
  assert(devID >= 0);
  assert(devID < int(Devices_.size()));

  int SmPerMultiproc = 0;
  if (Devices_[devID].Major == 9999 && Devices_[devID].Minor == 9999) {
    SmPerMultiproc = 1;
  } else {
    SmPerMultiproc =
        _ConvertSMVer2Cores(Devices_[devID].Major, Devices_[devID].Minor);
  }
  return SmPerMultiproc;
}

uint64_t CCudaGateImpl::getMultiProcessorCount(int devID) {
  assert(devID >= 0);
  assert(devID < int(Devices_.size()));

  int multiProcessorCount = 0;
  if (cudaDeviceGetAttribute(&multiProcessorCount,
                             cudaDevAttrMultiProcessorCount,
                             devID) != cudaSuccess)
    throw std::runtime_error("");
  return multiProcessorCount;
}

} // namespace NSCudaGateDetail

CCudaGate::CCudaGate() {
  try {
    Gate_ = std::make_unique<CCudaGateImpl>();
  } catch (...) {
    qDebug() << "Cuda Gate Error\n";
  }
}

bool CCudaGate::isAvailable() const {
  return Gate_.operator bool();
}

} // namespace NSCompute
} // namespace NSApplication
