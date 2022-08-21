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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *c11fetch_getDistroName() {
	return strdup("Parabola GNU/Linux-libre");
}

char **c11fetch_getASCIIArt() {
	char **buf = malloc(sizeof(char *) * 5);
	if (!buf) {
		fprintf(stderr, "%s\n", strerror(errno));
		return NULL;
	}

	buf[0] = "        .-\t";
	buf[1] = "    .-'    '\t";
	buf[2] = ".-'.---.  '\t";
	buf[3] = "        ''\t";
	buf[4] = "        '\t";

	return buf;
}

long c11fetch_getInstalledPackagesNumber() {
	FILE *fp = popen("pacman -Q | wc -l", "r");
	if (!fp) {
		return -1;
	}

	char buf[255];
	if (!fgets(buf, 255, fp)) {
		pclose(fp);
		return -1;
	}
	pclose(fp);

	return atol(buf);
}

char *c11fetch_getFormatter() {
	return strdup("\033[1;30m");
}