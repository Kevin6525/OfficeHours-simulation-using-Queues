#include <iostream>
#include <cassert>
#include <cstdlib>
#include <queue>
#include <stack>
#include <time.h>
#include <stdlib.h>
#include "HW2.h"

using namespace std;
//We use assert to ensure the probability given is not below 0.0 or above 1.0
probabilityStudent::probabilityStudent(double prob)
{
	assert(prob >= 0);
	assert(prob <= 1);
	probability = prob;
}
//This determines whether or not a student comes into the office (T/F)
bool probabilityStudent::getProbability() const
{
	return(rand() < probability * RAND_MAX);
}
//Constructor
averager::averager()
{
	count = 0;
	sum = 0;
}
//Update values in the averager class
//We add one to count and add the value to sum
void averager::nextValue(double number)
{
	count ++;
	sum += number;
}
//Calculation of average given values
double averager::average() const
{
	assert(totalStudents() > 0);
	return sum/count;
}
//Constructor of teacher class
//In my case, I made minutes the maximum question length a student can have
//The questionTime variable is then set to a random value from 1, to the maximum length
teacher::teacher(int minutes)
{
	questionTime = rand() % (minutes) + 1;
	timeLeft = 0;
}
//One minute passes, so we subtract a minute from time remaining for office hours
void teacher::one_minute()
{
	if(isBusy())
	{
		timeLeft--;
	}
}
//We set timeLeft to questionTime (question duration).
//In one_minute(), we simulate the teacher helping the student by ticking time off office hrs
//until the teacher finishes the question's duration
void teacher::helpStudent()
{
	timeLeft = questionTime;
}
//A mutator function to randomize the duration of students' questions
void teacher::updateQuestion(int minutes)
{
	questionTime = rand() % (minutes) + 1;
}


void simulateOfficeHour(int questionTime, double probability, int totalTime, int& averageWait, int& averageQuestion, int& averageOver)
{
	//Queue of arrival times
	queue<int> arrivalTimes;
	//Stack for question durations
	stack<int> questionTimes;
	
	int next;
	int currentTime;
	int timeOver = 0;
	teacher professor(questionTime);
	probabilityStudent studentArrival(probability);
	averager averageTime;
	//We push 0 onto the stack to avoid underflow error when we go through our algorithm to update
	//question durations
	questionTimes.push(0);
	//We begin by looping through the office hours
	for(currentTime = 1; currentTime <= totalTime; currentTime++)
	{
		//If a student arrives, we push them into the queue at the currentTime they arrive at
		//We assume the professor has 150 students
		if(studentArrival.getProbability() && averageTime.totalStudents() <= 150)
		{
			arrivalTimes.push(currentTime);
		}
		//We check to see if the professor is not helping anyone and there is someone waiting
		//If these conditions are met, we randomize the question duration.
		//We then update our questionTimes stack
		//We access the top of the stack (previous question duration) and pop it off the stack
		//We will then add it to the current question duration and push it onto the stack
		//We will now access the front of the queue, pop it and then add the time waited to averageTime
		//Note: The time waited is calculated by currentTime - timeArrived
		//We then help the student with his question
		//We also check if the stack is empty and if it is then we just push the questionDuration onto the stack
		if((!professor.isBusy()) && (!arrivalTimes.empty()))
		{
			professor.updateQuestion(questionTime);	
			if(questionTimes.empty())
			{
				questionTimes.push(professor.questionDuration());
			}
			else
			{
				int prevQuestion = questionTimes.top();
				questionTimes.pop();
				questionTimes.push(professor.questionDuration() + prevQuestion);
			}
			
			next = arrivalTimes.front();
			arrivalTimes.pop();
			averageTime.nextValue(currentTime-next);
			professor.helpStudent();
		}
		//We call one minute to get through the question and update remaining time in office hours
		professor.one_minute();
	}
	//Once office hours have ended, we check to see if there are any students who are still waiting from arriving before the office hours ended
	//We repeat the steps above until there are no students left waiting
	while((!arrivalTimes.empty()))
	{
		professor.updateQuestion(questionTime);
		timeOver += professor.questionDuration();
		int prevQuestion = questionTimes.top();
		questionTimes.pop();
		questionTimes.push(professor.questionDuration() + prevQuestion);
		
		next = arrivalTimes.front();
		arrivalTimes.pop();
		averageTime.nextValue(currentTime-next);
		professor.helpStudent();
	}
	//We update our variables passed by reference to store the values
	//We check to see if the total students is 0 before calling the updates (avoid program crashing)
	//This is to help when the program runs 100 times w low probabilities
	if(averageTime.totalStudents() > 0)
	{
		averageWait = averageTime.average();
		averageQuestion = questionTimes.top()/averageTime.totalStudents();
		averageOver = timeOver;
	}
	else
	{
		averageWait = 0;
		averageQuestion = 0;
		averageOver = 0;
	}
}

//This program makes the following assumptions:
//Students questions range from 1-20 minutes long
//The office hour is 1 hour long
//There is no time in between students once the student is done getting help
//We also seed rand in the beginning, outside the loop to get random numbers
int main()
{
	srand(time(NULL));
	int averageWait, averageQuestion, averageOffice, tempWait, tempQuestion, tempOffice;
	double probability;
	cout<<"Input the probability for students visiting (i.e. 0.1, 0.2): "<<endl;
	cin>>probability;
	for(int i = 0; i < 100; i ++)
	{
		simulateOfficeHour(20, probability, 60, averageWait, averageQuestion, averageOffice);
		tempWait += averageWait;
		tempQuestion += averageQuestion;
		tempOffice += averageOffice;
	}
	cout<<"Average wait time: "<<tempWait/100<<" minutes."<<endl;
	cout<<"Average question length: "<<tempQuestion/100<<" minutes."<<endl;
	cout<<"Average time over office hour: "<<tempOffice/100<<" minutes."<<endl;
	return 0;
}
