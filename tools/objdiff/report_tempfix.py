import os
import re

# DELETE WHENEVER THEY FIX THIS

def main():
    progress = open("build/progress.json", "r")
    text = progress.readline()
    regex = r',\{\"name\":\"\[\.reginfo\]\"\,\"size\":\"\d+\",\"metadata\":\{\}\},\{\"name\":\"\[\.MIPS.abiflags\]\"\,\"size\":\"\d+\",\"metadata\":\{\}\},\{\"name\":\"\[\.pdr\]\"\,\"size\":\"\d+\",\"metadata\":\{\}\},\{\"name\":\"\[\.gnu.attributes\]\"\,\"size\":\"\d+\",\"metadata\":\{\}\}'
    text = re.sub(regex, "", text)
    progress.close()
    progress = open("build/progress.json", "w")
    progress.truncate(0)
    progress.write(text)
    

if __name__ == "__main__":
    main()