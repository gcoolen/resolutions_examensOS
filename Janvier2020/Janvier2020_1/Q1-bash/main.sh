# Gregory Coolen - Décembre 2020
# Examen d'OS Janvier 20202016 (Q1 - bash)
# main.sh

#first creates some files in directory dir and in subdirectory dir/sub_dir with "generate.sh"


if [ -d dir ]; then
  rm dir
fi
chmod +x generate.sh
./generate.sh


PATHS=/home/greg/Documents/BA2/OS/exo/j20/paths.txt

parcour() {
  f=$1
  idx=$(expr ${#f} - 4) #extension = 4 last caracters (.mp3, .mp4, .wav, .jpg), if not all of lenght 3 use delimiter "cut "
  #include "." in extension otherwise can be confused with directory (EX: "dir/subdirmp3" and "dir/file.mp3")
  ext=${f:idx}
  if [ "$ext" = ".mp4" ]
  then
    new_ext=".ogv"

  elif [ "$ext" = ".mp3" ]
  then
    new_ext=".ogg" 

  elif [ "$ext" = ".wav" ]
  then
    new_ext=".flac" 

  elif [ "$ext" = ".jpg" ]
  then
    new_ext=".png" 

  fi

  mv $f "${f:0:$idx}${new_ext}" #change name
}

main () {
  while IFS= read line
  #faux, ne check pas les sous-dossiers (pas récursif)
  do
    if [ -d $line ]; then
      for f in $line/*; do
        parcour $f
      done
    else
      parcour $line
    fi
  done < "paths.txt"
}

main
