#ifndef H_DATA
#define H_DATA

#include <boost/archive/binary_iarchive.hpp>

typedef unsigned int u_int;

/*
COORDS
*/
class CelestialCoord {
public:
	CelestialCoord();

	CelestialCoord(u_int azimuth, u_int zenith);

	CelestialCoord(const CelestialCoord &coord);

	CelestialCoord& operator= (const CelestialCoord &coord);

	bool operator== (const CelestialCoord&) const;

	inline u_int getAzimuth() const { return azimuth; }

	inline u_int getZenith() const { return zenith; }
private:
	friend class boost::serialization::access;

	template <class Archive>
	void serialize(Archive &archive, const u_int version);

public:
	// ranges
	static const u_int MAX_AZIMUTH;
	static const u_int MIN_AZIMUTH;
	static const u_int MAX_ZENITH;
	static const u_int MIN_ZENITH;

private:
	// data
	u_int azimuth;
	u_int zenith;
};

template <class Archive>
void CelestialCoord::serialize(Archive &archive, const u_int version) {
	archive & azimuth;
	archive & zenith;
}

/*
STAR
*/
class Star {
public:
	Star();

	Star(const std::string &name, const CelestialCoord &location, u_int magnitude);

	Star(const Star& star);

	bool operator== (const Star&) const;

	inline const std::string& getName() const { return name; }

	inline const CelestialCoord& getLocation() const { return location; }

	inline u_int getMagnitude() const { return magnitude; }

	inline void setName(const std::string &name) { this->name = name; }

	inline void setLocation(const CelestialCoord &location) { this->location = location; }

	inline void setMagnitude(u_int) { this->magnitude = magnitude; }
private:
	friend class boost::serialization::access;

	template <class Archive>
	void serialize(Archive &archive, const u_int version);

public:
	// ranges
	static const u_int MAX_MAGNITUDE;
	static const u_int MIN_MAGNITUDE;

private:
	// data
	std::string name;
	CelestialCoord location;
	u_int magnitude;
};

template <class Archive>
void Star::serialize(Archive &archive, const u_int version) {
	archive & name;
	archive & location;
	archive & magnitude;
}

#endif // !H_DATA
