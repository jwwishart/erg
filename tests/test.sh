# Copyright (c) 2016 Justin William Wishart
# Full License is found in the LICENSE.txt file

# Dxecutes all cpp files which include assertion based tests of relevant functionality
# in the complier. 
# To run tests run this at the terminal:
#
#   sh tests.sh
#
# If everything runs fine then you should see no output bar the final message, otherwise
# you ought to see standard assertions if they fail.
#

echo "Running tests in $PWD"

mkdir -p bin

for file in *.cpp
do
    filename=$(basename "$file")
    extension="${filename##*.}"
    filename="${filename%.*}"
    
    clang++ --std=c++14 -g $file -D SILENT -o bin/$filename && bin/$filename
done

echo "Testing Completed"