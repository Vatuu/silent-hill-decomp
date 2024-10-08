echo "Hard updating submodules..."

# Deinitialize submodules
git submodule deinit -f tools/asm-differ
git submodule deinit -f tools/mips_to_c
git submodule deinit -f tools/splat

# Remove from module cache
rm -rf .git/modules/tools/asm-differ
rm -rf .git/modules/tools/mips_to_c
rm -rf .git/modules/tools/splat

# Remove from git
git rm -f tools/asm-differ
git rm -f tools/mips_to_c
git rm -f tools/splat

# Remove any lingering files
rm -rf tools/asm-differ
rm -rf tools/mips_to_c
rm -rf tools/splat

# Re-add submodules
git submodule add https://github.com/simonlindholm/asm-differ.git tools/asm-differ
git submodule add https://github.com/matt-kempster/mips_to_c.git tools/mips_to_c
git submodule add https://github.com/ethteck/splat.git tools/splat

# Re-init submodules
git submodule init

