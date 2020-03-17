#!/bin/bash
for i in *.cc; do
    echo $i
    iconv -f ISO-8859-1 -t UTF-8//TRANSLIT $i > TEMP
    mv TEMP $i
done
for i in *.hh; do
    echo $i
    iconv -f ISO-8859-1 -t UTF-8//TRANSLIT $i > TEMP
    mv TEMP $i
done

