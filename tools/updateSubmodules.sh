echo "Hard updating submodules..."

# Deinitialize submodules
git submodule deinit -f tools/asm-differ
git submodule deinit -f tools/mips_to_c
git submodule deinit -f tools/splat
git submodule deinit -f tools/maspsx
git submodule deinit -f tools/decomp-permuter

# Remove from module cache
rm -rf .git/modules/tools/asm-differ
rm -rf .git/modules/tools/mips_to_c
rm -rf .git/modules/tools/splat
rm -rf .git/modules/tools/maspsx
rm -rf .git/modules/tools/decomp-permuter

# Remove from git
git rm -f tools/asm-differ
git rm -f tools/mips_to_c
git rm -f tools/splat
git rm -f tools/maspsx
git rm -f tools/decomp-permuter

# Remove any lingering files
rm -rf tools/asm-differ
rm -rf tools/mips_to_c
rm -rf tools/splat
rm -rf tools/maspsx
rm -rf tools/decomp-permuter

# Re-add submodules
git submodule add https://github.com/simonlindholm/asm-differ.git tools/asm-differ
git submodule add https://github.com/matt-kempster/mips_to_c.git tools/mips_to_c
git submodule add https://github.com/ethteck/splat.git tools/splat
git submodule add https://github.com/mkst/maspsx.git tools/maspsx
git submodule add https://github.com/simonlindholm/decomp-permuter tools/decomp-permuter

# Re-init submodules
git submodule init
