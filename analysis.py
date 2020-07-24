#!/usr/bin/env python
# -*- coding: utf-8 -*-

import psycopg2
import os
import datetime
import time


conn = psycopg2.connect(database="fpdb", user="postgres", password="javad-9831032", host="localhost", port="5432")
    
print("NOTICE:  connected to data base fpdb")

with conn:

    cur = conn.cursor()

    
    #creating a directory for saving analysis files
    path = "/tmp/final_project/analysis"
    try:
        os.mkdir(path)
    except OSError:
        print("NOTICE:  directory %s was available" % path)
    else: 
        print("NOTICE:  %s created" % path)

    
    with open("/tmp/final_project/analysis/analysis.txt", "w") as f:
        while(1 == 1):
            time.sleep(70)
            
            currentTime = str(datetime.datetime.now())
            log = '-----------------------Analysis At ' + currentTime + '-----------------------\n'
            f.write(log)



            #first analysis 
            cur.execute('SELECT province, max(has_sold) FROM fp_stores_data GROUP BY province')
            rows = cur.fetchall()
            f.write("\nA) witch product has been sold in each provinces and how many?\n")
            for row in rows:
                f.write(f"\nprovince: {row[0]}\nmax has sold: {row[1]}\n")
            
            #second analysis
            cur.execute('SELECT market_id, AVG(price), MAX(has_sold) FROM fp_store_aggregation WHERE market_id<20 GROUP BY market_id')
            rows = cur.fetchall()
            f.write("\nB) what was the average of price in markets that have id less than 20 in time that they had product with most sale?\n") 
            for row in rows:
                f.write(f"\nmarket id: {row[0]}\naverage of price: {row[1]}\nmaximum of sale: {row[2]}\n")
            

            #third analysis
            cur.execute('SELECT province, AVG(price) FROM fp_stores_data GROUP BY province')
            rows = cur.fetchall()
            f.write("\nC) what is the average of price in each province?\n")
            for row in rows: 
                f.write(f"\nprovince: {row[0]}\naverage of price: {row[1]}\n")


            #fourth analysis
            cur.execute("SELECT MAX(has_sold), time, city FROM fp_city_aggregation GROUP BY time, city")
            rows = cur.fetchall()
            f.write('\nD) in witch time each city had the maximum of sale in a product\n')
            for row in rows:
                f.write(f"\nmaximum number of sale: {row[0]}\ntime: {row[1]}\ncity: {row[2]}\n")


            #fifth analysis
            cur.execute("SELECT city, MIN(quantity), MAX(has_sold) FROM fp_city_aggregation GROUP BY city")
            rows = cur.fetchall()
            f.write('\nE) what is the min of quantity and max of sale in each city?\n')
            for row in rows:
                f.write(f"\ncity: {row[0]}\nmin of quantity: {row[1]}\nmax of sale: {row[2]}\n")


            #sixth analysis
            cur.execute("SELECT MIN(price), market_id FROM fp_store_aggregation WHERE market_id<10 GROUP BY market_id")
            rows = cur.fetchall()
            f.write('\nF) what is the min of product price in markets with ids less than 10?\n')
            for row in rows:
                f.write(f"\nminimum price: {row[0]}\nmarket_id: {row[1]}\n")

            print("NOTICE:  details saved in /tmp/final_project/analysis/analysis.txt\n")
