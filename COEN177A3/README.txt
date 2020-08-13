	In this lab, we investigated the performance of our computer's file system by 
reading data from different sizes of files using two different methods of reading,
one in which we read each bit of data sequentially and the other which we read bits
of data in a random order. The purpose of doing this was to not only compare the 
difference in user/system/real time it took to read a file using two different 
methods, but to also understand the meanings behind user, system and real times
for the operations. 

-----------------------------------------------------------------------------------

	RESULTS OF OPERATIONS:
	
	Average time to complete seqread for 1G file:
	real:12.975s
	user: 12.630s
	sys: 0.270s
	
	Average time to complete seqread for 2.5G file:
	real: 29.522s
	user: 28.897s
	sys: 0.571s
	
	Average time to complete seqread for 5G file:
	real: 1m0.664s
	user: 59.406s
	sys: 1.520s
	
	
	
	Average time to complete randread for 1G file:
	real: 56m3.685s
	user: 5m9.021s
	sys: 48m15.325s
	
	Average time to complete randread for 2.5G file:
	real: 127m16.903s
	user: 12m37.745s
	sys: 111m31.375s
	
	Average time to complete randread for 5G file:
	real: 251m53.19s
	user: 26m38.893s
	sys: 221m31.499s
	
-----------------------------------------------------------------------------------

	After analyzing this data, it is clear to see that sequentially reading the 
	bits of data from the different file sizes with seqread.c were much faster in 
	comparison when the same data was read in a random order using randread.c
	
	After looking up the manuel pages for time, I saw that real time was representative
	for the wall-clock time and user time was the time spent on user calls and the system
	time was the time spent on system calls total. From examining the times from each
	execution, I noticed that the system calls took up most of the time and the user
	calls only took up a very small fraction of the time. After looking back at my code,
	this makes sense since the heavier system calls such as fopen, fread, and fseek took 
	much more time than the user calls since they were much more costly executions than
	the user calls and were executed more often than the user calls. It makes sense why 
	the randread.c file took longer to execute than the seqread.c file since the 
	randread.c file had more system calls such as fseek in its while loop and had to 
	constantly check an if condition for if the file data pointer had passed the limits 
	of the file, while the seqread.c file had less system calls in its while loop such
	as fread, and did not have to constantly check for extra conditions. 
	
	From my collected time data, the average rate seqread took to read a file was about
	12s per Gigabit of data read, which seemed to be constant for files of greater sizes.
	for the randread file, the average rate it took to read a file was about 50m per Gigabit
	of data read, which also seemed to be constant for files of greater sizes. Therefore,
	the randread file took about 3000 times longer to read data than the seqread, which is 
	a very big difference, but makes sense due to more costly system calls.
	