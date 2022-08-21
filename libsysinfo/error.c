/*
MIT License

Copyright (c) 2022 Zapomnij

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#define LIBSYSINFO_GET_INTERNAL
#include <libsysinfo.h>

libsysinfo_err libsysinfo_errno = LE_SUCCESS;
char *libsysinfo_error_phase = NULL;

char *libsysinfo_strerror(libsysinfo_err *er) {
	if (er == NULL) {
		er = &libsysinfo_errno;
	}

	switch (*er) {
		case LE_SUCCESS: return strdup("success");
		case LE_GETKERNEL: return libsysinfo_xprintf("failed to get kernel version at phase: '%s'", libsysinfo_error_phase);
		case LE_OS_NAME: return libsysinfo_xprintf("failed to get OS name at phase: '%s'", libsysinfo_error_phase);
		case LE_LOGIN: return libsysinfo_xprintf("failed to get current login information at phase: '%s'", libsysinfo_error_phase);
		case LE_SHELL: return libsysinfo_xprintf("failed to determine current running shell at phase: '%s'", libsysinfo_error_phase);
		default: return strdup("unknown error code");
	}

	return NULL;
}

void libsysinfo_clear_error() {
	libsysinfo_errno = LE_SUCCESS;
	libsysinfo_error_phase = NULL;
}