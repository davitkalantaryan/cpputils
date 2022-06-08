//
// file:			0010_endian_h.cpp
// created on:		2022 Feb 28
//

#include "gtest/gtest.h"
#include <cpputils/endian.h>

#define CPPUTILS_INIT_VAL	1

TEST(f_0010_endian_h, t0001_b16)
{
	uint16_t valBe = htobe16(CPPUTILS_INIT_VAL);
	uint16_t valLe = htole16(CPPUTILS_INIT_VAL);

	ASSERT_TRUE((valBe== CPPUTILS_INIT_VAL)!=(valLe== CPPUTILS_INIT_VAL));

	uint16_t rcVal = be16toh(valBe);
	ASSERT_EQ(rcVal, uint16_t(CPPUTILS_INIT_VAL));

	rcVal = le16toh(valLe);
	ASSERT_EQ(rcVal, uint16_t(CPPUTILS_INIT_VAL));
}


TEST(f_0010_endian_h, t0002_b32)
{
	uint32_t valBe = htobe32(CPPUTILS_INIT_VAL);
	uint32_t valLe = htole32(CPPUTILS_INIT_VAL);

	ASSERT_TRUE((valBe == CPPUTILS_INIT_VAL) != (valLe == CPPUTILS_INIT_VAL));

	uint32_t rcVal = be32toh(valBe);
	ASSERT_EQ(rcVal, uint32_t(CPPUTILS_INIT_VAL));

	rcVal = le32toh(valLe);
	ASSERT_EQ(rcVal, uint32_t(CPPUTILS_INIT_VAL));
}


TEST(f_0010_endian_h, t0003_b64)
{
	uint64_t valBe = htobe64(CPPUTILS_INIT_VAL);
	uint64_t valLe = htole64(CPPUTILS_INIT_VAL);

	ASSERT_TRUE((valBe == CPPUTILS_INIT_VAL) != (valLe == CPPUTILS_INIT_VAL));

	uint64_t rcVal = be64toh(valBe);
	ASSERT_EQ(rcVal, uint64_t(CPPUTILS_INIT_VAL));

	rcVal = le64toh(valLe);
	ASSERT_EQ(rcVal, uint64_t(CPPUTILS_INIT_VAL));
}
