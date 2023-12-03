#!/bin/bash

# Test case 1: -b flag
echo -e "one\ntwo\n\nfour" > testfile.txt
./../s21_cat -b testfile.txt > s21_cat_output.txt
cat -b testfile.txt > cat_output.txt
diff s21_cat_output.txt cat_output.txt

# Test case 2: -e flag
echo -e "one\ntwo\n\nfour" > testfile.txt
./../s21_cat -e testfile.txt > s21_cat_output.txt
cat -e testfile.txt > cat_output.txt
diff s21_cat_output.txt cat_output.txt

# Test case 3: -n flag
echo -e "one\ntwo\n\nfour" > testfile.txt
./../s21_cat -n testfile.txt > s21_cat_output.txt
cat -n testfile.txt > cat_output.txt
diff s21_cat_output.txt cat_output.txt

# Test case 4: -s flag
echo -e "one\ntwo\n\nfour" > testfile.txt
./../s21_cat -s testfile.txt > s21_cat_output.txt
cat -s testfile.txt > cat_output.txt
diff s21_cat_output.txt cat_output.txt

# Test case 5: -t flag
echo -e "one\ttwo\n\t\nfour" > testfile.txt
./../s21_cat -t testfile.txt > s21_cat_output.txt
cat -t testfile.txt > cat_output.txt
diff s21_cat_output.txt cat_output.txt

# Test case 6: -v flag
echo -e "one\ttwo\n\nfour" > testfile.txt
./../s21_cat -v testfile.txt > s21_cat_output.txt
cat -v testfile.txt > cat_output.txt
diff s21_cat_output.txt cat_output.txt


