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
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <sys/types.h>

#define LIBSYSINFO_GET_INTERNAL
#include <libsysinfo.h>

char *libsysinfo_getCurrentDesktop() {
	libsysinfo_clear_error();

	char *xdg_session_type = getenv("XDG_SESSION_TYPE");
	if (xdg_session_type) {
		if (!strcmp(xdg_session_type, "tty")) {
			return strdup(xdg_session_type);
		}

		if (!strcmp(xdg_session_type, "x11") || !strcmp(xdg_session_type, "wayland")) {
			char *xdg_session_desktop = getenv("XDG_SESSION_DESKTOP");
			if (xdg_session_desktop) {
				return strdup(xdg_session_desktop);
			} else return strdup(xdg_session_type);
		}
	}

	char *osid = libsysinfo_getOSID();
	if (osid) {
		if (!strcmp(osid, "haiku")) {
			free(osid);
			return strdup("Haiku DE");
		} else if (!strcmp(osid, "macos")) {
			free(osid);
			return strdup("Aqua");
		}

		free(osid);
	}

	return strdup("unknown");
}

char *libsysinfo_getOSID() {
	libsysinfo_errno = LE_OS_NAME;

	struct stat st;
	int fd = open("/etc/os-release", O_RDONLY);
	if (fd == -1) {
		if ((!access("/system/app", F_OK)) && (!access("/system/priv-app", F_OK))) {
			libsysinfo_clear_error();
			return strdup("android");
		}
		if (!access("/usr/bin/sw_vers", X_OK)) {
			libsysinfo_clear_error();
			return strdup("macos");
		}
		struct utsname *ut = malloc(sizeof(struct utsname) * 1);
		if (ut) {
			if (!uname(ut)) {
				if (!strcmp(ut->sysname, "Linux")) {
					libsysinfo_clear_error();
					free(ut);
					return strdup("linux");
				} else if (!strcmp(ut->sysname, "Haiku")) {
					libsysinfo_clear_error();
					free(ut);
					return strdup("haiku");
				} else if (!strcmp(ut->sysname, "OpenBSD")) {
					libsysinfo_clear_error();
					free(ut);
					return strdup("openbsd");
				}
			}
			free(ut);
		}
		libsysinfo_error_phase = "determine OS";
		return NULL;
	}
	if (fstat(fd, &st)) {
		libsysinfo_error_phase = "stat() error";
		return NULL;
	}
	char *content = malloc(st.st_size);
	if (!content) {
		libsysinfo_error_phase = "memory allocation";
		return NULL;
	}
	if (read(fd, content, st.st_size) == -1) {
		free(content);
		libsysinfo_error_phase = "reading /etc/os-release";
		return NULL;
	}

	size_t size;
	char **lines = libsysinfo_splitLines(content, &size);
	free(content);
	if (!lines) {
		return NULL;
	}
	char *value = libsysinfo_getValue((const char **) lines, "ID", size);
	if (!value) {
		libsysinfo_error_phase = "getting NAME value from /etc/os-release";
		
		free(lines);
		return NULL;
	}
	libsysinfo_freePointerArray((void **) lines, size);

	value = libsysinfo_stripDoubleQuote(value);

	libsysinfo_clear_error();
	return value;
}

char *libsysinfo_getUserHostname() {
	libsysinfo_errno = LE_LOGIN;

	struct passwd *user = getpwuid(getuid());
	if (!user) {
		libsysinfo_error_phase = "getpwuid()";
		return NULL;
	}

	struct utsname ut;
	if (uname(&ut) != 0) {
		libsysinfo_error_phase = "uname()";
		return NULL;
	}

	char *str = libsysinfo_xprintf("%s@%s", user->pw_name, ut.nodename);
	libsysinfo_clear_error();
	return str;
}

char *libsysinfo_getShell() {
	libsysinfo_errno = LE_SHELL;

	char *shell_getenv = getenv("SHELL");
	if (!shell_getenv) {
		libsysinfo_error_phase = "getenv()";
		return NULL;
	}

	libsysinfo_clear_error();
	return strdup(shell_getenv);
}
