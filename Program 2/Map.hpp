#ifndef _MAPXXXYXXZ_H_
#define _MAPXXXYXXZ_H_

#include <utility>
#include <map>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
#include <initializer_list>
#include <utility>
#include <iostream>
#include <algorithm>
#include <string>
#include <exception>
#include <functional>

namespace cs540{
									//INCREMENT ITERATORS WITH PREFIX-----------------
    template<typename Key_T, typename Mapped_T>
    class SkipNodeBase{
    public:
        SkipNodeBase(int);
        ~SkipNodeBase();
        //int getHeight();
        //int getSentinel();
        //void setSentinel(int);
        int isSentinel;
        int nodeHeight;
        SkipNodeBase<Key_T, Mapped_T>** fwdNodes;
        SkipNodeBase<Key_T, Mapped_T>** backNodes;
    };


    template< typename Key_T, typename Mapped_T>
    class SkipNode : public SkipNodeBase<Key_T, Mapped_T> {
        typedef std::pair<const Key_T, Mapped_T> ValueType;
    public:
        SkipNode(const Key_T, Mapped_T, int);
        ~SkipNode();
        //const Key_T getKey();
        //Mapped_T getObj();
        //int getHeight();
        //void setHeight(int);
        //int getSentinel();
        //void setSentinel(int);
        SkipNodeBase<Key_T, Mapped_T>** fwdNodes;  //array of all connected nodes at every level
        SkipNodeBase<Key_T, Mapped_T>** backNodes;
        ValueType nodePair;
    };

	/*template<typename Key_T, typename Mapped_T>
	class InsertionPair{
		public:
			InsertionPair();
			InsertionPair(Skip


	}*/





 template<typename Key_T, typename Mapped_T>
  class SkipList{
    public:
        SkipList();
        ~SkipList();
       	std::pair<SkipNodeBase<Key_T, Mapped_T>*, bool> insert(const Key_T, Mapped_T, int);
        bool removeNode(const Key_T);
        SkipNodeBase<Key_T, Mapped_T>* search(const Key_T) const;
        int listRandomizer();
        SkipNodeBase<Key_T, Mapped_T>* getHead() const;
        SkipNodeBase<Key_T, Mapped_T>* getTail() const;

    private:
        SkipNodeBase<Key_T, Mapped_T>* head;
        SkipNodeBase<Key_T, Mapped_T>* tail;
        float prob;
        int maxHeight;
        int currentHeight;
  };


    template< typename Key_T, typename Mapped_T>
    class Map{

    public:
        typedef std::pair<const Key_T, Mapped_T> ValueType;
        Map();
        Map(const Map &);
        Map &operator=(const Map &);
        Map(std::initializer_list<ValueType>);
        ~Map();
        size_t size() const;
        bool empty() const;
        class ConstIterator;
        class Iterator{     //------->POSTDECREMENT MIGHT NEED TO HAVE NO IF STATEMENT
        public:
            Iterator(const Iterator &);
            ~Iterator();
           	Iterator(SkipNodeBase<Key_T, Mapped_T>*);
			 Iterator& operator=(const Iterator &);
            Iterator &operator++();
            Iterator operator++(int);
            Iterator &operator--();
            Iterator operator--(int);
            ValueType &operator*() const;
            ValueType *operator->() const;
            SkipNodeBase<Key_T, Mapped_T>* getNodePtr() const;
			void setNodePtr(SkipNodeBase<Key_T, Mapped_T>*);

            friend bool operator==(const typename Map<Key_T, Mapped_T>::Iterator &I1, const typename Map<Key_T, Mapped_T>::Iterator &I2){
                if(I1.getNodePtr() == NULL || I2.getNodePtr() == NULL) return false;
        		else if(I1.getNodePtr() == I2.getNodePtr())	 return true;
        		else return false;
            }

            friend bool operator==(const typename Map<Key_T, Mapped_T>::Iterator &I1, const typename Map<Key_T, Mapped_T>::ConstIterator &I2){
                if(I1.getNodePtr() == NULL || I2.getConstNodePtr() == NULL) return false;
        		else if(I1.getNodePtr() == I2.getConstNodePtr())	 return true;
        		else return false;
            }

            friend bool operator!=(const typename Map<Key_T, Mapped_T>::Iterator &I1, const typename Map<Key_T, Mapped_T>::Iterator &I2){
                if(I1 == I2) return false;
        		else return true;
            }

            friend bool operator!=(const typename Map<Key_T, Mapped_T>::Iterator &I1, const typename Map<Key_T, Mapped_T>::ConstIterator &I2){
                if(I1 == I2) return false;
        		else return true;
            }
        private:
            SkipNodeBase<Key_T, Mapped_T>* nodePtr;
        };

        class ConstIterator{
        public:
            ConstIterator(const ConstIterator &);
            ConstIterator(const Iterator &);
			ConstIterator(SkipNodeBase<Key_T, Mapped_T>*);
            ~ConstIterator();
			ConstIterator& operator=(const ConstIterator &);
			ConstIterator &operator++();
			ConstIterator operator++(int);
			ConstIterator &operator--();
			ConstIterator operator--(int);
			const ValueType &operator*() const;
            const ValueType *operator->() const;
			SkipNodeBase<Key_T, Mapped_T>* getConstNodePtr() const;
			void setConstNodePtr(SkipNodeBase<Key_T, Mapped_T>*);

            friend bool operator==(const typename Map<Key_T, Mapped_T>::ConstIterator &I1, const typename Map<Key_T, Mapped_T>::ConstIterator &I2){
                if(I1.getConstNodePtr() == NULL || I2.getConstNodePtr() == NULL) return false;
        		else if(I1.getConstNodePtr() == I2.getConstNodePtr())	 return true;
        		else return false;
            }

            friend bool operator==(const typename Map<Key_T, Mapped_T>::ConstIterator &I1, const typename Map<Key_T, Mapped_T>::Iterator &I2){
                if(I1.getConstNodePtr() == NULL || I2.getNodePtr() == NULL) return false;
        		else if(I1.getConstNodePtr() == I2.getNodePtr()) return true;
        		else return false;
            }

            friend bool operator!=(const typename Map<Key_T, Mapped_T>::ConstIterator &I1, const typename Map<Key_T, Mapped_T>::ConstIterator &I2){
                if(I1 == I2) return false;
                else return true;
            }

