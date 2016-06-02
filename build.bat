@echo off

call :opt64
call :avx2
goto :eof

:opt64
mkdir build-opt64
pushd build-opt64

cmake -G"NMake Makefiles" -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_COMPILER_IS_MSVC=1 -DBEE2_INCLUDE="../../bee2/include" -DBEE2_LIBS="../.." ..
nmake
test\keccakbench-opt64

popd
goto :eof

:avx2
mkdir build-avx2
pushd build-avx2

cmake -G"NMake Makefiles" -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_COMPILER_IS_MSVC=1 -DBEE2_INCLUDE="../../bee2/include" -DBEE2_LIBS="../.." -DWITH_AVX2=ON ..
nmake
test\keccakbench-avx2

popd
goto :eof
