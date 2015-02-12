#include "data.hpp"

/*
COORDS
*/

const u_int CelestialCoord::MAX_AZIMUTH = 360;
const u_int CelestialCoord::MIN_AZIMUTH = 0;
const u_int CelestialCoord::MAX_ZENITH = 180;
const u_int CelestialCoord::MIN_ZENITH = 0;

CelestialCoord::CelestialCoord() {
	azimuth = MIN_AZIMUTH;
	zenith = MIN_ZENITH;
}

CelestialCoord::CelestialCoord(u_int azimuth, u_int zenith) {
	if (azimuth < MIN_AZIMUTH) this->azimuth = MIN_AZIMUTH;
	else if (azimuth > MAX_AZIMUTH) this->azimuth = MAX_AZIMUTH;
	else this->azimuth = azimuth;

	if (zenith < MIN_ZENITH) this->zenith = MIN_ZENITH;
	else if (zenith > MAX_ZENITH) this->zenith = MAX_ZENITH;
	else this->zenith = zenith;
}

CelestialCoord::CelestialCoord(const CelestialCoord &coord) {
	azimuth = coord.azimuth;
	zenith = coord.zenith;
}

CelestialCoord& CelestialCoord::operator= (const CelestialCoord &coord) {
	azimuth = coord.azimuth;
	zenith = coord.zenith;
	return (*this);
}

bool CelestialCoord::operator== (const CelestialCoord& c) const {
	return azimuth == c.azimuth && zenith == c.zenith;
}

/*
STAR
*/

const u_int Star::MAX_MAGNITUDE = 6;
const u_int Star::MIN_MAGNITUDE = 1;

Star::Star() {
	name = std::string();
	location = CelestialCoord();
	magnitude = MIN_MAGNITUDE;
}

Star::Star(const std::string &name, const CelestialCoord &location, u_int magnitude) {
	this->name = name;
	this->location = location;

	if (magnitude < MIN_MAGNITUDE) this->magnitude = MIN_MAGNITUDE;
	else if (magnitude > MAX_MAGNITUDE) this->magnitude = MAX_MAGNITUDE;
	else this->magnitude = magnitude;
}

Star::Star(const Star& star) {
	name = star.name;
	location = star.location;
	magnitude = star.magnitude;
}

bool Star::operator== (const Star& s) const {
	return name == s.name && location == s.location && magnitude == s.magnitude;
}