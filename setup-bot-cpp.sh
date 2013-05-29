#!/bin/bash

cd `dirname $0`
rootdir=`pwd`

botname=$*
botfile=`echo $botname | sed "s/[^a-zA-Z0-9]//g"`
botdir=$rootdir/bots/$botfile

mkdir $botdir

sed "s/BOTNAME/$botfile/g" $rootdir/client/Makefile.template > $botdir/Makefile
sed "s/BOTNAME/$botname/g" $rootdir/client/bot-template.c > $botdir/$botfile.cpp

sed "s/${botfile}.c/${botfile}.cpp/g" -i $botdir/Makefile
sed "s/gcc/g++/g" -i $botdir/Makefile

cd $botdir
ln -s $rootdir/client/mm-client.c
ln -s $rootdir/client/mm-client.h
