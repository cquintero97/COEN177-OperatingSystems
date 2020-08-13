For the first part of the assignment, I located the main.c file in 
the minix source code since it was responsible for the initialization
of the system. In the code, I found a section labeled "announcement" which
contained a printf statement for the banner. I then just added an additional
printf statement as my edit for the first part of the assignment. I then saved 
the file and then rebooted the system to verify my changes worked.

For the second part of the assignment, I located the proc.c file since it is 
responsible for all process and message handling. I then scrolled through the 
file until I came across a section labeled "pick_proc" which contained the 
functions responsible for process selection to run. In order to add some
randomness to the current priority queue, I decided to add the condition:

	if(q>5)
	{
		q = (rand() % NR_SCHED_QUEUES);
	}	
	
In this condition, if the priority queue is greater than 5, then the current 
queue being observed will be changed to a random queue priority. I did this so 
that the system would try to run a process out of traditional queue order, which
would possible try running a process that would take longer to run with less 
priority. This would then in return slow down the time it takes for the 
operating system to set up. I used the hint provided in the assignment instructions
choose my value for "q>5" since the probability to choose a different process 
would be higher and slow down the OS startup. I noticed that when I chose a number
less than 5, the OS startup took much, much longer since there would be an even higher
probability of random selection of processes. If I chose a number higher than 5, such
as 8, I did not notice much of a difference in OS startup since the probability of
random process selection was much lower, since only processes with priority queues 
higher than 8 would be randomly selected, as opposed to all processes with priority
queue greater than 5.