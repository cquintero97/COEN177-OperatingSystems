Christian Quintero
COEN 177L
Assignment 4: Page Replacement
Lab Section: Thursday 2:15pm - 5:00pm

For this lab, we practiced conducting page replacements using 3 different replacement 
algorithms (First-In-First-Out, Second Chance, Least Recently Used). I implemented 
each page replacement algorithm in separate files, using different methods and variables
to execute each implementation on the same accesses.txt file included. I've included all 
3 page replacement algorithm in seperate files in this .tar file.


The FIFO.c file using FIFO(First-in-First-Out) algorithm for page replacements. In this 
implementation, I used a sort of queued array to insert the most recently inserted
pages at the end of the array and the oldest pages at the beginning of the array in 
order. I made a few conditions for this implementation; When calling:

		if (!isInMemory(pageRequest, pageTable, tableSize))

on line 58, the function isInMemory checks throughout the array to see if there
is a page with the same page request number. If there are no matches and there is
still space in the table, I just insert the page after the last inserted page request
and incrememnt the page table index. However, if the table is full and there are no
matches, I shift every value in the page table up using:

				for (i=0; i<tableSize;i++)
				{
					pageTable[i]=pageTable[i+1];
				}
				
found on lines 71-74 and then insert the new page request to the end of the array 
in position tableSize-1. If there is a match found, I do nothing.


The FSC.c file implements the Second Chance algorithm. For this implementation, I
used two sets of arrays; One array to hold the page values and one array to hold
the reference values associated directly with each page in the array to keep track
of second chances. I created the second array table using:

        int *pageRef = (int*) malloc(sizeof(int)*tableSize);
		
found on line 52 to hold the reference values to check if a page in the table has
had a second chance or not. I modified the isInMemory to return the position of the
matched page in the table to make it easier to change the value of the corresponding
value in the pageRef table to 1 to show that the page has received a second chance.
I also have a condition to loop through the tables and overwrite the selected position
with the next positions value only if it has not been given a second chance yet. I used
a flag to also make sure I only reset the second chances reference values once after
the firlst shift. I also used a counter to keep track for the condition where all pages
in the tables already have had a second chance, so in that case I just do regular FIFO
algorithm.


The LRU.c file implements the Least Recently Used page replacement algorithm. For this 
implementation I used a doubly linked list of nodes to manage my page replacements since
it would reduce the amount of shifting I would have to do. For this, I used a 
node struct with an additional int variable named pageNum to hold the value of the page.
I added functions such as GetNewNode to create a new node with the page request,
InsertAtTail to insert a node with the page request at the tail of the linked list, and
PopAtHead to handle deleting nodes at the head. I modified the IsInMemory function to 
return a node pointer of the node with the matched page request. When there is no match
and the table is not full, I just called the InsertAtTail function to add the page
request to the tail. If the table is full, I call PopAtHead then InsertAtTail to update
the list. However, if a match is found, I used 2 conditions to handle different situations
where the matched node is located in the list. I used:

			if (nodeSelected == head && nodeSelected != tail)
			
on line 125 to handle the condition where the matched node is the head and is not
the only node in the list. I also used:

			else if (nodeSelected != head && nodeSelected != tail)
			
on line 134 to handle the condition where the matched node is in the middle of the list 
and is neither the head or tail. If the matched node is the tail, I do nothing since it
is already the tail, which I set as the most recently used.


I ran all 3 files using the accesses.txt inputs provided and ran each file 10 times, varying
table sizes from 50 to 500 with increments of size 50. I then plotted the hit rates of each 
run on a table included in the HitRateData.pdf file under Figure 1. I then went ahead and 
graphed my table shown in the HitRateData.pdf file under Figure 2. When looking at the data, 
I noticed that LRU algorithm had noticebly higher hit rates than the FIFO and Second Chance 
implementations for lower table sizes. However, as the table sizes increased up to 500, the 
hit rates for all 3 implementations seemed to be relatively close to one another, averaging 
close to about 0.9, with even the FIFO and Second Chance implementations having higher hit 
rates than LRU with table sizes greater than 350. Therefore I can tell that LRU tends to have
higher hit rates than FIFO and Second Chance for smaller table sizes but lower hit rates for 
bigger table sizes.