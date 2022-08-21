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
#include <errno.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

char *_getCommandOutput(const char *command) {
	FILE *fp = popen(command, "r");
	if (!fp) return NULL;

	char buf[255];
	if (!fgets(buf, 255, fp)) {
		pclose(fp);
		return NULL;
	}
	pclose(fp);

	return strdup(buf);
}

char *c11fetch_getDistroName() {
	char *out = _getCommandOutput("echo $(sw_vers -productName) $(sw_vers -productVersion)");
	out[strlen(out) - 1] = '\0';
	return out;
}

long _getFilesNumber(const char *path) {
	DIR *d = opendir(path);
	if (!d) return -1;

	long count = 0;

	while (readdir(d)) {
		count++;
	}
	closedir(d);

	return count;
}

long c11fetch_getInstalledPackagesNumber() {
	long packages = 0;

	if (!access("/usr/local/bin/brew", X_OK)) {
		char *cellar = _getCommandOutput("brew --cellar");
		if (cellar) {
			cellar[strlen(cellar) - 1] = '\0';
			long a = _getFilesNumber(cellar);
			free(cellar);
			if (a == -1) {
				return -1;
			}

			packages += a;
		}

		char *casks = _getCommandOutput("brew --caskroom");
		if (casks) {
			casks[strlen(casks) - 1] = '\0';
			long a = _getFilesNumber(casks);
			free(casks);
			if (a == -1) {
				return -1;
			}

			packages += a;
		}
	}

	return packages;
}

char *c11fetch_getFormatter() {
	return strdup("\033[1;33m");
}

char **c11fetch_getASCIIArt() {
	char **buf = malloc(sizeof(char *) * 5);
	if (!buf) {
		fprintf(stderr, "%s\n", strerror(errno));
		return NULL;
	}

	buf[0] = "        /\\\t";
	buf[1] = "     __/ /_\t";
	buf[2] = "    /     /\t";
	buf[3] = "    |     |\t";
	buf[4] = "    \\_____\\\t";

	return buf;
}