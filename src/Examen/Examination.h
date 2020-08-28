#pragma once
#include "../Database/Adress.h"

#include <memory>
#include <string>
#include <vector>

class my_time;
class Database;
class Examination {
    // Database db;
	struct Answer {		
        Adress adress;
		std::string str; 
		Answer():adress(0,0){ }
	};
	std::string name;
	std::vector<Answer> answers;

    std::string question_rus;
    std::string answer_rus;
    std::unique_ptr<my_time> _time;
    std::unique_ptr<Database> db;
    Examination(const Examination&) = delete;
    Examination& operator=(const Examination&) = delete;
public:
	Examination();
	~Examination();
    std::string get_ext() const;
    std::string getTitle() const;
	void startExamen();
	void MakeAnswerOrder(void);
	size_t size() const;
	std::string get_question( size_t n )const;
	std::string get_answer( size_t n ) const;
	void set_answer( size_t n, std::string s );
	bool LoadFromFile( std::istream &is );	
	void SaveToFile( std::ostream &os, const char * username ) const;	
	std::string get_time_differense() const;
    void setAnswer_rus(const std::string &value);
    void setQuestion_rus(const std::string &value);
};
