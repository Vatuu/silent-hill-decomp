# Replace arg1 with arg2 in all files recursively. Requires ag and sd
agsd() {
    if [[ $# != 2 ]]; then
        echo "need two parameters"
    fi

    ag -Q "${1}" -l | xargs -I{} sd -F "${1}" "${2}" {}
}

# Call permuter for a function in a map file
perm() {
    ./permute.sh --clean --run -j 20 $2 asm/maps/$1/nonmatchings/$1/$2.s src/maps/$1/$1.c
}
ovdiff(){ vimdiff <(hexdump -C assets/$1) <(hexdump -C build/out/$1); }
makef() { ../good-decomp/run bash -c "make clean-build -j20"; }
makej() { ../good-decomp/run bash -c "make build -j20"; }
asym() { local addr="$1"; local name="$2"; sym="configs/sym.bodyprog.txt"; echo "${name} = 0x${addr}; // type:func" >> "$sym"; }
ggg(){ git add -u; git commit -m "$1 => $2"; }
remm() { agsd "$1" "$2"; asym "$1" "$2"; ggg "$1" "$2"; }
repsha() { v1=$(printf 'INCLUDE_ASM("asm/maps/%s/nonmatchings/%s", %s);' $2 $2 $1); v2=$(printf '#include "maps/shared/%s.h"' $1); agsd "$v1" "$v2";}
finsym(){ find ./ -name "$1" | xargs -I {} bash -c "echo {}; sed -n '${2}p' {}"; }

addsym() {
    local isfunc=1
    local info="${1}"
    local sym="${2}"
    local addr="${3}"
    local map="${4}"

    if [[ "${addr}" == D_* ]]; then
        isfunc=0
        addr="${addr#D_}"
    elif [[ "${addr}" == func_* ]]; then
        isfunc=1
        addr="${addr#func_}"
    fi

    if [ -z "${info}" ]; then
        if [[ "${isfunc}" == 1 ]]; then
            info="type:func"
        fi
    fi

    echo "${sym} = 0x${addr}; // ${info}" >> "configs/USA/maps/sym.${map}.txt"
}
