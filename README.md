# C++ Data Locality Benchmark

This is a simple C++ benchmark attempt, trying to demonstrate the massive performance impact of data locality. The code attempts to compare sequential vs. random memory access patterns to measure the "performance cliff" caused by **TLB (Translation Lookaside Buffer) misses** and **L3 cache misses** by outpacing the prefetcher. This is just a simple benchmark with a single run per size.

## Benchmark Results (AMD Ryzen 9 9950X3D)

These results were run on an **AMD Ryzen 9 9950X3D**, which features a **128 MB L3 cache**. The tests measure the time to access arrays of various sizes, starting from a size that fits _inside_ the L3 cache (64 MB total) to one that exceeds it (512 MB total).

| Data Size | Index Size | Total Memory | Sequential Time | Random Time | Slowdown Factor |
| :--- | :--- | :--- | :--- | :--- | :--- |
| 32 MB | 32 MB | **64 MB** | 0.018710 s | 0.186372 s | **9.96x** |
| 64 MB | 64 MB | **128 MB** | 0.036706 s | 0.367378 s | **10.00x** |
| 96 MB | 96 MB | **192 MB** | 0.058060 s | 0.450665 s | **7.76x** |
| 112 MB | 112 MB | **224 MB** | 0.066678 s | 0.565334 s | **8.47x** |
| 128 MB | 128 MB | **256 MB** | 0.095894 s | 0.697046 s | **7.26x** |
| 144 MB | 144 MB | **288 MB** | 0.087107 s | 0.814619 s | **9.35x** |
| 160 MB | 160 MB | **320 MB** | 0.096325 s | 0.937948 s | **9.73x** |
| 256 MB | 256 MB | **512 MB** | 0.156317 s | 1.733915 s | **11.09x** |


## Further Reading & Research

* [Wikipedia: Translation Lookaside Buffer](https://en.wikipedia.org/wiki/Translation_lookaside_buffer)
* [Wikipedia: CPU Cache](https://en.wikipedia.org/wiki/CPU_cache)
* [GeeksforGeeks: Translation Lookaside Buffer (TLB) in Paging](https://www.geeksforgeeks.org/operating-systems/translation-lookaside-buffer-tlb-in-paging/)
* [OSTEP (Chapter 19): Virtual Memory - TLBs (.pdf)](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-tlbs.pdf)
* [UCR CS153 Slides: Cache Performance (.pdf)](https://www.cs.ucr.edu/~csong/cs153/19f/l/cache.pdf)
* [Reddit: Data Locality (or how I made a benchmark 50x faster)](https://www.reddit.com/r/programming/comments/1sgry7/data_locality_or_how_i_made_a_benchmark_50x/)

