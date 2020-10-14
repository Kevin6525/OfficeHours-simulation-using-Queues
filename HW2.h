//Header file
class probabilityStudent
{
	public:
		//Constructor
		probabilityStudent(double prob = 0.5);
		//Constant function, gets our probability a student comes in
		bool getProbability() const;
	private:
		double probability;
};
class averager
{
	public:
		//Constructor
		averager();
		//Modification function
		void nextValue(double number);
		//Constant functions
		//Return the number of students in office hours
		int totalStudents() const {return count;}
		//Calculate average wait time
		double average() const;
	private:
		double sum;
		int count;
};
class teacher
{
	public:
		//Constructor
		teacher(int minutes = 20);
		//Modifications functions
		void one_minute();
		void helpStudent();
		void updateQuestion(int minutes);
		//Constant function
		//Check if the teacher is busy/helping a student
		bool isBusy() const {return (timeLeft > 0);}
		//Returns the question length in minutes
		int questionDuration() const {return questionTime;}
	private:
		int questionTime;
		int timeLeft;
};

