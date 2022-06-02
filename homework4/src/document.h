#pragma once

class document {
public:
	document(const std::string& name) {}
	
private:
	std::string m_name;
	std::string m_data;
	int m_fileSize;
};