            friend bool operator!=(const typename Map<Key_T, Mapped_T>::ConstIterator &I1, const typename Map<Key_T, Mapped_T>::Iterator &I2){
                if(I1 == I2) return false;
                else return true;
            }

		private:
			SkipNodeBase<Key_T, Mapped_T>* constNodePtr;  //MIGHT HAVE TO CHANGE TO CONST---------

        };

        class ReverseIterator{
        public:
            ReverseIterator(const ReverseIterator &);
        	ReverseIterator(SkipNodeBase<Key_T, Mapped_T>*);
		    ~ReverseIterator();
			ReverseIterator& operator=(const ReverseIterator &);
			ReverseIterator &operator++();
			ReverseIterator operator++(int);
			ReverseIterator &operator--();
			ReverseIterator operator--(int);
            ValueType &operator*() const;
            ValueType *operator->() const;
			SkipNodeBase<Key_T, Mapped_T>* getReverseNodePtr() const;
			void setReverseNodePtr(SkipNodeBase<Key_T, Mapped_T>*);


            friend bool operator==(const typename Map<Key_T, Mapped_T>::ReverseIterator &I1, const typename Map<Key_T, Mapped_T>::ReverseIterator &I2){
                if(I1.getReverseNodePtr() == NULL || I2.getReverseNodePtr() == NULL) return false;
        		else if(I1.getReverseNodePtr() == I2.getReverseNodePtr()) return true;
        		else return false;
            }

            friend bool operator!=(const typename Map<Key_T, Mapped_T>::ReverseIterator &I1, const typename Map<Key_T, Mapped_T>::ReverseIterator &I2){
                if(I1 == I2) return false;
                else return true;
            }

		private:
			SkipNodeBase<Key_T, Mapped_T>* reverseNodePtr;
		};
        Map<Key_T, Mapped_T>::Iterator begin();
        Map<Key_T, Mapped_T>::Iterator end();
        Map<Key_T, Mapped_T>::ConstIterator begin() const;
        Map<Key_T, Mapped_T>::ConstIterator end() const;
        Map<Key_T, Mapped_T>::ReverseIterator rbegin();
        Map<Key_T, Mapped_T>::ReverseIterator rend();
        Map<Key_T, Mapped_T>::Iterator find(const Key_T &);
        Map<Key_T, Mapped_T>::ConstIterator find(const Key_T &) const;
        Mapped_T &at(const Key_T &);
        const Mapped_T &at(const Key_T &) const;
        Mapped_T &operator[](const Key_T &);
        std::pair<Map<Key_T, Mapped_T>::Iterator, bool> insert(const ValueType &);

        template <typename IT_T>
        void insert(IT_T range_beg, IT_T range_end);

	    void erase(Map<Key_T, Mapped_T>::Iterator pos);
        void erase(const Key_T &);
        void clear();
        SkipList<Key_T, Mapped_T> getMapList() const;

        friend bool operator==(const Map<Key_T, Mapped_T> &m1, const Map<Key_T, Mapped_T> &m2){
        	if(m1.size() == m2.size()){
    			if(m1.size() == 0) return true;
    			typename Map<Key_T, Mapped_T>::ConstIterator iter1 = m1.begin();
    			typename Map<Key_T, Mapped_T>::ConstIterator iter2 = m2.begin();
    			for(; iter1 != m1.end(); ++iter1, ++iter2){
    				SkipNode<Key_T, Mapped_T>* temp1 = (static_cast<SkipNode<Key_T, Mapped_T>*>( iter1.getConstNodePtr() ) );
    				SkipNode<Key_T, Mapped_T>* temp2 = (static_cast<SkipNode<Key_T, Mapped_T>*>( iter2.getConstNodePtr() ) );
    				if(temp1->nodePair != temp2->nodePair) return false;
    			}
    			return true;
    		}
    		else  return false;
        }

        friend bool operator!=(const Map<Key_T, Mapped_T> &m1, const Map<Key_T, Mapped_T> &m2){
            if(m1 == m2) return false;
    		else return true;
        }

        friend bool operator<(const Map<Key_T, Mapped_T> &m1, const Map<Key_T, Mapped_T> &m2){

    		typename Map<Key_T, Mapped_T>::ConstIterator iter1 = m1.begin();
        	typename Map<Key_T, Mapped_T>::ConstIterator iter2 = m2.begin();
    		if(iter1.getConstNodePtr() == NULL && iter2.getConstNodePtr() != NULL) return true;
    		else if(iter1.getConstNodePtr() != NULL && iter2.getConstNodePtr() == NULL) return false;
    		else if(iter1.getConstNodePtr() == NULL && iter2.getConstNodePtr() == NULL) return false;
    		else{
    			if(m1.size() < m2.size()){
    				for(; iter1 != m1.end(); ++iter1, ++iter2){
    					SkipNode<Key_T, Mapped_T>* temp1 = (static_cast<SkipNode<Key_T, Mapped_T>*>( iter1.getConstNodePtr() ) );
    					SkipNode<Key_T, Mapped_T>* temp2 = (static_cast<SkipNode<Key_T, Mapped_T>*>( iter2.getConstNodePtr() ) );
    					if(temp1->nodePair < temp2->nodePair) return true;
    					else if(temp1->nodePair > temp2->nodePair) return false;
    				}
    				return true;   //M1.SIZE < M2.SIZE AND EACH CORRESPONDING ELEMENT IS EQUAL
    			}
    			else{
                    //std::cout << "map sizes are the same" << std::endl;
    				for(; iter2 != m2.end(); ++iter2, ++iter1){
    					SkipNode<Key_T, Mapped_T>* temp1 = (static_cast<SkipNode<Key_T, Mapped_T>*>( iter1.getConstNodePtr() ) );
    					SkipNode<Key_T, Mapped_T>* temp2 = (static_cast<SkipNode<Key_T, Mapped_T>*>( iter2.getConstNodePtr() ) );
    					if(temp1->nodePair < temp2->nodePair) return true;
    				}
    				return false;
    			}
    		}
    	}

    private:
        size_t mapSize;
        SkipList<Key_T, Mapped_T> mapList;

        //friend bool operator==(const Iterator &, const Iterator &);

};


    /*************************MAP CLASS *******************************************/
    template< typename Key_T, typename Mapped_T>
    Map<Key_T, Mapped_T>::Map(){
        //mapList = new SkipList<Key_T, Mapped_T>();
        mapSize = 0;
    }

