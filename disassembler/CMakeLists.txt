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

add_executable(bn-arm64-disasm-test test.c)
target_link_libraries(bn-arm64-disasm-test bn-arm64-disasm)

# target_link_libraries(jevmachopp PUBLIC arch_arm64 Boost::callable_traits enum.hpp fmt nanorange visit)
# target_compile_definitions(jevmachopp PRIVATE USE_FMT=1)
# target_compile_options(jevmachopp PRIVATE -Wall -Wextra -Wpedantic)
# target_compile_options(jevmachopp PRIVATE -fno-rtti -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables)

# target_include_directories(jevmachopp PUBLIC ../../include ../../3rdparty/static_string/include ../../3rdparty/static_vector/include ../../3rdparty/hedley)

# target_compile_options(jevmachopp PRIVATE -Xclang -fdump-record-layouts)
