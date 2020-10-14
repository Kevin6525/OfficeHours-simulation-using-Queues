# OfficeHours-simulation-using-Queues
The program is intended to simulate a professor's office hours given a probability of students entering office hours.
The program makes the following assumptions:
1. Each student needs to be helped for 1-20 minutes (random)
2. The professor's office hour is 1 hour long
3. The professor has 150 students total

The program runs 100 times and returns the averages of the following values.
1. Average wait time for students before they are helped
2. Average question duration (How long on average did the students need help for)
3. How long the professor goes over his office hours (If people arrive before office hours end, but are not helped, the professor will stay until everyone is helped)

Note: The professor stays after hours to help students, but does not accept new students past the 1 hour limit.
