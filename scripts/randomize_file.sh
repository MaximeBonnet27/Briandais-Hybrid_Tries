#! /bin/bash

# Get all shakespeare words
cat test_files/shakespeare/* | sort | uniq  > test_files/list_shakespeare

# Shuffle the words and put it in another file
shuf test_files/list_shakespeare > test_files/temp

# Add random words to the file
for i in `seq 1 1000`
do
		# Write a random word of size $rand
		rand=`shuf -i 1-10 -n 1`
		cat /dev/urandom | tr -dc 'a-z' | fold -w $rand | head -n 10 >> test_files/temp
done
# Shuffle the file
shuf test_files/temp > test_files/search_test_file

# Clean temp file
rm -f test_files/temp
