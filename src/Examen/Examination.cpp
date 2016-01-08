﻿#define _CRT_SECURE_NO_DEPRECATE
#include "Examination.h"
#include <stdlib.h>
#include <algorithm>
#include "../Codec/my_time.h"
#include "../Codec/codec.h"

typedef unsigned int uint;

Examination::Examination(): _time(0) {
    setAnswer_rus("Ответ");
    setQuestion_rus("Вопрос");
}

Examination::~Examination() {delete _time;}

void Examination::MakeAnswerOrder(void)
{
	srand( (uint)time(0) );
	std::vector<Adress > an; 
	for (size_t i = 0; i < db.size(); ++i)
	{
		int rnd = rand()%db[i].size();
		an.push_back( Adress(i, rnd));
	}
	random_shuffle( an.begin( ), an.end( ) );
	answers.resize(an.size());
	for (size_t i = 0; i < answers.size(); ++i) 
	{
		answers[i].adress = an[i];
	}
}

bool Examination::LoadFromFile( std::istream & is ) 
{
	return db.LoadFromBinFile( is )>0;
}

std::string Examination::get_question( size_t n ) const
{
	std::string str;
	
	const q_zone& temp_zone = db[answers[n].adress.getZoneNumber()];
	if (temp_zone.difficult() != 0) 
	{
		str += "#\r\n";	
	}
	str += temp_zone[answers[n].adress.getQuestionNumber()];
	return str;
}

std::string Examination::get_answer( size_t n ) const
{
	return answers[n].str;
}

void Examination::set_answer( size_t n, std::string s ) 
{
	answers[n].str = s;
}

size_t Examination::size() const 
{
	return answers.size();
}
	
void Examination::SaveToFile( std::ostream &os, const char * username ) const
{
	void (*save_string)(std::ostream &os, const std::string &s);
	save_string = Codec::SaveStringToFile;
	db.set.SaveToFile(os,save_string);
	save_string( os, username );
	save_string(os, _time->get_date());
	save_string(os, _time->get_time());
	save_string(os, _time->get_time_differense());
	save_string (os, IntToString(size()));
	for( size_t i=0; i<size(); i++ ) 
	{
		std::string str;
        str+="-------- " + question_rus + " "+ IntToString(i+1)+"( "+IntToString(answers[i].adress.getZoneNumber() +1)+"_"+ IntToString(answers[i].adress.getQuestionNumber() +1)+")"+"--------";
		str+="\r\n";
		str+=get_question(i);
		str+="\r\n";
        str += "-------- " + answer_rus + " --------";
		str+="\r\n";
		str+=get_answer(i);
		str+="\r\n";
		save_string(os,str);
	}
}


void Examination::setAnswer_rus(const std::string &value)
{
    answer_rus = value;
}

void Examination::setQuestion_rus(const std::string &value)
{
    question_rus = value;
}

void Examination::setTime(my_time *t)
{
    delete _time;
    _time = t;
}

void Examination::startExamen()
{
	setTime(new my_time);
}

std::string Examination::get_time_differense() const
{
    // if (!_time) return "";
	return _time->get_time_differense();	
}
