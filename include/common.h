#ifndef SCNN_COMMON_H_
#define SCNN_COMMON_H_

#include <iomanip>
#include <deque>
#include <vector>
#include <tuple>
#include <string>
#include <set>
#include <map>
#include <random>   
#include <assert.h>
#include <tuple>
#include <fstream>
#include <iostream>
#include <utility>


namespace Scnn {
    using namespace std;

// Hardware Configuration
struct HardwareConfig{
    static const int NUM_PE = 64;
    static const int NUM_MULTIPLIERS = 16;
    static const int IA_VECTOR_SIZE = 4;
    static const int W_VECTOR_SIZE = 4;
    static const int OUTPUT_PORT = 16;
    static const int FILTERS_PER_GROUP = 32;
    static const int BUFFER_QUEUE_DEPTH = 4;
    static const int NUM_BANKS = 32;
};

// Layer (CNN) Configuration
struct LayerConfig {
    static const int C = 48;
    static const int H = 7;
    static const int W = 7;
    static const int S = 5;
    static const int R = 5;
    static const int K = 128;

    static const int STRIDE = 1;
    static const int DILATION = 1;
    static const int PADDING = 2;

    static constexpr float IA_MIN_VAL = 0.0;
    static constexpr float IA_MAX_VAL = 1.0;
    static constexpr float IA_SPARSITY = 0.55;

    static constexpr float FW_MIN_VAL = 0.0;
    static constexpr float FW_MAX_VAL = 1.0;
    static constexpr float FW_SPARSITY = 0.65;
};

}

#endif