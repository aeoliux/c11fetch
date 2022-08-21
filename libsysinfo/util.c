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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#define LIBSYSINFO_GET_INTERNAL
#include <libsysinfo.h>

#define MAX_PRINTF 4095
char *libsysinfo_xprintf(const char *fmt, ...) {
	char buf[MAX_PRINTF];
	va_list ap;
	va_start(ap, fmt);

	vsnprintf(buf, MAX_PRINTF, fmt, ap);

	va_end(ap);

	return strdup(buf);
}

char **libsysinfo_splitLines(const char *data, size_t *size) {
	char **buf = malloc(1 * sizeof(char *));
	size_t maxindex = 0;
	if (!buf) {
		libsysinfo_error_phase = "splitLines: memory allocation";
		return NULL;
	}

	char *dup = strdup(data);
	char *token = strtok(dup, "\n");
	size_t curind = 0;
	while (token) {
		if (curind > maxindex) {
			char **newptr = realloc(buf, (curind + 1) * sizeof(char *));
			if (!newptr) {
				libsysinfo_error_phase = "splitLines: memory allocation";
				free(dup);
				free(buf);
				return NULL;
			}

			buf = newptr;
			maxindex = curind;
		}
		buf[curind] = strdup(token);

		token = strtok(NULL, "\n");
		curind++;
		*size = curind;
	}

	free(dup);
	return buf;
}

void libsysinfo_freePointerArray(void **array, size_t size) {
	for (size_t i = 0; i < size; i++) {
		free(array[i]);
	}
	free(array);
}

char *libsysinfo_getValue(const char **keys, const char *key, size_t size) {
	for (size_t i = 0; i < size; i++) {
		char *dup = strdup(keys[i]);
		char *token = strtok(dup, "=");
		if (strcmp(token, key)) {
			free(dup);
			continue;
		}
		token = strtok(NULL, "=");

		char *dup2 = strdup(token);
		free(dup);
		return dup2;
	}
	return NULL;
}

char *libsysinfo_stripDoubleQuote(char *buf) {
	size_t len = strlen(buf), i2 = 0;
	for (size_t i = 0; i < len; i++) {
		if (buf[i] == '\"') {
			if (i2 == 0) i2 = i + 1;
			buf[i] = '\0';
		}
	}

	return buf + i2;
}