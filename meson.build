project(
    'powerctl',
    ['c'],
    version : '1.0',
    license : 'GPL-2.0',
    default_options : [
        'c_std=c99',
    ],
)

c_args = [
    '-Wall',
    '-Wextra',
    '-O2',
    '-D_GNU_SOURCE',
]

app_deps = [
    dependency('tinyc'),
    dependency('xscrnsaver'),
    dependency('x11'),
    dependency('xext'),
]

app_src = [
    'asound.c',
    'cpuload.c',
    'dmsg.c',
    'main.c',
    'sysidle.c',
]

executable(
    meson.project_name(),
    c_args : c_args,
    dependencies : app_deps,
    sources : app_src,
    install : true,
)


