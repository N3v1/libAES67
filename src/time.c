/*
 *  _ _ _      _   ___ ___   ______
 * | (_) |__  /_\ | __/ __| / /__  |
 * | | | '_ \/ _ \| _|\__ \/ _ \/ /
 * |_|_|_.__/_/ \_\___|___/\___/_/
 *
 * AES67 real-time audio-over-IP streaming library for C/C++.
 *
 * Copyright (c) 2025 - 2026 Nevio Hirani. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice, this
 *     list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 *  3. Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * src/time.c
 * Description: Clock and time abstraction for PTP.
 */

#include <time.h>

#include "../include/libAES67/time.h"
#include "../include/libAES67/__tai.h"

int la_time_get(la_time_t *xtp, const la_clock_t clock_type) {
    if (!xtp) { return -1; }

    struct timespec ts;

    switch (clock_type) {
        case LA_CLOCK_UTC:
            if (clock_gettime(CLOCK_REALTIME, &ts) != 0) { return -1; }
            break;

        case LA_CLOCK_TAI:
            #ifdef CLOCK_TAI
                if (clock_gettime(CLOCK_TAI, &ts) != 0) return -1;
            #else
                /*
                 * Simulate TAI on platforms without CLOCK_TAI (e.g., macOS).
                 * Read UTC via CLOCK_REALTIME and compute TAI using leap second table <__tai.h>.
                 */
                if (clock_gettime(CLOCK_REALTIME, &ts) != 0) { return -1; }

                int64_t ts_ns = (ts.tv_sec * LA_NS_PER_SEC) + ts.tv_nsec;

                ts_ns = la_utc_ns_to_tai_ns(ts_ns);

                ts.tv_sec  = ts_ns / LA_NS_PER_SEC;
                ts.tv_nsec = (long)(ts_ns % LA_NS_PER_SEC);
            #endif
            break;

        case LA_CLOCK_MONOTONIC:
            #ifdef CLOCK_MONOTONIC_RAW
                if (clock_gettime(CLOCK_MONOTONIC_RAW, &ts) != 0) { return -1; }
            #else
                if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) { return -1; }
            #endif
            break;

        case LA_CLOCK_PROCESS:
            if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts) != 0) { return -1; }
            break;

        case LA_CLOCK_THREAD:
            if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts) != 0) { return -1; }
            break;

        case LA_CLOCK_PTP:
        case LA_CLOCK_PTPv2:
            // TODO: Implement PTP via ptp.h
            return -1;

        default:
            return -1;
    }

    xtp->sec = ts.tv_sec;
    xtp->nsec = (int_fast32_t)ts.tv_nsec;
    la_time_normalize(xtp);

    return 0;
}

int la_time_getres(la_time_t *res, la_clock_t clock) {}

int la_time_sleep(const la_time_t *duration) {}

int la_time_sleep_until(const la_time_t *time, la_clock_t clock) {}

int la_tz_prep(la_timezone_t **timezone, const char *tzstring) {}

char *la_tz_error(la_timezone_t *timezone) {}

void la_tz_free(la_timezone_t *timezone) {}

int la_time_make(la_time_t *xtp, const struct tm *tmptr, const la_timezone_t *timezone) {}

int la_time_breakup(struct tm *tmptr, const la_time_t *xtp, const la_timezone_t *timezone) {}

int la_time_conv(la_time_t *dst, int dst_clock_type, const la_time_t *src, int src_clock_type) {}

size_t la_strfxtime(char* restrict s, size_t maxsize, const char* restrict format,
                    const la_time_t *xtp, const la_timezone_t *timezone) {}

int la_time_normalize(la_time_t *xtp) {}

int la_time_add(la_time_t *dst, const la_time_t *lhs, const la_time_t *rhs) {}

int la_time_sub(la_time_t *dst, const la_time_t *lhs, const la_time_t *rhs) {}

int la_time_cmp(const la_time_t *lhs, const la_time_t *rhs) {}

uint64_t la_time_to_ns(const la_time_t *time) {}

void la_time_from_ns(la_time_t *time, uint64_t ns) {}

uint64_t la_time_to_ptp(const la_time_t *time) {}

uint32_t la_time_to_rtp(const la_time_t *time, uint32_t rate) {}

double la_time_to_double(const la_time_t *time) {}

void la_time_from_double(la_time_t *time, double secs) {}

void la_time_from_ptp(la_time_t *time, uint64_t ptpns) {}
