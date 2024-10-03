#include "Hero.h"
#include <iostream>
bool HeroStats::Deserialize(const rapidjson::Value& obj)
{
	Intelligence = (obj["intelligence"].GetInt());
	Strength = (obj["strength"].GetInt());
	Speed = (obj["speed"].GetInt());
	Durability = (obj["durability"].GetInt());
	Power = (obj["power"].GetInt());
	Combat = (obj["combat"].GetInt());
	return true;
}
bool HeroAppearance::Deserialize(const rapidjson::Value& obj)
{
	Gender = obj["gender"].GetString();
	if(obj["race"].IsString())
		Race = obj["race"].GetString();

	const rapidjson::Value& heights = obj["height"];
	for (rapidjson::SizeType i = 0; i < heights.Size(); ++i)
	{
		Height.push_back(heights[i].GetString());
	}

	const rapidjson::Value& weights = obj["weight"];
	for (rapidjson::SizeType i = 0; i < weights.Size(); ++i)
	{
		Weight.push_back(weights[i].GetString());
	}

	EyeColor = obj["eyeColor"].GetString();
	HairColor = obj["hairColor"].GetString();
	return true;
}
bool HeroBio::Deserialize(const rapidjson::Value& obj)
{
	FullName = obj["fullName"].GetString();
	AlterEgos = obj["alterEgos"].GetString();

	const rapidjson::Value& aliases = obj["aliases"];
	for (rapidjson::SizeType i = 0; i < aliases.Size(); ++i)
	{
		Aliases.push_back(aliases[i].GetString());
	}
	PlaceOfBirth = obj["placeOfBirth"].GetString();
	FirstAppearance = obj["firstAppearance"].GetString();
	if (obj["publisher"].IsString())
		Publisher = obj["publisher"].GetString();
	Alignment = obj["alignment"].GetString();
	return true;
}
bool HeroWork::Deserialize(const rapidjson::Value& obj)
{
	Occupation = obj["occupation"].GetString();
	Base = obj["base"].GetString();
	return true;
}
bool HeroConnections::Deserialize(const rapidjson::Value& obj)
{
	GroupAffiliation = obj["groupAffiliation"].GetString();
	Relatives = obj["relatives"].GetString();
	return true;
}
bool HeroImages::Deserialize(const rapidjson::Value& obj)
{
	XS = obj["xs"].GetString();
	SM = obj["sm"].GetString();
	MD = obj["md"].GetString();
	LG = obj["lg"].GetString();
	return true;
}

Hero::Hero() : _id(-1)
{ }
Hero::Hero(const rapidjson::Value& obj)
{
	Deserialize(obj);
}
//Hero::~Hero()
//{
//
//}
bool Hero::Equals(Hero other)
{
	return _name == other._name && _id == other._id;
}


bool Hero::Deserialize(const rapidjson::Value& obj)
{
	Id(obj["id"].GetInt());
	Name(obj["name"].GetString());
	//std::cout << Name() << std::endl;

	_powerstats.Deserialize(obj["powerstats"].GetObject());
	_appearance.Deserialize(obj["appearance"].GetObject());
	_biography.Deserialize(obj["biography"].GetObject());
	_work.Deserialize(obj["work"].GetObject());
	_connections.Deserialize(obj["connections"].GetObject());
	_images.Deserialize(obj["images"].GetObject());

	//read object for Stats, Appearance, Bio, etc

	return true;
}

bool Hero::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
{
	//writer->StartObject();

	//writer->String("id");
	//writer->Int(_id);

	//writer->String("name");
	//writer->String(_name.c_str());

	//writer->String("category");
	//writer->String(_category.c_str());

	//writer->String("sales");
	//writer->Double(_sales);

	//writer->EndObject();

	return true;
}