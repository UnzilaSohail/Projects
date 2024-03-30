
/*NAME : UNZILA ANJUM
ROLL NO : 22i-2550
SECTION : A
---ASSIGNMENT # 03---*/



//QUESTION NO 2


#include<iostream>
#include<string>
#include<cmath>
using namespace std;

class Creature {
protected:
	string name = "";
	int level=0;
	int healthpoints=0;
	int force=0;
	
public:
	int position = 0;
	//constructor
	Creature(string name  , int level, int healthpoints, int force, int position) {
		this->name = name;
		this->level = level;
		this->healthpoints = healthpoints;
		this->force = force;
		this->position = position;
	}
	//method to check if the creature is alive
	bool isalive() {
		if (healthpoints > 0) {
			return true;
		}
		else {
			return false;
		}
	}
	//method to calculate creatures attacking points
	int attackpoints() {
		if (isalive()) {
			return level * force;
		}
		else {
			return 0;
		}
	}
	//Method to move the creature
	void Move(int steps) {
		position = position + steps;
	}
	//message to display if the creature dies
	void Goodbye() {
		cout << name << " is no more!" << endl;
	}
	// to check if the creature is weak by their health points 
	void Weak(int points) {
		if (isalive()) {
			healthpoints = healthpoints - points;
		}
		if (!isalive()) {
			Goodbye();
			healthpoints = 0;
		}
	}
	//to print the creatures information
	void Display() {
		cout << name << " , level: " << level << " , health_status: " << healthpoints << " , force: "
			<< force << " , Attacking points: " << attackpoints() << " , Position: " << position << endl;
	}
};

class Dragon: public Creature {
protected:
	int flames;
public:
	//constructor
	Dragon(string n, int l, int hp, int f, int p ) : Creature (n, l, hp, f, p=0) , flames(f){
		
	}
	// function to moves dragons position
	void Fly(int pos) {
		position = pos;
	}

	// to blow flame on ichneumon 
	void BlowFlame(Creature& c)
	{
		if (isalive() && c.isalive() && abs(c.position - position) <= flames) {
			int damage = attackpoints();
			int distance = abs(c.position - position);
			healthpoints = healthpoints - distance;
			c.Weak(damage);
			if (!c.isalive()) {
				level++;
			}
		}
	}
};
class Ichneumon: public Creature {
private:
	int neck_length;
	int PoisonDose;
public:
	Ichneumon(string n, int l, int hp, int f, int nl, int pd, int p = 0) : Creature{ n,l,hp,f,p } {
		neck_length = nl;
		PoisonDose = pd;
	}
	//method for class Ichneumon to attack the dragon with poison
	void InjectPoison(Creature& d) {
		if (isalive() && d.isalive() && abs(d.position - position) <= neck_length) {
			int damage = attackpoints() + PoisonDose;
			d.Weak(damage);
			if (!d.isalive()) {
				level++;
			}
		}
	}
};

void Fight(Dragon& dragon, Ichneumon& ichneumon) {
	ichneumon.InjectPoison(dragon);
	dragon.BlowFlame(ichneumon);
}

int main()
{
	Dragon dragon("Dragon red", 2, 10, 3, 20);
	Ichneumon  ichneumon("ichneumon evil", 2, 10, 1, 10, 1, 42);

	dragon.Display();
	cout << "is preparing for fight with :" << endl;
	ichneumon.Display();

	cout << endl;
	cout << "1st Fight :" << endl;
	cout << "    the creature-s are not within range, so can not Attacke."
		<< endl;
	Fight(dragon, ichneumon);

	cout << "After the Fight :" << endl;
	dragon.Display();
	ichneumon.Display();

	cout << endl;
	cout << "Dragon has flown close to ichneumon :" << endl;
	dragon.Fly(ichneumon.position - 1);
	dragon.Display();

	cout << endl;
	cout << "ichneumon moves :" << endl;
	ichneumon.Move(1);
	ichneumon.Display();

	cout << endl;
	cout << "2nd Fight :" << endl;
	cout << ""
		<< "+ ichneumon inflicts a 3-point attack on dragon\n"
		" [ level (2) * force (1) + poison (1) = 3 ] ;\n"
		"+ Dragon inflicts a 6-point attack on ichneumon\n"
		"[ level (2) * force (3) = 6 ] ;\n"
		"+ during his attack, dragon loses two additional points\n"
		"      [ corresponding to the distance between dragon and ichneumon : 43 - 41 = 2 ]." << endl;
	Fight(dragon, ichneumon);

	cout << "After the Fight :" << endl;
	dragon.Display();
	ichneumon.Display();

	cout << endl;
	cout << "Dragon moves by one step " << endl;
	dragon.Move(1);
	dragon.Display();

	cout << endl;
	cout << "3rd Fight :" << endl;
	cout << "  + ichneumon inflicts a 3-point attack on dragon \n "
		"    [ level (2) * force (1) + poison (1) = 3 ] ; \n "
		"+ Dragon inflicts a 6-point attack on ichneumon \n "
		"      [ level (2) * force (3) = 6 ] ; \n"
		"+ during his attack, dragon lost 1 additional life point.\n"
		"[ corresponding to the distance between dragon and ichneumon : 43 - 42 = 1 ] ;\n"
		"+ ichneumon is defeated and the dragon rises to level 3" << endl;
	Fight(dragon, ichneumon);

	cout << "After the Fight :" << endl;
	dragon.Display();
	ichneumon.Display();

	cout << endl;
	cout << "4th Fight :" << endl;
	cout << "    when one creatures is defeated, nothing happpens" << endl;
	Fight(dragon, ichneumon);

	cout << "After the Fight :" << endl;
	dragon.Display();
	ichneumon.Display();

	return 0;
}