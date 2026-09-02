
#ifndef ArrayTableStorage_hpp
	#define ArrayTableStorage_hpp

	#include "TableStorage.hpp"
	#include "MemoryHolderManager.hpp"

	#if defined(pankey_Log) && (defined(ArrayTableStorage_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
	#include "Logger_status.hpp"
		#define ArrayTableStorageLog(status,method,mns) pankey_Log(status,"ArrayTableStorage",method,mns)
	#else
		#define ArrayTableStorageLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class H>
			class ArrayTableStorage : virtual public TableStorage<H>{
				public:
					using MANAGER_TYPE = typename TableStorage<H>::MANAGER_TYPE;
					using VOID_TYPE = typename TableStorage<H>::VOID_TYPE;
					using HOLDER_TYPE = typename TableStorage<H>::HOLDER_TYPE;

					ArrayTableStorage(){
						ArrayTableStorageLog(pankey_Log_StartMethod, "Constructor", "");
						ArrayTableStorageLog(pankey_Log_EndMethod, "Constructor", "");
					}

					virtual ~ArrayTableStorage(){
						ArrayTableStorageLog(pankey_Log_StartMethod, "Destructor", "");
						ArrayTableStorageLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					virtual bool isNull()const{
						ArrayTableStorageLog(pankey_Log_StartMethod, "isNull", "");
						ArrayTableStorageLog(pankey_Log_EndMethod, "isNull", this->m_keys == nullptr || this->m_values == nullptr);
						return this->m_keys == nullptr || this->m_values == nullptr;
					}
					
					virtual bool isNull(int a_index)const{
						ArrayTableStorageLog(pankey_Log_StartMethod, "isNull", "");
						ArrayTableStorageLog(pankey_Log_Statement, "isNull", "Index:");
						ArrayTableStorageLog(pankey_Log_Statement, "isNull", a_index);
						if(this->m_keys == nullptr || this->m_values == nullptr){
							ArrayTableStorageLog(pankey_Log_EndMethod, "isNull", "this->m_values == nullptr");
							return true;
						}
						if(this->getSize() <= 0){
							ArrayTableStorageLog(pankey_Log_EndMethod, "isNull", "this->getSize() < 0");
							return true;
						}
						if(this->m_keys[a_index] == nullptr || this->m_values[a_index] == nullptr){
							ArrayTableStorageLog(pankey_Log_EndMethod, "isNull", "this->m_values[a_index] == nullptr");
							return true;
						}
						ArrayTableStorageLog(pankey_Log_EndMethod, "isNull", "");
						return false;
					}
					
					virtual bool isKeyNull(int a_index)const{
						ArrayTableStorageLog(pankey_Log_StartMethod, "isKeyNull", "");
						ArrayTableStorageLog(pankey_Log_Statement, "isKeyNull", "Index:");
						ArrayTableStorageLog(pankey_Log_Statement, "isKeyNull", a_index);
						if(this->m_keys == nullptr){
							ArrayTableStorageLog(pankey_Log_EndMethod, "isKeyNull", "this->m_values == nullptr");
							return true;
						}
						if(this->getSize() <= 0){
							ArrayTableStorageLog(pankey_Log_EndMethod, "isKeyNull", "this->getSize() < 0");
							return true;
						}
						if(this->m_keys[a_index] == nullptr){
							ArrayTableStorageLog(pankey_Log_EndMethod, "isKeyNull", "this->m_values[a_index] == nullptr");
							return true;
						}
						ArrayTableStorageLog(pankey_Log_EndMethod, "isKeyNull", "");
						return false;
					}
					
					virtual bool isValueNull(int a_index)const{
						ArrayTableStorageLog(pankey_Log_StartMethod, "isValueNull", "");
						ArrayTableStorageLog(pankey_Log_Statement, "isValueNull", "Index:");
						ArrayTableStorageLog(pankey_Log_Statement, "isValueNull", a_index);
						if(this->m_values == nullptr){
							ArrayTableStorageLog(pankey_Log_EndMethod, "isValueNull", "this->m_values == nullptr");
							return true;
						}
						if(this->getSize() <= 0){
							ArrayTableStorageLog(pankey_Log_EndMethod, "isValueNull", "this->getSize() < 0");
							return true;
						}
						if(this->m_values[a_index] == nullptr){
							ArrayTableStorageLog(pankey_Log_EndMethod, "isValueNull", "this->m_values[a_index] == nullptr");
							return true;
						}
						ArrayTableStorageLog(pankey_Log_EndMethod, "isValueNull", "");
						return false;
					}

					virtual bool set(int a_position, const MemoryHolder<H>& a_key, const MemoryHolder<H>& a_value){
						// ArrayTableStorageLog(pankey_Log_StartMethod, "set", "");
						// ArrayTableStorageLog(pankey_Log_Statement, "set", "Position: ");
						// ArrayTableStorageLog(pankey_Log_Statement, "set", a_position);

						// if(this->isNull() || a_position >= this->getSize() || a_position < 0){
						// 	ArrayTableStorageLog(pankey_Log_EndMethod, "set", "this->isNull() || a_position >= this->getSize() || a_position < 0");
						// 	return false;
						// }

						// HOLDER_TYPE i_key_holder = a_key.getHolder();
						// HOLDER_TYPE i_value_holder = a_key.getHolder();

						// ArrayTableStorageLog(pankey_Log_Statement, "set", "Is Key Holder == nullptr");
						// ArrayTableStorageLog(pankey_Log_Statement, "set", i_key_holder == nullptr);

						// ArrayTableStorageLog(pankey_Log_Statement, "set", "Is Value Holder == nullptr");
						// ArrayTableStorageLog(pankey_Log_Statement, "set", i_value_holder == nullptr);

						// if(i_key_holder == this->m_keys[a_position] && i_value_holder == this->m_values[a_position]){
						// 	ArrayTableStorageLog(pankey_Log_EndMethod, "set", "i_holder == this->m_values[a_position]");
						// 	return true;
						// }

						// MemoryHolderManager<H>::add(this->getManager(), i_key_holder);
						// MemoryHolderManager<H>::remove(this->getManager(), this->m_keys[a_position]);

						// MemoryHolderManager<H>::add(this->getManager(), i_value_holder);
						// MemoryHolderManager<H>::remove(this->getManager(), this->m_values[a_position]);
						
						// this->m_keys[a_position] = i_key_holder;
						// this->m_values[a_position] = i_value_holder;

						// ArrayTableStorageLog(pankey_Log_EndMethod, "set", "");
						return true;
					}

					virtual bool add(int a_position, const MemoryHolder<H>& a_key, const MemoryHolder<H>& a_value){
						ArrayTableStorageLog(pankey_Log_StartMethod, "add", "");
						ArrayTableStorageLog(pankey_Log_Statement, "add", "Position: ");
						ArrayTableStorageLog(pankey_Log_Statement, "add", a_position);

						if(this->isNull() || a_position >= this->getSize() || a_position < 0){
							ArrayTableStorageLog(pankey_Log_Statement, "add", "this->isNull() || a_position >= this->getSize() || a_position < 0");
							this->expand(a_position - this->getSize() + this->expandRate);
						}
						ArrayTableStorageLog(pankey_Log_EndMethod, "add", "");
						return this->set(a_position, a_key, a_value);
					}

					virtual bool contain(const MemoryHolder<H>& a_value)const{
						ArrayTableStorageLog(pankey_Log_StartMethod, "contain", "");
						if(this->isNull()){
							ArrayTableStorageLog(pankey_Log_Statement, "contain", "this->isNull()");
							ArrayTableStorageLog(pankey_Log_EndMethod, "contain", "return false");
							return false;
						}

						// VOID_TYPE i_pointer_1 = a_value.getRawPointer();

						// for(int x = 0; x < this->getSize(); x++){
						// 	VOID_TYPE f_pointer_2 = MemoryHolderManager<H>::get(this->getManager(), this->m_values[x]);;
						// 	if(i_pointer_1 == f_pointer_2){
						// 		ArrayTableStorageLog(pankey_Log_Statement, "contain", "a_value == this->m_values[x]");
						// 		ArrayTableStorageLog(pankey_Log_EndMethod, "contain", "return true");
						// 		return true;
						// 	}
						// }

						ArrayTableStorageLog(pankey_Log_EndMethod, "contain", "");
						return false;
					}
					
					virtual int getIndex(const MemoryHolder<H>& a_value)const{
						ArrayTableStorageLog(pankey_Log_StartMethod, "getIndex", "");
						if(this->isNull()){
							ArrayTableStorageLog(pankey_Log_EndMethod, "getIndex", "this->isNull()");
							return -1;
						}

						// VOID_TYPE i_pointer_1 = a_value.getRawPointer();

						// for(int x = 0; x < this->getSize(); x++){
						// 	VOID_TYPE f_pointer_2 = MemoryHolderManager<H>::get(this->getManager(), this->m_values[x]);;
						// 	if(i_pointer_1 == f_pointer_2){
						// 		ArrayTableStorageLog(pankey_Log_EndMethod, "getIndex", "a_value == this->m_values[x]");
						// 		return x;
						// 	}
						// }

						ArrayTableStorageLog(pankey_Log_EndMethod, "getIndex", "");
						return -1;
					}
					
					virtual VOID_TYPE getKeyRawPointer(int a_position)const{
						ArrayTableStorageLog(pankey_Log_StartMethod, "getRawPointer", "");

						// if(this->isNull() || a_position >= this->getSize() || a_position < 0){
						// 	ArrayTableStorageLog(pankey_Log_EndMethod, "getRawPointer", "");
						// 	return nullptr;
						// }

						// ArrayTableStorageLog(pankey_Log_EndMethod, "getRawPointer", "");
						// return MemoryHolderManager<H>::get(this->getManager(), this->m_values[a_position]);
						return nullptr;
					}
					
					virtual VOID_TYPE getValueRawPointer(int a_position)const{
						ArrayTableStorageLog(pankey_Log_StartMethod, "getValueRawPointer", "");

						// if(this->isNull() || a_position >= this->getSize() || a_position < 0){
						// 	ArrayTableStorageLog(pankey_Log_EndMethod, "getRawPointer", "");
						// 	return nullptr;
						// }

						// ArrayTableStorageLog(pankey_Log_EndMethod, "getValueRawPointer", "");
						// return MemoryHolderManager<H>::get(this->getManager(), this->m_values[a_position]);
						return nullptr;
					}
					
					virtual HOLDER_TYPE getKeyHolder(int a_position)const{
						ArrayTableStorageLog(pankey_Log_StartMethod, "get", "");

						// if(this->isNull() || a_position >= this->getSize() || a_position < 0){
						// 	ArrayTableStorageLog(pankey_Log_EndMethod, "get", "");
						// 	return nullptr;
						// }

						// ArrayTableStorageLog(pankey_Log_EndMethod, "get", "");
						// return this->m_values[a_position];
						return nullptr;
					}
					
					virtual HOLDER_TYPE getValueHolder(int a_position)const{
						ArrayTableStorageLog(pankey_Log_StartMethod, "getValueHolder", "");

						// if(this->isNull() || a_position >= this->getSize() || a_position < 0){
						// 	ArrayTableStorageLog(pankey_Log_EndMethod, "getValueHolder", "");
						// 	return nullptr;
						// }

						// ArrayTableStorageLog(pankey_Log_EndMethod, "getValueHolder", "");
						// return this->m_values[a_position];
						return nullptr;
					}

					virtual bool removeByPointer(const MemoryHolder<H>& a_value){
						ArrayTableStorageLog(pankey_Log_StartMethod, "removeByPointer", "");

						// int i_position = this->getIndex(a_value);

						// ArrayTableStorageLog(pankey_Log_Statement, "removeByPointer", "removed position: ");
						// ArrayTableStorageLog(pankey_Log_Statement, "removeByPointer", i_position);

						// if(this->isNull() || i_position >= this->getSize() || i_position < 0){
						// 	ArrayTableStorageLog(pankey_Log_EndMethod, "removeByPointer", "");
						// 	return false;
						// }
						
						// MemoryHolderManager<H>::remove(this->getManager(), this->m_values[i_position]);

						// ArrayTableStorageLog(pankey_Log_EndMethod, "removeByPointer", "");
						return true;
					}

					virtual bool removeFirstIndex(int a_length, int a_amount){
						ArrayTableStorageLog(pankey_Log_StartMethod, "removeFirstIndex", "");

						// if(this->isNull() || a_amount <= 0){
						// 	ArrayTableStorageLog(pankey_Log_EndMethod, "removeFirstIndex", "");
						// 	return false;
						// }

						// if(a_amount > a_length){
						// 	ArrayTableStorageLog(pankey_Log_Statement, "removeFirstIndex", "a_amount > this->getSize()");
						// 	a_amount = a_length;
						// }

						// for(int x = 0; x < a_amount; x++){
						// 	ArrayTableStorageLog(pankey_Log_Statement, "removeFirstIndex", "for loop index");
						// 	ArrayTableStorageLog(pankey_Log_Statement, "removeFirstIndex", x);
						// 	MemoryHolderManager<H>::remove(this->getManager(), this->m_values[x]);
						// }

						// ArrayTableStorageLog(pankey_Log_EndMethod, "removeFirstIndex", "");
						return true;
					}

					virtual bool removeLastIndex(int a_length, int a_amount){
						ArrayTableStorageLog(pankey_Log_StartMethod, "removeLastIndex", "");

						// if(this->isNull() || a_amount < 0){
						// 	ArrayTableStorageLog(pankey_Log_EndMethod, "removeLastIndex", "");
						// 	return false;
						// }

						// if(a_amount > a_length){
						// 	ArrayTableStorageLog(pankey_Log_Statement, "removeFirstIndex", "a_amount > this->getSize()");
						// 	a_amount = a_length;
						// }

						// for(int x = a_length - 1; x >= a_length - a_amount; x--){
						// 	ArrayTableStorageLog(pankey_Log_Statement, "removeLastIndex", "for loop index");
						// 	ArrayTableStorageLog(pankey_Log_Statement, "removeLastIndex", x);
						// 	MemoryHolderManager<H>::remove(this->getManager(), this->m_values[x]);
						// }

						// ArrayTableStorageLog(pankey_Log_EndMethod, "removeLastIndex", "");
						return true;
					}

					virtual bool removePart(int a_index, int a_length, int a_amount){
						ArrayTableStorageLog(pankey_Log_StartMethod, "removePart", "");

						// if(this->isNull() || a_index < 0 || a_amount <= 0){
						// 	ArrayTableStorageLog(pankey_Log_EndMethod, "removePart", "this->isNull() || a_index <= 0 || a_amount <= 0");
						// 	return false;
						// }

						// if(a_index + a_amount > a_length){
						// 	ArrayTableStorageLog(pankey_Log_Statement, "removePart", "a_index + a_amount > a_length");
						// 	ArrayTableStorageLog(pankey_Log_Statement, "removePart", a_index + a_amount);
						// 	a_amount = a_length - a_index;
						// }

						// for(int x = a_index; x < a_index + a_amount; x++){
						// 	ArrayTableStorageLog(pankey_Log_Statement, "removePart", "for loop index");
						// 	ArrayTableStorageLog(pankey_Log_Statement, "removePart", x);
						// 	MemoryHolderManager<H>::remove(this->getManager(), this->m_values[x]);
						// }

						// ArrayTableStorageLog(pankey_Log_EndMethod, "removePart", "");
						return true;
					}

					virtual bool removeFirst(){
						ArrayTableStorageLog(pankey_Log_StartMethod, "removeFirst", "");

						// if(this->isNull() || this->getSize() < 1){
						// 	ArrayTableStorageLog(pankey_Log_EndMethod, "removeFirst", "");
						// 	return false;
						// }
						
						// MemoryHolderManager<H>::remove(this->getManager(), this->m_values[0]);

						// ArrayTableStorageLog(pankey_Log_EndMethod, "removeFirst", "");
						return true;
					}

					virtual bool removeLast(){
						ArrayTableStorageLog(pankey_Log_StartMethod, "removeLast", "");
						// ArrayTableStorageLog(pankey_Log_Statement, "removeLast", "removing index");
						// ArrayTableStorageLog(pankey_Log_Statement, "removeLast", this->getSize() - 1);

						// if(this->isNull() || this->getSize() < 1){
						// 	ArrayTableStorageLog(pankey_Log_EndMethod, "removeLast", "");
						// 	return false;
						// }
						
						// MemoryHolderManager<H>::remove(this->getManager(), this->m_values[this->getSize() - 1]);
						
						// ArrayTableStorageLog(pankey_Log_EndMethod, "removeLast", "");
						return true;
					}

					virtual bool clear(){
						ArrayTableStorageLog(pankey_Log_StartMethod, "clear", "");

						// if(this->isNull()){
						// 	ArrayTableStorageLog(pankey_Log_EndMethod, "clear", "this->isNull()");
						// 	return false;
						// }

						// for(int x = 0; x < this->getSize(); x++){
						// 	ArrayTableStorageLog(pankey_Log_Statement, "clear", "for loop index");
						// 	ArrayTableStorageLog(pankey_Log_Statement, "clear", x);
						// 	MemoryHolderManager<H>::remove(this->getManager(), this->m_values[x]);
						// }

						// ArrayTableStorageLog(pankey_Log_EndMethod, "clear", "");
						return true;
					}

					virtual int reorder(){
						ArrayTableStorageLog(pankey_Log_StartMethod, "reorder", "");

						// if(this->isNull()){
						// 	ArrayTableStorageLog(pankey_Log_EndMethod, "reorder", "this->isNull()");
						// 	return -1;
						// }

						int i_offset = 0;

						// for(int x = 0; x < this->getSize(); x++){
						// 	ArrayTableStorageLog(pankey_Log_Statement, "reorder", "for loop index");
						// 	ArrayTableStorageLog(pankey_Log_Statement, "reorder", x);
						// 	ArrayTableStorageLog(pankey_Log_Statement, "reorder", "for loop i_offset");
						// 	ArrayTableStorageLog(pankey_Log_Statement, "reorder", i_offset);

						// 	HOLDER_TYPE f_value = this->m_values[x];

						// 	if(f_value == nullptr){
						// 		ArrayTableStorageLog(pankey_Log_Statement, "reorder", "f_value == nullptr");
						// 		continue;
						// 	}
							
						// 	if(i_offset != x){
						// 		ArrayTableStorageLog(pankey_Log_Statement, "reorder", "i_offset != x");
						// 		this->m_values[i_offset] = f_value;
						// 		this->m_values[x] = nullptr;
						// 	}

						// 	ArrayTableStorageLog(pankey_Log_Statement, "reorder", "this->m_values[i_offset] = f_value");
						// 	i_offset++;
						// }

						// ArrayTableStorageLog(pankey_Log_EndMethod, "reorder", "");
						return i_offset;
					}

					virtual int reorder(int a_index, int a_length, int a_amount){
						ArrayTableStorageLog(pankey_Log_StartMethod, "reorder", "");

						if(this->isNull()){
							ArrayTableStorageLog(pankey_Log_EndMethod, "reorder", "this->isNull()");
							return -1;
						}

						int i_offset = a_index;

						// if(this->getSize() - a_length < a_amount && a_length < a_index + a_amount){
						// 	ArrayTableStorageLog(pankey_Log_Statement, "reorder", "this->getSize() - a_length < a_amount && a_length < a_index + a_amount");
						// 	ArrayTableStorageLog(pankey_Log_Statement, "reorder", "this->getSize() - a_length");
						// 	ArrayTableStorageLog(pankey_Log_Statement, "reorder", this->getSize() - a_length);
						// 	ArrayTableStorageLog(pankey_Log_Statement, "reorder", "a_amount");
						// 	ArrayTableStorageLog(pankey_Log_Statement, "reorder", a_amount);
						// 	ArrayTableStorageLog(pankey_Log_Statement, "reorder", "a_length");
						// 	ArrayTableStorageLog(pankey_Log_Statement, "reorder", a_length);
						// 	ArrayTableStorageLog(pankey_Log_Statement, "reorder", "a_index + a_amount");
						// 	ArrayTableStorageLog(pankey_Log_Statement, "reorder", a_index + a_amount);
						// 	return -1;
						// }

						// if(a_index + a_amount > a_length){
						// 	ArrayTableStorageLog(pankey_Log_Statement, "reorder", "a_index + a_amount > a_length");
						// 	ArrayTableStorageLog(pankey_Log_Statement, "reorder", a_index + a_amount);
						// 	a_amount = a_length - a_index;
						// }

						// for(int x = a_index + a_amount; x < a_length; x++){
						// 	ArrayTableStorageLog(pankey_Log_Statement, "reorder", "for loop index");
						// 	ArrayTableStorageLog(pankey_Log_Statement, "reorder", x);
						// 	ArrayTableStorageLog(pankey_Log_Statement, "reorder", "for loop i_offset");
						// 	ArrayTableStorageLog(pankey_Log_Statement, "reorder", i_offset);

						// 	HOLDER_TYPE f_value = this->m_values[x];
							
						// 	if(i_offset != x){
						// 		ArrayTableStorageLog(pankey_Log_Statement, "reorder", "i_offset != x");
						// 		this->m_values[i_offset] = f_value;
						// 		this->m_values[x] = nullptr;
						// 	}

						// 	ArrayTableStorageLog(pankey_Log_Statement, "reorder", "this->m_values[i_offset] = f_value");
						// 	i_offset++;
						// }

						// ArrayTableStorageLog(pankey_Log_EndMethod, "reorder", "");
						return i_offset;
					}

					virtual int reorder(int a_index, int a_length){
						return this->reorder(a_index, a_length, 1);
					}

					virtual int insert(int a_index, int a_length, int a_size){
						ArrayTableStorageLog(pankey_Log_StartMethod, "insert", "");

						if(this->isNull()){
							ArrayTableStorageLog(pankey_Log_EndMethod, "insert", "this->isNull()");
							return -1;
						}

						int i_offset = a_size + a_length - 1;
						// int i_size = a_size + a_length;

						// if(i_offset > this->getSize()){
						// 	i_offset = this->getSize() - 1;
						// }

						// ArrayTableStorageLog(pankey_Log_Statement, "insert", "a_index");
						// ArrayTableStorageLog(pankey_Log_Statement, "insert", a_index);

						// ArrayTableStorageLog(pankey_Log_Statement, "insert", "a_length");
						// ArrayTableStorageLog(pankey_Log_Statement, "insert", a_length);

						// ArrayTableStorageLog(pankey_Log_Statement, "insert", "a_size");
						// ArrayTableStorageLog(pankey_Log_Statement, "insert", a_size);

						// ArrayTableStorageLog(pankey_Log_Statement, "insert", "i_offset");
						// ArrayTableStorageLog(pankey_Log_Statement, "insert", i_offset);

						// ArrayTableStorageLog(pankey_Log_Statement, "insert", "i_size");
						// ArrayTableStorageLog(pankey_Log_Statement, "insert", i_size);

						// if(i_size > this->getSize()){
						// 	ArrayTableStorageLog(pankey_Log_EndMethod, "insert", "i_size > this->getSize()");
						// 	this->expand(i_size - this->getSize() + this->expandRate);
						// }

						// for(int x = a_length - 1; x >= a_index; x--){
						// 	ArrayTableStorageLog(pankey_Log_Statement, "insert", "for loop index");
						// 	ArrayTableStorageLog(pankey_Log_Statement, "insert", x);
						// 	ArrayTableStorageLog(pankey_Log_Statement, "insert", "for loop offset");
						// 	ArrayTableStorageLog(pankey_Log_Statement, "insert", i_offset);
						// 	HOLDER_TYPE f_value = this->m_values[x];

						// 	if(i_offset != x){
						// 		ArrayTableStorageLog(pankey_Log_Statement, "reorder", "i_offset != x");
						// 		this->m_values[i_offset] = f_value;
						// 		this->m_values[x] = nullptr;
						// 	}
							
						// 	i_offset--;
						// }
						
						// ArrayTableStorageLog(pankey_Log_EndMethod, "insert", "");
						return i_offset;
					}

					virtual bool expand(int a_size){
						ArrayTableStorageLog(pankey_Log_StartMethod, "expand", "");
						
						int i_size = this->getArraySize() + a_size;
						ArrayTableStorageLog(pankey_Log_Statement, "expand", "List Size:");
						ArrayTableStorageLog(pankey_Log_Statement, "expand", this->getSize());	
						ArrayTableStorageLog(pankey_Log_Statement, "expand", "List extra size added:");
						ArrayTableStorageLog(pankey_Log_Statement, "expand", a_size);
						ArrayTableStorageLog(pankey_Log_Statement, "expand", "List new size:");
						ArrayTableStorageLog(pankey_Log_Statement, "expand", i_size);
						if(i_size <= 1){
							ArrayTableStorageLog(pankey_Log_EndMethod, "expand", "new size is too small");
							return false;
						}
						HOLDER_TYPE** nT = nullptr;
						nT = new HOLDER_TYPE*[i_size];
						if(nT == nullptr){
							ArrayTableStorageLog(pankey_Log_EndMethod, "expand", "new array is null");
							return false;
						}

						// ArrayTableStorageLog(pankey_Log_Statement, "expand", "starting transfer iteration:");

						// if(this->m_values != nullptr){
						// 	ArrayTableStorageLog(pankey_Log_Statement, "expand", "this->m_values != nullptr");
						// 	for(int x = 0; x < this->getSize(); x++){
						// 		ArrayTableStorageLog(pankey_Log_Statement, "expand", "iteration:");
						// 		ArrayTableStorageLog(pankey_Log_Statement, "expand", x);
						// 		nT[x] = this->m_values[x];
						// 	}
						// 	MemoryHolderManager<H>::removeHolderArray(this->getManager(), this->m_values);
						// }

						// ArrayTableStorageLog(pankey_Log_Statement, "expand", "starting null iteration:");

						// for(int x = this->getSize(); x < i_size; x++){
						// 	ArrayTableStorageLog(pankey_Log_Statement, "expand", "iteration:");
						// 	ArrayTableStorageLog(pankey_Log_Statement, "expand", x);
						// 	nT[x] = nullptr;
						// }
						// this->m_values = nT;
						// this->m_size = i_size;
						
						// ArrayTableStorageLog(pankey_Log_Statement, "expand", "List Size:");
						// ArrayTableStorageLog(pankey_Log_Statement, "expand", this->getSize());	
						// ArrayTableStorageLog(pankey_Log_EndMethod, "expand", "");
						return true;
					}

					virtual bool shrink(int a_amount){
						ArrayTableStorageLog(pankey_Log_StartMethod, "shrink", "");
						// if(this->m_values == nullptr || this->getSize() == 0){
						// 	ArrayTableStorageLog(pankey_Log_EndMethod, "shrink", "this->m_values == nullptr || this->getSize() == 0");
						// 	return false;
						// }
						// ArrayTableStorageLog(pankey_Log_Statement, "shrink", "initial m_size:");
						// ArrayTableStorageLog(pankey_Log_Statement, "shrink", this->m_size);
						// ArrayTableStorageLog(pankey_Log_Statement, "shrink", "a_amount that is going to remove:");
						// ArrayTableStorageLog(pankey_Log_Statement, "shrink", a_amount);

						// for(int x = this->getSize() - 1; x >= this->getSize() - a_amount && x >= 0; x--){
						// 	ArrayTableStorageLog(pankey_Log_Statement, "shrink", "index:");
						// 	ArrayTableStorageLog(pankey_Log_Statement, "shrink", x);
						// 	MemoryHolderManager<H>::remove(this->getManager(), this->m_values[x]);
						// }

						// this->m_size -= a_amount;
						// ArrayTableStorageLog(pankey_Log_Statement, "shrink", "last m_size:");
						// ArrayTableStorageLog(pankey_Log_Statement, "shrink", this->m_size);

						// ArrayTableStorageLog(pankey_Log_EndMethod, "shrink", "");
						return true;
					}

					virtual bool destroy(){
						ArrayTableStorageLog(pankey_Log_StartMethod, "destroy", "");
						// this->shrink(this->getSize());
						// MemoryHolderManager<H>::removeHolderArray(this->getManager(), this->m_values);
						// ArrayTableStorageLog(pankey_Log_EndMethod, "destroy", "");
						return true;
					}

					virtual void setExpansionRate(int a_rate){
						this->expandRate = a_rate;
					}

					virtual int getExpansionRate(){
						return this->expandRate;
					}
				
				protected:
					HOLDER_TYPE** m_keys = nullptr;
					HOLDER_TYPE** m_values = nullptr;
					int expandRate = 5;
			};

		}

	}

#endif