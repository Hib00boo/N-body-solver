#include "AstroSim.cpp"


int main() {
	System solarSys = System("solar system");
	solarSys.addPlanet("mars", MARS_MASS, 0.0, 0.0, 0.0);
	solarSys.addSatellite("vanguard", 80, 1.0, 6.0, 7.0);



	Planet* mars = dynamic_cast<Planet*>   (solarSys.celestialObjects[0].get());
	Satellite* vanguard = dynamic_cast<Satellite*>(solarSys.celestialObjects[1].get());


	//std::cout << solarSys.computeFg(mars, vanguard);
	auto v = solarSys.computeFgVector(mars, vanguard);

	for (auto i : v) { std::cout << i << "\n"; };

	solarSys.plotSystem("Solar System", "X", "Y", "Z", true, true, mars, vanguard);

	return 0;
}
