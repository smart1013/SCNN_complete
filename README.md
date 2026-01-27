# SCNN Cycle-Accurate Simulator 🚀

A high-fidelity, cycle-accurate simulator for **Sparse Convolutional Neural Network (SCNN)** hardware accelerators. This project models the architectural behavior of an SCNN chip, specifically designed to exploit sparsity in both activations and weights to maximize performance and energy efficiency.

## 📖 Overview

Standard CNN accelerators often waste cycles performing multiplications with zero values. **SCNN** optimizes this by processing only non-zero elements using a Cartesian Product-based computation approach.

This simulator provides a detailed look at the hardware pipeline, tracking:
- **Cycle counts** for convolution operations.
- **Processing Element (PE)** utilization.
- **Sparsity benefits** (skipping zero-valued computations).
- **Buffer & Bandwidth** usage.

## ✨ Key Features

- **Cycle-Accurate Timing**: Simulates the exact number of cycles required for the Dispatcher, Multiplier Array, and Accumulator stages.
- **Sparsity Awareness**: Automatically detects and skips zero values in Input Activations (IA) and Filter Weights (FW), modeling the compressed format processing of real SCNN hardware.
- **Configurable Hardware**: easy-to-tweak parameters for PE count, multiplier array size, and buffer depths via `common.h`.
- **Spatial Tiling**: Implements intelligent data mapping, distributing input tiles across a grid of Processing Elements (e.g., 64 PEs).

## 📂 Project Structure

```text
scnn_complete/
├── top.cc                 # Main entry point: drives the simulation loop and collects stats
├── verify_top.cc          # Verification suite for cycle-accurate correctness
├── Makefile               # Build configuration
├── README.md              # Project documentation
├── include/               # Header files
│   ├── accumulator.h      # Accumulator class definition
│   ├── buffer_queue.h     # BufferQueue class for storing partial sums
│   ├── common.h           # Global Hardware & Layer configuration parameters
│   ├── convlayer.h        # ConvLayer class for managing IA/FW/OA tensors
│   ├── dispatcher.h       # Dispatcher class for instruction/data feed
│   ├── loader.h           # Loader class for data compression and tiling
│   ├── mult_array.h       # MultArray class for PE multiplier grid
│   └── tensor.h           # Tensor class definition (3D/4D support)
└── src/                   # Implementation files
    ├── accumulator.cc     # Logic for accumulating partial sums into final output
    ├── buffer_queue.cc    # Implementation of partial sum queue management
    ├── convlayer.cc       # Initialization and management of layer tensors
    ├── dispatcher.cc      # Logic for fetching and dispatching vectors
    ├── loader.cc          # Handles sparsity compression, tiling, and PE mapping
    ├── mult_array.cc      # Simulates the Cartesian Product multiplier array
    └── tensor.cc          # Tensor operations (addressing, value retrieval)
```

## 🛠️ Getting Started

### Prerequisites
- GCC/G++ Compiler (C++17 or later recommended)
- Make

### Build and Run

1.  **Compile the simulator:**
    ```bash
    make
    ```

2.  **Run the simulation:**
    ```bash
    ./top
    ```

3.  **Clean build artifacts:**
    ```bash
    make clean
    ```

## ⚙️ Configuration

You can customize the hardware architecture and target neural network layer by editing **`include/common.h`**.

### Hardware Config
| Parameter | Default | Description |
|-----------|---------|-------------|
| `NUM_PE` | 64 | Number of Processing Elements in the mesh |
| `NUM_MULTIPLIERS` | 16 | Multipliers per PE |
| `IA_VECTOR_SIZE` | 4 | Input Activation vector width |
| `W_VECTOR_SIZE` | 4 | Weight vector width |

### Layer Config
| Parameter | Default | Description |
|-----------|---------|-------------|
| `C` | 48 | Input Channels |
| `H, W` | 7, 7 | Input Height & Width |
| `K` | 128 | Number of Filters (Output Channels) |
| `IA_SPARSITY` | 0.55 | % of zeros in generated Input Activations |
| `FW_SPARSITY` | 0.65 | % of zeros in generated Weights |

## 🏗️ Architecture Pipeline

The simulator models the following pipeline stages within each PE:

1.  **Loader**: Compresses raw data into non-zero buffers and tiles it across PEs.
2.  **Dispatcher**: Fetches vectors of compressed weights and inputs.
3.  **Multiplier Array**: Performs Cartesian products on the vectors.
4.  **Buffer Queue**: Temporarily holds partial sums.
5.  **Accumulator**: Reduces partial sums into final Output Activations (OA).

---
*Created for advanced research into sparse deep learning accelerators.*
