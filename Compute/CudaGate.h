#ifndef NSAPPLICATION_NSCOMPUTE_CCUDAGATE_H
#define NSAPPLICATION_NSCOMPUTE_CCUDAGATE_H

#include <cuda_runtime.h>
#include <helper_cuda.h>
#include <thrust/device_vector.h>

#include <stdint.h>
#include <vector>

namespace NSApplication {
namespace NSCompute {

namespace NSCudaGateDetail {

// TO DO
// Would be ideal to preinitialize Cuda Context using the driver api
class CCudaDevices {
  struct CCudaInfo {
    int ComputeMode = -1;
    int Major = 0;
    int Minor = 0;
  };
  using CDevicesInfoContainer = std::vector<CCudaInfo>;

public:
  CCudaDevices();

protected:
  static int getDevicesCount();
  CCudaInfo getCudaDeviceInfo(int devID);
  void initializeDevicesInfo();

  CDevicesInfoContainer Devices_ = CDevicesInfoContainer(getDevicesCount());
};

class CCudaGateImpl : protected CCudaDevices {
public:
  CCudaGateImpl();

protected:
  void gpuDeviceInit(int devID);
  void setMaxGflopsDevice();
  uint64_t getPerformance(int devID);
  uint64_t getClockRate(int devID);
  uint64_t getSmPerMultiproc(int devID);
  uint64_t getMultiProcessorCount(int devID);

  void setCudaContext();

  static constexpr const int kErrorID = -1;

  int CurrentDevice_ = kErrorID;

  thrust::device_vector<double> X_;
  thrust::device_vector<double> Y_;
};
} // namespace NSCudaGateDetail

class CCudaGate {
  using CCudaGateImpl = NSCudaGateDetail::CCudaGateImpl;
  using CUptr = std::unique_ptr<CCudaGateImpl>;

public:
  CCudaGate();

  bool isAvailable() const;

private:
  CUptr Gate_;
};

} // namespace NSCompute
} // namespace NSApplication

#endif // NSAPPLICATION_NSCOMPUTE_CCUDAGATE_H
