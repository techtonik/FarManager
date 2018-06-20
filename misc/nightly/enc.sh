#!/bin/bash

ROOT=$(dirname $0)/../..
REPO=far.git
if [ ! -d "$REPO" ]; then
        REPO=$ROOT
fi


function benc2 {
LNG=$1
L=$2

cd ${LNG} || return 1
wine "C:/Program Files (x86)/HTML Help Workshop/hhc.exe" plugins${L}.hhp

( \
	cp -vf FarEncyclopedia.${LNG}.chm $ROOT/outfinalnew32/Encyclopedia/ && \
	cp -vf FarEncyclopedia.${LNG}.chm $ROOT/outfinalnew64/Encyclopedia/ \
) || return 1

cd ..

}

function blua {

mkdir $1
cd $1 || return 1

wine "C:/src/enc/tools/lua/lua.exe" "C:/src/enc/tools/lua/scripts/tp2hh.lua" "../../../enc_lua/${1}.tsi" tsi "C:/src/enc/tools/lua/templates/api.tem" 
wine "C:/Program Files (x86)/HTML Help Workshop/hhc.exe" ${1}.hhp

( \
	cp -f ${1}.chm $ROOT/outfinalnew32/Encyclopedia/ && \
	cp -f ${1}.chm $ROOT/outfinalnew64/Encyclopedia/ \
) || return 1

cd ..

}

rm -fR $ROOT/build
mkdir $ROOT/build

cp -R $ROOT/enc $ROOT/build/ || exit 1

mkdir -p $ROOT/outfinalnew32/Encyclopedia
mkdir -p $ROOT/outfinalnew64/Encyclopedia

pushd build/enc/tools || exit 1
python tool.make_chm.py
cd ../build/chm

( \
	#benc2 en e && \
	benc2 ru r \
) || exit 1

popd

mkdir -p enc/build/lua
pushd enc/build/lua || exit 1

( \
	blua macroapi_manual.ru && \
	blua macroapi_manual.en && \
	blua luafar_manual \
) || exit 1

popd

#update api.farmanager.com
pushd enc/tools || exit 1
python ./tool.make_inet.py || exit 1
popd 
rm -Rf /var/www/api/* || exit 1
cp -Rf enc/build/inet/* /var/www/api/ || exit 1
