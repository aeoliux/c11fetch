project('c11fetch', 'c', version: '1.0.0')

prefix = get_option('prefix')
template = '-DPREFIX="@0@"'
option = template.format(prefix)
add_global_arguments(['-std=c99', option], language: 'c')
args = [option, '-std=c99']

if get_option('enable-lto')
	add_global_arguments('-flto', language: 'c')
	args = [args, '-flto']
endif
if get_option('native-optimization')
	add_global_arguments('-march=native', language: 'c')
	args = [args, '-march=native']
endif
if get_option('third-optlevel')
	add_global_arguments('-O3', language: 'c')
	args = [args, '-O3']
endif
if get_option('enable-debug')
	add_global_arguments('-g', language: 'c')
	args = [args, '-g']
endif

subdir('libsysinfo')

include = include_directories('include')
lib = static_library('sysinfo', libsrc, include_directories: include)

dep = declare_dependency(link_with: lib, include_directories: include)


if get_option('link-libdl')
	link_args = ['-ldl', option]
else
	link_args = option
endif

bin = executable('c11fetch', 'c11fetch/main.c', dependencies: dep, link_args: [link_args, args], install: true)
if not get_option('disable-c11fetch-default-plugins')
	comp = meson.get_compiler('c').get_id()
	if get_option('strip-plugins')
		dfl_flags = [comp, args, '-shared', '-fPIC', '-s', '-o']
	else
		dfl_flags = [comp, args, '-shared', '-fPIC', '-o']
	endif

	artix = custom_target(
		'artix-plugin',
		output: 'artix.so',
		input: 'c11fetch/plugins/artix.c',
		command: [dfl_flags, '@OUTPUT@', '@INPUT@'],
		install: true,
		install_dir: 'share/c11fetch/plugins',
	)
	gentoo = custom_target(
		'gentoo-plugin',
		output: 'gentoo.so',
		input: 'c11fetch/plugins/gentoo.c',
		command: [dfl_flags, '@OUTPUT@', '@INPUT@'],
		install: true,
		install_dir: 'share/c11fetch/plugins'
	)
	arch = custom_target(
		'arch-plugin',
		output: 'arch.so',
		input: 'c11fetch/plugins/arch.c',
		command: [dfl_flags, '@OUTPUT@', '@INPUT@'],
		install: true,
		install_dir: 'share/c11fetch/plugins'
	)
	fedora = custom_target(
		'fedora-plugin',
		output: 'fedora.so',
		input: 'c11fetch/plugins/fedora.c',
		command: [dfl_flags, '@OUTPUT@', '@INPUT@'],
		install: true,
		install_dir: 'share/c11fetch/plugins'
	)
	devuan = custom_target(
		'devuan-plugin',
		output: 'devuan.so',
		input: 'c11fetch/plugins/devuan.c',
		command: [dfl_flags, '@OUTPUT@', '@INPUT@'],
		install: true,
		install_dir: 'share/c11fetch/plugins'
	)
	debian = custom_target(
		'debian-plugin',
		output: 'debian.so',
		input: 'c11fetch/plugins/debian.c',
		command: [dfl_flags, '@OUTPUT@', '@INPUT@'],
		install: true,
		install_dir: 'share/c11fetch/plugins'
		)
	android = custom_target(
		'android-plugin',
		output: 'android.so',
		input: 'c11fetch/plugins/android.c',
		command: [dfl_flags, '@OUTPUT@', '@INPUT@'],
		install: true,
		install_dir: 'share/c11fetch/plugins'                                                                   
	)
	macos = custom_target(
		'macos-plugin',
		output: 'macos.so',
		input: 'c11fetch/plugins/macos.c',
		command: [dfl_flags, '@OUTPUT@', '@INPUT@'],
		install: true,
		install_dir: 'share/c11fetch/plugins'                                                                   
		)
	manjaro = custom_target(
		'manjaro-plugin',
		output: 'manjaro.so',
		input: 'c11fetch/plugins/manjaro.c',
		command: [dfl_flags, '@OUTPUT@', '@INPUT@'],
		install: true,
		install_dir: 'share/c11fetch/plugins'
	)
	haiku = custom_target(
		'haiku-plugin',
		output: 'haiku.so',
		input: 'c11fetch/plugins/haiku.c',
		command: [dfl_flags, '@OUTPUT@', '@INPUT@'],
		install: true,
		install_dir: 'share/c11fetch/plugins'
	)
	openbsd = custom_target(
		'openbsd-plugin',
		output: 'openbsd.so',
		input: 'c11fetch/plugins/openbsd.c',
		command: [dfl_flags, '@OUTPUT@', '@INPUT@'],
		install: true,
		install_dir: 'share/c11fetch/plugins'
	)
	alpine = custom_target(
		'alpine-plugin',
		output: 'alpine.so',
		input: 'c11fetch/plugins/alpine.c',
		command: [dfl_flags, '@OUTPUT@', '@INPUT@'],
		install: true,
		install_dir: 'share/c11fetch/plugins'
	)
	parabola = custom_target(
		'parabola-plugin',
		output: 'parabola.so',
		input: 'c11fetch/plugins/parabola.c',
		command: [dfl_flags, '@OUTPUT@', '@INPUT@'],
		install: true,
		install_dir: 'share/c11fetch/plugins'
	)
endif