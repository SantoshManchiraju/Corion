/*
 * CObjectDatabase.h
 *
 *  Created on: Aug 22, 2017
 *      Author: bob
 */

#ifndef SRC_VISION_COBJECTDATABASE_H_
#define SRC_VISION_COBJECTDATABASE_H_

#include <vector>
#include <map>
#include <string>

struct object_t {
	int key;
	std::string name;
	bool isUpToDate;
};

class CObjectDatabase {
private:
	std::vector<object_t> m_data;
	std::string m_file;
	int m_key;

	int getKey(std::string& object);
public:
	CObjectDatabase(std::string fileName);
	~CObjectDatabase();

	void loadDBfromFile();
	void writeDBtoFile();
	void addObjectToDB(std::string objectName);
	void setUpToDateStatus(std::string objectName, bool status);
	const std::vector<object_t>& getData() const;
};

#endif /* SRC_VISION_COBJECTDATABASE_H_ */
