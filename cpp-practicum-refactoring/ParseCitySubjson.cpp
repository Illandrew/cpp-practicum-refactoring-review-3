#include <string>
#include <vector>
using namespace std;

using Language = string;
struct Country {
    string name;
    string iso_code;
    string phone_code;
    string time_zone;
    vector<Language> languages;
};

// Дана функция ParseCitySubjson, обрабатывающая JSON-объект со списком городов конкретной страны:
static void ParseCitySubjson(vector<City>& cities, const Json& json, const Country& country) {
    for (const auto& city_json : json.AsList()) {
        const auto& city_obj = city_json.AsObject();
        cities.emplace_back(City{
            city_obj["name"s].AsString(),
            city_obj["iso_code"s].AsString(),
            country.phone_code + city_obj["phone_code"s].AsString(),
            country.name,
            country.iso_code,
            country.time_zone,
            country.languages
            });
    }
}

// ParseCitySubjson вызывается только из функции ParseCountryJson следующим образом:
static void ParseCountryJson(vector<Country>& countries, vector<City>& cities, const Json& json) {
    for (const auto& country_json : json.AsList()) {
        const auto& country_obj = country_json.AsObject();
        countries.emplace_back(Country{
            country_obj["name"s].AsString(),
            country_obj["iso_code"s].AsString(),
            country_obj["phone_code"s].AsString(),
            country_obj["time_zone"s].AsString()
            });

        Country& country = countries.back();
        for (const auto& lang_obj : country_obj["languages"s].AsList()) {
            country.languages.push_back(FromString<Language>(lang_obj.AsString()));
        }
        ParseCitySubjson(cities, country_obj["cities"s], country);
    }
}