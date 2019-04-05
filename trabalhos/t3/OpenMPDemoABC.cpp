/*
 *  rvales@inf.ufsm.br
 *  ELC139 - Programação Paralela - UFSM
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <sys/time.h>
#include <omp.h>

#define N_THREADS 3
#define N_TIMES 60
#define N_CHUNK 6

class SharedArray {
private:
    char* array;
    int index;
    int size;

public:
    SharedArray(int n) : size(n), index(0) {
        array = new char[size];
        std::fill(array, array+size, '-');
    }

    void addChar(char c) {
        array[index] = c;
        spendSomeTime();
        index++;
    }

    int countOccurrences(char c) {
        return std::count(array, array+size, c);
    }

    std::string toString() {
        return std::string(array, size);
    }

    ~SharedArray() {
        delete[] array;
    }

private:
    void spendSomeTime() {
        for (int i = 0; i < 10000; i++) {
            for (int j = 0; j < 100; j++) {
                // These loops shouldn't be removed by the compiler
            }
        }
    }
};

class ArrayFiller {
private:
    const int nThreads = N_THREADS;
    const int nTimes = N_TIMES;
    const int chunkSize = N_CHUNK;
    const int scheduleType;
    long start_time, end_time;
    SharedArray* array;

public:
    ArrayFiller(int threads, int times, int chunk, int type) : nThreads(threads), nTimes(times), chunkSize(chunk), scheduleType(type) {
        array = new SharedArray(nTimes);
    }

    void fillArrayConcurrently() {
        switch (scheduleType) {
            case 10: runCase1a(); break; // static sem chunk
            case 11: runCase1b(); break; // static com chunk
            case 20: runCase2a(); break; // dynamic sem chunk
            case 21: runCase2b(); break; // dynamic com chunk
            case 30: runCase3a(); break; // guided sem chunk
            case 31: runCase3b(); break; // guided com chunk
            case 40: runCase4();  break; // runtime
            case 50: runCase5();  break; // auto
            case 60: runCase6();  break; // sem mutex
        }
    }

    void printStats() {
        std::cout << array->toString() << std::endl;
        for (int i = 0; i < nThreads; ++i)
            std::cout << (char) ('A'+i) << "=" << array->countOccurrences('A'+i) << " ";
        std::cout << std::endl;
    }

    ~ArrayFiller() {
        delete array;
    }

private:
    void runCase1a() {
        start_time = wtime();
        #pragma omp parallel for schedule(static) num_threads(nThreads)
        for (int i = 0; i < nTimes; i++) {
            #pragma omp critical
            array->addChar('A'+omp_get_thread_num());
        }
        end_time = wtime();
        std::cout << "time: " << (end_time - start_time) << "usec" << std::endl;
    }

    void runCase1b() {
        start_time = wtime();
        #pragma omp parallel for schedule(static, chunkSize) num_threads(nThreads)
        for (int i = 0; i < nTimes; i++) {
            #pragma omp critical
            array->addChar('A'+omp_get_thread_num());
        }
        end_time = wtime();
        std::cout << "time: " << (end_time - start_time) << "usec" << std::endl;
    }

    void runCase2a() {
        start_time = wtime();
        #pragma omp parallel for schedule(dynamic) num_threads(nThreads)
        for (int i = 0; i < nTimes; i++) {
            #pragma omp critical
            array->addChar('A'+omp_get_thread_num());
        }
        end_time = wtime();
        std::cout << "time: " << (end_time - start_time) << "usec" << std::endl;
    }

    void runCase2b() {
        start_time = wtime();
        #pragma omp parallel for schedule(dynamic, chunkSize) num_threads(nThreads)
        for (int i = 0; i < nTimes; i++) {
            #pragma omp critical
            array->addChar('A'+omp_get_thread_num());
        }
        end_time = wtime();
        std::cout << "time: " << (end_time - start_time) << "usec" << std::endl;
    }

    void runCase3a() {
        start_time = wtime();
        #pragma omp parallel for schedule(guided) num_threads(nThreads)
        for (int i = 0; i < nTimes; i++) {
            #pragma omp critical
            array->addChar('A'+omp_get_thread_num());
        }
        end_time = wtime();
        std::cout << "time: " << (end_time - start_time) << "usec" << std::endl;
    }

    void runCase3b() {
        start_time = wtime();
        #pragma omp parallel for schedule(guided, chunkSize) num_threads(nThreads)
        for (int i = 0; i < nTimes; i++) {
            #pragma omp critical
            array->addChar('A'+omp_get_thread_num());
        }
        end_time = wtime();
        std::cout << "time: " << (end_time - start_time) << "usec" << std::endl;
    }

    void runCase4() {
        start_time = wtime();
        #pragma omp parallel for schedule(runtime) num_threads(nThreads)
        for (int i = 0; i < nTimes; i++) {
            #pragma omp critical
            array->addChar('A'+omp_get_thread_num());
        }
        end_time = wtime();
        std::cout << "time: " << (end_time - start_time) << "usec" << std::endl;
    }

    void runCase5() {
        start_time = wtime();
        #pragma omp parallel for schedule(auto) num_threads(nThreads)
        for (int i = 0; i < nTimes; i++) {
            #pragma omp critical
            array->addChar('A'+omp_get_thread_num());
        }
        end_time = wtime();
        std::cout << "time: " << (end_time - start_time) << "usec" << std::endl;
    }

    void runCase6() {
        start_time = wtime();
        #pragma omp parallel for num_threads(nThreads)
        for (int i = 0; i < nTimes; i++) {
            array->addChar('A'+omp_get_thread_num());
        }
        end_time = wtime();
        std::cout << "time: " << (end_time - start_time) << "usec" << std::endl;
    }

    long wtime() {
        struct timeval t;
        gettimeofday(&t, NULL);
        return t.tv_sec*1000000 + t.tv_usec;
    }
};

int main(int argc, char **argv) {
    int threads = N_THREADS;
    int times = N_TIMES;
    int chunk = N_CHUNK;

    if (argc == 4) {
        threads = atoi(argv[1]);
        times = atoi(argv[2]);
        chunk = atoi(argv[3]);
    }

    std::cout << "Each thread should add its char until the array fills" << std::endl;
    std::cout << threads << " thread(s), " << times << " char(s), chunksize " << chunk << std::endl;

    std::cout << std::endl << "Schedule STATIC sem chunk" << std::endl;
    ArrayFiller c1a(threads, times, chunk, 10);
    c1a.fillArrayConcurrently(); c1a.printStats();
    
    std::cout << std::endl << "Schedule STATIC com chunk" << std::endl;
    ArrayFiller c1b(threads, times, chunk, 11);
    c1b.fillArrayConcurrently(); c1b.printStats();

    std::cout << std::endl << "Schedule DYNAMIC sem chunk" << std::endl;
    ArrayFiller c2a(threads, times, chunk, 20);
    c2a.fillArrayConcurrently(); c2a.printStats();

    std::cout << std::endl << "Schedule DYNAMIC com chunk" << std::endl;
    ArrayFiller c2b(threads, times, chunk, 21);
    c2b.fillArrayConcurrently(); c2b.printStats();

    std::cout << std::endl << "Schedule GUIDED sem chunk" << std::endl;
    ArrayFiller c3a(threads, times, chunk, 30);
    c3a.fillArrayConcurrently(); c3a.printStats();

    std::cout << std::endl << "Schedule GUIDED com chunk" << std::endl;
    ArrayFiller c3b(threads, times, chunk, 31);
    c3b.fillArrayConcurrently(); c3b.printStats();

    std::cout << std::endl << "Schedule RUNTIME" << std::endl;
    ArrayFiller c4a(threads, times, chunk, 40);
    c4a.fillArrayConcurrently(); c4a.printStats();
    
    std::cout << std::endl << "Schedule AUTO" << std::endl;
    ArrayFiller c5a(threads, times, chunk, 50);
    c5a.fillArrayConcurrently(); c5a.printStats();

    std::cout << std::endl << "Sem exclusao mutua 1" << std::endl;
    ArrayFiller c6a(threads, times, chunk, 60);
    c6a.fillArrayConcurrently(); c6a.printStats();

    std::cout << std::endl << "Sem exclusao mutua 2" << std::endl;
    ArrayFiller c6b(threads, times, chunk, 60);
    c6b.fillArrayConcurrently(); c6b.printStats();
}