    template< typename Key_T, typename Mapped_T>
    Map<Key_T, Mapped_T>::Map(const Map<Key_T, Mapped_T> &m1){
		if(m1.mapSize == 0) mapSize = 0;
		else{
			mapSize = 0;
			Map<Key_T, Mapped_T>::ConstIterator iter = m1.begin();
			for(; iter != m1.end(); ++iter){
				SkipNode<Key_T, Mapped_T>* temp = static_cast<SkipNode<Key_T, Mapped_T>*>(iter.getConstNodePtr());
				mapList.insert(temp->nodePair.first, temp->nodePair.second, -1);
				mapSize++;
			}
		}
	}

	template<typename Key_T, typename Mapped_T>
	Map<Key_T, Mapped_T>& Map<Key_T, Mapped_T>::operator=(const Map &m1){
		if( (*this) != m1){
			if(m1.mapSize == 0) mapSize = 0;
			else {   //DELETE EXISTING NODES*********
                this->clear();
				mapSize = 0;
				Map<Key_T, Mapped_T>::ConstIterator iter = m1.begin();
				for(; iter != m1.end(); iter++){
					SkipNode<Key_T, Mapped_T>* temp = static_cast<SkipNode<Key_T, Mapped_T>*>(iter.getConstNodePtr());
					mapList.insert(temp->nodePair.first, temp->nodePair.second, -1);
					mapSize++;
				}
			}
		}
		return (*this);
	}

    template< typename Key_T, typename Mapped_T>
    Map<Key_T, Mapped_T>::Map(std::initializer_list<ValueType> initList){
        typename std::initializer_list<ValueType>::iterator it;
        mapSize = 0;
        //mapList = SkipList<Key_T, Mapped_T>();
        for(it = initList.begin(); it != initList.end(); it++){
                if( &(it->first) != NULL && &(it->second) != NULL ){
                    mapList.insert(it->first, it->second, -1);
                    mapSize++;
                }
                /*else{
                    keyPtr = NULL;
                    objPtr = NULL;
                }
                std::cout << "key value: " << *keyPtr << std::endl;
                std::cout << "obj value: " << *objPtr << std::endl;

            mapList->insert(keyPtr, objPtr, -1);*/
            //mapSize++;
        }

        //SkipNode<Key_T, Mapped_T>* temp = mapList->getHead();


        /*while(temp){
            std::cout << "<-";
            if(temp->getKey() == NULL) std::cout << "X->";
            else std::cout << *(temp->getKey()) << "->";
            temp = temp->fwdNodes[0];
        }
        std::cout << '\n';*/
        //std::cout << "reaches end of MAP CTOR" << std::endl;
        //std::cout << "reaches end of Map(initializer_list)" << std::endl;
    }


    template< typename Key_T, typename Mapped_T>
    Map<Key_T, Mapped_T>::~Map(){
        //std::cout << "map DTOR called" << std::endl;
        //mapList;
        //mapSize = 0;
    }

    template<typename Key_T, typename Mapped_T>
    size_t Map<Key_T, Mapped_T>::size() const{
        return mapSize;
    }

    template< typename Key_T, typename Mapped_T>
    bool Map<Key_T, Mapped_T>::empty() const{
        if(mapSize == 0) return true;
        else return false;
    }

    template< typename Key_T, typename Mapped_T>
    SkipList<Key_T, Mapped_T> Map<Key_T, Mapped_T>::getMapList() const{
        return mapList;
    }

    template< typename Key_T, typename Mapped_T>
	std::pair<typename Map<Key_T, Mapped_T>::Iterator, bool> Map<Key_T, Mapped_T>::insert(const ValueType& valuePair){
		std::pair<SkipNodeBase<Key_T, Mapped_T>*, bool> insertPair;
		insertPair = mapList.insert(valuePair.first, valuePair.second, -1);
		//std::pair<Map<Key_T, Mapped_T>::Iterator, bool> returnPair;
		Map<Key_T, Mapped_T>::Iterator tempIter(insertPair.first);  //Iterator ctor with skipNodeBase pointer
		//returnPair.first = tempIter;
		//returnPair.second = insertPair.second;
		if(insertPair.second) mapSize++;

        std::pair<Map<Key_T, Mapped_T>::Iterator, bool> returnPair = std::make_pair(tempIter, insertPair.second);
		return returnPair;
	}

	template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::begin(){
		SkipNodeBase<Key_T, Mapped_T>* temp = mapList.getHead()->fwdNodes[0];
		if(temp == mapList.getTail()){
             Iterator iter1(temp);    //<---- INITIALLY SET TO NULL!!!
             return iter1;
        }
        else{
            Map<Key_T, Mapped_T>::Iterator iter1(temp);
            return iter1;
        }
	}


	template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::end(){
		Map<Key_T, Mapped_T>::Iterator iter1(mapList.getTail());
		return iter1;
	}

	template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::begin() const{
		SkipNodeBase<Key_T, Mapped_T>* temp = mapList.getHead()->fwdNodes[0];
		if(temp == mapList.getTail()){
             Map<Key_T, Mapped_T>::ConstIterator iter1(temp);
             return iter1;
        }
		else{
            Map<Key_T, Mapped_T>::ConstIterator iter1(temp);
            return iter1;
        }
	}

	template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::end() const{
		Map<Key_T, Mapped_T>::Iterator iter1(mapList.getTail());
		return iter1;
	}

	template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T>::ReverseIterator Map<Key_T, Mapped_T>::rbegin(){
		SkipNodeBase<Key_T, Mapped_T>* temp = mapList.getTail()->backNodes[0];
		if(temp == mapList.getHead()){
            Map<Key_T, Mapped_T>::ReverseIterator iter1(temp);
            return iter1;
        }
		else{
            Map<Key_T, Mapped_T>::ReverseIterator iter1(temp);
            return iter1;
        }
	}

	template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T>::ReverseIterator Map<Key_T, Mapped_T>::rend(){
		Map<Key_T, Mapped_T>::ReverseIterator iter1(mapList.getHead());
        return iter1;
	}

	template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::find(const Key_T &k){
		SkipNodeBase<Key_T, Mapped_T>* temp = mapList.search(k);
		if(temp != NULL){
            Map<Key_T, Mapped_T>::Iterator iter1(temp);
            return iter1;
        }
        else{
            Map<Key_T, Mapped_T>::Iterator iter1(this->end());
            return iter1;
        }
	}

