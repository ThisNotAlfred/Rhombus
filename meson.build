project(
    'Rhombus',
    'cpp',
    default_options: [
        'cpp_std=c++23',
        'warning_level=3',
    ],
)

sources = [
    'source/rhombus.cpp',
    'source/parser.cpp',
    'source/runner.cpp',
    'source/tokenizer.cpp',
]

includes = [
    'include/instruction.hpp',
    'include/parser.hpp',
    'include/runner.hpp',
    'include/tokenizer.hpp',
]

include_dirs = include_directories(
    [
        'include',
    ],
)

executable(
    'rhombus',
    [sources, includes],
    include_directories: [include_dirs],
)