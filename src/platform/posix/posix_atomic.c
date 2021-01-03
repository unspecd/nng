//
// Copyright 2020 Staysail Systems, Inc. <info@staysail.tech>
// Copyright 2018 Capitar IT Group BV <info@capitar.com>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

// POSIX atomics.

#include "core/nng_impl.h"

#ifdef NNG_PLATFORM_POSIX

#ifndef NNG_HAVE_STDATOMIC

#include <pthread.h>

static pthread_mutex_t plat_atomic_lock = PTHREAD_MUTEX_INITIALIZER;

bool
nni_atomic_flag_test_and_set(nni_atomic_flag *f)
{
	bool v;
	pthread_mutex_lock(&plat_atomic_lock);
	v    = f->f;
	f->f = true;
	pthread_mutex_unlock(&plat_atomic_lock);
	return (v);
}

void
nni_atomic_flag_reset(nni_atomic_flag *f)
{
	pthread_mutex_lock(&plat_atomic_lock);
	f->f = false;
	pthread_mutex_unlock(&plat_atomic_lock);
}

void
nni_atomic_set_bool(nni_atomic_bool *b, bool n)
{
	pthread_mutex_lock(&plat_atomic_lock);
	b->b = n;
	pthread_mutex_unlock(&plat_atomic_lock);
}

bool
nni_atomic_get_bool(nni_atomic_bool *b)
{
	bool v;
	pthread_mutex_lock(&plat_atomic_lock);
	v = b->b;
	pthread_mutex_unlock(&plat_atomic_lock);
	return (v);
}

bool
nni_atomic_swap_bool(nni_atomic_bool *b, bool n)
{
	bool v;
	pthread_mutex_lock(&plat_atomic_lock);
	v    = b->b;
	b->b = n;
	pthread_mutex_unlock(&plat_atomic_lock);
	return (v);
}

void
nni_atomic_init_bool(nni_atomic_bool *b)
{
	b->b = false;
}

void
nni_atomic_add64(nni_atomic_u64 *v, uint64_t bump)
{
	pthread_mutex_lock(&plat_atomic_lock);
	v->v += bump;
	pthread_mutex_unlock(&plat_atomic_lock);
}

void
nni_atomic_sub64(nni_atomic_u64 *v, uint64_t bump)
{
	pthread_mutex_lock(&plat_atomic_lock);
	v->v -= bump;
	pthread_mutex_unlock(&plat_atomic_lock);
}

uint64_t
nni_atomic_get64(nni_atomic_u64 *v)
{
	uint64_t rv;
	pthread_mutex_lock(&plat_atomic_lock);
	rv = v->v;
	pthread_mutex_unlock(&plat_atomic_lock);
	return (rv);
}

void
nni_atomic_set64(nni_atomic_u64 *v, uint64_t u)
{
	pthread_mutex_lock(&plat_atomic_lock);
	v->v = u;
	pthread_mutex_unlock(&plat_atomic_lock);
}

uint64_t
nni_atomic_swap64(nni_atomic_u64 *v, uint64_t u)
{
	uint64_t rv;
	pthread_mutex_lock(&plat_atomic_lock);
	rv   = v->v;
	v->v = u;
	pthread_mutex_unlock(&plat_atomic_lock);
	return (rv);
}

void
nni_atomic_init64(nni_atomic_u64 *v)
{
	v->v = 0;
}

void
nni_atomic_inc64(nni_atomic_u64 *v)
{
	pthread_mutex_lock(&plat_atomic_lock);
	v->v++;
	pthread_mutex_unlock(&plat_atomic_lock);
}

uint64_t
nni_atomic_dec64_nv(nni_atomic_u64 *v)
{
	uint64_t nv;
	pthread_mutex_lock(&plat_atomic_lock);
	v->v--;
	nv = v->v;
	pthread_mutex_unlock(&plat_atomic_lock);
	return (nv);
}

bool
nni_atomic_cas64(nni_atomic_u64 *v, uint64_t comp, uint64_t new)
{
	bool result = false;
	pthread_mutex_lock(&plat_atomic_lock);
	if (v->v == comp) {
		v->v   = new;
		result = true;
	}
	pthread_mutex_unlock(&plat_atomic_lock);
	return (result);
}

void
nni_atomic_init(nni_atomic_int *v)
{
	pthread_mutex_lock(&plat_atomic_lock);
	v->v = 0;
	pthread_mutex_unlock(&plat_atomic_lock);
}

void
nni_atomic_add(nni_atomic_int *v, int bump)
{
	pthread_mutex_lock(&plat_atomic_lock);
	v->v += bump;
	pthread_mutex_unlock(&plat_atomic_lock);
}

void
nni_atomic_sub(nni_atomic_int *v, int bump)
{
	pthread_mutex_lock(&plat_atomic_lock);
	v->v -= bump;
	pthread_mutex_unlock(&plat_atomic_lock);
}

int
nni_atomic_get(nni_atomic_int *v)
{
	int rv;
	pthread_mutex_lock(&plat_atomic_lock);
	rv = v->v;
	pthread_mutex_unlock(&plat_atomic_lock);
	return (rv);
}

void
nni_atomic_set(nni_atomic_int *v, int i)
{
	pthread_mutex_lock(&plat_atomic_lock);
	v->v = i;
	pthread_mutex_unlock(&plat_atomic_lock);
}

int
nni_atomic_swap(nni_atomic_int *v, int i)
{
	int rv;
	pthread_mutex_lock(&plat_atomic_lock);
	rv   = v->v;
	v->v = i;
	pthread_mutex_unlock(&plat_atomic_lock);
	return (rv);
}

void
nni_atomic_inc(nni_atomic_int *v)
{
	pthread_mutex_lock(&plat_atomic_lock);
	v->v++;
	pthread_mutex_unlock(&plat_atomic_lock);
}

void
nni_atomic_dec(nni_atomic_int *v)
{
	pthread_mutex_lock(&plat_atomic_lock);
	v->v--;
	pthread_mutex_unlock(&plat_atomic_lock);
}

int
nni_atomic_dec_nv(nni_atomic_int *v)
{
	int nv;
	pthread_mutex_lock(&plat_atomic_lock);
	v->v--;
	nv = v->v;
	pthread_mutex_unlock(&plat_atomic_lock);
	return (nv);
}

bool
nni_atomic_cas(nni_atomic_int *v, int comp, int new)
{
	bool result = false;
	pthread_mutex_lock(&plat_atomic_lock);
	if (v->v == comp) {
		v->v   = new;
		result = true;
	}
	pthread_mutex_unlock(&plat_atomic_lock);
	return (result);
}

#endif

#endif // NNG_PLATFORM_POSIX
