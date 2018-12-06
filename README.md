# simple-key-value-in-memory-DBMS
A simple key-value in-memory DBMS (database management system, which keeps everything in RAM). In the very simple case is a hash table. Implementation example is MongoDB, the MongoDB interface is also taken as an example.

## Fields data
You can specify data fields while creating table or add it later after creating

*To specify field type you should write name of field and than type of it in following format*
```
    // example
    {name: string}
    // or you can specify few fields together
    {name: string, age: int}
```

In each cases data (for looking for or for insert) should be writen in "{}" brackets in format **key: value**

```
    // example
    {name: "Misha"}
``` 
You can also write few keys in one brackets
```
    //example
    {name: "Misha", age: 18,...}
```

When you are looking for some specific row always try to specify looking data as much as you can

```
    // bad example
    exampleTable.getOneRow({name: "Misha"}) // will find first row with value "Misha" in name field
    // good example
    exampleTable.getOneRow({name: "Misha", age: 18, gender: "male", ...}
```
**Note:** Every inserted data should be the same type as it mentioned while creating otherwise it will cause an error
```
    createTable("tableExample", {name: string})
    // bad example
    tableExample.insert({name: 123}) // will cause an error
    // good example 
    tableExample.insert({name: "Misha"})
```

## Data types

Data type | Description
--------- | -------
short (2 bytes) | –32767 to 327677
int (4 bytes) | −2 147 483 647 to 2 147 483 647
float (4 bytes) | +/- 3.4E-38 to 3.4E+38
tinytext (255 bytes)| Holds a string with a maximum length of 255 characters
text | Can contain any text
bool | Can contain only **true** or **false** value 

## Default values
*The values wich becames fields by default if they are not specified*

Data type | Default value
--------- | -------
short  | 0
int  | 0
float | 0
tinytext | ""
text | ""
bool | false 

**NOTE:**
Each text values should be written in quotes
```
    // example
    "Misha"
    "Kyiv"
```

## Commands
##### Create Table:
```
    createTable("name"[, fields])
    // example
    createTable("exampleTable")
    // or
    createTable("exampleTable", {name: string, age: int})
``` 
##### Drop Table:
```
    dropTable(tableName)
    // example
    dropTable("exampleTable")
```

##### Add fields to table 

```
    tableName.addFields({name: dataType[, age: dataType]})
    // example
    // you can add one
    exampleTable.addFields({lastName: string})
    // or few fields
    exampleTable.addFields({lastName: string, growth: double})
```

##### Delete fields from table 

```
    tableName.deleteFields(lastName[, growth]}")
    // example
    // you can delete one
    exampleTable.deleteFields(lastName)
    // or few fields
    exampleTable.deleteFields(lastName, growth)
```

##### Insert data to table 
     
 *You can insert data for one or many fields*
 
 **Note:** if you don't set value for field that is in table 
 it's value became to default value (Table above)
```
    tableName.insert({name: "Misha"[, age: 18]})
    // example
    exampleTable.insert({name: "Misha"})
    // or
    exampleTable.insert({name: "Misha", age: 18})    
```

##### Get all data from table 

```
    tableName.getAll()
    // example
    exampleTable.getAll()
```

##### Get one row by field value

*Returns first founded row according to looking data*

***Note, that if you pass empty data an error will occur***

```
    tableName.getOneRow({name: "Misha"[, age: 18]})
    // example
    exampleTable.getOneRow({name: "Misha"})
    // or
    exampleTable.getOneRow({name: "Misha, age: 18"})
```

##### Get few rows by field value

*Returns all founded rows according to looking data*

***Note, that if you pass empty data an error will occur***

```
    tableName.getRows({name: "Misha"[, age: 18]})
    // example
    exampleTable.getRows({name: "Misha"})
    // or
    exampleTable.getRows({name: "Misha, age: 18"})
```

##### Change data for one row

*Change first founded row data according to looking data*

```
    tableName.changeOneRowData(fieldsToFind, newFieldsValue)
    // example 
    exampleTable.changeOneRowData({name: "Misha"}, {name: "Mike"});
    // or
    exampleTable.changeOneRowData({name: "Misha"}, {name: "Mike", age: 19});
    // or
    exampleTable.changeOneRowData({name: "Misha", age: "18"}, {name: "Mike", age: 19});
```

##### Change data for few rows

*Change all founded rows data according to looking data*

```
    tableName.changeData(fieldsToFind, newFieldsValue)
    // example 
    exampleTable.changeData({name: "Misha"}, {name: "Mike"});
    // or
    exampleTable.changeData({name: "Misha"}, {name: "Mike", age: 19});
    // or
    exampleTable.changeData({name: "Misha", age: "18"}, {name: "Mike", age: 19});
```

##### Delete one row

*Delete first founded row according to looking data*
```
    tableName.deleteRow(fieldsToFinds)
    // example 
    exampleTable.deleteRow({name: "Misha"});
    // or
    exampleTable.deleteRow({name: "Misha", age: "18"});
```

##### Delete few rows

*Delete all founded rows according to looking data*
```
    tableName.deleteRows(fieldsToFinds)
    // example 
    exampleTable.deleteRows({name: "Misha"});
    // or
    exampleTable.deleteRows({name: "Misha", age: "18"});
```

