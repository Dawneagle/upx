/* bele_policy.h -- access memory in BigEndian and LittleEndian byte order

   This file is part of the UPX executable compressor.

   Copyright (C) 1996-2023 Markus Franz Xaver Johannes Oberhumer
   Copyright (C) 1996-2023 Laszlo Molnar
   All Rights Reserved.

   UPX and the UCL library are free software; you can redistribute them
   and/or modify them under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.
   If not, write to the Free Software Foundation, Inc.,
   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

   Markus F.X.J. Oberhumer              Laszlo Molnar
   <markus@oberhumer.com>               <ezerotven+github@gmail.com>
 */

// this is an internal include file private to bele.h

/*************************************************************************
//
**************************************************************************/

#if defined(BELE_CTP)
// CTP - Compile-Time Polymorphism (templates)
#define V static inline
#define S static int __acc_cdecl_qsort
#define C noexcept
#elif defined(BELE_RTP)
// RTP - Run-Time Polymorphism (virtual functions)
#define V virtual
#define S virtual int
#define C const noexcept
#else
#error
#endif

#if defined(BELE_RTP)
struct AbstractPolicy {
    inline AbstractPolicy() noexcept {}
    virtual inline ~AbstractPolicy() noexcept {}
    V bool isBE() C = 0;
    V bool isLE() C = 0;

    V unsigned get16(const void *p) C = 0;
    V unsigned get24(const void *p) C = 0;
    V unsigned get32(const void *p) C = 0;
    V upx_uint64_t get64(const void *p) C = 0;

    V void set16(void *p, unsigned v) C = 0;
    V void set24(void *p, unsigned v) C = 0;
    V void set32(void *p, unsigned v) C = 0;
    V void set64(void *p, upx_uint64_t v) C = 0;

    V int get16_signed(const void *p) C = 0;
    V int get24_signed(const void *p) C = 0;
    V int get32_signed(const void *p) C = 0;
    V upx_int64_t get64_signed(const void *p) C = 0;

    S u16_compare(const void *a, const void *b) C = 0;
    S u24_compare(const void *a, const void *b) C = 0;
    S u32_compare(const void *a, const void *b) C = 0;
    S u64_compare(const void *a, const void *b) C = 0;

    S u16_compare_signed(const void *a, const void *b) C = 0;
    S u24_compare_signed(const void *a, const void *b) C = 0;
    S u32_compare_signed(const void *a, const void *b) C = 0;
    S u64_compare_signed(const void *a, const void *b) C = 0;

private:
    // disable copy, assignment and move assignment
    AbstractPolicy(const AbstractPolicy &) = delete;
    AbstractPolicy &operator=(const AbstractPolicy &) = delete;
    AbstractPolicy &operator=(AbstractPolicy &&) = delete;
    // disable dynamic allocation
    ACC_CXX_DISABLE_NEW_DELETE
};
#endif

#if defined(BELE_RTP)
#undef C
#define C const noexcept override
#endif

struct BEPolicy
#if defined(BELE_RTP)
    final : public AbstractPolicy
#endif
{
    inline BEPolicy() noexcept {}
#if defined(BELE_CTP)
    typedef N_BELE_RTP::BEPolicy RTP_Policy;
#elif defined(BELE_RTP)
    typedef N_BELE_CTP::BEPolicy CTP_Policy;
#endif
    V bool isBE() C { return true; }
    V bool isLE() C { return false; }

    typedef BE16 U16;
    typedef BE32 U32;
    typedef BE64 U64;

    V unsigned get16(const void *p) C { return get_be16(p); }
    V unsigned get24(const void *p) C { return get_be24(p); }
    V unsigned get32(const void *p) C { return get_be32(p); }
    V upx_uint64_t get64(const void *p) C { return get_be64(p); }

    V void set16(void *p, unsigned v) C { set_be16(p, v); }
    V void set24(void *p, unsigned v) C { set_be24(p, v); }
    V void set32(void *p, unsigned v) C { set_be32(p, v); }
    V void set64(void *p, upx_uint64_t v) C { set_be64(p, v); }

    V int get16_signed(const void *p) C { return get_be16_signed(p); }
    V int get24_signed(const void *p) C { return get_be24_signed(p); }
    V int get32_signed(const void *p) C { return get_be32_signed(p); }
    V upx_int64_t get64_signed(const void *p) C { return get_be64_signed(p); }

    S u16_compare(const void *a, const void *b) C { return be16_compare(a, b); }
    S u24_compare(const void *a, const void *b) C { return be24_compare(a, b); }
    S u32_compare(const void *a, const void *b) C { return be32_compare(a, b); }
    S u64_compare(const void *a, const void *b) C { return be64_compare(a, b); }

    S u16_compare_signed(const void *a, const void *b) C { return be16_compare_signed(a, b); }
    S u24_compare_signed(const void *a, const void *b) C { return be24_compare_signed(a, b); }
    S u32_compare_signed(const void *a, const void *b) C { return be32_compare_signed(a, b); }
    S u64_compare_signed(const void *a, const void *b) C { return be64_compare_signed(a, b); }

    static void compileTimeAssertions() {
        COMPILE_TIME_ASSERT(sizeof(U16) == 2)
        COMPILE_TIME_ASSERT(sizeof(U32) == 4)
        COMPILE_TIME_ASSERT(sizeof(U64) == 8)
        COMPILE_TIME_ASSERT_ALIGNED1(U16)
        COMPILE_TIME_ASSERT_ALIGNED1(U32)
        COMPILE_TIME_ASSERT_ALIGNED1(U64)
    }

private:
    // disable copy, assignment and move assignment
    BEPolicy(const BEPolicy &) = delete;
    BEPolicy &operator=(const BEPolicy &) = delete;
    BEPolicy &operator=(BEPolicy &&) = delete;
    // disable dynamic allocation
    ACC_CXX_DISABLE_NEW_DELETE
};