	template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::find(const Key_T &k) const{
		SkipNodeBase<Key_T, Mapped_T>* temp = mapList.search(k);
		if(temp != NULL){
            Map<Key_T, Mapped_T>::ConstIterator iter1(temp);
            return iter1;
        }
        else{
            Map<Key_T, Mapped_T>::ConstIterator iter1(this->end());
            return iter1;
        }
	}


	template<typename Key_T, typename Mapped_T>
	Mapped_T&  Map<Key_T, Mapped_T>::at(const Key_T &tempKey){
		SkipNodeBase<Key_T, Mapped_T>* temp = mapList.search(tempKey);
		if(temp == NULL){
			throw std::out_of_range("Element not in map.");
		}
		else{
            return (static_cast<SkipNode<Key_T, Mapped_T>*>(temp)->nodePair.second);

        }
	}

	template<typename Key_T, typename Mapped_T>
	const Mapped_T&  Map<Key_T, Mapped_T>::at(const Key_T &tempKey) const{
		SkipNodeBase<Key_T, Mapped_T>* temp = mapList.search(tempKey);
		if(temp == NULL){
			throw std::out_of_range("Element not in map.");
		}
		else{
            return (static_cast<SkipNode<Key_T, Mapped_T>*>(temp)->nodePair.second);
        }
	}

	template<typename Key_T, typename Mapped_T>
	void Map<Key_T, Mapped_T>::erase(typename Map<Key_T, Mapped_T>::Iterator pos){
		if( (pos.getNodePtr() != NULL) && (pos.getNodePtr()->isSentinel) != 1) {
            //std::cout << "reaches beginning of erase(): " << "mapSize == " << mapSize  << std::endl;
			mapList.removeNode( (static_cast<SkipNode<Key_T, Mapped_T>*>(pos.getNodePtr())->nodePair.first) );
			mapSize--;
            //std::cout << "reaches end of erase(): " << "mapSize == " << mapSize  << std::endl;
		}
	}

	template<typename Key_T, typename Mapped_T>
	void Map<Key_T, Mapped_T>::erase(const Key_T &k){
		SkipNodeBase<Key_T, Mapped_T>* temp = mapList.search(k);
		if(temp == NULL) throw std::out_of_range("Element not in map.");
		else{
			 mapList.removeNode( (static_cast<SkipNode<Key_T, Mapped_T>*>(temp)->nodePair.first) );
			 mapSize--;
             //std::cout << "reaches end of erase()" << std::endl;
		}
	}

	template<typename Key_T, typename Mapped_T>
	void Map<Key_T, Mapped_T>::clear(){
		if(mapSize != 0){  //map isn't empty  (mapList.getHead())->fwdNodes[0] != mapList.getTail() <-- ORIGINAL
			//SkipNodeBase<Key_T, Mapped_T>* temp = (mapList.getHead())->fwdNodes[0];
			//Map<Key_T, Mapped_T>::Iterator iter(this->begin());
            //for(; iter != this->end(); iter++) std::cout << "iter++: " << (static_cast<SkipNode<Key_T, Mapped_T>*>(iter.getNodePtr())->nodePair.first) << std::endl;
            //iter++;
            //std::cout << "iter++: " << (static_cast<SkipNode<Key_T, Mapped_T>*>(iter.getNodePtr())->nodePair.first) << std::endl;
            //std::cout << "MAP SIZE BEFORE DELETION: " << mapSize << std::endl;

            SkipNodeBase<Key_T, Mapped_T>* temp2 = mapList.getHead();
            /*temp = list.getHead();
        	while(temp2){
        		std::cout << "<-";
        		if(temp2->isSentinel == 1){
        			std::cout << "(X,X)->" <<  " HEIGHT: " <<  temp2->nodeHeight <<std::endl;
        		}
        		else {
        			std::cout << "(" << (static_cast<cs540::SkipNode<int,char>*>(temp2)->nodePair.first) << "," << (static_cast<cs540::SkipNode<int,char>*>(temp2)->nodePair.second)
        			<< ")->" << " HEIGHT: " << temp2->nodeHeight << std::endl;
        		}
        		temp2 = temp2->fwdNodes[0];
        	}*/

            temp2 = mapList.getHead();
            //if(temp2->isSentinel == 1) std::cout << "head is sentinel" << std::endl;
            SkipNodeBase<Key_T, Mapped_T>* temp3 = temp2;
        	while(temp3){
        		if(temp3->isSentinel == 1){
        			//std::cout << "(X,X)->" <<  " HEIGHT: " <<  temp3->nodeHeight <<std::endl;
                    temp3 = temp3->fwdNodes[0];
        		}
        		else {
                    temp2 = temp3;
                    temp3 = temp3->fwdNodes[0];
                    //std::cout << "deleted node: " << (static_cast<cs540::SkipNode<Key_T,Mapped_T>*>(temp2)->nodePair.first) << " " << (static_cast<cs540::SkipNode<Key_T,Mapped_T>*>(temp2)->nodePair.second) << '\n';
        			mapList.removeNode(static_cast<cs540::SkipNode<Key_T,Mapped_T>*>(temp2)->nodePair.first);
                    mapSize--;
        		}
        	}






			/*for(; iter != this->end(); iter++){
                //std::cout << "MAP.CLEAR LOOP" << std::endl;
				//mapList.removeNode( (static_cast<SkipNode<Key_T, Mapped_T>*>(iter.getNodePtr())->nodePair.first) );
                std::cout << (static_cast<SkipNode<Key_T, Mapped_T>*>(iter.getNodePtr())->nodePair.first) << std::endl;
                if(iter.getNodePtr() == NULL) std::cout << "iter's ptr is null" << std::endl;
                else if(iter.getNodePtr() != NULL) std::cout << "iter's ptr is not null" << std::endl;
			}*/
			//std::cout << "MAP SIZE AFTER DELETION: " << mapSize << std::endl;
		}
	}

