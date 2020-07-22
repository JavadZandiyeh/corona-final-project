#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include<dirent.h>
#include <string.h>


//public variables
PGresult *res;
PGconn *conn;

//starting connection with data base
void connectingToDB(){
    //The PGconn encapsulates the connection to database
    //mean we started a connection to databas with bellow details
    //here we connect to default data base of postgresql (mean postgres) and after
    //that we will create a new data base and switch on it
    conn = PQconnectdb("host=localhost dbname=postgres user=postgres password=javad-9831032");	

    //The PQstatus() function checks the status of connection to database
    //and if is BAD it shows the error and finishes the connection
    //then program finishes
    if (PQstatus(conn) == CONNECTION_BAD) {

        fprintf(stderr, "Connection to database failed: %s\n",
            PQerrorMessage(conn));

        PQfinish(conn);
        exit(1);
    }
}


//this function is for finishing connection with data base
void do_exit() {
    
    fprintf(stderr, "%s\n", PQerrorMessage(conn));    

    //clearing resualt of queries
    PQclear(res);
    
    //finishing connection
    PQfinish(conn);    
    
    //finishing program
    exit(1);
}


void checkResualtStatus(){
    //The PQresultStatus() function should be called to check the return value for any errors.
    //The PGRES_COMMAND_OK is returned if the command was properly executed and it does not return data.
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit();
    }

    //clearing result of queries
    PQclear(res);
}


//create new data base and switch on it
void createDB(){
    res = PQexec(conn, "CREATE DATABASE fpdb ENCODING 'UTF8'"); 
    checkResualtStatus();


    //change data base to 'fpdb'
    res = PQexec(conn, "\c fpdb");
    checkResualtStatus();
}


//creating tables we need
void createTables(){
    res = PQexec(conn, "CREATE TABLE fp_stores_data(time bigint, province varchar(50), city varchar(50), market_id integer,product_id integer,price integer, quantity integer, has_sold integer)");
    checkResualtStatus();
    
    //............................................problem here.......................


}


void readFiles(){

    char dirName[100];
    strcpy(dirName, "/tmp/final_project/");

    //dirent.h header file contains variables and functions related to directory streams.
    DIR *d;
    struct dirent *dir;
    d = opendir(dirName);
    
    if (d){
        while ((dir = readdir(d)) != NULL){
	    
	    //finding the name of file
	    char file[100];
	    strcpy(file, "tmp\\final_project\\");
	    //dir->d_name is the name of a file in (d) directory 
	    strcat(file, dir->d_name);

	    //pointer to file
	    FILE *fp = fopen (file, "r");
	    
	    //reading all lines of file
	    char line[256];
     	    while (fgets(line, sizeof(line), fp)) {
		    //printf("%s", line);
	    	//..................i have to insert into tables.................
	    
	    }

	    fclose(fp);
	    remove(file)
    	}
        closedir(d);
    }
}


//main function of program
int main() {
 
    connectingToDB();
    createDB();
    createTables();
    readFiles();

    //...........................................
    
    res = PQexec(conn, "INSERT INTO Cars VALUES(1,'Audi',52642)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) 
        do_exit(conn, res);     
    
    PQclear(res);    
    
    res = PQexec(conn, "INSERT INTO Cars VALUES(2,'Mercedes',57127)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn, res);   
    }
    
    PQclear(res);    
    
    res = PQexec(conn, "INSERT INTO Cars VALUES(3,'Skoda',9000)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn, res);   
    }
    
    PQclear(res);  
    
    res = PQexec(conn, "INSERT INTO Cars VALUES(4,'Volvo',29000)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn, res);   
    }
    
    PQclear(res);      
    
    res = PQexec(conn, "INSERT INTO Cars VALUES(5,'Bentley',350000)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn, res);   
    }
    
    PQclear(res);  
    
    res = PQexec(conn, "INSERT INTO Cars VALUES(6,'Citroen',21000)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn, res);   
    }
    
    PQclear(res);  
    
    res = PQexec(conn, "INSERT INTO Cars VALUES(7,'Hummer',41400)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn, res);   
    }
    
    PQclear(res);  
    
    res = PQexec(conn, "INSERT INTO Cars VALUES(8,'Volkswagen',21600)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn, res);   
    }
    
    PQclear(res);  
    PQfinish(conn);

    return 0;
}
