## wsr

A command-line tool to read WAVE files.

Supports most documented chunks, as well as RIFX and RF64.

Not supported: Sony Wave64, Dolby ADM, XML chunks. However, any unsupported chunk will still be outputted as a Generic with their identifier and size.

For example:
```
Chunk identifier: minf 
Size: 18
```
