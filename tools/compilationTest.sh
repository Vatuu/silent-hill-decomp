printf 'Running Compilation Test'

make clean
rm -rf asm
rm -rf linkers

# Flags
COMPILATION_TEST_PROGRESS=1
COMPILATION_TEST_MATCH=1
COMPILATION_FLAG_BUILDMAPS=1

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color


if [ "$1" = "--skip-maps" ] || [ "$1" = "-sm" ]; then
COMPILATION_FLAG_BUILDMAPS=0
fi

{
make BUILD_MAPS=$COMPILATION_FLAG_BUILDMAPS generate
} || {
printf "\n\n\nOops! ${RED}Files were unable to be splitted.${NC}\n\nCheck the .yaml files in (repo)/config or run the setup process again.\n\n\n"
exit 1
}

{
make BUILD_MAPS=$COMPILATION_FLAG_BUILDMAPS progress
} || {
COMPILATION_TEST_PROGRESS=0
}

rm -rf build

{
make BUILD_MAPS=$COMPILATION_FLAG_BUILDMAPS check
} || {
COMPILATION_TEST_MATCH=0
}

if [ $COMPILATION_TEST_PROGRESS -eq 1 ]; then
  printf "\n\nCOMPILATION TEST - PROGRESS: ${GREEN}SUCCESSFUL${NC}\n"
else
  printf "\n\nCOMPILATION TEST - PROGRESS: ${RED}FAILED${NC}\n"
fi

if [ $COMPILATION_TEST_MATCH -eq 1 ]; then
  printf "COMPILATION TEST - CHECK: ${GREEN}SUCCESSFUL${NC}\n"
else
  printf "COMPILATION TEST - CHECK: ${RED}FAILED${NC}\n"
fi

if [ $COMPILATION_TEST_PROGRESS -eq 0 ] && [ $COMPILATION_TEST_MATCH -eq 1 ]; then
  printf "\n\nTIP: The issue is likely ocurring in a function marked as ${RED}NONMATCHING${NC}\n"
fi


if [ $COMPILATION_FLAG_BUILDMAPS -eq 0 ]; then
  printf "\n${RED}MAP COMPILATION SKIPPED${NC} | If you have work in a something that could be related to maps please re-run this script without the map compilation skip.\n"
fi