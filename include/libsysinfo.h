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

#ifndef LIBSYSINFO_DEFS

// Definition of libsysinfo error type.
typedef unsigned libsysinfo_err;
#define LE_SUCCESS 0
#define LE_GETKERNEL 1
#define LE_OS_NAME 3
#define LE_LOGIN 4
#define LE_SHELL 5

#ifdef LIBSYSINFO_GET_INTERNAL
extern libsysinfo_err libsysinfo_errno;
extern char *libsysinfo_error_phase;

extern void libsysinfo_clear_error();

extern char *libsysinfo_xprintf(const char *fmt, ...);

extern char **libsysinfo_splitLines(const char *data, size_t *size);
extern void libsysinfo_freePointerArray(void **array, size_t size);
extern char *libsysinfo_getValue(const char **keys, const char *key, size_t size);
extern char *libsysinfo_stripDoubleQuote(char *buf);
#endif

// libsysinfo strerror. If first argument is a NULL pointer, function takes internal libsysinfo errno as an error value. Function allocates memory so it's recommended to free() returned pointer.
extern char *libsysinfo_strerror(libsysinfo_err *er);

// Get current running kernel version. Function allocates memory so it's recommended to free() returned pointer.
extern char *libsysinfo_getKernelVersion();
// Get name of current desktop environment. Function allocates memory so it's recommended to free() returned pointer.
extern char *libsysinfo_getCurrentDesktop();
// Get operating system ID (for example: artix, arch, devuan, gentoo). Function allocates memory so it's recommended to free() returned pointer.
extern char *libsysinfo_getOSID();
// Get <username>@<hostname>. Function allocates memory so it's recommended to free() returned pointer.
extern char *libsysinfo_getUserHostname();
// Get current running shell. Function allocates memory so it's recommended to free() returned pointer.
extern char *libsysinfo_getShell();

#define LIBSYSINFO_DEFS
#endif