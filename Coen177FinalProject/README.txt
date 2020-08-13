Christian Quintero
COEN 177L
Final Project Assignment
Due 6/16/18

For this project, I chose to implement a Clock Page Replacement Algorithm and compare its efficiency with my Second Chance Page Replacement Algorithm using the
provided accesses.txt file from last lab and testing out different table sizes. Since my Clock algorithm uses a circularly double linked list with a hand pointer, 
I wondered if it would return the total hit rate faster than the Second Chance algorithm in all cases since it only required inserting at the hand pointer and no
shifting of other elements in the table, which is what Second Chance did. Therefore, I chose to compare the two algorithms with different table sizes in order to
observe and patterns that would help me to answer my question. 

For this experiment, I did not have either algorithm implementation print out each page that caused a segmentation fault, since it would've taken much longer to
receive a time for each test, and technically both algorithms should cause the same page segmentation faults in the same order. Therefore, I ran each algorithm 
with the: 
		time cat accesses.txt|"alg" "#"

command and just replaced "alg" with the algorithm I was testing along with the table size in the "#" field.
I chose to test efficiency with the time it took to fully execute the program and print out the hitrate since the time command would show me just how much real 
time (clock time) it took to run each test for each algorithm. I executed each run 4 times for each table size for each algorithm and took the average of the
real time, then put the times onto a table to compare the times together. Now I originally assumed that Clock would finish faster in all cases, however, I noticed
from the data table that Clock had finished faster than Second Chance for smaller table sizes, but as the table sizes increased, it was Second Chance that had
better completion times. I then graphed the table and was able to see this patter more vividly. Although Clock uses a circular linked lists and doesnt have to shift 
the elements in the array, I realized that that only benefits Clock when the table is full and there is a unique request not in the table. That may explain why 
Second Chance had quicker completion times at larger table sizes since it only had to add a page to the positon after the last inserted element until the table
is filled. Clock may take longer for larger tables since it doesnt really benefit from the unfilled size scenario and still has to create a node and insert pointers
to connect the node in the linked list. Therefore, from my experimentation for my project, I was able to answer my original question about whether Clock is more 
efficient as far as completion time than Second Chance for all scenarios. From my results it is clear that Clock is more efficient than Second Chance when the table 
sizes are not as large, so somewhere between 500 to 1000 according to my data. After that, Clock is no longer more efficient that Second Chance when the table sizes
are huge.  
