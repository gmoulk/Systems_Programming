#!/bin/bash

#find all .out files
for arguments in ${*:1}
do
    FILE_LIST='ls ../*.out'
    i=0
    apps=0
    for file in ${FILE_LIST}
        do 
        if [[ $i -gt 0 ]]; then
            while line_readed= read line; do
            #read line by line
                itsthere=0
                j=0
                for name in $line
                do  
                    if [[ $j -eq 0 ]]; then
                    if [[ $name == *".$arguments" ]]; then
                        itsthere=1
                    elif [[ $name == "$arguments."* ]]; then
                        itsthere=1
                    elif [[ $name == *".$arguments."* ]]; then
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
echo $arguments apearances are $apps
done