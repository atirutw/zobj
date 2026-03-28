zobj_lib = static_library('zobj',
    'src/zobj.c',
    include_directories: include_directories('include')
)

zobj = declare_dependency(
    include_directories: include_directories('include'),
    link_with: zobj_lib
)
