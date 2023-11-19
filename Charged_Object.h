#ifndef _CHARGED_OBJECT_H_
#define _CHARGED_OBJECT_H_

#define _USE_MATH_DEFINES
#include <math.h>
#include <array>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Charged_Object {
public:
	Charged_Object(string name=nullptr);
	virtual array<double,3> electric_field(array<double,3>)=0;
	virtual string get_type()=0;
	string get_name()const;
	friend istream& operator>>(istream& fs, Charged_Object& cho); // for deserialization
	friend fstream& operator<<(fstream& os, Charged_Object& cho); // for serialization
	virtual void set_parameters()=0;
	virtual void show()const = 0; // print parameters, virtual because every charged object has a different parameters
	void set_name();
	virtual ~Charged_Object() {}

protected:
	string m_name;
	const double k = 9 * pow(10, 9);
	virtual istream& set_param(istream& fs)=0; // for serialization
	virtual fstream& get_param(fstream& os)const=0; // for deserialization
};


class Sphere : public Charged_Object {
public:
	Sphere(string name,int Q,int R,int x,int y,int z);
	Sphere(string name="");
	array<double, 3> electric_field(array<double, 3>);
	string get_type();
	int get_Q();
	void set_parameters();
	void show()const;
	~Sphere() {}

private:	
	istream& set_param(istream& fs); // for serialization
	fstream& get_param(fstream& os)const; // for deserialization
	int m_Q;
	int m_R;
	array<double, 3> m_point;
	static int m_counter ;

};


class Point : public Charged_Object {
public:
	Point(string name="");
	array<double, 3> electric_field(array<double, 3>);
	string get_type();
	int get_Q();
	void set_parameters();
	void show()const;
	~Point(){}

private:	
	istream& set_param(istream& fs); // for serialization
	fstream& get_param(fstream& os)const; // for deserialization
	int m_Q;
	array<double, 3> m_point;
	static int m_counter;
};

class Wire : public Charged_Object {
public:
	Wire(string name = "");
	Wire(string name,int ro);
	array<double, 3> electric_field(array<double, 3>);
	string get_type();
	void set_parameters();
	void show()const;	
	~Wire(){}

private:	
	istream& set_param(istream& fs); // for serialization
	fstream& get_param(fstream& os)const; // for deserialization
	static int m_counter;
	int m_ro;
	array<double, 3> m_point;
	array<double, 3> m_dir;
};

#endif //_CHARGED_OBJECT_H_
