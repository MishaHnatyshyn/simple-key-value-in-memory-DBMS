#include "Row.h"
#include "DBMSError.h"
#include <map>
#include <unordered_map>
#include <iterator>

class Table {
private:
    unordered_map<int, Row> table;
    vector<string> fields_name;
    vector<string> types;
    int last_index;
    string name;
    unordered_map<int, Row>::iterator itr;
public:
    Table(vector<Data> data, string name);

    string getName();

    void display();

    void update(int id, Data data);

    void update(int id, vector<Data> options_update);

    void update(Data queryData, Data updateData);

    void update(Data queryData, vector<Data> updateData);

    void update(vector<Data> queryData, Data updateData);

    void update(vector<Data> queryData, vector<Data> updateData);

    void updateOne(vector<Data> queryData, vector<Data> updateData);

    void add(Row row);

    void remove(int id);

    void remove(Data data);

    void remove(vector<Data> data);

    void removeOne(vector<Data> data);

    int getIndex(Data data);

    int getIndexOfOne(vector<Data> options);

    vector<int> getIndex(vector<Data> options);

    int getFieldIndex(string field_name);

    void add(vector<Data> data);

    Row* findById(int id);

    vector<Row*> findManyByOneOption(string field_name, string value);

    Row* findOneByOneOption(string field_name, string value);

    vector<Row*> findManyBySeveralOptions(vector<Data> options);

    Row* findOneBySeveralOptions(vector<Data> options);
};

