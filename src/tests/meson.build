catch2_dep = dependency('catch2')

rang_util_test = executable('rang_util-test', [ 'util_tests.cpp', ], dependencies: [ catch2_dep, rang_util_dep ])

test('rang-util-test', rang_util_test)

# demo app in README.md
get_started = executable('get_started', 'get_started.cpp', dependencies: [rang_util_dep])
test('get-started', get_started)