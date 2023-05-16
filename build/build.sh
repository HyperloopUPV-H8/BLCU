#!/bin/bash

PROJECT_NAME=BLCU_NEW
EXECUTABLE=BLCU_NEW.elf
ERROR=0
start=`date +%s.%N`

if [[ $* = *--nucleo* ]] || [[ $* = *-n* ]]
then
  TARGET="NUCLEO"
else
  if [[ $* = *--board* ]] || [[ $* = *-b* ]]
  then
    TARGET="BOARD"
  else
    echo "No target chosen. Do ./build [--nucleo | --board]"
    exit 1
  fi
fi

if [[ $* == *--NOETH* ]]
then
  ETH="NOETH"
else
  ETH="HAL_ETH_MODULE_ENABLED"
fi

if [[ $* == *--DEBUG* ]]
then
  PROFILE="-g3"
  PROFILE="-g0"
fi

cmake -DCMAKE_TOOLCHAIN_FILE=arm-none-eabi.cmake -DDEBUG:STRING=${DEBUG} -D${TARGET}=ON -D${ETH}=ON ..
make -j16 all
RET_STATUS=$(echo "$?")

end=`date +%s.%N`
runtime=$( echo "$end - $start" | bc -l )

arm-none-eabi-objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin

RED='\033[1;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color


if [[ $RET_STATUS == 0 ]]
then
  printf "\n\n\n${RED}%25s${NC} built!\n\n" ${PROJECT_NAME}
else
  printf "\n\n\n${RED}%15s${NC} not built correctly, errors ocurred.\n\n" ${PROJECT_NAME}
  ERROR=1
fi

printf "${RED}%20s ${NC}: ${YELLOW}\t%s\n" Target ${TARGET}
printf "${RED}%20s ${NC}: ${YELLOW}\t%ss\n" Compile $runtime
if ([ $ETH = "NOETH" ])
then
  printf "${RED}%20s ${NC}: ${YELLOW}\t%s\n" Ethernet OFF
fi
printf "\n"

if ([ $DEBUG = "-g3" ])
then
  printf "${RED}%20s ${NC}: ${YELLOW}\t%s\n" Debug ON 
else
  printf "${RED}%20s ${NC}: ${YELLOW}\t%s\n" Debug OFF
fi
printf "\n"

printf "${RED}%20s ${NC}: ${YELLOW}\t%s\n" Warnings ${WARNINGS}

printf "\n\n"

rm -R .cmake CMakeCache.txt cmake_install.cmake Makefile CMakeFiles BLCU_NEW.map BLCU_NEW.hex &>/dev/null
mv compile_commands.json ..

exit $ERROR
