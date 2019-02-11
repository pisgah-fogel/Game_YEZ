#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stdexcept>

#include "Log.hpp"
#include "Config.hpp"

/*!
 * \brief Verifie si un caractère est alpha numérique
 *
 * Le caractère peur une lettre, majuscule et minuscule,
 * un chiffre ainsi que '_', '/' '\' ou '.'
 *
 * \param c caractère à tester
 * \return true si le caractère est alpha numérique, false
 * sinon
 */
bool isAlphaNum(char c)
{
	register bool a = false;
	if (c>='a' && c<='z')
		a = true;
	else if (c>='A' && c<='Z')
		a = true;
	else if (c>='0' && c<='9')
		a = true;
	else if (c=='_' || c=='-' || c=='/' || c=='\\' || c=='.' || c==',')
		a = true;
	return a;
}

bool isIntStr(std::string str)
{
	char c;
	if (str.rfind("0x", 0) == 0) {
		for (size_t i=2; i<str.size(); i++) {
			c = str.at(i);
			if ((c<'a' || c>'z') && (c<'0' || c>'9'))
				return false;
		}
	}
	else if (str.rfind("0b", 0) == 0) {
		for (size_t i=2; i<str.size(); i++) {
			c = str.at(i);
			if (c!='0' && c!='1')
				return false;
		}
	}
	else {
		for (size_t i=0; i<str.size(); i++) {
			c = str.at(i);
			if ((c<'0' || c>'9') && c!='-')
				return false;
		}
	}
	return true;
}

int strToInt(std::string str)
{
	int b = 0;
	if (str.rfind("0b", 0) == 0) {
		str.erase(str.begin());
		str.erase(str.begin());
		b = std::stoi(str,nullptr,2);
	}
	else if (str.rfind("0x", 0) == 0) {
		b = std::stoi(str,nullptr,16);
	}
	else {
		b = std::stoi(str);
	}
	return b;
}

bool isFloatStr(std::string str)
{
	char c;
	for (size_t i=0; i<str.size(); i++) {
		c = str.at(i);
		if ((c<'0' || c>'9') && c!='.' && c!=',' && c!='E' && c!='-')
			return false;
	}
	return true;
}

bool utils::Config::parseYEZ(const char* filename)
{
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	size_t i = 0;
	ssize_t z;
	std::string a, b, c;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		LOG("Error Open file %s", filename);
		return false;
	}	

	while ((read = getline(&line, &len, fp)) != -1) {
		z=0;
		a.clear();
		b.clear();
		c.clear();
		while(z<read && not isAlphaNum(line[z]))
			z++; // ignorer les caractères non alpha numériques

		while(z<read && isAlphaNum(line[z])) {
			a.push_back(line[z]);
			z++;
		}

		while(z<read && not isAlphaNum(line[z]))
			z++; // ignorer les caractères non alpha numériques

		while(z<read && isAlphaNum(line[z])) {
			b.push_back(line[z]);
			z++;
		}

		while(z<read && not isAlphaNum(line[z]))
			z++; // ignorer les caractères non alpha numériques

		while(z<read && isAlphaNum(line[z])) {
			c.push_back(line[z]);
			z++;
		}
		i++;
		if (b.size()==0 || c.size()==0) {
			LOG("Error in config file %s l.%d", filename, i);
			LOG("> %s", line);
			LOG(" - Expect an eguality");
		}
		else if (a == "string") {
			u_string_map[b]=c;
		}
		else if (a == "int") {
			if (not isIntStr(c)) {
				LOG("Error in config file %s l.%d", filename, i);
				LOG("> %s", line);
				LOG(" - %s is not a valid int", c.c_str());
				LOG(" W: decimal, hexadecimal and binaries format are supported");
				continue;
			}
			try {
				u_int_map[b] = strToInt(c);
			} catch (const std::out_of_range& oor) {
				LOG("Error in config file %s l.%d", filename, i);
				LOG("> %s", line);
				LOG(" - %s is out of range", c.c_str());
			}
		}
		else if (a == "float") {
			if (not isFloatStr(c)) {
				LOG("Error in config file %s l.%d", filename, i);
				LOG("> %s", line);
				LOG(" - %s is not a valid float", c.c_str());
				continue;
			}
			try {
				u_float_map[b] = std::stof(c);
			} catch (const std::out_of_range& oor) {
				LOG("Error in config file %s l.%d", filename, i);
				LOG("> %s", line);
				LOG(" - %s is out of range", c.c_str());
			}
		}
		else {
			LOG("Error in config file %s l.%d", filename, i);
			LOG("> %s", line);
			LOG(" - No type %s", a.c_str());
		}
	}
	fclose(fp);
	LOG("Ok %d lines read from %s", i, filename);
	if (line)
		free(line);
	return true;
}
