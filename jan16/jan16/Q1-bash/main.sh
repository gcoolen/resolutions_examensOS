# Gregory Coolen - Décembre 2020
# Examen d'OS Janvier 2016 (Q1 - bash)
# main.h

# install pdflatex with:
# sudo apt-get install texlive-latex-base


if [ -d dir ]; then
  rm -r dir
fi
chmod +x ./generate.sh
./generate.sh


DIR_PATH=$1     #full path to dir = /home/.../Q1-bash/dir


delete_files() {
    res=$(find /$DIR_PATH -type f \( -iname \*.synctex.gz -o -iname \*.log -o -iname \*.aux \))
    for f in $res; do
        rm $f
    done
}

check_for_pdfs() {
    res=$(find /$DIR_PATH -type f -iname \*.tex)
    for f in $res; do
        bname=$(basename $f)                    #filename without path
        name_wo_ext=${bname%".tex"}             #filename without extension
        name_w_pdf="${name_wo_ext}.pdf"         #check in all directories => name without path
        found=$(find $DIR_PATH -name $name_w_pdf)
        if [ "$found" = "" ]; then
            v=$(pdflatex $f)
            if [ $? = 0 ]; then                 #succes
                echo "${name_w_pdf} créé"
            fi
        else
            echo "${name_w_pdf} à jour"
        fi
    done
}

./generate.sh
sleep 5 #check files
delete_files
sleep 10 #check deletes
check_for_pdfs
sleep 10 #check solution

rm -r dir
