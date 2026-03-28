project('zobj', 'c',
    default_options: [
        'c_std=c99'
    ]
)
add_project_arguments('-pedantic-errors', language: 'c')

zobj_lib = static_library('zobj',
    'src/zobj.c',
    include_directories: include_directories('include')
)

zobj = declare_dependency(
    include_directories: include_directories('include'),
    link_with: zobj_lib
)
