#!/bin/bash

#find all .out files
for arguments in ${*:1}
do
    FILE_LIST='ls *.out'
    i=0
    apps=0
    for file in ${FILE_LIST}
        do 
        if [[ $i -gt 0 ]]; then
            while line_readed= read line; do
            #read line by line
                domain=$(echo $line | tr " " "\n")
                #tokenize with " " or "\n" character
                itsthere=0
                j=0
                for name in $domain
                do  
                    if [[ $j -eq 0 ]]; then
                    if [[ $domain == *"$arguments" ]]; then
                        itsthere=1
                    elif [[ $domain == "$arguments"* ]]; then
                        itsthere=1
                    elif [[ $domain == *"$arguments"* ]]; then
                        itsthere=1
                    fi
        fi
        if [ $j -eq 1 -a $itsthere -eq 1 ]; then
            let apps=apps+$name
        fi 
        let j=j+1
    done
    done < $file
fi  
    let i=i+1
done
echo Apearances are $apps
done