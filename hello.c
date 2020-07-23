#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

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
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
        do_exit();

    //clearing result of queries
    PQclear(res);
}


//create new data base and switch on it
void createDB(){

    res = PQexec(conn, "DROP DATABASE IF EXISTS fpdb");
    checkResualtStatus();


    res = PQexec(conn, "CREATE  DATABASE fpdb ENCODING 'UTF8'"); 
    checkResualtStatus();

    PQfinish(conn);	


    conn = PQconnectdb("host=localhost dbname=fpdb user=postgres password=javad-9831032");
    
    if (PQstatus(conn) == CONNECTION_BAD) {

        fprintf(stderr, "Connection to database failed: %s\n",
            PQerrorMessage(conn));

        PQfinish(conn);
        exit(1);
    }

    printf("NOTICE:  connected to data base by name fpdb\n");
}


//creating tables we need
void createTables(){

    //deleting last tables with simiular name as tables want to create 
    res = PQexec(conn, "DROP TABLE IF EXISTS fp_stores_data");
    checkResualtStatus();

    res = PQexec(conn, "DROP TABLE IF EXISTS fp_city_aggregation");
    checkResualtStatus();

    res = PQexec(conn, "DROP TABLE IF EXISTS fp_store_aggregation");
    checkResualtStatus();


    
    res = PQexec(conn, "CREATE TABLE fp_stores_data(time integer, province varchar(50), city varchar(50), market_id integer,product_id integer,price integer, quantity integer, has_sold integer, PRIMARY KEY(time, province, city, market_id, product_id, price, quantity, has_sold))");
    checkResualtStatus();

    res = PQexec(conn, "CREATE TABLE fp_city_aggregation(time integer, city varchar(50), price integer, quantity integer, has_sold integer)");
    checkResualtStatus();

    res = PQexec(conn, "CREATE TABLE fp_store_aggregation (market_id integer, price integer, has_sold integer)");
    checkResualtStatus();

    printf("NOTICE:  all tables were created\n");
}


void insertIntoTables(char time[50], char province[50], char city[50], char market_id[50], char product_id[50], char price[50], char quantity[50], char has_sold[50]){  

    char command[256];
    sprintf(command, "INSERT INTO fp_stores_data VALUES(%s, '%s', '%s', %s, %s, %s, %s, %s)", time, province, city, market_id, product_id,  price, quantity, has_sold);
    res = PQexec(conn, command);
    checkResualtStatus();


    char command_1[256];
    sprintf(command_1, "INSERT INTO fp_city_aggregation VALUES(%s, '%s', %s, %s, %s)", time, city, price, quantity, has_sold);
    res = PQexec(conn, command_1);
    checkResualtStatus();


    char command_2[256];
    sprintf(command_2, "INSERT INTO fp_store_aggregation VALUES(%s, %s, %s)", market_id, price, has_sold);
    res = PQexec(conn, command_2);
    checkResualtStatus();
}

void readFiles(){

    //dirent.h header file contains variables and functions related to directory streams.
    DIR *d;
    struct dirent *dir;
    d = opendir("/tmp/final_project/");
    
    if (d){
	      while ((dir = readdir(d)) != NULL){
	    
      	          //finding name of file
		  //dir->d_name is the name of a file in (d) directory
	          char file[100] = "/tmp/final_project/"; 
	          strcat(file, dir->d_name);

		
		  //we want to read text files not other files
	  	  char *ptr = strstr(dir->d_name, "text");	  
		  if (ptr == NULL)
            		continue;
        	  
		  printf("NOTICE:  start inserting datas into tables\n");

	          //pointer to file
	          FILE *fp = fopen (file, "r");
	    
	          //reading file line by line
	          char line[256];
     	          while (fgets(line, sizeof(line), fp)) {
		      
		      	  int i = 0;		     
			  char c;

			  char time[50] = "";
			  char province[50] = "";
			  char city[50] = "";
			  char market_id[50] = "";
			  char product_id[50] = "";
			  char price[50] = "";
			  char quantity[50] = "";
			  char has_sold[50] = "";
			

			  while((c = line[i++]) != ',')
                       	        strncat(time, &c, 1);

			  
			  while((c = line[i++]) != ',')
                                strncat(province, &c, 1);


			  while((c = line[i++]) != ',')
                                strncat(city, &c, 1);
                       
	
			  while((c = line[i++]) != ',')
                                strncat(market_id, &c, 1);
			  
			  while((c = line[i++]) != ',')
                                strncat(product_id, &c, 1);
	
			  while((c = line[i++]) != ',')
                                strncat(price, &c, 1);
		
			  while((c = line[i++]) != ',')
                                strncat(quantity, &c, 1);

			  while(i != strlen(line)){
                           	c = line[i++];
			     	strncat(has_sold, &c, 1);
			  }
			  
			 insertIntoTables(time, province, city, market_id, product_id, price, quantity, has_sold);
		  	    
	         }//end of --> while (fgets(line, sizeof(line), fp))

	         fclose(fp);
	         remove(file);
		 printf("NOTICE:  %s was removed\n", file);
    	    }//while ((dir = readdir(d)) != NULL)
        closedir(d);
    }//end of --> if (d)
}//end of function


//main function of program
int main() {
 
    connectingToDB();
    
    createDB();
    
    createTables();
    
    while(1){
        readFiles();
	printf("NOTICE:  start sleeping\n");
	sleep(65);
	printf("NOTICE:  finish sleeping\n");
    }//end of --> while(1)
    
    PQfinish(conn);

    return 0;
}
