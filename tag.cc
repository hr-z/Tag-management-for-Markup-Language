#include "tag.h"

//Normal constructor
Tag::Tag(const std::string &type): type{type}, id{""}, value{""}, parent{nullptr}, 
                                    children{nullptr}, childrenLength{0}, childrenCapacity{0} {}

//Destructor
Tag::~Tag() {
    if (children) {
        for (int i = 0; i < childrenLength; i++) {
            delete children[i];
        }   
    }
    delete [] children;
      
}

//Copy constructor
Tag::Tag(const Tag & other): type{other.type}, id{other.id}, value{other.value}, 
                             parent{other.parent}, childrenLength{other.childrenLength}, 
                             childrenCapacity{other.childrenCapacity} {
    children = new Tag*[other.childrenCapacity];
    for (int i = 0; i < other.childrenLength; i++) {
        children[i] = new Tag{*other.children[i]};        
        children[i]->parent = this;
    }
    
}

//Move constructor
Tag::Tag(Tag && other): type{other.type}, id{other.id}, value{other.value}, 
                        parent{other.parent}, children{other.children}, 
                        childrenLength{other.childrenLength}, childrenCapacity{other.childrenCapacity} {
                            
    other.parent = nullptr;
    other.children = nullptr;
}

//swap
void Tag::swap(Tag & other) {
    std::string temp;
    temp = type;
    type = other.type;
    other.type = temp;
    temp = id;
    id = other.id;
    other.id = temp;
    temp = value;
    value = other.value;
    other.value = temp;

    Tag *temp_ptr = parent;
    parent = other.parent;
    other.parent = temp_ptr;
    Tag **temp_arr_ptr = children;
    children = other.children;
    other.children = temp_arr_ptr;

    int temp_int = childrenLength;
    childrenLength = other.childrenLength;
    other.childrenLength = temp_int;
    temp_int = childrenCapacity;
    childrenCapacity = other.childrenCapacity;
    other.childrenCapacity = temp_int;

}

//Copy assignment operator
Tag &Tag::operator=(const Tag & other) {
    Tag temp = other;
    swap(temp);
    return *this;
}

//Move assignment operator
Tag &Tag::operator=(Tag &&other) {
    swap(other);
    return *this;
}

//resize
void Tag::resizeChildren(){
    if (!children) {
        children = new Tag*[1];
        childrenCapacity = 1;
    } else {
        Tag **new_children = new Tag*[childrenCapacity*2];
        for (int i = 0; i < childrenLength; i++) {
            new_children[i] = children[i];
        }
        delete[] children;
        children = new_children;
        childrenCapacity *= 2;
    }
}

//type getter
const std::string &Tag::getType() const {
    return type;
}

//id getter
const std::string &Tag::getId() const {
    return id;
}

//id mutator
void Tag::setId(const std::string &_id) {
    id = _id;
}

//value getter
const std::string &Tag::getValue() const {
    return value;
}

//value mutator
void Tag::setValue(const std::string &_value) {
    value = _value;
}

//parent getter
Tag *Tag::getParent() const {
    return parent;
}

//parent mutator
void Tag::setParent(Tag *_parent) {
    //delete parent;
    parent = _parent;
}

//Iterator Ctor
TagIterator::TagIterator(Tag **t): t{t}, element_No{0} {}

//operator*()
Tag *TagIterator::operator*() const {
    return *t;
}

//Advance
TagIterator TagIterator::operator++(){
    element_No++;
    t = &(((*t)->getParent())->children[element_No]);
    return *this;
}

//Compare equal
bool TagIterator::operator==(const TagIterator &other) const {
    return t == other.t;
}

//Compare not equal
bool TagIterator::operator!=(const TagIterator &other) const {
    return !(*this == other);
}

TagIterator Tag::begin() const {
    return TagIterator{children};
}

TagIterator Tag::end() const {
    return TagIterator{&children[childrenLength]};
}


void Tag::print(std::ostream &out, int indentLevel) const {
    for (int i = 0; i < indentLevel; i++) {
        out << "  ";
    }
    if (id == "") {
        if (value == "") {
            out << "<" << type << ">" << std::endl;
        } else {
            out << "<" << type << " value=" << "'" << value << "'" << ">" << std::endl;
        }
    } else {
        if (value == "") {
            out << "<" << type << " id=" << "'" << id << "'" << ">" << std::endl;
        } else {
            out << "<" << type << " id=" << "'" << id << "'" << " value=" << "'" << value << "'"  ">" << std::endl;
        }
    }
    if (childrenLength > 0) {
        //std::cout << "begin points to: " <<((*begin())->type) << std::endl;
        //std::cout << "end points to: " << ((*end())->type) << std::endl;
    }
    
    for (auto it = begin(); it != end(); ++it) {
        if (*it) {
            (*it)->print(out,indentLevel + 1);
        }       
    }
    for (int i = 0; i < indentLevel; i++) {
        out << "  ";
    }
    out << "</" << type << ">" << std::endl;
}

void Tag::addChild(Tag *other) {
    childrenLength++;
    if (childrenLength >= childrenCapacity) {
        resizeChildren();
    }
    children[childrenLength-1] = other;  
}

void Tag::removeChild(Tag *other) {
    int counter = 0;
    for (int i = 0; i < childrenLength; i ++) {
        if (children[i] == other) {
            children[i] = nullptr;
            childrenLength--;
            break;
        }
        counter++;
    }
    for (int i = counter; i < childrenLength; i++) {
        children[i] = children[i+1];
    }
    children[childrenLength] = nullptr;
}

Tag *Tag::findChild(std::string &type) {
    for (auto it = begin(); it != end(); ++it) {
        if ((*it)->type == type) {
            return *it;
        }
    }
    return nullptr;
}

Tag *Tag::findChildId(std::string &id) {
    for (auto it = begin(); it != end(); ++it) {
        if ((*it)->id == id) {
            return *it;
        }
    }
    return nullptr;
}

std::ostream &operator<<(std::ostream &out, const Tag &tag) {
    tag.print(out);
    return out;
}
