/**
* Copyright: Copyright (c) 2018 angeltears-hyj, All right reserved.
* 
* @Functional description:
* @Author : angeltears-onter
* @Date : 18-11-4.
* @package : dataCompression
*/

#include <cstdio>
#define BOOST_TEST_MODULE bitTest
#include <boost/test/included/unit_test.hpp>
using namespace boost;
#include "bit.h"

BOOST_AUTO_TEST_SUITE(bitTest)

    BOOST_AUTO_TEST_CASE(littleEnding)
    {
        union node
        {
            int num;
            char ch;
        } p;
        p.num = 0x12345678;
        BOOST_CHECK_EQUAL(p.ch, 0x78);
    }
    BOOST_AUTO_TEST_CASE(bitGet)
    {
        unsigned char c = 130;  // 0x12
        BOOST_CHECK_EQUAL(1, bit_get(&c, 0));
        BOOST_CHECK_EQUAL(1, bit_get(&c, 6));
        unsigned char s[2];   //0x1001
        s[0] = 128;
        s[1] = 1;
        BOOST_CHECK_EQUAL(1, bit_get(s, 0));
        BOOST_CHECK_EQUAL(1, bit_get(s, 15));
    }
    BOOST_AUTO_TEST_CASE(bitSet)
    {
        unsigned char c = 0;
        bit_set(&c, 1, 1);  // 0100 0000 64
        BOOST_CHECK_EQUAL(64, c);
        unsigned char s[2];
        memset(s, 0, sizeof s);
        bit_set(s, 15, 1);
        BOOST_CHECK_EQUAL(1, s[1]);
    }
    BOOST_AUTO_TEST_CASE(bitXor)
    {
        unsigned char s1[2];
        s1[0] = 128;  // 1000 0000
        s1[1] = 16;   //  0001 0000
        unsigned char s2[2];
        s2[0] = 1;    // 0000 0001
        s2[1] = 16;   // 0001 0000
        unsigned char s[2];
        memset(s, 0, sizeof s);
        bit_xor(s1, s2, s, sizeof s * 8);
        // 1000 0001 0000 0000
        BOOST_CHECK_EQUAL(129, s[0]);
        BOOST_CHECK_EQUAL(0, s[1]);
    }
    BOOST_AUTO_TEST_CASE(bitRotLeft)
    {
        unsigned char s[2];
        s[0] = 0;
        s[1] = 255;
        bit_rot_left(s, sizeof s * 8, 4); // 0000 1111 1111 0000
        BOOST_CHECK_EQUAL(s[0], 15);
        BOOST_CHECK_EQUAL(s[1], 240);
        bit_rot_left(s, sizeof s * 8, 8+4);
        BOOST_CHECK_EQUAL(s[0], 0);
        BOOST_CHECK_EQUAL(s[1], 255);
    }
BOOST_AUTO_TEST_SUITE_END()