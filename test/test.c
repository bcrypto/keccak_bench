/*
*******************************************************************************
\file test.c
\brief Keccak benchmarking
\project keccak-bench
\author (C) Semenov Vlad [semenov.vlad.by@gmail.com]
\created 2016.06.02
\version 2016.06.02
\license This program is released under the GNU General Public License
version 3. See Copyright Notices in bee2/info.h.
*******************************************************************************
*/

#include <stdio.h>
#include <bee2/defs.h>

extern bool_t keccakBench();

int testCrypto()
{
	bool_t code;
	int ret = 0;
	code = keccakBench(),	ret |= !code;
	return ret;
}

/*
*******************************************************************************
main
*******************************************************************************
*/

int main()
{
	int ret = 0;
	ret |= testCrypto();
	return ret;
}

