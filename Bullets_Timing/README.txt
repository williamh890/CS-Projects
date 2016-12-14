******************| ASM PROJECT 2 |***********************

Topics Covered: Threads and timing

Overview:
	I wrote this game for fun so I though for my project I could go through and look at the timings
	for all the functions and see how I could improve perfomace. The hope was to using both the 
	technics we learned in class and threads to do this. For my rough draft I looked at the set of
	functions that was taking up the most time to run (the draw/generate funcs). I ended up
	both threadifing and combining them and in the end it turned out the slowest part was the cout.
	
	To make threads viable for the draw/gen funcs I had to run the prog on a larger scale, so the next
	step is to jack up the enemies and bullets checks and add threads to those somehow.

	Also want to end up implementing somehow promises and futures.

Code:
	Modified for every time data was grabbed, so 