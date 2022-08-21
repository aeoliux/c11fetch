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
#include <dlfcn.h>

#define LIBSYSINFO_GET_INTERNAL
#include <libsysinfo.h>

char *c11fetch_get_distro_name();
long c11fetch_return_zero();
char **c11fetch_return_empty_ascii_art();
char *c11fetch_get_formatter();

int main(int argc, const char **argv) {
	char *plpath = getenv("C11FETCH_PLUGINS_PATH");
	if (!plpath) plpath = libsysinfo_xprintf("%s/share/c11fetch/plugins", PREFIX);
	else plpath = strdup(plpath);

	char *distroid;
	if (argc == 1) distroid = libsysinfo_getOSID();
	else distroid = strdup(argv[1]);
	
	char *path = libsysinfo_xprintf("%s/%s.so", plpath, distroid);
	free(plpath);
	free(distroid);

	char *(*c11fetch_getDistroName)() = NULL;
	long (*c11fetch_getInstalledPackagesNumber)() = NULL;
	char **(*c11fetch_getASCIIArt)() = NULL;
	char *(*c11fetch_getFormatter)() = NULL;
	char *reset = "\033[0m";

	void *dl = dlopen(path, RTLD_LAZY);
	free(path);
	if (!dl) {
		c11fetch_getDistroName = &c11fetch_get_distro_name;
		c11fetch_getInstalledPackagesNumber = &c11fetch_return_zero;
		c11fetch_getASCIIArt = &c11fetch_return_empty_ascii_art;
		c11fetch_getFormatter = &c11fetch_get_formatter;
	} else {
		c11fetch_getDistroName = dlsym(dl, "c11fetch_getDistroName");
		c11fetch_getInstalledPackagesNumber = dlsym(dl, "c11fetch_getInstalledPackagesNumber");
		c11fetch_getASCIIArt = dlsym(dl, "c11fetch_getASCIIArt");
		c11fetch_getFormatter = dlsym(dl, "c11fetch_getFormatter");
		if ((!c11fetch_getInstalledPackagesNumber) || (!c11fetch_getDistroName) || (!c11fetch_getASCIIArt) || (!c11fetch_getFormatter)) {
			c11fetch_getDistroName = &c11fetch_get_distro_name;
			c11fetch_getInstalledPackagesNumber = &c11fetch_return_zero;
			c11fetch_getASCIIArt = &c11fetch_return_empty_ascii_art;
			c11fetch_getFormatter = &c11fetch_get_formatter;
		}
	}

	char **ascii = c11fetch_getASCIIArt();
	char *name = c11fetch_getDistroName();
	long pkgs = c11fetch_getInstalledPackagesNumber();
	char *kernel = libsysinfo_getKernelVersion();
	char *shell = libsysinfo_getShell();
	char *env = libsysinfo_getCurrentDesktop();
	char *host = libsysinfo_getUserHostname();
	char *format = c11fetch_getFormatter();
	if ((!name) || (pkgs == -1) || (!kernel) || (!shell) || (!env) || (!host)) {
		fprintf(stderr, "c11fetch: failed to fetch system information\n");
		
		char *debug = getenv("C11FETCH_DEBUG");
		if (debug) {
			if (!strcmp(debug, "1"))
				fprintf(stderr, "c11fetch: additional debugging information:\n\terrno: %s\n\tlibsysinfo_errno: %s\n", strerror(errno), libsysinfo_strerror(NULL));
		} 
		
		if (format) free(format);
		if (host) free(host);
		if (env) free(env);
		if (shell) free(shell);
		if (kernel) free(kernel);
		if (name) free(name);
		if (ascii) free(ascii);
		return 1;
	}
	if (!format) format = strdup(reset);

	printf("\t\t\t %s%s\n", format, host);
	printf("%s Name:%s %s\n", ascii[0], reset, name);
	printf("%s%s Kernel:%s %s\n", format, ascii[1], reset, kernel);
	printf("%s%s Shell:%s %s\n", format, ascii[2], reset, shell);
	printf("%s%s Environment:%s %s\n", format, ascii[3], reset, env);
	printf("%s%s Packages:%s %li\n", format, ascii[4], reset, pkgs);

	free(format);
	free(host);
	free(env);
	free(shell);
	free(kernel);
	free(name);
	free(ascii);

	if (dl) dlclose(dl);
}

char *c11fetch_get_distro_name() {
	return strdup("Unknown");
}

long c11fetch_return_zero() {
	return 0;
}

char **c11fetch_return_empty_ascii_art() {
	char **ascii = malloc(5 * sizeof(char *));
	if (!ascii) {
		fprintf(stderr, "%s\n", strerror(errno));
		return NULL;
	}

	ascii[0] = "\t\t";
	ascii[1] = "\t\t";
	ascii[2] = "\t\t";
	ascii[3] = "\t\t";
	ascii[4] = "\t\t";

	return ascii;
}

char *c11fetch_get_formatter() {
	return strdup("\033[0m");
}
