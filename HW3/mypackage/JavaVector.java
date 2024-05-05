
package mypackage;

import java.util.Iterator;
import java.util.Vector;

public class JavaVector implements JavaContainer {
	private Vector<Object> vector; // "var vector "

	/**
	 * constructor for vector
	 **/
	public JavaVector() {
		this.vector = new Vector<>(); // 'var' is inferred here
	}

	/**
	 * add override
	 * 
	 * @param Object
	 **/
	@Override
	public void add(Object element) {
		vector.add(element);
	}

	/**
	 * remove override
	 * 
	 * @param Object
	 **/
	@Override
	public void remove(Object element) {
		vector.remove(element);
	}

	/**
	 * set size
	 **/
	@Override
	public int size() {
		return vector.size();
	}

	/**
	 * getter
	 **/
	@Override
	public Iterator<Object> getIterator() {
		return vector.iterator();
	}
	/**
	 * tostring override
	 * 
	 **/
	@Override
	public String toString() {
		return vector.toString();
	}
	/**
	 * remove override 
	 * @param Object
	 * @param This
	 * if object=this true
	 * else false 
	 **/
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null || getClass() != obj.getClass())
			return false;
		JavaVector javaVector = (JavaVector) obj; // Using 'var' for local variable "var javavector"
		return vector.equals(javaVector.vector);
	}

}
