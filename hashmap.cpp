#include "hashmap.hpp"

template<typename T>
HashMap<T>::HashMap(){
	associativeArr = std::vector<std::optional<HashPair<T>>>(10);
	assignedValues = 0;
}

template<typename T>
double HashMap<T>::getLoadFactor(){
	return static_cast<double>(assignedValues)/associativeArr.size();
}

template<typename T>
void HashMap<T>::insert(string key, T value, bool resizing){
	// Increase size when load factor > 0.5
	double load_factor = this->getLoadFactor();
	if (load_factor >= 0.5){
		cout << ">0.5 load factor, doubling size\n";
		this->resize(associativeArr.size()*2);
	}

	size_t hashedKey = hasher(key);
	int idx = hashedKey % associativeArr.size();

	HashPair<T> tupleToInsert = make_tuple(key, value);

	if (associativeArr[idx].has_value()){
		// Hash collision, linear probe until we can put our tuple in
		bool insertedSuccessfully = false;

		// iterate from idx + 1 to the end
		for(int i=idx+1; i < associativeArr.size(); i++){
			if(!associativeArr[i].has_value()){
				// Add it here
				insertedSuccessfully = true;
				associativeArr[i] = tupleToInsert;
				break;
			}
		}

		// If still not inserted try to insert from 0 to idx-1
		if (!insertedSuccessfully){
			for(int i=0; i < idx-1; i++){
				if(!associativeArr[i].has_value()){
					// Add it here
					insertedSuccessfully = true;
					associativeArr[i] = tupleToInsert;
					break;
				}
			}
		}

		if (!insertedSuccessfully){
			throw std::runtime_error("Was unable to find place to insert into hashmap!");
		}else{
			cout << "Inserted " << key << " into map\n";
			if(!resizing){
				++assignedValues;
			}
		}

	} else{
		// No collision, we can just add it
		cout << "Inserted " << key << " into map\n";
		associativeArr[idx] = tupleToInsert;
		if(!resizing){
			++assignedValues;
		}
	}
}

template<typename T>
T HashMap<T>::get(string key){
	size_t hashedKey = hasher(key);
	int idx = hashedKey % associativeArr.size();

	if (associativeArr[idx].has_value() && std::get<0>(associativeArr[idx].value()) == key){
		return std::get<1>(associativeArr[idx].value());
	}else{
		// Collision, do linear search
		for(int i = 0; i<associativeArr.size(); i++){
			if(associativeArr[i].has_value()){
				if (std::get<0>(associativeArr[i].value()) == key){
					return std::get<1>(associativeArr[i].value());
				}
			}
		}
	}
	throw std::runtime_error(key + " not found in hashmap.");
}

template<typename T>
void HashMap<T>::remove(string key){
	size_t hashedKey = hasher(key);
	int idx = hashedKey % associativeArr.size();
	cout << "possible location of " << key << " " << idx << "\n";

	bool successfullyDeleted = false;

	if(associativeArr[idx].has_value()){
		if (std::get<0>(associativeArr[idx].value()) == key){
			// Delete at idx
			associativeArr[idx] = std::nullopt;
			successfullyDeleted = true;
		}else{
			// Hash collision, Linear search
			for(int i=0; i<associativeArr.size(); i++){
				if (associativeArr[i].has_value()){
					cout << std::get<0>(associativeArr[i].value());
					if (std::get<0>(associativeArr[i].value()) == key) {
						associativeArr[i] = std::nullopt;
						successfullyDeleted = true;
						break;
					}
				}
			}
		}
	}

	if (successfullyDeleted){
		cout << "Successfully deleted " << key << " from map.\n";
		--assignedValues;
	}else{
		cout << "Failed to locate " << key << " in map.\n";
	}
}

template<typename T>
void HashMap<T>::resize(int size){
	// Copy old array
	std::vector<std::optional<HashPair<T>>> oldAssociativeArr = associativeArr;
	
	// Create new array
	associativeArr = std::vector<std::optional<HashPair<T>>>(size);

	// Reinsert all values of old array into new one
	for(std::optional<HashPair<T>> tup : oldAssociativeArr){
		if (tup.has_value()){
			this->insert(std::get<0>(tup.value()), std::get<1>(tup.value()), true);
		}
	}
}

template<typename T>
void HashMap<T>::print(){
	cout << "--------------------\nHashmap\n";
	for(int i = 0; i<associativeArr.size(); i++){
		if(associativeArr[i].has_value()){
			HashPair<T> item = associativeArr[i].value();
			cout << "Idx " << i << ": (" << std::get<0>(item) << "->" << std::get<1>(item) << ")\n";
		}else{
			cout << "Idx " << i << ": Empty \n";
		}
	}	
	cout << "Load factor: "<< this->getLoadFactor() << "\n";
	cout << "--------------------\n";
}

// This code allows the generic class to be defined in the .hpp and implemented in this .cpp
template class HashMap<int>;
template class HashMap<float>;
template class HashMap<double>;
template class HashMap<bool>;
template class HashMap<char>;

template class HashMap<std::string>;