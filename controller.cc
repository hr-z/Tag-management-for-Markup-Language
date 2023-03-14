#include "controller.h"
using namespace std;

Controller::Controller(): doc{new Tag{"document"}}, cur{doc}, clip{nullptr} {}

Controller::~Controller() {
    delete clip;
    delete doc;
}

void Controller::printCurrent() {
    cout << "<" << cur->getType() << "> is now the current tag." << endl;
}

void Controller::print() {
    cout << *cur;
}

void Controller::addChild(string option) {
    if (option == "document") {
        cerr << "Cannot create new <document> tag." << endl;
        return;
    }
    
    Tag *newTag = new Tag{option};
    newTag->setParent(cur);
    cur->addChild(newTag);
    cur = newTag;
    printCurrent();
}

void Controller::deleteCur() {
    if (cur == doc) {
        cerr << "Document tag cannot be removed." << endl;
        return;
    }
    Tag *tmp = cur;
    cur = tmp->getParent();
    cur->removeChild(tmp);
    delete tmp;
    printCurrent();
}

void Controller::parent() {
    if (cur->getParent() == nullptr) {
        cerr << "Current tag is already the upper level tag." << endl;
        return;
    }
    cur = cur->getParent();
    printCurrent();
}

void Controller::up() {
    cur = doc;
    printCurrent();
}

void Controller::setId(string option) {
    cur->setId(option);
    cout << "<" << cur->getType() << "> id set to '" << option << "'." << endl;
}

void Controller::setValue(string option) {
    cur->setValue(option);
    cout << "<" << cur->getType() << "> value set to '" << option << "'." << endl;
}

void Controller::findChild(string option) {
    Tag *tmp = cur->findChild(option);
    if (tmp == nullptr) {
        cerr << "<" << option << "> not found." << endl;
        return;
    }
    cur = tmp;
    printCurrent();
}

void Controller::findChildId(string option) {
    Tag *tmp = cur->findChildId(option);
    if (tmp == nullptr) {
        cerr << "Tag with id '" << option << "' not found." << endl;
        return;
    }
    cur = tmp;
    printCurrent();
}

void Controller::list() {
    cout << "<" << cur->getType() << "> has the following children:" << endl;
    for (Tag *child : *cur) {
        cout << "- <" << child->getType() << ">" << endl;
    }
}

void Controller::cut() {
    if (cur == doc) {
        cerr << "Document tag cannot be cut." << endl;
        return;
    }
    // remove tag from parent
    Tag *parent = cur->getParent();
    parent->removeChild(cur);
    // move tag to clipboard
    if (clip == nullptr) {
        clip = new Tag{std::move(*cur)};
    } else {
        *clip = std::move(*cur);
    }
    // delete original tag
    delete cur;
    cur = parent;
    cout << "<" << clip->getType() << "> is now in the clipboard." << endl;
    printCurrent();
}

void Controller::copy() {
    if (cur == doc) {
        cerr << "Document tag cannot be copied." << endl;
        return;
    }
    // copy tag to clipboard
    if (clip == nullptr) {
        clip = new Tag{*cur};
    } else {
        *clip = *cur;
    }
    
    cout << "<" << clip->getType() << "> is now in the clipboard." << endl;
}

void Controller::paste() {
    if (clip == nullptr) {
        cerr << "The clipboard is empty." << endl;
        return;
    }
    // copy tag from clipboard as a new child of the current tag
    Tag *newTag = new Tag{*clip};
    newTag->setParent(cur);
    cur->addChild(newTag);
    cur = newTag;
    printCurrent();
}
