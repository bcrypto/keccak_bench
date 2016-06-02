if(WITH_AVX2)
#include_directories(../KeccakCodePackage/Common/)
include_directories(../KeccakCodePackage/SnP/KeccakP-1600/OptimizedAVX2/)
add_executable(keccakbench-avx2
	../KeccakCodePackage/SnP/KeccakP-1600/OptimizedAVX2/KeccakP-1600-AVX2.cpp
	crypto/keccak-bench.c
	test.c
)
target_link_libraries(keccakbench-avx2 bee2_static)

else(WITH_AVX2)
include_directories(../KeccakCodePackage/Common/)
include_directories(../KeccakCodePackage/SnP/)
include_directories(../KeccakCodePackage/SnP/KeccakP-1600/Optimized/)
include_directories(../KeccakCodePackage/SnP/KeccakP-1600/Optimized64/)
include_directories(../KeccakCodePackage/SnP/KeccakP-1600/Optimized64/ufull/)
add_executable(keccakbench-opt64
	../KeccakCodePackage/SnP/KeccakP-1600/Optimized64/KeccakP-1600-opt64.c
	crypto/keccak-bench.c
	test.c
)
target_link_libraries(keccakbench-opt64 bee2_static)

endif(WITH_AVX2)

