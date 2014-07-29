#!/bin/sh -u -e 

echo "Generating tools"

rm -Rf tools/build
mkdir -p tools/build
mkdir -p tools/bin

CC_OPTS=" -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG "
#BISON_FLAGS=" --report=all,state,look-ahead,itemset --token-table --debug "

#echo $CC_OPTS

#exit


test -e tools/src/filename_without_path.c
cc $CC_OPTS tools/src/filename_without_path.c -o tools/build/filename_without_path.exe
rm -f tools/bin/filename_without_path 
ln -s ../build/filename_without_path.exe tools/bin/filename_without_path 

test -e tools/src/filename_remove_extension.c
cc $CC_OPTS tools/src/filename_remove_extension.c -o tools/build/filename_remove_extension.exe
rm -f tools/bin/filename_remove_extension 
ln -s ../build/filename_remove_extension.exe tools/bin/filename_remove_extension

if true; then
for file_path_i in `ls tools/src/*.c`; do
  file_i=`./tools/bin/filename_without_path $file_path_i`
  file_i_wo_ext=`./tools/bin/filename_remove_extension $file_i`
#  echo $file_path_i
#  echo $file_i
#  echo $file_i_wo_ext
  cc $CC_OPTS tools/src/$file_i_wo_ext.c -o tools/build/$file_i_wo_ext.exe
  rm -f tools/bin/$file_i_wo_ext 
  ln -s ../build/$file_i_wo_ext.exe tools/bin/$file_i_wo_ext 
done;
fi;

#exit

echo "Generating ./build.sh"

rm -f build.sh


echo "#!/bin/sh -u -e -x " > build.sh
echo "rm -Rf build" >> build.sh
echo "mkdir -p build" >> build.sh

files_looked_pattern=src/*.c
#echo ${files_looked_pattern}
files_looked=`ls $files_looked_pattern 2>&1 || true`
#echo ${files_looked}

if ./tools/bin/string-equal-huh "$files_looked" "ls: $files_looked_pattern: No such file or directory"; then
  # do nothing
  printf "";
else 
#  echo "else";
    for file_path_i in ${files_looked}; do
	file_i=`./tools/bin/filename_without_path $file_path_i`
	file_i_wo_ext=`./tools/bin/filename_remove_extension $file_i`
#  echo $file_path_i
#  echo $file_i
#  echo $file_i_wo_ext
	echo "cc -c $CC_OPTS src/$file_i_wo_ext.c -o build/$file_i_wo_ext.o " >> build.sh
    done;
fi;

ar_cmd="ar -r -c build/lex-simple.a "
if ./tools/bin/string-equal-huh "$files_looked" "ls: $files_looked_pattern: No such file or directory"; then
  # do nothing
  printf "";
else 
#  echo "else";
    for file_path_i in ${files_looked}; do
	file_i=`./tools/bin/filename_without_path $file_path_i`
	file_i_wo_ext=`./tools/bin/filename_remove_extension $file_i`
#  echo $file_path_i
#  echo $file_i
#  echo $file_i_wo_ext
#	echo "cc -c $CC_OPTS src/$file_i_wo_ext.c -o build/$file_i_wo_ext.o " >> build.sh
	ar_cmd=${ar_cmd}" build/$file_i_wo_ext.o "
    done;
fi;


echo ${ar_cmd} >> build.sh

echo "ranlib build/lex-simple.a 2>&1 " >> build.sh
echo "cc -o build/lex-simple.exe -lm  build/lex-simple.a 2>&1 " >> build.sh
echo "" >> build.sh
echo "rm -f run 2>&1 " >> build.sh 
echo "ln -s build/lex-simple.exe run 2>&1 " >> build.sh 
echo "chmod +x run 2>&1 " >> build.sh 

chmod +x build.sh

exit 0;



ar -r -c build/lex-simple.a build/arbre.o build/arbre_liste.o build/arbre_methode.o build/automate.o build/automate_methode.o build/biglib.o build/compilation.o build/lexer.o build/main.o build/programme.o build/str_liste.o build/str_ltab.o build/structures.o build/test.o build/token.o build/token_liste.o build/parser.o 2>&1
ranlib build/lex-simple.a 2>&1
cc -o build/lex-simple.exe -lm  build/lex-simple.a 2>&1

rm -f run
ln -s build/lex-simple.exe run
chmod +x run




chmod +x build.sh






exit 0;


echo $CC_OPTS
echo ${CC_OPTS}

CC_OPTS2=" -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG "
echo ${CC_OPTS2}

cc_opts3=" -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG "
echo ${cc_opts3}

cc_opts4="tools"
echo ${cc_opts4}


#set -a
# 2>&1
#files_looked_pattern=tools/src/*.cdsadasd
#set files_looked_pattern
#declare -x files_looked_pattern=tools

files_looked_pattern="tools"
files_looked_pattern=tools/src/*.cdsadasd

echo "XXX: "
echo ${files_looked_pattern}

#exit 0

echo "XXX: "$files_looked_pattern;
files_looked=`ls $files_looked_pattern 2>&1 || true`
echo "FILES_LOOKED: $files_looked";
strings_equal=`string-equal-huh "$files_looked" "ls: $files_looked_pattern: No such file or directory"`
echo "EQUALS: ${strings_equal}";


#exit 0;

if string-equal-huh "$files_looked" "ls: $files_looked_pattern: No such file or directory"; then
echo "then";
else 
echo "else";
fi;


if true; then
echo "then";
else 
echo "else";
fi;

if false; then
echo "then";
else 
echo "else";
fi;

#for file_path_i in $files_looked; do
#    echo $file_path_i
#done;

