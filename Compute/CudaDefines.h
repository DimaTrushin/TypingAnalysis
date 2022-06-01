#ifndef CUDADEFINES_H
#define CUDADEFINES_H

#ifndef DISABLE_CUDA
#define DEVICE_FUNCTION __device__
#else
#define DEVICE_FUNCTION
#endif

#endif // CUDADEFINES_H
