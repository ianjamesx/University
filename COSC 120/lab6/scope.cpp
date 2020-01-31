#include <iostream>
#include <iomanip>
using namespace std;

//Ian Thomas

const double PI = 3.14;
const double RATE = .25;

void findArea(float, float&);
void findCircumference(float, float&);

int main() {

	cout << fixed << showpoint << setprecision(2);
	float radius = 12;

	cout << "Main function outer block" << endl;
	cout << "radius is active here" << endl;
	
	{

		float area;
		cout << "Main function outer block" << endl;
		cout << "area and radius are active here" << endl << endl;

		findArea(radius, area);

		cout << "Radius = " << radius << endl;
		cout << "Area = " << area << endl << endl;

	}

	{

		float radius = 10;
		float circumference;

		cout << "Main function second inner block" << endl;
		cout << "radius, circumference, and area are active here" << endl << endl;

		findCircumference(radius, circumference);

		cout << "Radius = " << radius << endl;
		cout << "Circumference = " << circumference << endl << endl;

	}

	cout << "Main function after all calls" << endl;
	cout << "area, radius, and cirfumference are active here" << endl << endl;

	return 0;

}

void findArea(float rad, float& answer) {

	cout << "Area = PI * Radius^2" << endl << endl;
	cout << "radius, area and PI are active here" << endl << endl;

	answer = PI * (rad * rad);

}

void findCircumference(float length, float& distance) {

	cout << "Circumference = 2 * PI * Radius" << endl << endl;
	cout << "length, distance, and PI are active here" << endl << endl;

	distance = 2 * PI * length;

}