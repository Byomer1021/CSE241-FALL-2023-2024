package mypackage;

import java.util.Iterator;

public interface JavaContainer {
    /***
     * interface
     * 
     */
    void add(Object element);
    void remove(Object element);
    int size();
    Iterator<Object> getIterator();
    String toString();
}