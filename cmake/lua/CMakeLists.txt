project(lua)

add_library(lua STATIC
    src/lauxlib.c
    src/liolib.c
    src/lopcodes.c
    src/lstate.c
    src/lobject.c
    src/lmathlib.c
    src/loadlib.c
    src/lvm.c
    src/lfunc.c
    src/lstrlib.c
    src/lua.c
    src/linit.c
    src/lstring.c
    src/lundump.c
    src/lctype.c
    src/ltable.c
    src/ldump.c
    src/loslib.c
    src/lgc.c
    src/lzio.c
    src/ldblib.c
    src/lutf8lib.c
    src/lmem.c
    src/lcorolib.c
    src/lcode.c
    src/ltablib.c
    src/lbitlib.c
    src/lapi.c
    src/lbaselib.c
    src/ldebug.c
    src/lparser.c
    src/llex.c
    src/ltm.c
    src/ldo.c
)

target_include_directories(lua PUBLIC src)
