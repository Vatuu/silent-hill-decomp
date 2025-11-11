printf 'Running Compilation Test'

make clean
rm -rf asm
rm -rf linkers

# Flags
COMPILATION_TEST_PROGRESS=1
COMPILATION_TEST_MATCH=1

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

{
make generate
} || {
printf "\n\n\nOops! ${RED}Files were unable to be splitted.${NC}\n\nCheck the .yaml files in (repo)/config or run the setup process again.\n\n\n"
exit 1
}

{
make progress
} || {
COMPILATION_TEST_PROGRESS=0
}

rm -rf build

{
make check
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