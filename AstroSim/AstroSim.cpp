// AstroSim.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <matplot/matplot.h>
#include <vector>
#include <string>
#include <cmath>
#include <memory>

const double MARS_MASS = 0.64169e24;
const double G_CONST = 6.67430e-11;

class Object {
public:
	Object() {};
	Object(std::string name, double objectMass, double x, double y, double z) {
		objectName = name;
		mass       = objectMass;
		positionX  = x;
		positionY  = y;
		positionZ  = z;
	};

	virtual ~Object() = default;

	// All objects have a name and a position
	std::string objectName;
	double positionX = 0;
	double positionY = 0;
	double positionZ = 0;

	double mass = 0;

	virtual void identifySelf() = 0;
	virtual void statePosition() = 0;
};

class Planet : public Object {
public:
	Planet(std::string name, double mass, double x, double y, double z) : Object(name, mass, x, y, z) {
		mass = mass;
		std::cout << "A planet has been created : " << name << '\n';
	}

	// TODO : update formatting
	void identifySelf() {
		std::cout << "Planet " << objectName << " has a mass of " << mass << " kg.\n";
	}

	// TODO : update formatting
	void statePosition() {
		std::cout << objectName << " : My position is at X = " << positionX << ", Y = " << positionY << " , Z = " << positionZ << " .\n\n";
	}
};

class Satellite : public Object {
public:
	Satellite(std::string name, double mass, double x, double y, double z) : Object(name, mass, x, y, z) {
		mass = mass;
		std::cout << "A satellite has been created : " << name << "\n";
		identifySelf();
		statePosition();
	}
	// TODO : update formatting
	void identifySelf() {
		std::cout << "Satellite " << objectName << " has a mass of " << mass << " kg.\n";
	}

	// TODO : update formatting
	void statePosition() {
		std::cout << objectName << " : My position is at X = " << positionX << ", Y = " << positionY << " , Z = " << positionZ << " .\n\n";
	}
};

// System class holds information on all of the positions and velocities of every body it holds
class System {
public:
	System(std::string name) {
		systemName = name;
		std::cout << "A system has been created : " << name << "\n";
	};

	// Creates a planet and adds it to the system
	void addPlanet(std::string name, double mass, double x, double y, double z) {
		auto newPlanet = std::make_unique<Planet>(name, mass, x, y, z);
		celestialObjects.push_back(std::move(newPlanet));
		// TODO : optimise 
		x_positions.push_back(x);
		y_positions.push_back(y);
		z_positions.push_back(z);
		std::cout << "Added planet " << name << " to the system.\n";
	}
	// Creates a satellite and adds it to the system
	void addSatellite(std::string name, float mass, double x, double y, double z) {
		auto newSatellite = make_unique<Satellite>(name, mass, x, y, z);
		celestialObjects.push_back(move(newSatellite));
		x_positions.push_back(x);
		y_positions.push_back(y);
		z_positions.push_back(z);
		std::cout << "Added satellite " << name << " to the system.\n";
	}

	// TODO : plot fg droite
	// Computes the gravitational force between two astral bodies
	template <typename T, typename S> double computeFg(T* a, S* b) {
		std::vector<double> r;
		double x = b->positionX - a->positionX;
		double y = b->positionY - a->positionY;
		double z = b->positionZ - a->positionZ;

		double rNorm = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

		double gravForce = -((G_CONST * a->mass * b->mass) / pow(rNorm, 2.0));

		return gravForce;
	}

	template <typename T, typename S> std::vector<double> computeFgVector(T* a, S* b) {
		double x = b->positionX - a->positionX;
		double y = b->positionY - a->positionY;
		double z = b->positionZ - a->positionZ;
		std::vector<double> r{x, y, z};

		double rNorm = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

		double force = -((G_CONST * a->mass * b->mass) / pow(rNorm, 3.0));

		std::for_each(r.begin(), r.end(), [force](double& position) {
			position *= force;
			});

		return r;
	}

	// TODO : add droite option
	template <typename T, typename S>
	void plotSystem(std::string title, std::string x_label, std::string y_label, std::string z_label, bool isGrid,
		bool hasFgArrow, T* objectA, S* objectB)
	{
		// TODO : Make customisable
		std::vector<double> sizes(x_positions.size() * 2, 16);

		// Create a scatter plot with additional customization
		matplot::scatter3(x_positions, y_positions, z_positions, sizes);

		if (hasFgArrow) {
			auto fgVector = computeFgVector(objectA, objectB);
			matplot::hold(true);

			matplot::quiver3(
				std::vector<double>{objectB->positionX},
				std::vector<double>{objectB->positionY},
				std::vector<double>{objectB->positionZ},
				std::vector<double>{fgVector[0]},
				std::vector<double>{fgVector[1]},
				std::vector<double>{fgVector[2]});

		matplot::hold(false);
		}

		matplot::title(title);
		matplot::xlabel(x_label);
		matplot::ylabel(y_label);
		matplot::zlabel(z_label);
		matplot::grid(isGrid);

		double xMax = *std::max_element(x_positions.begin(), x_positions.end()) * 10;
		double yMax = *std::max_element(y_positions.begin(), y_positions.end()) * 10;
		double zMax = *std::max_element(z_positions.begin(), z_positions.end()) * 10;

		matplot::xlim({ -xMax, xMax });
		matplot::ylim({ -yMax, yMax });
		matplot::zlim({ -zMax, zMax });

		matplot::show();
	}

	std::string systemName;
	std::vector<std::unique_ptr<Object>> celestialObjects; // All the objects in the system will be held in here
	std::vector<double> x_positions;
	std::vector<double> y_positions;
	std::vector<double> z_positions;

};