struct LEPolicy
#if defined(BELE_RTP)
    final : public AbstractPolicy
#endif
{
    inline LEPolicy() noexcept {}
#if defined(BELE_CTP)
    typedef N_BELE_RTP::LEPolicy RTP_Policy;
#elif defined(BELE_RTP)
    typedef N_BELE_CTP::LEPolicy CTP_Policy;
#endif
    V bool isBE() C { return false; }
    V bool isLE() C { return true; }

    typedef LE16 U16;
    typedef LE32 U32;
    typedef LE64 U64;

    V unsigned get16(const void *p) C { return get_le16(p); }
    V unsigned get24(const void *p) C { return get_le24(p); }
    V unsigned get32(const void *p) C { return get_le32(p); }
    V upx_uint64_t get64(const void *p) C { return get_le64(p); }

    V void set16(void *p, unsigned v) C { set_le16(p, v); }
    V void set24(void *p, unsigned v) C { set_le24(p, v); }
    V void set32(void *p, unsigned v) C { set_le32(p, v); }
    V void set64(void *p, upx_uint64_t v) C { set_le64(p, v); }

    V int get16_signed(const void *p) C { return get_le16_signed(p); }
    V int get24_signed(const void *p) C { return get_le24_signed(p); }
    V int get32_signed(const void *p) C { return get_le32_signed(p); }
    V upx_int64_t get64_signed(const void *p) C { return get_le64_signed(p); }

    S u16_compare(const void *a, const void *b) C { return le16_compare(a, b); }
    S u24_compare(const void *a, const void *b) C { return le24_compare(a, b); }
    S u32_compare(const void *a, const void *b) C { return le32_compare(a, b); }
    S u64_compare(const void *a, const void *b) C { return le64_compare(a, b); }

    S u16_compare_signed(const void *a, const void *b) C { return le16_compare_signed(a, b); }
    S u24_compare_signed(const void *a, const void *b) C { return le24_compare_signed(a, b); }
    S u32_compare_signed(const void *a, const void *b) C { return le32_compare_signed(a, b); }
    S u64_compare_signed(const void *a, const void *b) C { return le64_compare_signed(a, b); }

    static void compileTimeAssertions() {
        COMPILE_TIME_ASSERT(sizeof(U16) == 2)
        COMPILE_TIME_ASSERT(sizeof(U32) == 4)
        COMPILE_TIME_ASSERT(sizeof(U64) == 8)
        COMPILE_TIME_ASSERT_ALIGNED1(U16)
        COMPILE_TIME_ASSERT_ALIGNED1(U32)
        COMPILE_TIME_ASSERT_ALIGNED1(U64)
    }

private:
    // disable copy, assignment and move assignment
    LEPolicy(const LEPolicy &) = delete;
    LEPolicy &operator=(const LEPolicy &) = delete;
    LEPolicy &operator=(LEPolicy &&) = delete;
    // disable dynamic allocation
    ACC_CXX_DISABLE_NEW_DELETE
};

// Native Endianness policy (aka host policy)
#if (ACC_ABI_BIG_ENDIAN)
typedef BEPolicy NEPolicy;
typedef BEPolicy HostPolicy;
#elif (ACC_ABI_LITTLE_ENDIAN)
typedef LEPolicy NEPolicy;
typedef LEPolicy HostPolicy;
#else
#error "ACC_ABI_ENDIAN"
#endif

#undef V
#undef S
#undef C

/* vim:set ts=4 sw=4 et: */
