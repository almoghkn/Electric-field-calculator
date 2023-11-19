#include "Menu.h"
#include "Charged_Object.h"
#include "Space.h"

void Menu::start(Space& sp)
{
	cout << "Menu" << endl;
	while (1)
	{
		cout << "choose an option:" << endl;
		cout << "1. calculate electric field" << endl; 
		cout << "2. add charged object" << endl;  
		cout << "3. remove charged object" << endl; 
		cout << "4. change charged object" << endl; 
		cout << "5. show charged objects" << endl; 
		cout << "6. export to txt file" << endl; 
		cout << "7. import from txt file" << endl; 
		cout << "8. show as size and direction" << endl; 
		cout << "9. show as vector" << endl; 
		cout << "10. end" << endl;
		int choise;
		cin >> choise;
		switch (choise)
		{
		case 1: 
			sp.set_point();
			cout<< sp.electric_field(sp.get_point())<<endl; 
			break;
		case 2:
			sp.add_charged_object();
			break;
		case 3:
			sp.remove_charged_object();
			break;
		case 4:
			sp.change_charged_object();
			break;
		case 5:
			cout<<sp<<endl;
			break;
		case 6:
			sp.serialize("electric_field.txt");
			break;
		case 7:
			sp.deserialize("electric_field.txt");
			break;
		case 8:
			sp.show_size_dir(sp.electric_field(sp.get_point()));
			break;
		case 9:
			cout << sp.electric_field(sp.get_point()) << endl;
			break;
		case 10:
			return;
		default:
			cout << "choose another option" << endl;
		}
	}

}
