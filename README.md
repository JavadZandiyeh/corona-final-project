# corona-final-project

##  bash script program

### introduction
this program is for downloading files from sever 'loh.istgahesalavati'\n
and also this files have .tar.gz format that program extract it first \n
and put the .text files of this zip file to '/tmp/corona_filnal_project/' \n
and also delete the extracted zip file(because we don't need it after extractioin) \n

### how to run it?
for repeat downloading every 60 sec, we have to run it by this command on shell: \n
watch -n 60 ./download.sh \n

##  c program

### introduction
this c program do this works: \n
1)connection to data base as default db named postgres \n
2)creation new data base by name fpdb \n
3)switch to fpdb data base \n
4)create three tables \n
5)read files from where the shell program saved text files \n
6)add datas of each line of files to tables \n
7)sleep until shell program downloads new files \n
8)repeat (5) and (6) and (7) forever :) \n

### how to run it?
first compile it : gcc -o hello hello.c -I/usr/include/postgresql -lpq -std=c99 \n
then run bash script program as i said befor and at last run this program \n
by  command : ./hello \n