	template<typename Key_T, typename Mapped_T>
	Mapped_T& Map<Key_T, Mapped_T>::operator[](const Key_T& k){
		//std::pair<Map<Key_T, Mapped_T>::Iterator, bool> returnPair;
		SkipNodeBase<Key_T, Mapped_T>* temp = mapList.search(k);
		if(temp == NULL){
			Mapped_T m{};
			ValueType tempPair = std::make_pair(k,m);
            //std::pair<Map<Key_T, Mapped_T>::Iterator, bool> tempPair = std::make_pair(k, m);
			//tempPair.first = k; tempPair.second = m;
            std::pair<Map<Key_T, Mapped_T>::Iterator, bool> returnPair = this->insert(tempPair);
            //mapSize++;
			//this->insert(tempPair);
            return (static_cast<SkipNode<Key_T, Mapped_T>*>(returnPair.first.getNodePtr())->nodePair.second);
		}
		else{
			return ( (static_cast<SkipNode<Key_T, Mapped_T>*>(temp)->nodePair.second) );
		}
	}

	template<typename Key_T, typename Mapped_T>
	template<typename IT_T>
	void Map<Key_T, Mapped_T>::insert(IT_T range_beg, IT_T range_end){
		IT_T iter;
		for(iter = range_beg; iter != range_end; iter++){
			ValueType temp(iter->first, iter->second);
			this->insert(temp);
            mapSize++;
		}
	}
    /**********************************************************************************/

    /********************************ITERATOR CLASS *****************************************************************/

	template<typename Key_T, typename Mapped_T>
	Map<Key_T, Mapped_T>::Iterator::Iterator(SkipNodeBase<Key_T, Mapped_T>* temp){
		if(temp == NULL) nodePtr = NULL;
		else nodePtr = temp;

	}

    template<typename Key_T, typename Mapped_T>
    Map<Key_T, Mapped_T>::Iterator::Iterator(const Map<Key_T,Mapped_T>::Iterator &iter1){
        if(iter1.nodePtr == NULL) nodePtr = NULL;
        else nodePtr = iter1.nodePtr;
    }

    template<typename Key_T, typename Mapped_T>
    Map<Key_T, Mapped_T>::Iterator::~Iterator(){

    }

    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T>::Iterator& Map<Key_T, Mapped_T>::Iterator::operator++(){
        if(nodePtr == NULL) return (*this);
        else{

            nodePtr = nodePtr->fwdNodes[0];
            return (*this);
        }
    }

    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::Iterator::operator++(int){
        Map<Key_T, Mapped_T>::Iterator iter(*this);
        if(nodePtr != NULL){
            nodePtr = nodePtr->fwdNodes[0];
        }
        return iter;
    }

    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T>::Iterator& Map<Key_T, Mapped_T>::Iterator::operator--(){
        if(nodePtr == NULL) return (*this);
        else{
            nodePtr = nodePtr->backNodes[0];
            return (*this);
        }
    }


    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::Iterator::operator--(int){
        Map<Key_T, Mapped_T>::Iterator iter(*this);
        if(nodePtr != NULL){
            nodePtr = nodePtr->backNodes[0];
        }
        return iter;
    }

    /*template<typename Key_T, typename Mapped_T>
    ValueType& Map<Key_T, Mapped_T>::Iterator::operator*() const{
    }*/
     template<typename Key_T, typename Mapped_T>
	 void Map<Key_T, Mapped_T>::Iterator::setNodePtr(SkipNodeBase<Key_T, Mapped_T>* temp){
		nodePtr = temp;
	 }

	 template<typename Key_T, typename Mapped_T>
	 SkipNodeBase<Key_T, Mapped_T>* Map<Key_T, Mapped_T>::Iterator::getNodePtr() const{
		return nodePtr;
	 }

	 template<typename Key_T, typename Mapped_T>
	 typename Map<Key_T, Mapped_T>::Iterator&  Map<Key_T, Mapped_T>::Iterator::operator=(const Iterator &iter1){
	 	if(iter1.nodePtr == NULL) nodePtr = NULL;
		else{
			nodePtr = iter1.nodePtr;
		}
        return (*this);
	 }

     template<typename Key_T, typename Mapped_T>
	 typename Map<Key_T, Mapped_T>::ValueType& Map<Key_T, Mapped_T>::Iterator::operator*() const{
		return (static_cast<SkipNode<Key_T, Mapped_T>*>(nodePtr)->nodePair);
	 }

	 template<typename Key_T, typename Mapped_T>
	 typename Map<Key_T, Mapped_T>::ValueType* Map<Key_T, Mapped_T>::Iterator::operator->() const{
		//Map<Key_T, Mapped_T>::ValueType* pairPtr;
		return &(static_cast<SkipNode<Key_T, Mapped_T>*>(nodePtr)->nodePair);
	 }

/**********************************************************************************************/

/******************************CONST ITERATOR CLASS********************************/

 	template<typename Key_T, typename Mapped_T>
	Map<Key_T, Mapped_T>::ConstIterator::ConstIterator(SkipNodeBase<Key_T, Mapped_T>* temp){
		if(temp == NULL) constNodePtr = NULL;
		else constNodePtr = temp;
	}

    template<typename Key_T, typename Mapped_T>
    Map<Key_T, Mapped_T>::ConstIterator::ConstIterator(const Map<Key_T,Mapped_T>::ConstIterator &iter1){
        if(iter1.constNodePtr == NULL) constNodePtr = NULL;
        else constNodePtr = iter1.constNodePtr;
    }

    template<typename Key_T, typename Mapped_T>
    Map<Key_T, Mapped_T>::ConstIterator::ConstIterator(const Map<Key_T,Mapped_T>::Iterator &iter1){
        if(iter1.getNodePtr() == NULL) constNodePtr = NULL;
        else constNodePtr = iter1.getNodePtr();
    }

    template<typename Key_T, typename Mapped_T>
    Map<Key_T, Mapped_T>::ConstIterator::~ConstIterator(){
   	}

	template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T>::ConstIterator&  Map<Key_T, Mapped_T>::ConstIterator::operator=(const ConstIterator &iter1){
	 	if(iter1.constNodePtr == NULL) constNodePtr = NULL;
		else{
			constNodePtr = iter1.constNodePtr;
		}
        return (*this);
	 }


    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T>::ConstIterator& Map<Key_T, Mapped_T>::ConstIterator::operator++(){
        if(constNodePtr == NULL) return (*this);
        else{
            constNodePtr = constNodePtr->fwdNodes[0];
            return (*this);
        }
    }

    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::ConstIterator::operator++(int){
        Map<Key_T, Mapped_T>::ConstIterator iter(*this);
        if(constNodePtr != NULL){
            constNodePtr = constNodePtr->fwdNodes[0];
        }
        return iter;
    }

    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T>::ConstIterator& Map<Key_T, Mapped_T>::ConstIterator::operator--(){
        if(constNodePtr == NULL) return (*this);
        else{
            constNodePtr = constNodePtr->backNodes[0];
            return (*this);
        }
    }


    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::ConstIterator::operator--(int){
        Map<Key_T, Mapped_T>::ConstIterator iter(*this);
        if(constNodePtr != NULL){
            constNodePtr = constNodePtr->backNodes[0];
        }
        return iter;
    }

