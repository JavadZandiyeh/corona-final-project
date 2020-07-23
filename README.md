# corona-final-project
##   bash script program

### introduction?
this program is for downloading files from sever 'loh.istgahesalavati'
and also this files have .tar.gz format that program extract it first 
and put the .text files of this zip file to '/tmp/corona_filnal_project/'
and also delete the extracted zip file(because we don't need it after extractioin)

### how it works?
for repeat downloading every 60 sec, we have to run it by this command on shell:
watch -n 60 ./download.sh
