#include <vector>
#include <string_view>
#include <sstream>
#include <utility> 

using namespace std;
using namespace std::literals;

struct DbParams {
    string_view name;
    int connection_timeout = 0;
    bool allow_exceptions = true;
    DBLogLevel log_level;
};

vector<Person> LoadPersons(const DbParams& params, int min_age, int max_age, string_view name_filter) {
    DBConnector connector(params.allow_exceptions, params.log_level);
    DBHandler db;

    if (params.name.starts_with("tmp."s)) {
        db = connector.ConnectTmp(params.name, params.connection_timeout);
    }
    else {
        db = connector.Connect(params.name, params.connection_timeout);
    }

    if (!params.allow_exceptions && !db.IsOK()) {
        return {};
    }

    ostringstream query_str;
    query_str << "from Persons "s
        << "select Name, Age "s
        << "where Age between "s << min_age << " and "s << max_age << " "s
        << "and Name like '%"s << db.Quote(name_filter) << "%'"s;

    DBQuery query(query_str.str());

    vector<Person> persons;
    persons.reserve(db.RowCount()); //выделение памяти для вектора

    for (auto&& [name, age] : db.LoadRows<string, int>(query)) {
        persons.emplace_back(move(name), age);
    }

    return persons;
}