    template<typename Key_T, typename Mapped_T>
	const typename Map<Key_T, Mapped_T>::ValueType& Map<Key_T, Mapped_T>::ConstIterator::operator*() const{
		return (static_cast<SkipNode<Key_T, Mapped_T>*>(constNodePtr)->nodePair);
	 }

    template<typename Key_T, typename Mapped_T>
    const typename Map<Key_T, Mapped_T>::ValueType* Map<Key_T, Mapped_T>::ConstIterator::operator->() const{
		//Map<Key_T, Mapped_T>::ValueType* pairPtr;
		return &(static_cast<SkipNode<Key_T, Mapped_T>*>(constNodePtr)->nodePair);
	 }

	template<typename Key_T, typename Mapped_T>
   	SkipNodeBase<Key_T, Mapped_T>* Map<Key_T, Mapped_T>::ConstIterator::getConstNodePtr() const{
		return constNodePtr;
	}

	template<typename Key_T, typename Mapped_T>
	void Map<Key_T, Mapped_T>::ConstIterator::setConstNodePtr(SkipNodeBase<Key_T, Mapped_T>* temp){
		constNodePtr = temp;
	}



/**********************************************************************************************/

/******************************REVERSE ITERATOR CLASS********************************/
	template<typename Key_T, typename Mapped_T>
	Map<Key_T, Mapped_T>::ReverseIterator::ReverseIterator(SkipNodeBase<Key_T, Mapped_T>* temp){
		if(temp == NULL) reverseNodePtr = NULL;
		else reverseNodePtr = temp;
	}

    template<typename Key_T, typename Mapped_T>
    Map<Key_T, Mapped_T>::ReverseIterator::ReverseIterator(const Map<Key_T,Mapped_T>::ReverseIterator &iter1){
        if(iter1.reverseNodePtr == NULL) reverseNodePtr = NULL;
        else reverseNodePtr = iter1.reverseNodePtr;
    }

	template<typename Key_T, typename Mapped_T>
	Map<Key_T, Mapped_T>::ReverseIterator::~ReverseIterator(){
	}


	template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T>::ReverseIterator&  Map<Key_T, Mapped_T>::ReverseIterator::operator=(const ReverseIterator &iter1){
	 	if(iter1.reverseNodePtr == NULL) reverseNodePtr = NULL;
		else{
			reverseNodePtr = iter1.reverseNodePtr;
		}
        return (*this);
	 }

    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T>::ReverseIterator& Map<Key_T, Mapped_T>::ReverseIterator::operator++(){
        if(reverseNodePtr == NULL) return (*this);
        else{
            reverseNodePtr = reverseNodePtr->backNodes[0];
            return (*this);
        }
    }

    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T>::ReverseIterator Map<Key_T, Mapped_T>::ReverseIterator::operator++(int){
        Map<Key_T, Mapped_T>::ReverseIterator iter(*this);
        if(reverseNodePtr != NULL){
            reverseNodePtr = reverseNodePtr->fwdNodes[0];
        }
        return iter;
    }

    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T>::ReverseIterator& Map<Key_T, Mapped_T>::ReverseIterator::operator--(){
        if(reverseNodePtr == NULL) return (*this);
        else{
            reverseNodePtr = reverseNodePtr->fwdNodes[0];
            return (*this);
        }
    }


    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T>::ReverseIterator Map<Key_T, Mapped_T>::ReverseIterator::operator--(int){
        Map<Key_T, Mapped_T>::ReverseIterator iter(*this);
        if(reverseNodePtr != NULL){
            reverseNodePtr = reverseNodePtr->fwdNodes[0];
        }
        return iter;
    }

    template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T>::ValueType& Map<Key_T, Mapped_T>::ReverseIterator::operator*() const{
		return (static_cast<SkipNode<Key_T, Mapped_T>*>(reverseNodePtr)->nodePair);
	 }

    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T>::ValueType* Map<Key_T, Mapped_T>::ReverseIterator::operator->() const{
		//Map<Key_T, Mapped_T>::ValueType* pairPtr;
		return &(static_cast<SkipNode<Key_T, Mapped_T>*>(reverseNodePtr)->nodePair);
	 }


	template<typename Key_T, typename Mapped_T>
	SkipNodeBase<Key_T, Mapped_T>* Map<Key_T, Mapped_T>::ReverseIterator::getReverseNodePtr() const{
		return reverseNodePtr;
	}

	template<typename Key_T, typename Mapped_T>
	void Map<Key_T, Mapped_T>::ReverseIterator::setReverseNodePtr(SkipNodeBase<Key_T, Mapped_T>* temp){
		reverseNodePtr = temp;
	}

/**********************************************************************************************/







    /***********************SKIPNODEBASE CLASS********************************************/
    template<typename Key_T, typename Mapped_T>
    SkipNodeBase<Key_T, Mapped_T>::SkipNodeBase(int x){
        if(x == 0) nodeHeight = 0;
        else nodeHeight = x-1;
        fwdNodes = new SkipNodeBase<Key_T, Mapped_T>* [x];
        backNodes = new SkipNodeBase<Key_T, Mapped_T>* [x];
        for(int i = 0; i < x; i++){
            fwdNodes[i] = NULL;
            backNodes[i] = NULL;
        }
        isSentinel = 1;
    }

    template<typename Key_T, typename Mapped_T>
    SkipNodeBase<Key_T, Mapped_T>::~SkipNodeBase(){
        delete [] fwdNodes;
        delete [] backNodes;
    }

    /**********************************************************************************************/


