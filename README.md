# SHA-256 Rainbow Table Generator

Small tool to create rainbow tables from a txt file in C.

## Project Structure
- `main.c`: Handles file I/O and the user interface.
- `sha256/`: Contains the core cryptographic implementation.
- `Makefile`: Automates the build and local installation process.

## Prerequisites
- A C compiler (like `gcc`)
- `make` build utility

## Installation

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/thegesse/SHA-practice.git](https://github.com/thegesse/SHA-practice.git)
   cd SHA-practice
2. **Build and install locally**
    ```bash
    make
   make install
3. **Add to Path**
   ```bash
   echo 'export PATH="$PATH:$HOME/.local/bin"' >> ~/.bashrc
   source ~/.bashrc

## Usage
Once installed and added to your PATH, you can generate a table from any password list simply by calling the tool:
```bash
rbgen "password file name".txt "rainbow table file name".txt
