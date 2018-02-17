#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <stdlib.h>										
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>

#define Deque_DEFINE(t)														\
struct Deque_##t;															\
struct Deque_##t##_Iterator;												\
																			\
void inc_def(Deque_##t##_Iterator*);											\
t& deref_def(Deque_##t##_Iterator*);										\
void dec_def(Deque_##t##_Iterator*);								\
/* global function pointer */ 											\
bool (*comPtr_##t)(const t&, const t&);									\
																		\
/* wrapper function that creates proper pointer for qsort()*/					\
/*int wrapFoo_##t(const void * object1, const void * object2){*/							\
	/*obtain object1 and object references */						\
	/*const t object1_new = *(t*)object1;*/										\
	/*const t object2_new = *(t*)object2;*/									\
 	/*return -1 if true, 1 otherwise      */							\
	/*if(comPtr_##t(object1_new, object2_new)){*/			\
	/*	return -1;	*/								\
	/*}*/									\
	/*else return 1;*/		\
/*}*/		\
struct  Deque_##t##_Iterator {								\
	int index; 														\
	int isHead; /*set to 1 if pointing to head	*/				\
	int isTail; 				\
	Deque_##t * ptr;  /*pointer to deque object */              \
	int arrayCapacity;  /*capacity of current array */         \
	int arraySize;      /*size of data in current array*/      \
	void (*inc)(Deque_##t##_Iterator*) = inc_def; /*increment iterator*/   \
	t& (*deref)(Deque_##t##_Iterator*) = deref_def;  /*dereference iterator to obtain value*/	\
	void (*dec)(Deque_##t##_Iterator*) = dec_def; /*decrement iterator */			\
};		\
							\
void Deque_##t##_ctor(Deque_##t *, bool (*)(const t &, const t &));						\
size_t size_def(Deque_##t*);		\
bool empty_def(Deque_##t*);    \
t& front_def(Deque_##t*);		\
t& back_def(Deque_##t*);		\
void pop_front_def(Deque_##t*); \
void pop_back_def(Deque_##t*);		\
void push_front_def(Deque_##t*, t); \
void push_back_def(Deque_##t*, t);   \
Deque_##t##_Iterator end_def(Deque_##t*);  \
Deque_##t##_Iterator begin_def(Deque_##t*); \
t& at_def(Deque_##t*, int);   \
void clear_def(Deque_##t*);   \
void sort_def(Deque_##t*, Deque_##t##_Iterator, Deque_##t##_Iterator); \
void dtor_def(Deque_##t*);							\
											\
struct  Deque_##t{		\
	/*int* start; */			\
	/*int* end;	*/			\
	t *array; /*circular array representing the deque*/	\
	int numElements; /*tracks number of elements*/		\
	int capacity; /*total capacity of array	*/		\
	int startData; /*value at deque head*/			\
	int endData;   /*value at deque tail*/			\
	int startIndex; /*starting index of array*/		\
	int endIndex;   /*ending index of array	*/		\
	bool (*fptr)(const t&, const t&); /*function ptr that determines how deque is sorted*/	\
			\
     char type_name[sizeof("Deque_"#t)] = "Deque_"#t; 		\
	size_t (*size)(Deque_##t*) = size_def;  /*returns size of deque (**DONE**)*/			\
	bool (*empty)(Deque_##t*) = empty_def; /*returns true if empty (**DONE**)*/			\
	t& (*front)(Deque_##t*) = front_def; /*reference to value at front (**DONE**)*/		\
	t& (*back)(Deque_##t*) = back_def;  /*reference to value at end  (**DONE**)*/			\
	void (*pop_front)(Deque_##t*) = pop_front_def; /*eject value from front (**DONE**)*/		\
	void (*pop_back)(Deque_##t*) = pop_back_def;  /*eject value from end  (**DONE**)*/			\
	void (*push_front)(Deque_##t*, t) = push_front_def; /*insert value at front (**DONE**)*/		\
	void (*push_back)(Deque_##t*, t) = push_back_def; /*insert value at end (**DONE**)*/			\
	Deque_##t##_Iterator (*end)(Deque_##t*) = end_def; /*iterator pointing to end value (**DONE**)*/		\
	Deque_##t##_Iterator (*begin)(Deque_##t*) = begin_def; /*iterator pointing to front value (**DONE**)*/		\
	t& (*at)(Deque_##t*, int) = &at_def; /*reference to value at index (**DONE**)*/					\
	void (*clear)(Deque_##t*) = &clear_def; /*clear all values in the deque (**DONE**)*/				\
																									\
	void (*sort)(Deque_##t*, Deque_##t##_Iterator, Deque_##t##_Iterator) = sort_def;			\
	void (*dtor)(Deque_##t*) = dtor_def;															\
																							\
};																									\
																						\
void Deque_##t##_ctor(Deque_##t* dptr, bool (*fn)(const t &x, const t &y)){				\
	if(fn == NULL){														\
		std::cerr << "function pointer from class is null" << std::endl;	\
	}						\
	else{							\
		dptr->fptr = fn;				\
		dptr->startIndex = -1;			\
		dptr->endIndex = 0;				\
		dptr->numElements = 0;								\
		dptr->array = new t[10];		\
		dptr->capacity = 10;											\
	}									\
}						\
						\
/*DESTRUCTOR*/				\
/*deletes values in array*/ 	\
void dtor_def(Deque_##t * dptr){		\
	if(dptr && dptr->array){		\
		delete[] (dptr->array);		\
		dptr->clear(dptr);			\
	}				\
}					\
					\
									\
			\
			\
											\
size_t size_def(Deque_##t* dptr){						\
	if(dptr && dptr->array){					\
		return (size_t)dptr->numElements;				\
	}											\
	else printf("%s %d\n", "Deque is currently empty. Returning ", 0);		\
	return 0;									\
}											\
											\
	\
				\
t& front_def(Deque_##t* dptr){						\
		\
	if(dptr && dptr->array && (dptr->numElements != 0)){	\
		return (dptr->array)[dptr->startIndex];				\
	}														\
		\
	return (dptr->array)[0];				\
}				\
							\
		\
		\
t& back_def(Deque_##t* dptr){					\
	/*check if array has been initialized and isnt empty*/		\
				\
	if(dptr && dptr->array && dptr->numElements != 0){			\
		return (dptr->array)[dptr->endIndex];				\
	}													\
		\
	return (dptr->array)[0];								\
}					\
								\
/*returns true if deque is empty, false otherwise*/		\
bool empty_def(Deque_##t* dptr){					\
	/*true if dptr or deque hasnt been initialized*/		\
	if(dptr == NULL || dptr->array == NULL || dptr->size(dptr) == 0){		\
		return true;			\
	}				\
	/*check if any value in array isn't NULL */		\
	else if(dptr && dptr->array){			\
		if(dptr->numElements == 0){			\
			return true;					\
		}									\
		else return false;					\
	}										\
	return true;							\
}											\
											\
/*returns value at index*/					\
t& at_def(Deque_##t* dptr, int index){			\
	if(dptr && dptr->array){					\
		/*index out of bounds	*/				\
		if(index < 0 || index > (dptr->capacity)-1){		\
			std::cerr << "index out of bounds. returning 0" << std::endl;		\
			return (dptr->array)[0];											\
		}							\
		/*index inside of deque	*/							\
		if(index >= 0 && index < dptr->numElements){					\
			/*wrap-around needed		*/								\
			if((dptr->startIndex+index) >= dptr->capacity){				\
				/*wrap around to first element of array	*/				\
				if((dptr->startIndex+index) == dptr->capacity){			\
					return (dptr->array)[0];							\
				}														\
				/*greater wrap around needed (index > 1)*/				\
				else if((dptr->startIndex+index) > dptr->capacity){		\
										\
					if(dptr->startIndex == (dptr->capacity-1)){			\
										\
						return (dptr->array)[0+(index-1)];				\
					}													\
											\
					else if(dptr->startIndex != (dptr->capacity-1)){	\
						int i = 1;										\
								\
						while( (dptr->startIndex+i) != (dptr->capacity-1)){			\
							i++;													\
						}															\
								\
						return (dptr->array)[0+((index-i)-1)];						\
					}																\
				}																	\
			}																		\
														\
			else if((dptr->startIndex+index) < dptr->capacity){						\
				return (dptr->array)[dptr->startIndex+index];						\
			}																		\
		}																			\
		else{																		\
			std::cout << "index not in queue. returning 0." << std::endl;			\
			return (dptr->array)[0];																\
		}																			\
	}																				\
	std::cout << "array uninitialized. Returning 0." << std::endl;					\
	return (dptr->array)[0];																		\
}																					\
																					\
									\
Deque_##t##_Iterator begin_def(Deque_##t* dptr){											\
	Deque_##t##_Iterator iter;														\
								\
	if(dptr && dptr->array){														\
		iter.ptr = dptr;															\
		iter.index = (dptr->startIndex);											\
		iter.arrayCapacity = dptr->capacity;										\
		iter.arraySize = dptr->numElements;											\
		iter.isHead = 1;															\
		iter.isTail = 0;															\
		return iter;																\
	}																				\
	else{  									\
		iter.ptr = NULL;															\
		iter.index = -1;															\
		iter.arrayCapacity = iter.arraySize = 0;									\
		iter.isHead = iter.isTail = 0;												\
		return iter;																\
	}																				\
}																					\
																					\
										\
Deque_##t##_Iterator end_def(Deque_##t* dptr){											\
	Deque_##t##_Iterator iter;														\
	/*set Iter's ptr to NULL if dptr or its array is NULL*/							\
	if(dptr && dptr->array){														\
															\
		if(dptr->endIndex == (dptr->capacity)-1){									\
			iter.index = 0;															\
		}																			\
															\
		else{																		\
			iter.index = ((dptr->endIndex)+1);										\
		}																			\
		iter.ptr = dptr;															\
		iter.arrayCapacity = dptr->capacity;										\
		iter.arraySize = dptr->numElements;											\
		iter.isTail = 1;															\
		iter.isHead = 0;															\
		return iter;																\
	}																				\
	else{  									\
		iter.ptr = NULL;															\
		iter.index = -1;															\
		iter.arrayCapacity = iter.arraySize = 0;									\
		iter.isHead = iter.isTail = 0;												\
		return iter;																\
	}																				\
}																					\
																					\
														\
						\
void clear_def(Deque_##t* dptr){														\
	if(dptr && dptr->array){														\
													\
		dptr->startIndex = -1;														\
		dptr->endIndex = -1;														\
		dptr->numElements = 0;														\
	}																				\
	else{																			\
		std::cerr << "Deque or its array hasn't been initialized" << std::endl;		\
	}																				\
}																					\
																					\
												\
void pop_front_def(Deque_##t* dptr){													\
	/*check if deque and array are initialized*/										\
	if(dptr && dptr->array){														\
																\
		if(dptr->numElements > 0){													\
																\
			if(dptr->startIndex == dptr->endIndex){									\
				dptr->startIndex = -1;												\
				dptr->endIndex = -1;												\
			}																		\
							\
			else if(dptr->startIndex != (dptr->capacity)-1){						\
				(dptr->startIndex)++;												\
			}																		\
															\
			else if(dptr->startIndex == (dptr->capacity)-1){						\
				dptr->startIndex = 0;												\
			}																		\
			(dptr->numElements)--; 					\
		}																			\
		else{																		\
			std::cout << "Deque is empty" << std::endl;								\
			dptr->startIndex = dptr->endIndex = -1;									\
		}																			\
																					\
	}else{																			\
		std::cerr << "Deque and/or its array haven't been initialized" << std::endl;	\
	}																				\
}																					\
																				\
											\
void pop_back_def(Deque_##t *dptr){												\
									\
	if(dptr && dptr->array){												\
														\
		if(dptr->numElements > 0){											\
															\
			if(dptr->startIndex == dptr->endIndex){							\
				dptr->startIndex = dptr->endIndex = -1;						\
			}																\
			/*one more than one element and REAR isnt at front of array*/			\
			else if(dptr->endIndex != 0){									\
				(dptr->endIndex)--;											\
			}																\
			/*REAR is at front of array	*/									\
			else if(dptr->endIndex == 0){									\
				dptr->endIndex = (dptr->capacity)-1;						\
			}																\
			(dptr->numElements)--; 			\
		}																	\
		else{																\
			std::cout << "Deque is empty" << std::endl;						\
			dptr->startIndex = dptr->endIndex = -1;							\
		}																	\
	}else{																	\
		std::cout << "Deque is empty" << std::endl;							\
		dptr->startIndex = dptr->endIndex = -1;								\
	}																		\
}																				\
																			\
											\
				\
void push_front_def(Deque_##t *dptr, t val){									\
	if(dptr){															\
										\
		if(dptr->array == NULL){											\
			dptr->array = new t[10];										\
			dptr->capacity = 10;											\
			if(dptr->startIndex == -1){										\
				dptr->startIndex = dptr->endIndex = 0;						\
			}																\
			(dptr->array)[dptr->endIndex] = val; 		\
		}																		\
		else{ 								\
														\
			if(dptr->numElements == 0){											\
										\
				if(dptr->startIndex == -1){											\
					dptr->startIndex = 0;										\
					dptr->endIndex = 0;									\
				}														\
				dptr->array[dptr->endIndex] = val;						\
			}															\
											\
			if(dptr->numElements > 0 && dptr->numElements < dptr->capacity){		\
												\
				if(dptr->startIndex == 0){										\
					dptr->startIndex = (dptr->capacity)-1;						\
					(dptr->array)[dptr->startIndex] = val;					\
				}															\
								\
				else{													\
					(dptr->startIndex)--;								\
					(dptr->array)[dptr->startIndex] = val;				\
				}														\
																		\
			}															\
															\
			else if(dptr->numElements == dptr->capacity){				\
				t * temp = dptr->array;								\
				int i;													\
													\
				(dptr->capacity) *= 2;										\
				dptr->array = new t[dptr->capacity];						\
														\
				if(dptr->endIndex < dptr->startIndex){						\
					std::memcpy(&((dptr->array)[(dptr->capacity)/2]), &(temp[0]), (sizeof(t))*(dptr->endIndex+1));  \
					int currentIndex = dptr->endIndex;					\
											\
					dptr->endIndex = ((dptr->capacity)/2)+(currentIndex);			\
					delete[] temp; 					\
				}														\
												\
				else if(dptr->endIndex > dptr->startIndex){				\
					std::memcpy(&((dptr->array)[0]), &(temp[0]), (sizeof(t))*(( (dptr->endIndex)-(dptr->startIndex) )+1) );	\
								\
					dptr->startIndex = 0; 			\
					dptr->endIndex = ((dptr->capacity)/2)-1;      		\
					delete[] temp; 							\
				}																	\
													\
				if(dptr->startIndex == 0){											\
					dptr->startIndex = (dptr->capacity)-1;						\
					(dptr->array)[dptr->startIndex] = val;							\
				}																\
														\
				else if(dptr->startIndex != 0){										\
					(dptr->startIndex)--;											\
					(dptr->array)[dptr->startIndex] = val;							\
				}															\
																	\
			}													\
		}														\
		(dptr->numElements)++; 			\
	}														\
				\
	else{								\
		std::cerr << "Deque wasn't initialized" << std::endl;			\
	}													\
}											\
												\
void push_back_def(Deque_##t *dptr, t val){				\
	if(dptr){									\
					\
		if(dptr->array == NULL || dptr->numElements == 0){		\
			if(dptr->array == NULL){					\
				dptr->array = new t[10];				\
			}											\
			if(dptr->startIndex == -1){					\
				dptr->startIndex = dptr->endIndex = 0;		\
			}											\
			(dptr->array)[dptr->endIndex] = val;			\
		}													\
											\
		else if(dptr->numElements > 0 && dptr->numElements < dptr->capacity){	\
								\
			if(dptr->endIndex == ((dptr->capacity)-1)){			\
				dptr->endIndex = 0;							\
			}											\
			else{ 				\
			 (dptr->endIndex)++;						\
			}											\
			(dptr->array)[dptr->endIndex] = val;		\
		}												\
											\
		else if(dptr->numElements == dptr->capacity){			\
			t * temp = dptr->array;							\
								\
			(dptr->capacity) *= 2;						\
			dptr->array = new t[dptr->capacity];		\
									\
			if(dptr->endIndex < dptr->startIndex){			\
				std::memcpy(&((dptr->array)[(dptr->capacity)/2]), &(temp[0]), (sizeof(int))*(dptr->endIndex+1));		\
				int currentIndex = dptr->endIndex;			\
				dptr->endIndex = ((dptr->capacity)/2)+(currentIndex);		\
				delete[] temp;					\
			}							\
							\
			else if(dptr->endIndex > dptr->startIndex){		\
				std::memcpy(&((dptr->array)[0]), &(temp[0]), (sizeof(int))*(( (dptr->endIndex)-(dptr->startIndex) )+1));		\
				dptr->startIndex = 0; 			\
				dptr->endIndex =  ((dptr->capacity)/2)-1;    		\
				delete[] temp;				\
			}			\
					\
					\
			if(dptr->endIndex == (dptr->capacity)-1){		\
				dptr->endIndex = 0;						\
														\
			}												\
										\
			else if(dptr->endIndex != (dptr->capacity)-1){				\
				(dptr->endIndex)++;								\
			}											\
			(dptr->array)[dptr->endIndex] = val; 		\
		}						\
															\
		(dptr->numElements)++; 		\
	}							\
	else{			\
		std::cerr << "Deque wasn't initialized" << std::endl;					\
	}																	\
}								\
bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator iter1, Deque_##t##_Iterator iter2){  \
	/*check if iterators are pointing to Deques	*/			\
	if(iter1.ptr && iter2.ptr){								\
		if(iter1.ptr == iter2.ptr){							\
			/*std::cout << "iters are pointing to the same deque" << std::endl;*/			\
									\
			if(iter1.index == iter2.index){				\
				return true;					\
			}								\
		}					\
	}						\
	return false;						\
}												\
void sort_def(Deque_##t* dptr, Deque_##t##_Iterator iter1, Deque_##t##_Iterator iter2){	\
	/*qsort(void *base, size_t num, size_t size, int (*compar)(const void*, const void*));*/ \
	while(!Deque_##t##_Iterator_equal(iter1, iter2)){										\
		Deque_##t##_Iterator iter3 = iter1;									\
		int minIndex = iter3.index;									\
		while(!Deque_##t##_Iterator_equal(iter3, iter2)){						\
			if(dptr->fptr(iter3.deref(&iter3), iter1.deref(&iter1))){					\
				minIndex = iter3.index;			\
			}	\
			iter3.inc(&iter3);																\
		}																				\
			t temp = iter1.deref(&iter1);					\
			iter1.deref(&iter1) = (dptr->array)[minIndex]; 		\
			(dptr->array)[minIndex] = temp;	 \
			iter1.inc(&iter1);                                \
	}	   \
}																					\
																		\
bool Deque_##t##_equal(Deque_##t deq1, Deque_##t deq2){								\
				\
		bool retVal;									\
		if(deq1.numElements == deq2.numElements){					\
														\
			if(deq1.numElements == 0 && deq2.numElements == 0){						\
				return true;											\
			}													\
			Deque_##t##_Iterator iter1, iter2;						\
			iter1 = deq1.begin(&deq1);								\
			iter2 = deq2.begin(&deq2);								\
			for(; !Deque_##t##_Iterator_equal(iter1, deq1.end(&deq1)); iter1.inc(&iter1), iter2.inc(&iter2)){		\
				/*for(; !Deque_int_Iterator_equal(iter2, deq2.end(&deq2)); iter2.inc(&iter2)){*/		\
					/*printf("deq1: %d, deq2: %d\n", iter1.deref(&iter1), iter2.deref(&iter2)); */			\
					/*check if comparison function results are different*/				\
					/*deques are same if !(a.fn(a,b)) && !(b.fn(b,a))	*/				\
					if( (deq1.fptr(iter1.deref(&iter1), iter2.deref(&iter2))) || (deq2.fptr(iter2.deref(&iter2), iter1.deref(&iter1)))){	\
						return false;			\
					}								\
				/* } */					\
			}						\
					\
			return true;				\
		}				\
		else return false;			\
}				\
																					\
/*Iterator functions*/									\
																\
								\
void inc_def(Deque_##t##_Iterator* iter){									\
	if(iter){											\
		/*iter is at end of array	*/							\
		if(iter->index == (iter->ptr->capacity)-1){							\
			iter->index = 0;											\
		}														\
		/*iter is somewhere before the end of array*/						\
		else if(iter->index < (iter->ptr->capacity)-1){					\
			(iter->index)++;										\
		}														\
	}													\
	else{														\
		std::cerr << "iterator is uninitialized." << std::endl;				\
	}																	\
}																	\
										\
																\
/*TODO: might have to check if iter is in DATA RANGE*/					\
void dec_def(Deque_##t##_Iterator* iter){							\
	/*check if iter is initialized	*/								\
	if(iter){													\
		/*iter is at beginning of array	*/								\
		if(iter->index == 0){										\
			iter->index = (iter->ptr->capacity)-1;						\
			/*next data entry is at end of array*/							\
			/*if(iter->ptr->endIndex == (iter->ptr->capacity)-1){	} */					\
		}																\
		else{  				\
			(iter->index)--;								\
		}											\
	}									\
	else std::cerr << "iterator is uninitialized." << std::endl;		\
}					\
												\
										\
t& deref_def(Deque_##t##_Iterator* iter){				\
	if(iter){												\
		return ((iter->ptr->array)[iter->index]);			\
	}																\
	else{									\
		std::cerr << "Iterator isn't initialized. Returning 0." << std::endl;			\
		return ((iter->ptr->array))[0];														\
	}														\
}																		\

#endif															
