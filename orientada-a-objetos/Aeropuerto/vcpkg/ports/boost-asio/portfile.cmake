# Automatically generated by scripts/boost/generate-ports.ps1

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO boostorg/asio
    REF boost-${VERSION}
    SHA512 bbde7c60f208733d48713d2dcfe5be0e18b8372ecaae51055225e5da6bf3e4671e53da8917d27c17f84e34be858d3002c3ac62cdecfd8e3e3861edf365256bee
    HEAD_REF master
    PATCHES
        windows_alloca_header.patch
        opt-dep.diff
)

set(FEATURE_OPTIONS "")
boost_configure_and_install(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS ${FEATURE_OPTIONS}
)