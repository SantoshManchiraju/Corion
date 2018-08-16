/*
 * CObjectDatabase.cpp
 *
 *  Created on: Aug 22, 2017
 *      Author: bob
 */

#include "CObjectDatabase.h"
#include "../logger/Logger.h"

#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>

CObjectDatabase::CObjectDatabase(std::string fileName) {
	m_file = fileName;
	loadDBfromFile();
}

CObjectDatabase::~CObjectDatabase() {

}

void CObjectDatabase::loadDBfromFile() {
	std::string temp;
	std::ifstream infile;
	int key = 0;

	infile.open(m_file);
	while (getline(infile, temp, '\t')) {
		object_t tempObj;
		tempObj.key = stoi(temp);
		getline(infile, temp, '\t');
		tempObj.name = temp;
		getline(infile, temp);
		std::istringstream(temp) >> tempObj.isUpToDate;

		m_data.push_back(tempObj);
		LOG_INFO("inserted pair: " + std::to_string(key) + "  " + temp);
	}
	m_key = key;
	infile.close();
	LOG_INFO("total entries: " + std::to_string(key));
}

void CObjectDatabase::writeDBtoFile() {
	LOG_DEBUG("Writing DB to file");
	std::ofstream dataFile;
	dataFile.open(m_file, std::ios_base::out);
	for (auto &temp_object : m_data) {
		char updateStatus = '0';
		if (temp_object.isUpToDate) {
			updateStatus = '1';
		}
		dataFile << temp_object.key << "\t" << temp_object.name << "\t"
				<< updateStatus << "\n";
	}
	dataFile.close();
}

int CObjectDatabase::getKey(std::string& object) {

	for (auto &temp_object : m_data) {
		if (temp_object.name == object) {
			return temp_object.key;
		}
	}
	return -1;
}

void CObjectDatabase::addObjectToDB(std::string objectName) {
	if (getKey(objectName) == -1) {
		std::ofstream dataFile;
		object_t temp;
		temp.key = ++m_key;
		temp.name = objectName;
		temp.isUpToDate = false;

		m_data.push_back(temp);
	}
}

const std::vector<object_t>& CObjectDatabase::getData() const {
	return m_data;
}

void CObjectDatabase::setUpToDateStatus(std::string objectName, bool status) {
	for (auto &temp_object : m_data) {
		if (temp_object.name == objectName) {
			temp_object.isUpToDate = status;
		}
	}
}
