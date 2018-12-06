# simple-key-value-in-memory-DBMS
A simple key-value in-memory DBMS (database management system, which keeps everything in RAM). In the very simple case is a hash table. Implementation example is MongoDB, the MongoDB interface is also taken as an example.

## Fields data
You can specify data fields while creating table or add it later after creating

*To specify field type you should write name of field and than type of it in following format*
```
    {name: string}
    // or you can specify few fields together
    {name: string, age: int}
```

In each cases data (for looking for or for insert) should be writen in "{}" brackets in format **key: value**

```
    {name: "Misha"}
``` 
You can also write few keys in one brackets
```
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
    "Misha"
    "Kyiv"
```

## Commands
#### createTable(tableName[, fields]...)
*Creates table*
```
    createTable("exampleTable")
    // or
    createTable("exampleTable", {name: string, age: int})
``` 
#### dropTable(tableName)
*Deletes table*
```
    dropTable("exampleTable")
```

#### tableName.addFields({fieldName: dataType[, age: dataType]...})
*Adds field to table*
```
    // you can add one
    exampleTable.addFields({lastName: string})
    // or few fields
    exampleTable.addFields({lastName: string, growth: double})
```

#### tableName.deleteFields(fieldName[, fieldName]...})
*Deletes fields from table*

**NOTE:** it will delete fields from **ALL** rows
```
    // you can delete one
    exampleTable.deleteFields(lastName)
    // or few fields
    exampleTable.deleteFields(lastName, growth)
```

#### tableName.insert({fieldName: value[, fieldName: value]})
 *Inserts data to table*    
 *You can insert data for one or many fields*
 
 **Note:** if you don't set value for field that is in table 
 it's value became to default value (Table above)
```    
    exampleTable.insert({name: "Misha"})
    // or
    exampleTable.insert({name: "Misha", age: 18})    
```

#### tableName.getAll()
*Returns all rows from table*

```
    exampleTable.getAll()
```

#### tableName.getOneRow({fieldName: value[, fieldName: value]...})
*Returns first founded row according to looking data*

**Note**: if you pass empty data an error will occur

```
    exampleTable.getOneRow({name: "Misha"})
    // or
    exampleTable.getOneRow({name: "Misha, age: 18})
```

#### tableName.getRows({fieldName: value[, fieldName: value]...})

*Returns all founded rows according to looking data*

**Note**: if you pass empty data an error will occur

```
    exampleTable.getRows({name: "Misha"})
    // or
    exampleTable.getRows({name: "Misha, age: 18})
```

#### tableName.changeOneRowData(fieldsToFind, newFieldsValue)

*Change first founded row data according to looking data*

```
    exampleTable.changeOneRowData({name: "Misha"}, {name: "Mike"});
    // or
    exampleTable.changeOneRowData({name: "Misha"}, {name: "Mike", age: 19});
    // or
    exampleTable.changeOneRowData({name: "Misha", age: 18}, {name: "Mike", age: 19});
```

#### tableName.changeData(fieldsToFind, newFieldsValue)

*Change all founded rows data according to looking data*

```
    exampleTable.changeData({name: "Misha"}, {name: "Mike"});
    // or
    exampleTable.changeData({name: "Misha"}, {name: "Mike", age: 19});
    // or
    exampleTable.changeData({name: "Misha", age: 18}, {name: "Mike", age: 19});
```

#### tableName.deleteRow(fieldsToFinds)

*Delete first founded row according to looking data*
```
    exampleTable.deleteRow({name: "Misha"});
    // or
    exampleTable.deleteRow({name: "Misha", age: 18});
```

#### tableName.deleteRows(fieldsToFinds)

*Delete all founded rows according to looking data*
```
    exampleTable.deleteRows({name: "Misha"});
    // or
    exampleTable.deleteRows({name: "Misha", age: 18});
```
