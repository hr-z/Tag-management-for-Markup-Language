#ifndef __TAG_H__
#define __TAG_H__
#include <iostream>
#include <string>

class TagIterator;

class Tag {
    std::string type;   // the type of the tag
    std::string id;     // the id attribute of the tag
    std::string value;  // the value attribute of the tag
    Tag *parent;        // pointer to the parent tag (or nullptr for the document tag, which does not have a parent)
    Tag **children;     // array of children tag pointers
    int childrenLength;   // current number of children tags
    int childrenCapacity; // current capacity of the children array
    void swap(Tag &other); // swaps all the fields of this tag with other; used for copy/move operations
    void resizeChildren(); // creates the children array with capacity=1 or doubles the capacity of the existing array
  public:
    // Normal constructor
    // - initializes the type field according to the supplied parameter
    // - initializes id and value to ""
    // - initializes parent and children to nullptr
    // - initializes childrenLength and childrenCapacity to zero
    Tag(const std::string &type);

    // Copy constructor
    Tag(const Tag &other);
    // Move constructor
    Tag(Tag &&other);
    // Copy assignment operator
    Tag &operator=(const Tag &other);
    // Move assignment operator
    Tag &operator=(Tag &&other);
    // Destructor
    ~Tag();

    // Returns the value of the type field
    const std::string &getType() const;
    // Returns the value of the id field
    const std::string &getId() const;
    // Sets the value of the id field
    void setId(const std::string &_id);
    // Returns the value of the value field
    const std::string &getValue() const;
    // Sets the value of the value field
    void setValue(const std::string &_value);
    // Returns the value of the parent field
    Tag *getParent() const;
    // Sets the value of the parent field
    void setParent(Tag *_parent);

    // Prints this tag to out in the following format:
    // <type id='id' value='value'>
    //   ...children
    // </type>
    // For each children level, the indentLevel is increased.
    // For each indentLevel, add two spaces to the beginning of the line
    // If the id or value attributes are empty (""), they are not printed.
    // If this tag does not have children, it doesn't print anything for the ...children line.
    void print(std::ostream &out, int indentLevel = 0) const;

    // Adds other to the children array.
	  // Create or resize the array if needed.
    void addChild(Tag *other);
    // Removes other from the children array.
    // If other is not in the array, does nothing.
    // (Does NOT delete other).
    void removeChild(Tag *other);
    // Returns the first tag in the children array whose type is equal to the supplied parameter.
	  // If no such tag is found, returns nullptr.
    Tag *findChild(std::string &type);
    // Returns the first tag in the children array whose id is equal to the supplied parameter.
	  // If no such tag is found, returns nullptr.
    Tag *findChildId(std::string &id);

    // Returns an iterator to the start of the children array.
    TagIterator begin() const;
    // Returns an iterator past the end of the children array.
    TagIterator end() const;
    friend class TagIterator;
};

class TagIterator {
    Tag **t;                       // pointer to a position in a children array
    int element_No;
    explicit TagIterator(Tag **t); // constructor (initializes t)
  public:
    // Returns the tag that this iterator is currently pointing to
    Tag *operator*() const;
    // Advances the iterator
    TagIterator operator++();
    // Compares this iterator with other; returns true if they point to the same array position.
    bool operator==(const TagIterator &other) const;
    // Compares this iterator with other; returns true if they do not point to the same array position.
    bool operator!=(const TagIterator &other) const;
    friend class Tag;
};

// Prints the tag to out by calling its print() method.
std::ostream &operator<<(std::ostream &out, const Tag &tag);

#endif
