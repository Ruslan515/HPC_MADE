#include <omp.h>
#include <iostream>
#include <vector>

static constexpr size_t N = 1<<10;

void initVec(std::vector<float>* a) {
    for ( size_t i = 0; i < N; ++i) {
        (*a)[i] = (float)i;
    }
}

int main() {
    std::vector<float> a;
    a.resize(N);
    initVec(&a);

    // for(size_t i = 0; i < N; ++i) {
    //     std::cout << a[i] << "\t";
    // }
    // std::cout << "\n";

    float sum = 0.0;
     
    #pragma omp parallel default(none) shared(N, a) reduction(+:sum)
    {
        #pragma omp single nowait
        printf("i'm %d from %d\n", omp_get_thread_num(), omp_get_num_threads());

        #pragma omp for
        for(size_t i = 0; i < N; ++i) {
            sum = sum + a[i];
        }

    }

    std::cout << sum << "\n";

    return 0;
}