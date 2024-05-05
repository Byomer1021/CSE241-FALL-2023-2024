package mypackage;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

public class JavaSet implements JavaContainer {

    private Set<Object> set; // "var set"

    /**
     * constructor
     * 
     * 
     **/
    public JavaSet() {
        this.set = new HashSet<>();
    }

    /**
     * add override
     * 
     * @param Object
     **/

    @Override
    public void add(Object element) {
        set.add(element);
    }

    /**
     * remove override
     * 
     * @param Object
     **/
    @Override
    public void remove(Object element) {
        set.remove(element);
    }

    /**
     * setter
     **/
    @Override
    public int size() {
        return set.size();
    }

    /**
     * getter
     **/
    @Override
    public Iterator<Object> getIterator() {
        return set.iterator();
    }

    /**
     * 
     * tostring override
     * 
     **/
    @Override
    public String toString() {
        return set.toString();
    }

    /**
     * 
     * equals override
     * 
     * @param Object obj
     * 
     **/
    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null || getClass() != obj.getClass())
            return false;
        JavaSet javaSet = (JavaSet) obj;
        return set.equals(javaSet.set);
    }
}