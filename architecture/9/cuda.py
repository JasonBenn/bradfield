from copperhead import *
import numpy as np

@cu
def saxpy(a, x, y):
  return [a * xi + yi for xi, yi in zip(x, y)]

x = np.arange(2**20, dtype=np.float32)
y = np.arange(2**20, dtype=np.float32)

with places.gpu0:
  gpu_result = saxpy(2.0, x, y)
  print gpu_result

with places.openmp:
  cpu_result = saxpy(2.0, x, y)
  print cpu_result
