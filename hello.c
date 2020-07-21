#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

//this function is for finishing connection with data base
void do_exit(PGconn *conn, PGresult *res, PGresult *res_1, PGresult *res_2) {
    
    fprintf(stderr, "%s\n", PQerrorMessage(conn));    

    //clearing resualt of queries
    PQclear(res);
    PQclear(res_1);
    PQclear(res_2);

    //finishing connection
    PQfinish(conn);    
    
    //finishing program
    exit(1);
}

//main function of program
int main() {
 
    //The PGconn encapsulates the connection to database
    //mean we started a connection to databas with bellow details
    PGconn *conn = PQconnectdb("host=localhost dbname=postgres user=postgres password=javad-9831032"); 

    //The PQstatus() function checks the status of connection to database
    //and if is BAD it shows the error and finishes the connection
    //then program finishes
    if (PQstatus(conn) == CONNECTION_BAD) {
        
        fprintf(stderr, "Connection to database failed: %s\n",
            PQerrorMessage(conn));
            
        PQfinish(conn);
        exit(1);
    }

    //The PGresult encapsulates the result of a query
    //The PQexec() function submits an SQL command to the server and waits for the result
    //here we want to drop or remove last tables which have names that we want to make our new tables
    PGresult *res = PQexec(conn, "DROP TABLE IF EXISTS fp_stores_data");
    PGresult *res_1 = PQexec(conn, "DROP TABLE IF EXISTS fp_city_aggregation");
    PGresult *res_2 = PQexec(conn, "DROP TABLE IF EXISTS fp_store_aggregation");


    //The PQresultStatus() function should be called to check the return value for any errors.
    //The PGRES_COMMAND_OK is returned if the command was properly executed and it does not return data.
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn, res);
    }

    //clearing result of queries     
    PQclear(res);
    PQclear(res_1);
    PQclear(res_2);


    //creating tables............................................I am here..............................................
    res = PQexec(conn, "CREATE TABLE fp_stores_data(time INTEGER,province Varchar(50),city,market_id,product_id,price,quantity, has_sold)");
       
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn, res); 
    }
    
    PQclear(res);
    
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
