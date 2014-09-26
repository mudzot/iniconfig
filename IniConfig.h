#ifndef __INICONFIG_H
#define __INICONFIG_H

#include <map>
#include <string>
#include <vector>

class IniConfig {
public:
	/**
	 * Parse config from ini file
	 * @param filename
	 * @return 0 on success, -1 on file error, line number on parsing error
	 */
	int parse(const std::string& filename);

	/**
	 * Get string config value
	 * @param section
	 * @param name
	 * @param default_value
	 * @return 
	 */
	std::string get(const std::string& section, const std::string& name, const std::string& defaultValue);
	/**
	 * Get all string values with the same name
	 * @param values
	 * @param section
	 * @param name
	 */
	void getAll(std::vector<std::string>& values, const std::string& section, const std::string& name);

	/**
	 * Get long value
	 * @param section
	 * @param name
	 * @param default_value
	 * @return 
	 */
	long getInteger(const std::string& section, const std::string& name, long defaultValue);

	/**
	 * Get double value
	 * @param section
	 * @param name
	 * @param default_value
	 * @return 
	 */
	double getDouble(const std::string& section, const std::string& name, double defaultValue);

	bool getBoolean(const std::string& section, const std::string& name, bool defaultValue);

	/**
	 * Put additional name/value pair, duplicate names allowed
     * @param section
     * @param name
     * @param value
     */
	void putMore(const std::string& section, const std::string& name, const std::string& value);
	
	/**
	 * Put name/value pair, duplicate names not allowed
     * @param section
     * @param name
     * @param value
     */
	void put(const std::string& section, const std::string& name, const std::string& value);

	bool save(const std::string& filename);

private:
	std::map<std::string, std::multimap<std::string, std::string> > _values;
	static int _valueHandler(void* user, const char* section, const char* name, const char* value);
};

#endif  // __INICONFIG_H