    /***********************SKIPNODE CLASS********************************************/
    template<typename Key_T, typename Mapped_T>
    SkipNode<Key_T, Mapped_T>::SkipNode(const Key_T k, Mapped_T obj1, int height): SkipNodeBase<Key_T, Mapped_T>(height), nodePair(k,obj1){

        /*if(k != NULL && obj1 != NULL){     --------INDIRECTION CODE------------
            const Key_T tempkey = *k;
            const Mapped_T tempObj = *obj1;
            key = new Key_T(tempkey);
            obj = new Mapped_T(tempObj);
        }
        else{
            key = k;
            obj = obj1;
        }*/
        //nodePair(k, obj1);

        /*if(height == 0) this->nodeHeight = 0;
        else this->nodeHeight = height-1;
        fwdNodes = new SkipNodeBase<Key_T, Mapped_T>* [height];
        for(int i = 0; i < height; i++){
            fwdNodes[i] = NULL;
        }
        backNodes = new SkipNodeBase<Key_T, Mapped_T>* [height];
        for(int i = 0; i < height; i++){
            backNodes[i] = NULL;
        }*/
        this->isSentinel = 0;
    }

    template<typename Key_T, typename Mapped_T>
    SkipNode<Key_T, Mapped_T>::~SkipNode(){
        //std::cout << "SkipNode dtor called" << std::endl;
         //delete key;
        //delete obj;
         delete [] fwdNodes;
        delete [] backNodes;
    }

    /*template<typename Key_T, typename Mapped_T>
    const Key_T& SkipNode<Key_T, Mapped_T>::getKey(){
        const Key_T* temp = &(nodePair.first);
        if(temp == NULL) return NULL;
        else return nodePair.first;
    }

    template<typename Key_T, typename Mapped_T>
    Mapped_T& SkipNode<Key_T, Mapped_T>::getObj(){
        Mapped_T * temp = &(nodePair.second);
        if(temp == NULL) return NULL;
        else return nodePair.second;
    }*/

/****************************************************************************/

    /**************************SKIPLIST CLASS*********************************/
    template<typename Key_T, typename Mapped_T>
    SkipList<Key_T, Mapped_T>::SkipList(){
        //std::cout << "default skiplist ctor" << std::endl;
        srand(time(NULL));
        currentHeight = 0;
        maxHeight = 32;
        prob = 0.5;
        head = new SkipNodeBase<Key_T, Mapped_T>(maxHeight);
        tail = new SkipNodeBase<Key_T, Mapped_T>(maxHeight);
        //head->setSentinel(1); tail->setSentinel(1); --->taken care of in ctor()
        for(int i = 0; i < maxHeight; i++){
            head->fwdNodes[i] = tail;
            tail->backNodes[i] = head;
        }
        //if(head->fwdNodes[0] == tail) std::cout << "CTOR: head->next = tail" << std::endl;
    }

    template<typename Key_T, typename Mapped_T>
    SkipList<Key_T, Mapped_T>::~SkipList(){
        //std::cout << "SkipList dtor called" << std::endl;
        SkipNodeBase<Key_T, Mapped_T>* temp;
        SkipNodeBase<Key_T, Mapped_T>* next;
        /*SkipNode<Key_T, Mapped_T>* temp1 = head;

        while(temp1){
            std::cout << "<-";
            if(temp1->getKey() == NULL) std::cout << "X->";
            else std::cout << *(temp1->getKey()) << "->";
            temp1 = temp1->fwdNodes[0];
        }
        std::cout << '\n';*/





        temp = head;
        //if(temp->fwdNodes[0] == tail) std::cout << "DTOR: head->next = tail" << std::endl;
        //else std::cout << "DTOR: head->next != tail" << std::endl;
        while(temp){
            //if((temp->getKey()) == NULL) std::cout << "key to be deleted: X" << std::endl;
            //else std::cout << "key to be deleted: " << *(temp->getKey()) << std::endl;
            next = temp->fwdNodes[0];
            delete temp;
            temp = next;
            //std::cout << "reaches here" << std::endl;


        }
        //std::cout << "total deletions: " << i << std::endl;
    }

    template<typename Key_T, typename Mapped_T>
    SkipNodeBase<Key_T, Mapped_T>* SkipList<Key_T, Mapped_T>::getHead() const{
            return head;
    }

    template<typename Key_T, typename Mapped_T>
    SkipNodeBase<Key_T, Mapped_T>* SkipList<Key_T, Mapped_T>::getTail() const{
            return tail;
    }

    template<typename Key_T, typename Mapped_T>
    int SkipList<Key_T, Mapped_T>::listRandomizer(){
        int tempHeight = 0;
        while( (((float)rand())/RAND_MAX < prob) && (tempHeight < (maxHeight-1)) ){
            //std::cout << "enters randomizer" << std::endl;
            tempHeight++;
        }
        return tempHeight;
    }

