# PacketSequenceHandler
C++ utility designed to process incoming binary data packets that may arrive out of order

## Overview
PacketSequenceHandler is a C++ utility designed to process incoming binary data packets that may arrive out of order. It extracts payloads from these packets and writes them to a binary file in the correct sequence, excluding the initial 12-byte header of each packet.

## Features
Handles out-of-order binary data packets.
Extracts and reorders payloads based on sequence numbers.
Writes ordered payloads to a binary file.

## Input Format
data: A constant character pointer (const char* data) representing the binary data.
size: An integer (int size) indicating the size of the binary data, including a 12-byte header.

## How It Works
The function write(const char* data, int size) processes the input data.
Extracts the sequence number from the header (located at offset 2 in the 12-byte header).
Reorders the payload data based on the sequence numbers.
Writes the ordered payloads to an output binary file, excluding the 12-byte headers.

## Usage
### To use this utility, you need to:

Clone the repository:

```
git clone https://github.com/lsuc/PacketSequenceHandler.git
cd PacketSequenceHandler
TODO WIP need to add library, to be able to include the PacketSequenceHandler library in your C++ project. 
```

Call the write function with the appropriate data and size parameters.

```
#include "PacketSequenceHandler.h"

//Example usage of the write function:

const char* data = /* binary data with 12-byte headers */;
int size = /* size of the binary data including headers */;

PacketSequenceHandler handler("filePath.bin");
handler.write(data, size);
```

## Requirements

### Linux
- C++ compiler installed (e.g., g++, clang++)
- CMake installed (for building the project)

### Windows
- C++ compiler installed, such as MSVC (Microsoft Visual C++).
- CMake installed and added to your PATH
- Windows-specific networking functions (e.g., ntohs) are provided by the Winsock2 library.


## Installation

### Linux
Build the project using CMake:

```
cd /path/to/PacketSequenceHandler
mkdir build
cd build
cmake ..
make
```

### Windows
Build the project using CMake:
```
cd \path\to\PacketSequenceHandler
mkdir build
cd build
cmake ..
cmake --build .
```
