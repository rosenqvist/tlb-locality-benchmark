#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

/**
 * Runs a sequential vs. random access test for a given data size.
 */
static void run_test(size_t data_size_mb)
{
    size_t num_elements = (data_size_mb * 1024 * 1024) / sizeof(int);

    size_t index_size_mb = (num_elements * sizeof(uint32_t)) / (1024 * 1024);
    size_t total_mem_mb = data_size_mb + index_size_mb;

    std::cout << "--- Testing Size: " << data_size_mb << " MB ---" << std::endl;
    std::cout << "Data: " << data_size_mb << " MB, Indices: " << index_size_mb
              << " MB, Total: " << total_mem_mb << " MB\n";

    std::vector<int> data(num_elements);
    std::vector<uint32_t> random_indices(num_elements);

    for (size_t i = 0; i < num_elements; ++i)
    {
        data[i] = i;
    }
    std::iota(random_indices.begin(), random_indices.end(), 0);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(random_indices.begin(), random_indices.end(), g);

    volatile long long sum = 0;

    auto start_seq = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < num_elements; ++i)
    {
        sum += data[i];
    }

    auto end_seq = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_seq = end_seq - start_seq;

    sum = 0;
    auto start_rand = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < num_elements; ++i)
    {
        sum += data[random_indices[i]];
    }

    auto end_rand = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_rand = end_rand - start_rand;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Sequential: " << duration_seq.count() << " s\n";
    std::cout << "Random:     " << duration_rand.count() << " s\n";
    std::cout << "Slowdown:   "
              << (duration_rand.count() / duration_seq.count()) << "x\n"
              << std::endl;
}

int main()
{
    std::vector<size_t> test_sizes_mb = {32, 64, 96, 112, 128, 144, 160, 256};

    for (size_t size : test_sizes_mb)
    {
        run_test(size);
    }

    return 0;
}