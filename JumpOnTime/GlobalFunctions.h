#pragma once
#ifndef GLOBALFUNCS_H
#define GLOBALFUNCS_H

#include <string>
#include <sstream>
#include <random>

template <class T>
static std::string ToString(T From) {
	std::stringstream SStream;
	SStream << From;
	return SStream.str();
}

static int RandInt(int UniformLower, int UniformUpper) {
	static std::random_device RD;
	static std::default_random_engine RandomEngine(RD());
	std::uniform_int_distribution<int> Uniform(UniformLower, UniformUpper);
	return Uniform(RandomEngine);
};

#endif
