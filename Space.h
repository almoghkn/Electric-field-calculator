#ifndef _SPACE_H_
#define _SPACE_H_

#include "Charged_Object.h"

#include <fstream>
#include<unordered_map>
#include <array>
#include <vector>
#include <iostream>
using namespace std;



class Space {
public:
	array<double, 3> electric_field(array<double, 3 >); // calc the electric field at point in space
	void add_charged_object();
	void add_charged_object(Charged_Object*);
	void remove_charged_object();
	void remove_charged_object(Charged_Object*,int i);
	void remove_charged_object(string name);
	bool serialize(const string& fname)const; // serialization
	bool deserialize(const string& fname); // deserialization
	vector <Charged_Object*> get_charged_objects()const;
	void set_charged_objects(vector<Charged_Object*>);
	void show();
	unordered_map<string, Charged_Object*> get_co_map()const;
	void change_charged_object();
	void show_size_dir(array<double, 3>); // show vec as size and direction
	void set_point();
	array<double, 3> get_point()const;
	friend ostream& operator<<(ostream& os, Space& spa);
	~Space();

private:
	vector <Charged_Object*> co;
	unordered_map<string, Charged_Object*> co_map; // to search more effective a charged object
	array<double, 3> m_p0; // the point we want to calc the electric field in
};


template <typename T> // we do a superpositon to calc the total electric field
array<T,3> operator+=( array<T,3>& a1, const array<T,3>& a2) {
	for (int i=0; i<3 ;i++)
	{
		a1[i]=a1[i] + a2[i];
	}
	return a1;
}


template <typename T> // print an array as x,y,z
ostream& operator<<(ostream& os, const array<T, 3>& a) {
	os << a[0] <<","<< a[1] << ","<< a[2];
	return os;
}



#endif //_SPACE_H_
