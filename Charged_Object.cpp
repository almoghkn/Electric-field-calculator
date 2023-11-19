#include "Charged_Object.h"
#include "Space.h"



Charged_Object::Charged_Object(string name)
{
	m_name = name;
}

string Charged_Object::get_name()const
{
	return m_name;
}

void Charged_Object::set_name()
{
	cout << "enter the name" << endl;
	cin >> m_name;
}

istream& operator>>(istream& fs, Charged_Object& cho) // for serialization to get data
{
	cho.set_param(fs);
	return fs;
}

fstream& operator<<(fstream& os, Charged_Object& cho) // for serialization to insert data
{
	cho.get_param(os);
	return os;
}








int Sphere::m_counter(0); // intialize counter for default name

Sphere::Sphere(string name,int Q,int R,int x,int y, int z):Charged_Object(name) 
{
	m_Q = Q;
	m_R = R;
	m_point[0] = x;
	m_point[1] = y;
	m_point[2] = z;
	if (name == "")
	{
		m_counter++;
		m_name = "Sphere" + to_string(m_counter);
	}
}	

Sphere::Sphere(string name):Charged_Object(name)
{
	if (name == "")
	{
		m_counter++;
		m_name = "Sphere" + to_string(m_counter);
	}
	m_Q = 0;
	m_R = 0;
	m_point = { 0,0,0 };
}

array<double, 3> Sphere::electric_field(array<double, 3> p0) // calc the influence of Sphere on the point
{
	array<double, 3> ef;
	double dist = sqrt((p0[0] - m_point[0]) * (p0[0] - m_point[0]) + 
		(p0[1] - m_point[1]) * (p0[1] - m_point[1]) + (p0[2] - m_point[2]) * (p0[2] - m_point[2]));
	double r_size = (m_Q *1.6 * pow(10, -19)*dist) / (4 * M_PI * pow(m_R, 3)*1/(4*M_PI*k));
	array<double, 3> r_dir;
	r_dir[0] = (p0[0] - m_point[0]) / dist;
	r_dir[1] = (p0[1] - m_point[1]) / dist;
	r_dir[2] = (p0[2] - m_point[2]) / dist;
	ef[0] = r_size*r_dir[0];
	ef[1] = r_size*r_dir[1];
	ef[2] = r_size*r_dir[2];
	return ef;
}

string Sphere::get_type()
{
	return "Sphere";
}

int Sphere::get_Q()
{
	return m_Q;
}

istream& Sphere::set_param(istream& fs) // virtual function for serialization that get parameters
{
	fs >> m_Q >>m_R>> m_point[0] >> m_point[1] >> m_point[2];
	return fs;
}

fstream& Sphere::get_param(fstream& os)const // virtual function for serialization that insert parameters
{
	os << m_Q <<" "<<m_R<<" "<< m_point[0]<<" " << m_point[1] <<" "<< m_point[2];
	return os;
}

void Sphere::set_parameters()
{
	cout << "enter q" << endl;
	cin >> m_Q;
	cout << "enter R" << endl;
	cin >> m_R;
	cout << "enter point" << endl;
	cin >> m_point[0] >> m_point[1] >> m_point[2];
}

void Sphere::show()const // print parameters
{
	cout << m_name << " " << "q=" << m_Q <<"r="<<m_R<< " p=(" << m_point[0]<<"," << m_point[1] << "," << m_point[2] << ")";
}









int Point::m_counter(0); // intialize counter for default name

Point::Point(string name):Charged_Object(name)
{
	if (name == "")
	{
		m_counter++;
		m_name = "Point" +to_string(m_counter);
	}
	m_point = { 0,0,0 };
	m_Q = 0;
}

array<double, 3> Point::electric_field(array<double, 3> p0) // calc the influence of Point on the point
{
	array<double, 3> ef;
	double dist = sqrt((p0[0] - m_point[0]) * (p0[0] - m_point[0]) + (p0[1] - m_point[1]) * (p0[1] - m_point[1]) + (p0[2] - m_point[2]) * (p0[2] - m_point[2]));
	double r_size = (k * m_Q*1.6*pow(10,-19)) / pow(dist, 2);
	array<double, 3> r_dir;
	r_dir[0] = (p0[0] - m_point[0]) / dist; 
	r_dir[1] = (p0[1] - m_point[1]) / dist;
	r_dir[2] = (p0[2] - m_point[2]) / dist;
	ef[0] = r_size * r_dir[0];
	ef[1] = r_size * r_dir[1];
	ef[2] = r_size * r_dir[2];
	return ef;
}

