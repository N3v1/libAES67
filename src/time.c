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

#include "../include/libAES67/time.h"

int la_time_get(la_time_t *xtp, la_clock_t clock_type) {}

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
