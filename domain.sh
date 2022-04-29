#!/bin/bash

#find all .out files
for arguments in ${*:1}
do
    FILE_LIST='ls *.out'
    i=0
    apps=0
    for file in ${FILE_LIST}
        do 
        echo FILE = {$file}
        if [[ $i -gt 0 ]]; then
            while IFS= read -r line; do
                mails=$(echo $line | tr " " "\n")
                itsthere=0
                j=0
                for addr in $mails
                do  
                    if [[ $j -eq 0 ]]; then
                        echo "> $addr"
                    if [[ "$addr" == *".$arguments."* ]]; then
                        itsthere=1
                    elif [[ "$addr" == *"$arguments."* ]]; then
                        itsthere=1
                    elif [[ "$addr" == *".$arguments"* ]]; then
                        itsthere=1
                    fi
        fi
        if [ $j -eq 1 -a $itsthere -eq 1 ]; then
            let apps=apps+$addr
        fi 
        let j=j+1
    done
    done < $file
fi  
    let i=i+1
done
echo $apps
done