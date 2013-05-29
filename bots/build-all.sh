#!/bin/bash

cd `dirname $0`

function resetup()
{
	for i in `ls $1/`
	do
		if [[ $i == *.c ]]
		then
			name=${i%%.c}
			rm -rf $name/
			echo Deleted $name
			bash ../setup-bot.sh $name
			cp $1/$i $name/$i
		fi

		if [[ $i == *.cpp ]]
		then
			name=${i%%.cpp}
			rm -rf $name/
			echo Deleted $name
			bash ../setup-bot-cpp.sh $name
			cp $1/$i $name/$i
		fi
	done
}

resetup _BUILTIN/
resetup _CUSTOM/

for i in `ls`
do
	if [[ -d $i ]]
	then
		pushd $i > /dev/null 2>&1
		if [[ -e Makefile ]]
		then
			echo ">>> Making $i"
			make fresh
		fi
		popd > /dev/null 2>&1
	fi
done