    template<typename Key_T, typename Mapped_T>
  	std::pair<SkipNodeBase<Key_T, Mapped_T>*, bool> SkipList<Key_T, Mapped_T>::insert(const Key_T k, Mapped_T obj, int properHeight){
        //std::cout << "insert()" << std::endl;
        int level, height;
        level = height = 0;
        std::pair<SkipNodeBase<Key_T, Mapped_T>*, bool> valuePair;

		SkipNodeBase<Key_T, Mapped_T>** updateList = new SkipNodeBase<Key_T, Mapped_T>*[maxHeight];
        SkipNodeBase<Key_T, Mapped_T>* temp = head;
        //if(head->fwdNodes[0] == tail) std::cout << "current head points to tail" << std::endl;

        /*if(head->fwdNodes[currentHeight]->getKey()){
        std::cout << "highest node: " << *(head->fwdNodes[currentHeight]->getKey()) << ", height: " << currentHeight << std::endl;
        std::cout << "height: " << currentHeight << std::endl;
        }
        else std::cout << "highest node: NULL" << std::endl;*/

        const Key_T* compareKey;
        for(height = currentHeight; height >= 0; height--){
            if( (temp->fwdNodes[height] != NULL) && (temp->fwdNodes[height]->isSentinel == 0) ){
                compareKey = &(static_cast<SkipNode<Key_T, Mapped_T>*>(temp->fwdNodes[height])->nodePair.first);
            }
            else compareKey = NULL;
            while( (compareKey != NULL) && (*compareKey < k) ){
                temp = temp->fwdNodes[height];
                if( (temp->fwdNodes[height] != NULL) && (temp->fwdNodes[height]->isSentinel == 0) ){
                    compareKey = &(static_cast<SkipNode<Key_T, Mapped_T>*>(temp->fwdNodes[height])->nodePair.first);
                }
                else compareKey = NULL;
            }
            updateList[height] = temp;  //update the updateList
            //if(updateList[height] == head) std::cout << "updateList[height] at head" << std::endl;
        }
        temp = temp->fwdNodes[0];
        if( (temp != NULL)  && (temp->isSentinel == 0) ){
            compareKey = &(static_cast<SkipNode<Key_T, Mapped_T>*>(temp)->nodePair.first);
        }
        else compareKey = NULL;
		/*std::cout << "COMPARE KEY == KEY****" << std::endl;
        if(compareKey == NULL) std::cout << k << " == X" << std::endl;
        else std::cout << k << " == " << *compareKey << std::endl;*/

        if(compareKey != NULL && *compareKey == k){
            delete [] updateList;
            //std::pair<SkipNodeBase*, bool> valuePair;
			valuePair.first = temp;
			valuePair.second = false;
			return valuePair;
        }
        else{
            if(properHeight == -1) level = listRandomizer();
            else level = properHeight;
            //std::cout << "level generated: " << level << std::endl;
            if(level > currentHeight){
                for(int i = currentHeight+1; i <= level; i++){
                    updateList[i] = head;
                }
                currentHeight = level;
            }
            //std::cout << "generated level: " << level << std::endl;
            /*for(int i = 0; i <= level; i++){
                if(updateList[i] == head) std::cout << "updateList[" << i << "] = head" << std::endl;
                if((updateList[i]->fwdNodes[i] != NULL) && (updateList[i]->fwdNodes[i] == tail)){
                    std::cout << "updateList[" << i << "]->fwdNodes[" << i << "] - tail" << std::endl;
                }
            }*/
            //SkipNode<Key_T, Mapped_T> * newNode;
            temp = new SkipNode<Key_T, Mapped_T>(k, obj, level+1);

            for(int i = 0; i <= level; i++){
                //if(updateList[i]->fwdNodes[i] == NULL) std::cout << "updatelist ptr is NULL" << std::endl;
                temp->fwdNodes[i] = updateList[i]->fwdNodes[i];
                updateList[i]->fwdNodes[i]->backNodes[i] = temp;
                updateList[i]->fwdNodes[i] = temp;
                temp->backNodes[i] = updateList[i];
            }
        }
        delete[] updateList;
        //std::cout << "SUCCESSFULLY INSERTED " << k << "*******************" << std::endl;
		 //std::pair<SkipNodeBase*, bool> valuePair;
		 valuePair.first = temp;
		valuePair.second = true;

        return valuePair;
    }



    template<typename Key_T, typename Mapped_T>
    SkipNodeBase<Key_T, Mapped_T>* SkipList<Key_T, Mapped_T>::search(const Key_T k) const{
        //std::cout << "key value: " << *k << std::endl;
        int height = 0;
        SkipNodeBase<Key_T, Mapped_T>** updateList = new SkipNodeBase<Key_T, Mapped_T>*[maxHeight];
        SkipNodeBase<Key_T, Mapped_T>* temp = head;
        const Key_T* compareKey;

        for(height = currentHeight; height >= 0; height--){
            if( (temp->fwdNodes[height] != NULL) &&  (temp->fwdNodes[height]->isSentinel == 0) ){
                compareKey = &(static_cast<SkipNode<Key_T, Mapped_T>*>(temp->fwdNodes[height])->nodePair.first);
            }
            else compareKey = NULL;
            while( (compareKey != NULL) && (*compareKey < k) ){
                temp = temp->fwdNodes[height];
                if( (temp->fwdNodes[height] != NULL)  && (temp->fwdNodes[height]->isSentinel == 0)){
                    compareKey = &(static_cast<SkipNode<Key_T, Mapped_T>*>(temp->fwdNodes[height])->nodePair.first);
                }
                else compareKey = NULL;
            }
            updateList[height] = temp;
        }
        temp = temp->fwdNodes[0];
        if( (temp != NULL) && (temp->isSentinel == 0) ){
            compareKey = &(static_cast<SkipNode<Key_T, Mapped_T>*>(temp)->nodePair.first);
        }
        else compareKey = NULL;

        delete[] updateList;

        if(compareKey == NULL) return NULL;
        else if(*compareKey == k){
            //std::cout << *(temp->getKey()) << " ";
            return temp;
        }
        else return NULL;
    }

    template<typename Key_T, typename Mapped_T>
    bool SkipList<Key_T, Mapped_T>::removeNode(const Key_T k){
        SkipNodeBase<Key_T, Mapped_T>** updateList = new SkipNodeBase<Key_T, Mapped_T>* [maxHeight];
        SkipNodeBase<Key_T, Mapped_T>* temp = head;
        const Key_T* compareKey;

        for(int i = currentHeight; i >= 0; i--){
            if( (temp->fwdNodes[i] != NULL)  &&  (temp->fwdNodes[i]->isSentinel == 0)){
                compareKey = &(static_cast<SkipNode<Key_T, Mapped_T>*>(temp->fwdNodes[i])->nodePair.first);
            }
            else compareKey = NULL;
            while( (compareKey != NULL) && (*compareKey < k) ){
                temp = temp->fwdNodes[i];
                if( (temp->fwdNodes[i] != NULL) &&  (temp->fwdNodes[i]->isSentinel == 0) ){
                    compareKey = &(static_cast<SkipNode<Key_T, Mapped_T>*>(temp->fwdNodes[i])->nodePair.first);
                }
                else compareKey = NULL;
            }
            updateList[i] = temp;
        }
        temp = temp->fwdNodes[0];
        if( (temp != NULL)  && (temp->isSentinel == 0) ){
            compareKey = &(static_cast<SkipNode<Key_T, Mapped_T>*>(temp)->nodePair.first);
        }
        else compareKey = NULL;
        if((compareKey != NULL) && (*compareKey == k)){  //keys match
            for(int i = 0; i <= currentHeight; i++){
                if(updateList[i]->fwdNodes[i] != temp) break;
                updateList[i]->fwdNodes[i] = temp->fwdNodes[i];
                updateList[i]->fwdNodes[i]->backNodes[i] = updateList[i];
            }
            delete temp;
            //decrement height to find new tallest node
            while( (currentHeight > 0) && (head->fwdNodes[currentHeight]->isSentinel == 1) ){
                currentHeight--;
            }
            delete [] updateList;
            return true;
        }
        else{ //keys don't match
            delete [] updateList;
            return false;
        }
    }

}
#endif
