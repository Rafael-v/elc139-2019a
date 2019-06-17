/*
Adapted from fractal code for CS 4380 / CS 5351

Copyright (c) 2018, Texas State University. All rights reserved.

Redistribution and usage in source and binary form, with or without
modification, is only permitted for educational use.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Author: Martin Burtscher
Revision history:
20190610   andreainfufsm   Replaced the function to calculate the color of each pixel
20190615   rafael-v        Added CUDA to compute each frame on a different thread
*/

#include <stdio.h>
#include <cstdlib>
#include <sys/time.h>
#include <math.h>

__global__ void computeFrame(unsigned char* pic, int frames, int width) {

  int idx = threadIdx.x;
  int stride = blockDim.x;
  for (int frame = idx; frame < frames; frame += stride) {
    for (int row = 0; row < width; row++) {
      for (int col = 0; col < width; col++) {
        float fx = col - 1024/2;
        float fy = row - 1024/2;
        float d = sqrtf( fx * fx + fy * fy );
        unsigned char color = (unsigned char) (160.0f + 127.0f *
                                              cos(d/10.0f - frame/7.0f) /
                                              (d/50.0f + 1.0f));

        pic[frame * width * width + row * width + col] = (unsigned char) color;
      }
    }
  }
}

int main(int argc, char *argv[]) {

  // check cuda device
  int devCount;
  cudaGetDeviceCount(&devCount);
  if (devCount < 1) {fprintf(stderr, "error: there are no cuda devices\n"); exit(-1);}

  // check command line
  if (argc != 3) {fprintf(stderr, "usage: %s frame_width num_frames\n", argv[0]); exit(-1);}
  int width = atoi(argv[1]);
  if (width < 100) {fprintf(stderr, "error: frame_width must be at least 100\n"); exit(-1);}
  int frames = atoi(argv[2]);
  if (frames < 1) {fprintf(stderr, "error: num_frames must be at least 1\n"); exit(-1);}
  printf("computing %d frames of %d by %d picture\n", frames, width, width);

  // allocate picture array
  unsigned char* pic;
  cudaMallocManaged(&pic, frames * width * width * sizeof(unsigned char));

  // get the maximum number of threads per block supported by the cuda device
  cudaDeviceProp devProp;
  cudaGetDeviceProperties(&devProp, 0);
  int maxThreadsPerBlock = devProp.maxThreadsPerBlock;

  // start time
  timeval start, end;
  gettimeofday(&start, NULL);
  
  // run kernel on the GPU using the number of threads equal to the number of frames, or the maximum supported
  int numThreads = (frames > maxThreadsPerBlock) ? maxThreadsPerBlock : frames;
  computeFrame<<<1, numThreads>>>(pic, frames, width);

  // wait for GPU to finish before accessing on host
  cudaDeviceSynchronize();

  // end time
  gettimeofday(&end, NULL);
  double runtime = end.tv_sec + end.tv_usec / 1000000.0 - start.tv_sec - start.tv_usec / 1000000.0;
  printf("compute time: %.4f s\n", runtime);

  // free memory
  cudaFree(pic);

  return 0;
}
