#!/bin/bash

# Test case 1: Basic pattern matching with -e flag
echo -e "apple\nbanana\norange" > testfile.txt
./../s21_grep -e "banana" testfile.txt > s21_grep_output.txt
grep -e "banana" testfile.txt > grep_output.txt
diff s21_grep_output.txt grep_output.txt

# Test case 2: Case-insensitive pattern matching with -i flag
echo -e "Apple\nBanana\nOrange" > testfile.txt
./../s21_grep -i "orange" testfile.txt > s21_grep_output.txt
grep -i "orange" testfile.txt > grep_output.txt
diff s21_grep_output.txt grep_output.txt

# Test case 3: Invert match with -v flag
echo -e "apple\nbanana\norange" > testfile.txt
./../s21_grep -v "banana" testfile.txt > s21_grep_output.txt
grep -v "banana" testfile.txt > grep_output.txt
diff s21_grep_output.txt grep_output.txt

# Test case 4: Output count of matching lines with -c flag
echo -e "apple\nbanana\norange" > testfile.txt
./../s21_grep -c "apple" testfile.txt > s21_grep_output.txt
grep -c "apple" testfile.txt > grep_output.txt
diff s21_grep_output.txt grep_output.txt

# Test case 5: Output matching files only with -l flag
echo -e "apple\nbanana\norange" > testfile1.txt
echo -e "kiwi\ngrape\nbanana" > testfile2.txt
./../s21_grep -l "kiwi" testfile*.txt > s21_grep_output.txt
grep -l "kiwi" testfile*.txt > grep_output.txt
diff s21_grep_output.txt grep_output.txt

# Test case 6: Precede each matching line with a line number with -n flag
echo -e "apple\nbanana\norange" > testfile.txt
./../s21_grep -n "orange" testfile.txt > s21_grep_output.txt
grep -n "orange" testfile.txt > grep_output.txt
diff s21_grep_output.txt grep_output.txt

# Test case 7: Output matching parts of a line with -o flag
echo -e "apple orange\nbanana kiwi\ngrape lemon" > testfile.txt
./../s21_grep -o "a.e" testfile.txt > s21_grep_output.txt
grep -o "a.e" testfile.txt > grep_output.txt
diff s21_grep_output.txt grep_output.txt


