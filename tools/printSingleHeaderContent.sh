START=$(grep -n "#define" $1 | head -n 1 | awk -F ':' '{print $1}')
END=$(grep -n "#endif" $1 | tail -n 1 | awk -F ':' '{print $1}')
head -n $((END - 1)) $1 | tail -n $((END - START - 1))