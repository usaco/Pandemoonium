#!/bin/bash

cd `dirname $0`
for i in `ls _BUILTIN/`
do
	name=${i%%.c}
	rm -rf $name/
	bash ../setup-bot.sh $name
	cp _BUILTIN/$i $name/$i
done

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
