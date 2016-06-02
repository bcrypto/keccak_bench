/*
*******************************************************************************
\file bash-bench.c
\brief Benchmarks for keccak
\project keccak-bench
\author (C) Semenov Vlad [semenov.vlad.by@gmail.com]
\created 2016.06.02
\version 2016.06.02
\license This program is released under the GNU General Public License 
version 3. See Copyright Notices in bee2/info.h.
*******************************************************************************
*/

#include <stdio.h>
#include <bee2/core/prng.h>
#include <bee2/core/tm.h>
#include <bee2/core/util.h>

/*
Reference keccak implementation could be found at:
https://github.com/gvanas/KeccakCodePackage/SnP/KeccakP-1600/
*/
#include "KeccakP-1600-SnP.h"

/*
*******************************************************************************
Замер производительности
*******************************************************************************
*/


/*
The purpose of this benchmark is to run 
bash and keccak comparison tests in the same environment. 
*/
bool_t keccakBench0()
{
	// keccak state is 7 __m256i's, extra 64 octets are added for alignment
	octet keccak_state[7*256/8 + 64];
	intptr_t keccak_state_aligned = (((intptr_t) keccak_state) + 31) & ~((intptr_t)31);
	size_t data_block_lanes; // number of lanes processed at each iteration depending on level
	size_t data_size; // size of processed data, is multiple of hash block size

	// the main code is copy-pasted from bashBench0
	octet combo_state[256];
	octet buf[1024+64];
	octet hash[64];
	// заполнить buf псевдослучайными числами
	ASSERT(prngCOMBO_keep() <= sizeof(combo_state));
	prngCOMBOStart(combo_state, utilNonce32());
	prngCOMBOStepG(buf, sizeof(buf), combo_state);

	KeccakP1600_StaticInitialize();
	// оценить скорость хэширования
	{
		const size_t reps = 2000;
		size_t i;
		tm_ticks_t ticks;
		// эксперимент c keccak1600_256
		KeccakP1600_Initialize((void *) keccak_state_aligned);
		data_block_lanes = 17;
		data_size = sizeof(buf) / (data_block_lanes * 8) * (data_block_lanes * 8);
		for (i = 0, ticks = tmTicks(); i < reps; ++i)
			KeccakF1600_FastLoop_Absorb(
			        (void *)keccak_state_aligned, data_block_lanes, buf, data_size);
		KeccakP1600_ExtractBytes((void *)keccak_state_aligned, hash, 0, 256/8);
		ticks = tmTicks() - ticks;
		printf("keccak1600_256:   %3u cycles / byte [%5u kBytes / sec]\n",
			(unsigned)(ticks / data_size / reps),
			(unsigned)tmSpeed(reps * data_size / 1024, ticks));
		// эксперимент c keccak1600_384
		KeccakP1600_Initialize((void *) keccak_state_aligned);
		data_block_lanes = 13;
		data_size = sizeof(buf) / (data_block_lanes * 8) * (data_block_lanes * 8);
		for (i = 0, ticks = tmTicks(); i < reps; ++i)
			KeccakF1600_FastLoop_Absorb(
			        (void *)keccak_state_aligned, data_block_lanes, buf, data_size);
		KeccakP1600_ExtractBytes((void *)keccak_state_aligned, hash, 0, 384/8);
		ticks = tmTicks() - ticks;
		printf("keccak1600_384:   %3u cycles / byte [%5u kBytes / sec]\n",
			(unsigned)(ticks / data_size / reps),
			(unsigned)tmSpeed(reps * data_size / 1024, ticks));
		// эксперимент c keccak1600_512
		KeccakP1600_Initialize((void *) keccak_state_aligned);
		data_block_lanes = 9;
		data_size = sizeof(buf) / (data_block_lanes * 8) * (data_block_lanes * 8);
		for (i = 0, ticks = tmTicks(); i < reps; ++i)
			KeccakF1600_FastLoop_Absorb(
			        (void *)keccak_state_aligned, data_block_lanes, buf, data_size);
		KeccakP1600_ExtractBytes((void *)keccak_state_aligned, hash, 0, 512/8);
		ticks = tmTicks() - ticks;
		printf("keccak1600_512:   %3u cycles / byte [%5u kBytes / sec]\n",
			(unsigned)(ticks / data_size / reps),
			(unsigned)tmSpeed(reps * data_size / 1024, ticks));
	}
	// все нормально
	return TRUE;
}

bool_t keccakBench()
{
    bool_t ok;
    ok = keccakBench0();
    return ok;
}
