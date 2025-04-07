echo "Hard updating submodules..."

# Deinitialize submodules
git submodule deinit -f tools/asm-differ
git submodule deinit -f tools/m2c
git submodule deinit -f tools/maspsx
git submodule deinit -f tools/decomp-permuter

# Remove from module cache
rm -rf .git/modules/tools/asm-differ
rm -rf .git/modules/tools/m2c
rm -rf .git/modules/tools/maspsx
rm -rf .git/modules/tools/decomp-permuter

# Remove from git
git rm -f tools/asm-differ
git rm -f tools/m2c
git rm -f tools/maspsx
git rm -f tools/decomp-permuter

# Remove any lingering files
rm -rf tools/asm-differ
rm -rf tools/m2c
rm -rf tools/maspsx
rm -rf tools/decomp-permuter

# Re-add submodules
git submodule add https://github.com/simonlindholm/asm-differ.git tools/asm-differ
git submodule add https://github.com/matt-kempster/m2c.git tools/m2c
git submodule add https://github.com/mkst/maspsx.git tools/maspsx
git submodule add https://github.com/simonlindholm/decomp-permuter tools/decomp-permuter

# Re-init submodules
git submodule init
