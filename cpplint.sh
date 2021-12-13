cpplint $( find . -name \*.h -or -name \*.cpp | grep -vE -e "^./build/" -e "^./test/" -e "^./vendor/")> results/cpplint_test.txt
