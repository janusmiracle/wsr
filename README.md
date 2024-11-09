## wsr

A command-line tool to read WAVE files.

## Installation

Clone the repository and run `install.sh` to install the command globally.

If that doesn't work, run `$ chmod +x install.sh` then try again.

```
$ git clone https://github.com/janusmiracle/wsr.git 
$ ./install.sh
```

## Usage 

Call the command with the path leading to the WAVE file.

```
$ wsr ~/Downloads/testfile.wav
```

Supports most documented chunks, as well as RIFX.

Any unsupported chunk will still be outputted as a Generic with their identifier and size.

For example:
```
Chunk identifier: minf 
Size: 18
```
