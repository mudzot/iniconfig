#include <algorithm>
#include <fstream>
#include "ini.h"
#include "IniConfig.h"

using std::string;

int IniConfig::parse(const string& filename)
{
	return ini_parse(filename.c_str(), _valueHandler, this);
}

string IniConfig::get(const string& section, const string& name, const string& defaultValue)
{
	auto ptrSection = _values.find(section);
	if (ptrSection == _values.end()) {
		return defaultValue;
	}
	auto ptrPair = ptrSection->second.find(name);
	if (ptrPair == ptrSection->second.end()) {
		return defaultValue;
	}
	return ptrPair->second;
}

long IniConfig::getInteger(const string& section, const string& name, long defaultValue)
{
	string valstr = get(section, name, "");
	const char* value = valstr.c_str();
	char* end;
	long n = strtol(value, &end, 0);
	return end > value ? n : defaultValue;
}

double IniConfig::getDouble(const string& section, const string& name, double defaultValue)
{
	string valstr = get(section, name, "");
	const char* value = valstr.c_str();
	char* end;
	double n = strtod(value, &end);
	return end > value ? n : defaultValue;
}

bool IniConfig::getBoolean(const string& section, const string& name, bool defaultValue)
{
	string valstr = get(section, name, "");
	std::transform(valstr.begin(), valstr.end(), valstr.begin(), ::tolower);
	if (valstr == "true" || valstr == "yes" || valstr == "on" || valstr == "1")
		return true;
	else if (valstr == "false" || valstr == "no" || valstr == "off" || valstr == "0")
		return false;
	else
		return defaultValue;
}

void IniConfig::putMore(const string& section, const string& name, const string& value)
{
	_values[section].insert(std::pair<string, string>(name, value));
}

void IniConfig::put(const std::string& section, const std::string& name, const std::string& value)
{
	auto& map = _values[section];
	auto it = map.find(name);
	while (it != _values[section].end() && it->first == name) {
		auto delIt = it;
		++it;
		map.erase(delIt);
	}
	putMore(section, name, value);
}

bool IniConfig::save(const std::string& filename)
{
	std::ofstream ofs;
	ofs.open(filename, std::ios::out);
	if (ofs.good()) {
		for (auto secIt = _values.begin(); secIt != _values.end(); ++secIt) {
			ofs << "[" << secIt->first << "]" << std::endl;
			for (auto it = secIt->second.begin(); it != secIt->second.end(); ++it) {
				ofs << it->first << " = " << it->second << std::endl;
			}
			ofs << std::endl;
		}
	}
}

int IniConfig::_valueHandler(void* user, const char* section, const char* name, const char* value)
{
	IniConfig* reader = (IniConfig*) user;
	std::multimap<string, string>& sectionMap = reader->_values[section];
	sectionMap.insert(std::pair<string, string>(string(name), string(value)));
	return 1;
}
