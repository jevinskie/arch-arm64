cmake_minimum_required(VERSION 3.22)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(BN_ARM64_DISASM_IS_STANDALONE ON)
else()
    set(BN_ARM64_DISASM_IS_STANDALONE OFF)
endif()

if (BN_ARM64_DISASM_IS_STANDALONE)
    project(bn-arm64-disasm C)
endif()


set(BN_ARM64_DISASM_SRC
    decode.c
    format.c
    sysregs.c
    regs.c
    encodings_dec.c
    encodings_fmt.c
    operations.c
    pcode.c
    decode0.c
    decode1.c
    decode2.c
    decode_fields32.c
    decode_scratchpad.c
)

set(BN_ARM64_DISASM_HDR_STANDALONE
    feature_flags.h
)

set(BN_ARM64_DISASM_HDR)
foreach(HDR ${BN_ARM64_DISASM_HDR_STANDALONE})
    list(APPEND BN_ARM64_DISASM_HDR ${HDR})
endforeach()


foreach(SRC ${BN_ARM64_DISASM_SRC})
    string(REGEX REPLACE "\.c$" ".h" HDR ${SRC})
    if(EXISTS ${HDR})
        list(APPEND BN_ARM64_DISASM_HDR ${HDR})
    endif()
endforeach()

# BN_ARM64_DISASM_HDR added for Xcode project generation
add_library(bn-arm64-disasm ${BN_ARM64_DISASM_SRC} ${BN_ARM64_DISASM_HDR})
target_include_directories(bn-arm64-disasm PUBLIC include)

if (NOT CMAKE_CROSSCOMPILING)
    add_executable(bn-arm64-disasm-test test.c)
    target_link_libraries(bn-arm64-disasm-test bn-arm64-disasm)
endif()
