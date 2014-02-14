/*
 * Copyright (c) 2004-2006 Maxim Sobolev <sobomax@FreeBSD.org>
 * Copyright (c) 2006-2007 Sippy Software, Inc., http://www.sippysoft.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Id$
 *
 */

#ifndef _RTPP_UTIL_H_
#define _RTPP_UTIL_H_

#include "config.h"

#if defined(HAVE_ERR_H)
#include <err.h>
#else
#include <errno.h>
#include <stdio.h>
#include <string.h>
#endif
#include <pthread.h>

#include "rtpp_defines.h"

#define	GET_RTP(sp)	(((sp)->rtp != NULL) ? (sp)->rtp : (sp))
#define	NOT(x)		(((x) == 0) ? 1 : 0)
#ifdef MIN
#undef MIN
#endif
#ifdef MAX
#undef MAX
#endif
#ifdef ABS
#undef ABS
#endif
#define	MIN(x, y)	(((x) > (y)) ? (y) : (x))
#define	MAX(x, y)	(((x) > (y)) ? (x) : (y))
#define	ABS(x)		((x) > 0 ? (x) : (-x))

struct recfilter {
    double fcoef;
    double lastval;
};

/* Function prototypes */
double getdtime(void);
double ts2dtime(uint32_t, uint32_t);
void dtime2ts(double, uint32_t *, uint32_t *);
void seedrandom(void);
int drop_privileges(struct cfg *);
void init_port_table(struct cfg *);
char *rtpp_strsep(char **, const char *);
int rtpp_daemon(int, int);
int url_unquote(uint8_t *, int);
int pthread_mutex_islocked(pthread_mutex_t *);
double sigmoid(double);
double recfilter_apply(struct recfilter *, double);

/* Some handy/compat macros */
#if !defined(INFTIM)
#define	INFTIM		(-1)
#endif

#if !defined(ACCESSPERMS)
#define	ACCESSPERMS	(S_IRWXU|S_IRWXG|S_IRWXO)
#endif
#if !defined(DEFFILEMODE)
#define	DEFFILEMODE	(S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
#endif

#if !defined(HAVE_ERR_H)
#define err(exitcode, format, args...) \
  errx(exitcode, format ": %s", ## args, strerror(errno))
#define errx(exitcode, format, args...) \
  { warnx(format, ## args); exit(exitcode); }
#define warn(format, args...) \
  warnx(format ": %s", ## args, strerror(errno))
#define warnx(format, args...) \
  fprintf(stderr, format "\n", ## args)
#endif

#endif
