#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <iostream>
#include <string>
#include "tag.h"

class Controller {
    Tag *doc;
    Tag *cur;
    Tag *clip;
    void printCurrent();
    bool canMove();
  public:
    Controller();
    ~Controller();
    void print();                         // Prints the current tag to the standard output
    void addChild(std::string option);    /* Creates a new tag of the type specified by the argument, adds it as a child of the current tag, and
                                             makes it the new current tag. The newly created type cannot be "document". */
    void deleteCur();                     // Deletes the current tag, removes it from its parent, and makes its parent the new current tag.
    void parent();                        // Sets the parent of the current tag as the new current tag.
    void up();                            // Sets the topmost tag (<document>) as the current tag.
    void setId(std::string option);       // Sets the id attribute of the current tag to val. Note that val cannot contain whitespaces.
    void setValue(std::string option);    // Sets the value attribute of the current tag to val. Note that val cannot contain whitespaces.
    void findChild(std::string option);   /* Finds the first tag that is a child of the current tag and has the specified type. If such a tag is
                                             found, it is set as the current tag. Otherwise, nothing happens.*/
    void findChildId(std::string option); /* Finds the first tag that is a child of the current tag and has the specified id. If such a tag is found, 
                                             it is set as the current tag. Otherwise, nothing happens. */
    void list();                          // Lists the type of the direct children of the current tag.
    void cut();                           /* Removes the current tag from its parent and moves it to the program’s internal clipboard. Sets its
                                             parent tag as the current tag */
    void copy();                          // copies current tag to internal clipboard
    void paste();                         /* Adds a new child to the current tag, whose contents are a copy of the tag currently in the clipboard,
                                             and updates the pointers of the child and current tag accordingly. */
};

#endif
