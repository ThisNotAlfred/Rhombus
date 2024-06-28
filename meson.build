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
    'source/core.cpp',
    'source/parser.cpp',
    'source/tokenizer.cpp',
]

includes = [
    'include/instruction.hpp',
    'include/core.hpp',
    'include/parser.hpp',
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