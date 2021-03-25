# Custom String Class
This project includes a simplified string class, this class does not include any part of `std::string` in the implementation.

Below is the interface that my class must provide.

```
class String {
    String(const String &aString, size_t aPresize=0);
    String(const char* aBuffer, size_t aPresize=0);
    ~String();
    String& operator=(const String &aCopy);
    String& operator=(const char* aBuffer);
    
    //accessors...
    size_t size() const;    

    //mutation methods...
    char&       operator[](int pos);
  
    String  operator+(const String &aString);  //append (construct) methods
    String  operator+(const char* aBuffer);
    
    String& operator+=(const String &aString);  //append (to self) methods
    String& operator+=(const char* aBuffer);

    String& insert(size_t anIndex, const String &aString, size_t aMaxCopyLen);
    String& insert(size_t anIndex, const char* aString, size_t aMaxCopyLen);
      
    String& replace(size_t anIndex, size_t aMaxCopyLen, const String &aSubString);
    String& replace(size_t anIndex, size_t aMaxCopyLen, const char *aSubString);
        
    String& erase(size_t anIndex, size_t aCount); //from given position, remove N chars...("cut")
    
      //Comparision methods...
    int compare( const String& aString ) const; //[-1 if <, 0 if ==, 1 if >]
    
    bool operator==(const String &aString) const;
    bool operator==(const char* aBuffer) const;

    bool operator<(const String &aString) const;
    bool operator<(const char* aBuffer) const;

      //Search...
    int find( const String &aSubString, size_t anOffset = 0 ) const;
              
      //stream...
    friend std::ostream& operator << (std::ostream &out, const String &aStr);
    friend std::istream& operator >> (std::istream &in,  String &aString);      
}
```

## String Method Details (Implementation details for key methods listed above):

### OCF

### `String& operator=(const char* aBuffer);`
An assignment operator that accepts a `const char*`. 
  
### `size_t size()`; 
The `size()` method returns the current length of the underlying string.

### `char& operator[](size_t anIndex);` 
This method permits the caller to access a character at a given index. This method must guard against out-of-bounds accesses (0<=index<length). Should an out-of-bounds error occur, `String` will throw a `std::out_of_range` exception.

### `String  operator+(const String &aString);`
This method creates and returns a new string, equivalent to the given `aString` arugment appended to the string object in scope.

### `String  operator+(const char* aBuffer);`
Same as above, but accepts a `const char*` for backward compatiability.

### `String& operator+=(const String &aString);`
This overload operator (`+=`) appends the given `aString` argument to the existing string.  Return a reference to `*this`. 

### `String& operator+=(const char* aBuffer);`
Same as above, but accepts a `const char*` for backward compatiability.
         
### `String& insert(size_t anIndex, const String &aString, size_t aMaxCopyLen)`
This methods allows a caller to insert the given `aString` argument into the current string at a given `anIndex`. The 3rd argument (`anInsertLimit`) allows the caller to limit the number of characters from the given `aString` argument that are inserted in the string in scope. For example, if given `aString` said "Hello there", and I only want to insert "Hello", I would pass 5 as the last argument. If the last argument is 0, it means to insert all the characters from the given string.

### ` String& insert(size_t anIndex, const char* aString, size_t aMaxCopyLen);`
Same as above, but accepts a `const char*` for backward compatiability.
   
### `String& replace(size_t anIndex, size_t aMaxCopyLen, const String &aSubString);`
This method replaces a portion of the current string object with the contents given in `aSubString`, starting at anIndex.  The `aMaxCopyLen` allows the caller to pass a longer string (as a replacement) but only copy a portion of that `aSubString` into the current string. If the caller passes a `aMaxCopyLen` as "0", then the entire contents of `aSubString` will be inserted as the replacement in the current string.

### `String& replace(size_t anIndex, size_t aMaxCopyLen, const char *aBuffer);`
Same as above, but accepts a `const char*` for backward compatiability.

### `String& erase(size_t anIndex, size_t aCount);`
This method causes `aCount` characters in the underlying string to be removed starting at `anIndex`. It is not considered an error if the `aCount` size extends past the end of the underlying string. With right arguments, this method can be used to remove characters from the middle of the string, or to truncate the string, which discards all characters after a certain point.   
 
### `int compare( const String& str ) const;`
This method compares the given `aString` against the string in scope. We use the familiar results (from C) to indicate how the cast-sensitive strings compare lexographically. Return -1 if `*this` string is less than the given string. Return 0 if they're equal, and return 1 if `*this*` string is greater than the given `aString`.  
  
### `bool operator==(const String &aString) const;`
This Method return `true` `*this` this is equal to the given `aString`. 

### `bool operator==(const char* aBuffer) const;`
Same as above, but accepts a `const char*` for backward compatiability.

//NOTE: Follow a similar pattern for operator<()...

### `int find( const String &aSubString, size_type anOffset = 0 ) const;`
This method attempts to local the given `aSubString` within `*this` string, starting a given `anOffset`, searching left to right. If found, return the index associated with the index of the first matching chararater.  Return -1 if no match it found.

## BufferManager Class Details

`BufferManager` class is a delegate class that will actually manage the data buffer that holds string data. The `BufferManager` class is the interface the string class will use to do memory management related operations.
