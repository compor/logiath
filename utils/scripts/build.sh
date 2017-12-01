#!/usr/bin/env bash

[[ $TRAVIS == "true" ]] && set -evx

ci_exit() {
  local rc=0
  [[ ! -z $1 ]] && rc=$1

  if [[ $TRAVIS == "true" ]]; then
    true 
  else
    exit $rc
  fi
}

# initialize configuration vars

SRC_DIR=""
INSTALL_DIR=""


# set configuration vars

if [ -z "$1" ]; then 
  echo "error: source directory was not provided" 

  ci_exit 1
fi

SRC_DIR=$1

if [ -z "$2" ]; then 
  INSTALL_DIR="${SRC_DIR}/../install/"
else
  INSTALL_DIR="$2"
fi


# print configuration vars

echo "info: printing configuration vars"
echo "info: source dir: ${SRC_DIR}"
echo "info: install dir: ${INSTALL_DIR}"
echo ""


cmake \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=On \
  -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
  -DCMAKE_CXX_FLAGS="${CXX_FLAGS}" \
  -DCMAKE_EXE_LINKER_FLAGS="${LINKER_FLAGS}" \
  -DCMAKE_SHARED_LINKER_FLAGS="${LINKER_FLAGS}" \
  -DCMAKE_MODULE_LINKER_FLAGS="${LINKER_FLAGS}" \
  -DLOGIATH_SKIP_TESTS=${LOGIATH_SKIP_TESTS} \
  -DLOGIATH_DEBUG=${LOGIATH_DEBUG} \
  -DGTEST_ROOT=${GTEST_ROOT} \
  -DCMAKE_INSTALL_PREFIX="${INSTALL_DIR}" \
  "${SRC_DIR}"

ci_exit $?