string Point::get_type()
{
	return "Point";
}

int Point::get_Q()
{
	return m_Q;
}

istream& Point::set_param(istream& fs) // virtual function for serialization that get parameters
{
	fs >> m_Q >> m_point[0] >> m_point[1] >> m_point[2];
	return fs;
}

fstream& Point::get_param(fstream& os)const // virtual function for serialization that insert parameters
{
	os << m_Q<<" " << m_point[0] <<" "<< m_point[1] <<" "<< m_point[2];
	return os;
}

void Point::set_parameters()
{
	cout << "enter q" << endl;
	cin >> m_Q;
	cout << "enter point" << endl;
	cin >> m_point[0] >> m_point[1] >> m_point[2];
}

void Point::show()const // print parameters
{
	cout << m_name << " " << "q=" << m_Q<< " p=(" << m_point[0] << "," << m_point[1] << "," << m_point[2] << ")";
}






int Wire::m_counter(0); // intialize counter for default name

Wire::Wire(string name) :Charged_Object(name)
{
	if (name == "")
	{
		m_counter++;
		m_name = "Wire" + to_string(m_counter);
	}
	m_ro = 0;
	m_point = { 0,0,0 };
	m_dir = { 0,0,0 };
}

Wire::Wire(string name,int ro):Charged_Object(name)
{
	m_ro = ro;
	m_point = { 0,0,0 };
	m_dir = { 0,0,0 };
	if (name == "")
	{
		m_counter++;
		m_name = "Wire" + to_string(m_counter);
	}

}

array<double, 3> Wire::electric_field(array<double, 3> p0) // calc the influence of Wire on the point
{
	array<double, 3> ef;
	double t,x,y,z,dist,r_size;
	t = (p0[0] * m_dir[0] - m_point[0] * m_dir[0] + p0[1] * m_dir[1] - m_point[1] * m_dir[1] + p0[2] * m_dir[2] - m_point[2] * m_dir[2]) /
		(m_dir[0] * m_dir[0] + m_dir[1] * m_dir[1] + m_dir[2] * m_dir[2]);
	x = m_point[0] + t * m_dir[0];
	y = m_point[1] + t * m_dir[1];
	z = m_point[2] + t * m_dir[2];
	dist = sqrt((p0[0]-x)* (p0[0] - x)+ (p0[1] - y)* (p0[1] - y)+ (p0[2] - z)* (p0[2] - z));
	r_size = (m_ro * 1.6 * pow(10, -19)) / (2 * M_PI * dist * (1 / (4 * M_PI * k)));
	array<double, 3> r_dir;
	r_dir[0] = (p0[0] - m_point[0]) / dist;
	r_dir[1] = (p0[1] - m_point[1]) / dist;
	r_dir[2] = (p0[2] - m_point[2]) / dist;
	ef[0] = r_size * r_dir[0];
	ef[1] = r_size * r_dir[1];
	ef[2] = r_size * r_dir[2];
	return ef;
}

string Wire::get_type()
{
	return "Wire";
}

istream& Wire::set_param(istream& fs) // virtual function for serialization that get parameters
{
	fs >> m_ro >>m_dir[0]>> m_dir[1]>> m_dir[2]>> m_point[0] >> m_point[1] >> m_point[2];
	return fs;
}

fstream& Wire::get_param(fstream& os)const // virtual function for serialization that insert parameters
{
	os << m_ro << " " <<m_dir[0] << " " << m_dir[1] << " " << m_dir[2]<<" "<< m_point[0] <<" "<< m_point[1]<<" " << m_point[2];
	return os;
}

void Wire::set_parameters()
{
	cout << "enter ro" << endl;
	cin >> m_ro;
	cout << "enter direction" << endl;
	cin >> m_dir[0];
	cin >> m_dir[1];
	cin >> m_dir[2];
	cout << "enter point" << endl;
	cin >> m_point[0];
	cin >> m_point[1];
	cin >> m_point[2];
}

void Wire::show()const // print parameters
{
	cout <<m_name<<" "<< "ro=" << m_ro << " " << "dir=(" << m_dir[0] << "," << m_dir[1] << "," << m_dir[2] << ") " 
		<< "p=(" << m_point[0] << "," << m_point[1] << "," << m_point[2] << ")";
}