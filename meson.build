project('rang-util', ['cpp'], meson_version: '>=0.58.0', version: files('VERSION'), default_options : ['cpp_std=c++20', 'werror=true'])

# dependencies
rang_dep = dependency('rang')

rang_util_dep = declare_dependency(include_directories: 'src/include', dependencies: [rang_dep])

if get_option('build_test')
    subdir('src/tests')
endif