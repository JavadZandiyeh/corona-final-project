#! /bin/bash

#first we make directories for saving text and zip files
mkdir /tmp/final_project/
mkdir /tmp/final_project/zipFiles

#here we download the zip files and save them on the directory we made first for zip files
wget -O /tmp/final_project/zipFiles/$(($(date +%s%N)/1000000)).gz.tar loh.istgahesalavati.ir/report.gz.tar

#then we extract zip of better to say tar files and save them on /tmp/final_project path
tar -xvf /tmp/final_project/zipFiles/*.gz.tar -C /tmp/final_project/

#end of our work we remove extracted zip file becaus don't need it
rm /tmp/final_project/zipFiles/*.gz.tar

exit 0

#notic that we have to run this bash script file with command 
#(watch -n 60 ./download.sh) to repeat working every 1 min
