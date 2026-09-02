
#ifndef ArrayStorage_hpp
	#define ArrayStorage_hpp

	#include "MemoryStorage.hpp"
	#include "MemoryHolderManager.hpp"

	#if defined(pankey_Log) && (defined(ArrayStorage_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define ArrayStorageLog(status,method,mns) pankey_Log(status,"ArrayStorage",method,mns)
	#else
		#define ArrayStorageLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class H>
			class ArrayStorage : virtual public MemoryStorage<H>{
				public:
					using HOLDER_ARRAY_TYPE = typename MemoryStorage<H>::HOLDER_ARRAY_TYPE;
					using MANAGER_TYPE = typename MemoryStorage<H>::MANAGER_TYPE;
					using VOID_TYPE = typename MemoryStorage<H>::VOID_TYPE;
					using HOLDER_TYPE = typename MemoryStorage<H>::HOLDER_TYPE;

					ArrayStorage(){
						ArrayStorageLog(pankey_Log_StartMethod, "Constructor", "");
						ArrayStorageLog(pankey_Log_EndMethod, "Constructor", "");
					}

					virtual ~ArrayStorage(){
						ArrayStorageLog(pankey_Log_StartMethod, "Destructor", "");
						ArrayStorageLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					virtual bool isNull()const{
						ArrayStorageLog(pankey_Log_StartMethod, "isNull", "");
						ArrayStorageLog(pankey_Log_EndMethod, "isNull", this->m_values == nullptr);
						return this->m_values == nullptr;
					}
					
					virtual bool isNull(int a_index)const{
						ArrayStorageLog(pankey_Log_StartMethod, "isNull", "");
						ArrayStorageLog(pankey_Log_Statement, "isNull", "Index:");
						ArrayStorageLog(pankey_Log_Statement, "isNull", a_index);
						if(this->m_values == nullptr){
							ArrayStorageLog(pankey_Log_EndMethod, "isNull", "this->m_values == nullptr");
							return true;
						}
						if(this->getSize() <= 0){
							ArrayStorageLog(pankey_Log_EndMethod, "isNull", "this->getSize() < 0");
							return true;
						}
						if(this->m_values[a_index] == nullptr){
							ArrayStorageLog(pankey_Log_EndMethod, "isNull", "this->m_values[a_index] == nullptr");
							return true;
						}
						ArrayStorageLog(pankey_Log_EndMethod, "isNull", "");
						return false;
					}

					virtual bool replace(int a_index_1, int a_index_2){
						ArrayStorageLog(pankey_Log_StartMethod, "replace", "");
						ArrayStorageLog(pankey_Log_Statement, "replace", "Position 1: ");
						ArrayStorageLog(pankey_Log_Statement, "replace", a_index_1);
						ArrayStorageLog(pankey_Log_Statement, "replace", "Position 2: ");
						ArrayStorageLog(pankey_Log_Statement, "replace", a_index_2);

						if(this->isNull() || a_index_1 >= this->getSize() || a_index_2 >= this->getSize() || a_index_1 < 0 || a_index_2 < 0){
							ArrayStorageLog(pankey_Log_EndMethod, "replace", "this->isNull()");
							return false;
						}

						if(a_index_1 == a_index_2){
							ArrayStorageLog(pankey_Log_EndMethod, "replace", "a_index_1 == a_index_2");
							return true;
						}
						HOLDER_TYPE i_holder_1 = this->m_values[a_index_1];
						HOLDER_TYPE i_holder_2 = this->m_values[a_index_2];
						this->m_values[a_index_1] = i_holder_2;
						this->m_values[a_index_2] = i_holder_1;

						ArrayStorageLog(pankey_Log_EndMethod, "replace", "");
						return true;
					}

					virtual bool set(int a_position, MemoryHolder<H>& a_pointer){
						ArrayStorageLog(pankey_Log_StartMethod, "set", "");
						ArrayStorageLog(pankey_Log_Statement, "set", "Position: ");
						ArrayStorageLog(pankey_Log_Statement, "set", a_position);

						if(this->isNull() || a_position >= this->getSize() || a_position < 0){
							ArrayStorageLog(pankey_Log_EndMethod, "set", "this->isNull() || a_position >= this->getSize() || a_position < 0");
							return false;
						}

						HOLDER_TYPE i_holder = a_pointer.getHolder();

						ArrayStorageLog(pankey_Log_Statement, "set", "Is Holder == nullptr");
						ArrayStorageLog(pankey_Log_Statement, "set", i_holder == nullptr);

						if(i_holder == this->m_values[a_position]){
							ArrayStorageLog(pankey_Log_EndMethod, "set", "i_holder == this->m_values[a_position]");
							return true;
						}

						MemoryHolderManager<H>::add(this->getManager(), i_holder);
						MemoryHolderManager<H>::remove(this->getManager(), this->m_values[a_position]);
						
						this->m_values[a_position] = i_holder;

						ArrayStorageLog(pankey_Log_EndMethod, "set", "");
						return true;
					}

					virtual bool add(int a_position, MemoryHolder<H>& a_pointer){
						ArrayStorageLog(pankey_Log_StartMethod, "add", "");
						ArrayStorageLog(pankey_Log_Statement, "add", "Position: ");
						ArrayStorageLog(pankey_Log_Statement, "add", a_position);

						if(this->isNull() || a_position >= this->getSize() || a_position < 0){
							ArrayStorageLog(pankey_Log_Statement, "add", "this->isNull() || a_position >= this->getSize() || a_position < 0");
							this->expand(a_position - this->getSize() + this->expandRate);
						}
						ArrayStorageLog(pankey_Log_EndMethod, "add", "");
						return this->set(a_position, a_pointer);
					}

					virtual bool contain(Base::InvokeMethodReturn<bool,VOID_TYPE,VOID_TYPE> a_method, const MemoryHolder<H>& a_value)const{
						ArrayStorageLog(pankey_Log_StartMethod, "contain", "");
						if(this->isNull()){
							ArrayStorageLog(pankey_Log_Statement, "contain", "this->isNull()");
							ArrayStorageLog(pankey_Log_EndMethod, "contain", "return false");
							return false;
						}

						VOID_TYPE i_pointer_1 = a_value.getRawPointer();

						if(i_pointer_1 == nullptr){
							ArrayStorageLog(pankey_Log_EndMethod, "contain", "i_pointer_1 == nullptr");
							return false;
						}

						for(int x = 0; x < this->getSize(); x++){
							VOID_TYPE f_pointer_2 = MemoryHolderManager<H>::get(this->getManager(), this->m_values[x]);
							if(f_pointer_2 == nullptr){
								ArrayStorageLog(pankey_Log_EndMethod, "contain", "f_pointer_2 == nullptr");
								continue;
							}
							bool i_result = Base::invoke<bool,VOID_TYPE,VOID_TYPE>(a_method, i_pointer_1, f_pointer_2);
							if(i_result){
								ArrayStorageLog(pankey_Log_Statement, "contain", "a_value == this->m_values[x]");
								ArrayStorageLog(pankey_Log_EndMethod, "contain", "return true");
								return true;
							}
						}

						ArrayStorageLog(pankey_Log_EndMethod, "contain", "");
						return false;
					}

					virtual bool containByPointer(const MemoryHolder<H>& a_value)const{
						ArrayStorageLog(pankey_Log_StartMethod, "containByPointer", "");
						if(this->isNull()){
							ArrayStorageLog(pankey_Log_Statement, "containByPointer", "this->isNull()");
							ArrayStorageLog(pankey_Log_EndMethod, "containByPointer", "return false");
							return false;
						}

						VOID_TYPE i_pointer_1 = a_value.getRawPointer();

						for(int x = 0; x < this->getSize(); x++){
							VOID_TYPE f_pointer_2 = MemoryHolderManager<H>::get(this->getManager(), this->m_values[x]);;
							if(i_pointer_1 == f_pointer_2){
								ArrayStorageLog(pankey_Log_Statement, "containByPointer", "a_value == this->m_values[x]");
								ArrayStorageLog(pankey_Log_EndMethod, "containByPointer", "return true");
								return true;
							}
						}

						ArrayStorageLog(pankey_Log_EndMethod, "containByPointer", "");
						return false;
					}
					
					virtual int getIndex(Base::InvokeMethodReturn<bool,VOID_TYPE,VOID_TYPE> a_method, const MemoryHolder<H>& a_value)const{
						ArrayStorageLog(pankey_Log_StartMethod, "getIndex", "");
						if(this->isNull()){
							ArrayStorageLog(pankey_Log_EndMethod, "getIndex", "this->isNull()");
							return -1;
						}

						VOID_TYPE i_pointer_1 = a_value.getRawPointer();

						if(i_pointer_1 == nullptr){
							ArrayStorageLog(pankey_Log_EndMethod, "getIndex", "i_pointer_1 == nullptr");
							return -1;
						}

						for(int x = 0; x < this->getSize(); x++){
							VOID_TYPE f_pointer_2 = MemoryHolderManager<H>::get(this->getManager(), this->m_values[x]);
							if(f_pointer_2 == nullptr){
								ArrayStorageLog(pankey_Log_EndMethod, "getIndex", "f_pointer_2 == nullptr");
								continue;
							}
							bool i_result = Base::invoke<bool,VOID_TYPE,VOID_TYPE>(a_method, i_pointer_1, f_pointer_2);
							if(i_result){
								ArrayStorageLog(pankey_Log_EndMethod, "getIndex", "a_value == this->m_values[x]");
								return x;
							}
						}

						ArrayStorageLog(pankey_Log_EndMethod, "getIndex", "");
						return -1;
					}
					
					virtual int getIndexByPointer(const MemoryHolder<H>& a_value)const{
						ArrayStorageLog(pankey_Log_StartMethod, "getIndexByPointer", "");
						if(this->isNull()){
							ArrayStorageLog(pankey_Log_EndMethod, "getIndexByPointer", "this->isNull()");
							return -1;
						}

						VOID_TYPE i_pointer_1 = a_value.getRawPointer();

						for(int x = 0; x < this->getSize(); x++){
							VOID_TYPE f_pointer_2 = MemoryHolderManager<H>::get(this->getManager(), this->m_values[x]);;
							if(i_pointer_1 == f_pointer_2){
								ArrayStorageLog(pankey_Log_EndMethod, "getIndexByPointer", "a_value == this->m_values[x]");
								return x;
							}
						}

						ArrayStorageLog(pankey_Log_EndMethod, "getIndexByPointer", "");
						return -1;
					}
					
					virtual VOID_TYPE getRawPointer(int a_position)const{
						ArrayStorageLog(pankey_Log_StartMethod, "getRawPointer", "");

						if(this->isNull() || a_position >= this->getSize() || a_position < 0){
							ArrayStorageLog(pankey_Log_EndMethod, "getRawPointer", "");
							return nullptr;
						}

						ArrayStorageLog(pankey_Log_EndMethod, "getRawPointer", "");
						return MemoryHolderManager<H>::get(this->getManager(), this->m_values[a_position]);
					}
					
					virtual HOLDER_TYPE getHolder(int a_position)const{
						ArrayStorageLog(pankey_Log_StartMethod, "get", "");

						if(this->isNull() || a_position >= this->getSize() || a_position < 0){
							ArrayStorageLog(pankey_Log_EndMethod, "get", "");
							return nullptr;
						}

						ArrayStorageLog(pankey_Log_EndMethod, "get", "");
						return this->m_values[a_position];
					}

					virtual bool remove(Base::InvokeMethodReturn<bool,VOID_TYPE,VOID_TYPE> a_method, const MemoryHolder<H>& a_value){
						ArrayStorageLog(pankey_Log_StartMethod, "remove", "");

						int i_position = this->getIndex(a_method, a_value);

						ArrayStorageLog(pankey_Log_Statement, "remove", "removed position: ");
						ArrayStorageLog(pankey_Log_Statement, "remove", i_position);

						if(this->isNull() || i_position >= this->getSize() || i_position < 0){
							ArrayStorageLog(pankey_Log_EndMethod, "remove", "");
							return false;
						}
						
						MemoryHolderManager<H>::remove(this->getManager(), this->m_values[i_position]);

						ArrayStorageLog(pankey_Log_EndMethod, "remove", "");
						return true;
					}

					virtual bool removeByPointer(const MemoryHolder<H>& a_value){
						ArrayStorageLog(pankey_Log_StartMethod, "removeByPointer", "");

						int i_position = this->getIndexByPointer(a_value);

						ArrayStorageLog(pankey_Log_Statement, "removeByPointer", "removed position: ");
						ArrayStorageLog(pankey_Log_Statement, "removeByPointer", i_position);

						if(this->isNull() || i_position >= this->getSize() || i_position < 0){
							ArrayStorageLog(pankey_Log_EndMethod, "removeByPointer", "");
							return false;
						}
						
						MemoryHolderManager<H>::remove(this->getManager(), this->m_values[i_position]);

						ArrayStorageLog(pankey_Log_EndMethod, "removeByPointer", "");
						return true;
					}

					virtual bool removeFirstIndex(int a_length, int a_amount){
						ArrayStorageLog(pankey_Log_StartMethod, "removeFirstIndex", "");

						if(this->isNull() || a_amount <= 0){
							ArrayStorageLog(pankey_Log_EndMethod, "removeFirstIndex", "");
							return false;
						}

						if(a_amount > a_length){
							ArrayStorageLog(pankey_Log_Statement, "removeFirstIndex", "a_amount > this->getSize()");
							a_amount = a_length;
						}

						for(int x = 0; x < a_amount; x++){
							ArrayStorageLog(pankey_Log_Statement, "removeFirstIndex", "for loop index");
							ArrayStorageLog(pankey_Log_Statement, "removeFirstIndex", x);
							MemoryHolderManager<H>::remove(this->getManager(), this->m_values[x]);
						}

						ArrayStorageLog(pankey_Log_EndMethod, "removeFirstIndex", "");
						return true;
					}

					virtual bool removeLastIndex(int a_length, int a_amount){
						ArrayStorageLog(pankey_Log_StartMethod, "removeLastIndex", "");

						if(this->isNull() || a_amount < 0){
							ArrayStorageLog(pankey_Log_EndMethod, "removeLastIndex", "");
							return false;
						}

						if(a_amount > a_length){
							ArrayStorageLog(pankey_Log_Statement, "removeFirstIndex", "a_amount > this->getSize()");
							a_amount = a_length;
						}

						for(int x = a_length - 1; x >= a_length - a_amount; x--){
							ArrayStorageLog(pankey_Log_Statement, "removeLastIndex", "for loop index");
							ArrayStorageLog(pankey_Log_Statement, "removeLastIndex", x);
							MemoryHolderManager<H>::remove(this->getManager(), this->m_values[x]);
						}

						ArrayStorageLog(pankey_Log_EndMethod, "removeLastIndex", "");
						return true;
					}

					virtual bool removePart(int a_index, int a_length, int a_amount){
						ArrayStorageLog(pankey_Log_StartMethod, "removePart", "");

						if(this->isNull() || a_index < 0 || a_amount <= 0){
							ArrayStorageLog(pankey_Log_EndMethod, "removePart", "this->isNull() || a_index <= 0 || a_amount <= 0");
							return false;
						}

						if(a_index + a_amount > a_length){
							ArrayStorageLog(pankey_Log_Statement, "removePart", "a_index + a_amount > a_length");
							ArrayStorageLog(pankey_Log_Statement, "removePart", a_index + a_amount);
							a_amount = a_length - a_index;
						}

						for(int x = a_index; x < a_index + a_amount; x++){
							ArrayStorageLog(pankey_Log_Statement, "removePart", "for loop index");
							ArrayStorageLog(pankey_Log_Statement, "removePart", x);
							MemoryHolderManager<H>::remove(this->getManager(), this->m_values[x]);
						}

						ArrayStorageLog(pankey_Log_EndMethod, "removePart", "");
						return true;
					}

					virtual bool removeFirst(){
						ArrayStorageLog(pankey_Log_StartMethod, "removeFirst", "");

						if(this->isNull() || this->getSize() < 1){
							ArrayStorageLog(pankey_Log_EndMethod, "removeFirst", "");
							return false;
						}
						
						MemoryHolderManager<H>::remove(this->getManager(), this->m_values[0]);

						ArrayStorageLog(pankey_Log_EndMethod, "removeFirst", "");
						return true;
					}

					virtual bool removeLast(){
						ArrayStorageLog(pankey_Log_StartMethod, "removeLast", "");
						ArrayStorageLog(pankey_Log_Statement, "removeLast", "removing index");
						ArrayStorageLog(pankey_Log_Statement, "removeLast", this->getSize() - 1);

						if(this->isNull() || this->getSize() < 1){
							ArrayStorageLog(pankey_Log_EndMethod, "removeLast", "");
							return false;
						}
						
						MemoryHolderManager<H>::remove(this->getManager(), this->m_values[this->getSize() - 1]);
						
						ArrayStorageLog(pankey_Log_EndMethod, "removeLast", "");
						return true;
					}

					virtual bool clear(){
						ArrayStorageLog(pankey_Log_StartMethod, "clear", "");

						if(this->isNull()){
							ArrayStorageLog(pankey_Log_EndMethod, "clear", "this->isNull()");
							return false;
						}

						for(int x = 0; x < this->getSize(); x++){
							ArrayStorageLog(pankey_Log_Statement, "clear", "for loop index");
							ArrayStorageLog(pankey_Log_Statement, "clear", x);
							MemoryHolderManager<H>::remove(this->getManager(), this->m_values[x]);
						}

						ArrayStorageLog(pankey_Log_EndMethod, "clear", "");
						return true;
					}

					virtual int reorder(){
						ArrayStorageLog(pankey_Log_StartMethod, "reorder", "");

						if(this->isNull()){
							ArrayStorageLog(pankey_Log_EndMethod, "reorder", "this->isNull()");
							return -1;
						}

						int i_offset = 0;

						for(int x = 0; x < this->getSize(); x++){
							ArrayStorageLog(pankey_Log_Statement, "reorder", "for loop index");
							ArrayStorageLog(pankey_Log_Statement, "reorder", x);
							ArrayStorageLog(pankey_Log_Statement, "reorder", "for loop i_offset");
							ArrayStorageLog(pankey_Log_Statement, "reorder", i_offset);

							HOLDER_TYPE f_value = this->m_values[x];

							if(f_value == nullptr){
								ArrayStorageLog(pankey_Log_Statement, "reorder", "f_value == nullptr");
								continue;
							}
							
							if(i_offset != x){
								ArrayStorageLog(pankey_Log_Statement, "reorder", "i_offset != x");
								this->m_values[i_offset] = f_value;
								this->m_values[x] = nullptr;
							}

							ArrayStorageLog(pankey_Log_Statement, "reorder", "this->m_values[i_offset] = f_value");
							i_offset++;
						}

						ArrayStorageLog(pankey_Log_EndMethod, "reorder", "");
						return i_offset;
					}

					virtual int reorder(int a_index, int a_length, int a_amount){
						ArrayStorageLog(pankey_Log_StartMethod, "reorder", "");

						if(this->isNull()){
							ArrayStorageLog(pankey_Log_EndMethod, "reorder", "this->isNull()");
							return -1;
						}

						int i_offset = a_index;

						if(this->getSize() - a_length < a_amount && a_length < a_index + a_amount){
							ArrayStorageLog(pankey_Log_Statement, "reorder", "this->getSize() - a_length < a_amount && a_length < a_index + a_amount");
							ArrayStorageLog(pankey_Log_Statement, "reorder", "this->getSize() - a_length");
							ArrayStorageLog(pankey_Log_Statement, "reorder", this->getSize() - a_length);
							ArrayStorageLog(pankey_Log_Statement, "reorder", "a_amount");
							ArrayStorageLog(pankey_Log_Statement, "reorder", a_amount);
							ArrayStorageLog(pankey_Log_Statement, "reorder", "a_length");
							ArrayStorageLog(pankey_Log_Statement, "reorder", a_length);
							ArrayStorageLog(pankey_Log_Statement, "reorder", "a_index + a_amount");
							ArrayStorageLog(pankey_Log_Statement, "reorder", a_index + a_amount);
							return -1;
						}

						if(a_index + a_amount > a_length){
							ArrayStorageLog(pankey_Log_Statement, "reorder", "a_index + a_amount > a_length");
							ArrayStorageLog(pankey_Log_Statement, "reorder", a_index + a_amount);
							a_amount = a_length - a_index;
						}

						for(int x = a_index + a_amount; x < a_length; x++){
							ArrayStorageLog(pankey_Log_Statement, "reorder", "for loop index");
							ArrayStorageLog(pankey_Log_Statement, "reorder", x);
							ArrayStorageLog(pankey_Log_Statement, "reorder", "for loop i_offset");
							ArrayStorageLog(pankey_Log_Statement, "reorder", i_offset);

							HOLDER_TYPE f_value = this->m_values[x];
							
							if(i_offset != x){
								ArrayStorageLog(pankey_Log_Statement, "reorder", "i_offset != x");
								this->m_values[i_offset] = f_value;
								this->m_values[x] = nullptr;
							}

							ArrayStorageLog(pankey_Log_Statement, "reorder", "this->m_values[i_offset] = f_value");
							i_offset++;
						}

						ArrayStorageLog(pankey_Log_EndMethod, "reorder", "");
						return i_offset;
					}

					virtual int reorder(int a_index, int a_length){
						return this->reorder(a_index, a_length, 1);
					}

					virtual int insert(int a_index, int a_length, int a_size){
						ArrayStorageLog(pankey_Log_StartMethod, "insert", "");

						if(this->isNull()){
							ArrayStorageLog(pankey_Log_EndMethod, "insert", "this->isNull()");
							return -1;
						}

						int i_offset = a_size + a_length - 1;
						int i_size = a_size + a_length;

						if(i_offset > this->getSize()){
							i_offset = this->getSize() - 1;
						}

						ArrayStorageLog(pankey_Log_Statement, "insert", "a_index");
						ArrayStorageLog(pankey_Log_Statement, "insert", a_index);

						ArrayStorageLog(pankey_Log_Statement, "insert", "a_length");
						ArrayStorageLog(pankey_Log_Statement, "insert", a_length);

						ArrayStorageLog(pankey_Log_Statement, "insert", "a_size");
						ArrayStorageLog(pankey_Log_Statement, "insert", a_size);

						ArrayStorageLog(pankey_Log_Statement, "insert", "i_offset");
						ArrayStorageLog(pankey_Log_Statement, "insert", i_offset);

						ArrayStorageLog(pankey_Log_Statement, "insert", "i_size");
						ArrayStorageLog(pankey_Log_Statement, "insert", i_size);

						if(i_size > this->getSize()){
							ArrayStorageLog(pankey_Log_EndMethod, "insert", "i_size > this->getSize()");
							this->expand(i_size - this->getSize() + this->expandRate);
						}

						for(int x = a_length - 1; x >= a_index; x--){
							ArrayStorageLog(pankey_Log_Statement, "insert", "for loop index");
							ArrayStorageLog(pankey_Log_Statement, "insert", x);
							ArrayStorageLog(pankey_Log_Statement, "insert", "for loop offset");
							ArrayStorageLog(pankey_Log_Statement, "insert", i_offset);
							HOLDER_TYPE f_value = this->m_values[x];

							if(i_offset != x){
								ArrayStorageLog(pankey_Log_Statement, "reorder", "i_offset != x");
								this->m_values[i_offset] = f_value;
								this->m_values[x] = nullptr;
							}
							
							i_offset--;
						}
						
						ArrayStorageLog(pankey_Log_EndMethod, "insert", "");
						return i_offset;
					}

					virtual bool expand(int a_size){
						ArrayStorageLog(pankey_Log_StartMethod, "expand", "");
						
						int i_size = this->getSize() + a_size;
						ArrayStorageLog(pankey_Log_Statement, "expand", "List Size:");
						ArrayStorageLog(pankey_Log_Statement, "expand", this->getSize());	
						ArrayStorageLog(pankey_Log_Statement, "expand", "List extra size added:");
						ArrayStorageLog(pankey_Log_Statement, "expand", a_size);
						ArrayStorageLog(pankey_Log_Statement, "expand", "List new size:");
						ArrayStorageLog(pankey_Log_Statement, "expand", i_size);
						if(i_size <= 1){
							ArrayStorageLog(pankey_Log_EndMethod, "expand", "new size is too small");
							return false;
						}
						HOLDER_ARRAY_TYPE nT;
						nT = new HOLDER_TYPE[i_size];
						if(nT == nullptr){
							ArrayStorageLog(pankey_Log_EndMethod, "expand", "new array is null");
							return false;
						}

						ArrayStorageLog(pankey_Log_Statement, "expand", "starting transfer iteration:");

						if(this->m_values != nullptr){
							ArrayStorageLog(pankey_Log_Statement, "expand", "this->m_values != nullptr");
							for(int x = 0; x < this->getSize(); x++){
								ArrayStorageLog(pankey_Log_Statement, "expand", "iteration:");
								ArrayStorageLog(pankey_Log_Statement, "expand", x);
								nT[x] = this->m_values[x];
							}
							delete[] this->m_values;
							this->m_values = nullptr;
						}

						ArrayStorageLog(pankey_Log_Statement, "expand", "starting null iteration:");

						for(int x = this->getSize(); x < i_size; x++){
							ArrayStorageLog(pankey_Log_Statement, "expand", "iteration:");
							ArrayStorageLog(pankey_Log_Statement, "expand", x);
							nT[x] = nullptr;
						}
						this->m_values = nT;
						this->m_size = i_size;
						
						ArrayStorageLog(pankey_Log_Statement, "expand", "List Size:");
						ArrayStorageLog(pankey_Log_Statement, "expand", this->getSize());	
						ArrayStorageLog(pankey_Log_EndMethod, "expand", "");
						return true;
					}

					virtual bool shrink(int a_amount){
						ArrayStorageLog(pankey_Log_StartMethod, "shrink", "");
						if(this->m_values == nullptr || this->getSize() == 0){
							ArrayStorageLog(pankey_Log_EndMethod, "shrink", "this->m_values == nullptr || this->getSize() == 0");
							return false;
						}
						ArrayStorageLog(pankey_Log_Statement, "shrink", "initial m_size:");
						ArrayStorageLog(pankey_Log_Statement, "shrink", this->m_size);
						ArrayStorageLog(pankey_Log_Statement, "shrink", "a_amount that is going to remove:");
						ArrayStorageLog(pankey_Log_Statement, "shrink", a_amount);

						for(int x = this->getSize() - 1; x >= this->getSize() - a_amount && x >= 0; x--){
							ArrayStorageLog(pankey_Log_Statement, "shrink", "index:");
							ArrayStorageLog(pankey_Log_Statement, "shrink", x);
							MemoryHolderManager<H>::remove(this->getManager(), this->m_values[x]);
						}

						this->m_size -= a_amount;
						ArrayStorageLog(pankey_Log_Statement, "shrink", "last m_size:");
						ArrayStorageLog(pankey_Log_Statement, "shrink", this->m_size);

						ArrayStorageLog(pankey_Log_EndMethod, "shrink", "");
						return true;
					}

					virtual bool destroy(){
						ArrayStorageLog(pankey_Log_StartMethod, "destroy", "");
						this->shrink(this->getSize());
						if(this->m_values == nullptr){
							return false;
						}
						delete[] this->m_values;
						this->m_values = nullptr;
						ArrayStorageLog(pankey_Log_EndMethod, "destroy", "");
						return true;
					}

					virtual void setExpansionRate(int a_rate){
						this->expandRate = a_rate;
					}

					virtual int getExpansionRate(){
						return this->expandRate;
					}
				
				protected:
					HOLDER_ARRAY_TYPE m_values = nullptr;
					int expandRate = 5;
			};

		}

	}

#endif