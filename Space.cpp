#include "Space.h"
#include "Charged_Object.h"


ostream& operator<<(ostream& os, Space& spa) // print the charged objects
{
	vector <Charged_Object*>::iterator co_Iter;
	int i = 0;
	for (const auto& co_Iter : spa.co)
	{
		os << i << ".";
		co_Iter->show();
		os << endl;
		i++;
	}
	return os;
}

Space::~Space()
{
	for (auto it : co)
		delete it;
}

array<double,3> Space::electric_field(array<double, 3 > p0) // we do a superposition to calc the total electric field at a point
{
	vector <Charged_Object*>::iterator co_Iter;
	array<double, 3> ef = { 0,0,0 };
	for (co_Iter = co.begin(); co_Iter != co.end(); co_Iter++)
		ef += (*co_Iter)->electric_field(p0);
	return ef;
}
void Space::add_charged_object(Charged_Object* co1) 
{
	co.push_back(co1);
	co_map.insert({ co1->get_name(), co1 });
}

void Space::add_charged_object() // add charget object to data structure
{
	cout << "enter the type" << endl;
	cout << "1. Sphere" << endl;
	cout << "2. Point" << endl;
	cout << "3. Wire" << endl;
	int choise;
	cin >> choise;
	Charged_Object* co1;
	switch (choise)
	{
	case 1:
		co1 = new Sphere();
		add_charged_object(co1);
		co1->set_parameters();
		co_map.insert({ co1->get_name(), co1 });
		break;
	case 2:
		co1 = new Point();
		add_charged_object(co1);
		co1->set_parameters();
		co_map.insert({ co1->get_name(), co1 });
		break;
	case 3:
		co1 = new Wire();
		add_charged_object(co1);
		co1->set_parameters();
		co_map.insert({ co1->get_name(), co1 });
		break;
	default:
		cout << "please choose another option" << endl;
	}
}

void Space::remove_charged_object(Charged_Object* co1,int i) 
{
	vector <Charged_Object*>::iterator co_Iter=co.begin();	
	co_map.erase(co1->get_name());
	delete co[i];
	co.erase(co_Iter+i);
}

void Space::remove_charged_object(string name)
{
	int i=0;
	vector <Charged_Object*>::iterator co_Iter = co.begin();
	for (co_Iter = co.begin(); co_Iter != co.end(); co_Iter++)
	{
		if ((*co_Iter) == co_map[name])
			break;
		i++;
	}
	this->remove_charged_object(co_map[name],i);
}

void Space::remove_charged_object() // remove charged object from data structure
{	
	int choise;
	cout << "which one do you want to remove ?" << endl;
	cout << *this;
	cin >> choise;
	this->remove_charged_object(co[choise],choise);
}

bool Space::serialize(const string& fname) const {//serialization
	fstream dump(fname, ios::out);
	if (!dump) {//checks if legal
		return false;
	}
	//dump process
	dump << co.size()<< "\n" ;
	for (const auto& it :co) { // we save first name than type and than parameters
		dump << it->get_name() << " " << it->get_type() << " "; 
		dump << *it << "\n";
	}
	return true;
}


bool Space::deserialize(const string& fname)
{
	fstream dump(fname, ios::in); //checks if legal
	if (!dump) {
		return false;
	}
	//dump process
	string name,type;
	int size;
	dump >> size;
	while (size) {// we get first name than type and than parameters
		dump >> name;
		dump >> type;
		if (type == "Point") 
		{
			co.push_back(new Point(name)); 
			dump >> *co.back();
			co_map.insert({ name,co.back() }); 
		}
		if (type == "Sphere")
		{
			co.push_back(new Sphere(name)); 
			dump >> *co.back();
			co_map.insert({ name,co.back() });
		}
		if (type == "Wire")
		{
			co.push_back(new Wire(name)); 
			dump >> *co.back();
			co_map.insert({ name,co.back() });
		}
		size--;
	}
	return true;
}

vector <Charged_Object*> Space::get_charged_objects()const
{
	return co;
}
void Space::set_charged_objects(vector<Charged_Object*> co1)
{
	co=co1;
}

void Space::show() // show the charged objects
{
	vector <Charged_Object*>::iterator co_Iter;
	int i = 0;
	for (const auto& co_Iter : co)
	{
		cout << i<<".";
		co_Iter->show();
		cout << endl;
		i++;
	}
}

unordered_map<string, Charged_Object*> Space::get_co_map()const
{
	return co_map;
}

void Space::change_charged_object()
{
	int choise,choise1;
	cout << "which one do you want to change ?" << endl;
	this->show();
	cin >> choise;
	cout << "want to change name ?" << endl;
	cout << "1. yes" << endl;
	cout << "2. no" << endl;
	cin >> choise1;
	if (choise1 == 1)
		co[choise]->set_name();
	cout << "want to change parameters ?" << endl;
	cout << "1. yes" << endl;
	cout << "2. no" << endl;
	cin >> choise1;
	if (choise1 == 1)
	co[choise]->set_parameters();
}

void Space::show_size_dir(array<double, 3> a) // show vector as size and direction
{
	double size = sqrt(pow(a[0], 2) + pow(a[1], 2) + pow(a[2], 2));
	cout << "dir is" << a[0] / size << "," << a[1] / size << "," << a[2] / size << endl;
	cout << "size is" << size<<endl;
}

void Space::set_point() // set point we clac the electric field in
{
	cout << "please enter a point values x,y,z" << endl;
	cin >> m_p0[0];
	cin >> m_p0[1];
	cin >> m_p0[2];
}

array<double, 3> Space::get_point()const // get point we clac the electric field in
{
	return m_p0;
}



