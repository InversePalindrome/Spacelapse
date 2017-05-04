/*
Copyright (c) 2017 InversePalindrome
Spacelapse - ResourceManager.hpp
InversePalindrome.com
*/


#pragma once

#include <map>
#include <memory>
#include <string>


template<typename Resource, typename Identifier>
class ResourceManager
{
public:
	Resource& get(Identifier ID);

	void load(Identifier ID, const std::string& fileName);

private:
	std::map<Identifier, std::unique_ptr<Resource>> resources;
};

template<typename Resource, typename Identifier>
Resource& ResourceManager<Resource, Identifier>::get(Identifier ID)
{
	return *this->resources.at(ID);
}

template<typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::load(Identifier ID, const std::string& fileName)
{
	auto resource = std::make_unique<Resource>();
	resource->loadFromFile(fileName);

	this->resources.insert(std::make_pair(ID, std::move(resource)));
}