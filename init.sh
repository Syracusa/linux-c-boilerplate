#!/bin/bash

# Remove .git 
rm -r .git

# Change Project name
find . -name '*.c' -exec sed -i -e 's/___PROJECTNAME___/$1/g' {} \;
find . -name '*.h' -exec sed -i -e 's/___PROJECTNAME___/$1/g' {} \;

find . -name '*.c' -exec sed -i -e 's/___PROJECTNAMECAPITAL___/${1^^}/g' {} \;
find . -name '*.h' -exec sed -i -e 's/___PROJECTNAMECAPITAL___/${1^^}/g' {} \;

while read line
do
    IFS=',' read -a names <<< "${line}"
    for file in `find . -maxdepth 1 -type f -name "*${names[0]}*"`; do
        rename "s/${names[0]}/${names[1]}/" *
    done
done < ${inputfile}