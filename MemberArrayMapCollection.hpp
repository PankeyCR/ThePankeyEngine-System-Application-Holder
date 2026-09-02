
#ifndef MemberArrayMapCollection_hpp
	#define MemberArrayMapCollection_hpp

	#include "MapCollection.hpp"
	#include "MemberArrayStorage.hpp"
	#include "DuoMember.hpp"
	#include "Member.hpp"

	#if defined(pankey_Log) && (defined(MemberArrayMapCollection_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define MemberArrayMapCollectionLog(status,method,mns) pankey_Log(status,"MemberArrayMapCollection",method,mns)
	#else
		#define MemberArrayMapCollectionLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class H, class M>
			class MemberArrayMapCollection : virtual public MapCollection<H,M>{
				public:
					MemberArrayMapCollection(){
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "Constructor", "");
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "Constructor", "");
					}

					virtual ~MemberArrayMapCollection(){
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "Destructor", "");
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					virtual bool isEmpty()const{
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "isEmpty", "");
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "isEmpty", "");
						return this->m_keys.isNull() || this->m_keys.getSize() <= 0 || this->m_values.getSize() <= 0 || this->m_length <= 0;
					}
					
					virtual int getSize()const{
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "getSize", "");
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "getSize", "");
						return this->m_keys.getSize();
					}

					virtual bool replace(int a_index_1, int a_index_2){
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "replace", "");
						bool i_key_r = this->m_keys.replace(a_index_1, a_index_2);
						bool i_value_r = this->m_values.replace(a_index_1, a_index_2);
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "replace", "");
						return i_key_r && i_value_r;
					}

					virtual Member<H,M> getByPointer(const Member<H,M>& a_value)const{
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "getByPointer", "");
						int i_index = this->m_keys.getIndexByPointer(a_value);
						if(i_index == -1){
							MemberArrayMapCollectionLog(pankey_Log_Statement, "getByPointer", "i_index == -1");
							return Member<H,M>();
						}
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "getByPointer", "");
						return this->m_values.get(i_index);
					}

					virtual Member<H,M> getKeyByPointer(const Member<H,M>& a_value)const{
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "getKeyByPointer", "");
						int i_index = this->m_values.getIndexByPointer(a_value);
						if(i_index == -1){
							MemberArrayMapCollectionLog(pankey_Log_Statement, "getKeyByPointer", "i_index == -1");
							return Member<H,M>();
						}
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "getKeyByPointer", "");
						return this->m_keys.get(i_index);
					}

					virtual Member<H,M> getValueByPointer(const Member<H,M>& a_key)const{
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "getValueByPointer", "");
						int i_index = this->m_keys.getIndexByPointer(a_key);
						if(i_index == -1){
							MemberArrayMapCollectionLog(pankey_Log_Statement, "getValueByPointer", "i_index == -1");
							return Member<H,M>();
						}
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "getValueByPointer", "");
						return this->m_values.get(i_index);
					}

					virtual Member<H,M> get(int x)const{
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "get", "");
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "get", "");
						return this->m_values.get(x);
					}

					virtual Member<H,M> getKey(int x)const{
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "get", "");
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "get", "");
						return this->m_keys.get(x);
					}

					virtual Member<H,M> getValue(int x)const{
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "get", "");
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "get", "");
						return this->m_values.get(x);
					}

					virtual bool containByPointer(const Member<H,M>& a_value)const{
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "containByPointer", "");
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "containByPointer", "");
						return this->m_keys.containByPointer(a_value) || this->m_values.containByPointer(a_value);
					}

					virtual bool containKeyByPointer(const Member<H,M>& a_key)const{
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "containKeyByPointer", "");
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "containKeyByPointer", "");
						return this->m_keys.containByPointer(a_key);
					}

					virtual bool containValueByPointer(const Member<H,M>& a_value)const{
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "containValueByPointer", "");
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "containValueByPointer", "");
						return this->m_values.containByPointer(a_value);
					}
					
					virtual int getIndexByPointer(const Member<H,M>& a_value)const{
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "getIndexByPointer", "");
						int i_index = this->m_keys.getIndexByPointer(a_value);
						if(i_index == -1){
							MemberArrayMapCollectionLog(pankey_Log_Statement, "getIndexByPointer", "i_index == -1");
							return this->m_values.getIndexByPointer(a_value);
						}
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "getIndexByPointer", "");
						return i_index;
					}
					
					virtual int getKeyIndexByPointer(const Member<H,M>& a_value)const{
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "getKeyIndexByPointer", "");
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "getKeyIndexByPointer", "");
						return this->m_keys.getIndexByPointer(a_value);
					}
					
					virtual int getValueIndexByPointer(const Member<H,M>& a_value)const{
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "getKeyIndexByPointer", "");
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "getKeyIndexByPointer", "");
						return this->m_values.getIndexByPointer(a_value);
					}
					
					virtual bool removeByPointer(const Member<H,M>& a_value){
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "removeByPointer", "");
						int i_key_index = this->m_keys.getIndexByPointer(a_value);
						if(i_key_index >= 0){
							MemberArrayMapCollectionLog(pankey_Log_Statement, "removeByPointer", "i_key_index that is been removed:");
							MemberArrayMapCollectionLog(pankey_Log_Statement, "removeByPointer", i_key_index);
							this->m_keys.removeByIndex(i_key_index);
							this->m_values.removeByIndex(i_key_index);
							this->m_keys.reorder(i_key_index, this->length());
							this->m_values.reorder(i_key_index, this->length());
							this->decrementPosition();
						}
						int i_value_index = this->m_values.getIndexByPointer(a_value);
						if(i_value_index >= 0){
							MemberArrayMapCollectionLog(pankey_Log_Statement, "removeByPointer", "i_value_index that is been removed:");
							MemberArrayMapCollectionLog(pankey_Log_Statement, "removeByPointer", i_value_index);
							this->m_keys.removeByIndex(i_value_index);
							this->m_values.removeByIndex(i_value_index);
							this->m_keys.reorder(i_value_index, this->length());
							this->m_values.reorder(i_value_index, this->length());
							this->decrementPosition();
						}
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "removeByPointer", "");
						return i_key_index >= 0 || i_value_index >= 0;
					}
					
					virtual bool removeKeyByPointer(const Member<H,M>& a_value){
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "removeKeyByPointer", "");
						int i_key_index = this->m_keys.getIndexByPointer(a_value);
						if(i_key_index >= 0){
							MemberArrayMapCollectionLog(pankey_Log_Statement, "removeKeyByPointer", "i_key_index that is been removed:");
							MemberArrayMapCollectionLog(pankey_Log_Statement, "removeKeyByPointer", i_key_index);
							this->m_keys.removeByIndex(i_key_index);
							this->m_values.removeByIndex(i_key_index);
							this->m_keys.reorder(i_key_index, this->length());
							this->m_values.reorder(i_key_index, this->length());
							this->decrementPosition();
							return true;
						}
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "removeKeyByPointer", "");
						return false;
					}
					
					virtual bool removeValueByPointer(const Member<H,M>& a_value){
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "removeValueByPointer", "");
						int i_value_index = this->m_values.getIndexByPointer(a_value);
						if(i_value_index >= 0){
							MemberArrayMapCollectionLog(pankey_Log_Statement, "removeValueByPointer", "i_value_index that is been removed:");
							MemberArrayMapCollectionLog(pankey_Log_Statement, "removeValueByPointer", i_value_index);
							this->m_keys.removeByIndex(i_value_index);
							this->m_values.removeByIndex(i_value_index);
							this->m_keys.reorder(i_value_index, this->length());
							this->m_values.reorder(i_value_index, this->length());
							this->decrementPosition();
							return true;
						}
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "removeValueByPointer", "");
						return false;
					}
					
					virtual Member<H,M> remove(int a_index){
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "remove", "");
						if(a_index < 0 || this->isEmpty() || a_index >= this->length()){
							MemberArrayMapCollectionLog(pankey_Log_EndMethod, "remove", "");
							return Member<H,M>();
						}
						Member<H,M> i_key_pointer = this->m_keys.removeByIndex(a_index);
						Member<H,M> i_value_pointer = this->m_values.removeByIndex(a_index);
						this->m_keys.reorder(a_index, this->length());
						this->m_values.reorder(a_index, this->length());
						this->decrementPosition();
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "remove", "");
						return i_value_pointer;
					}
					
					virtual bool removeFirstIndex(int a_amount){
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "removeFirstIndex", "");
						bool i_key_remove = this->m_keys.removeFirstIndex(this->m_length, a_amount);
						bool i_value_remove = this->m_values.removeFirstIndex(this->m_length, a_amount);
						if(i_key_remove && i_key_remove){
							MemberArrayMapCollectionLog(pankey_Log_Statement, "removeFirstIndex", "i_key_remove && i_key_remove");
							this->m_keys.reorder(0, this->length(), a_amount);
							this->m_values.reorder(0, this->length(), a_amount);
							this->decrementPosition(a_amount);
							MemberArrayMapCollectionLog(pankey_Log_EndMethod, "removeFirstIndex", "");
							return true;
						}
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "removeFirstIndex", "");
						return false;
					}

					virtual bool removeLastIndex(int a_amount){
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "removeLastIndex", "");
						bool i_key_remove = this->m_keys.removeLastIndex(this->m_length, a_amount);
						bool i_value_remove = this->m_values.removeLastIndex(this->m_length, a_amount);
						if(i_key_remove && i_key_remove){
							MemberArrayMapCollectionLog(pankey_Log_Statement, "removeLastIndex", "i_key_remove && i_key_remove");
							this->decrementPosition(a_amount);
							MemberArrayMapCollectionLog(pankey_Log_EndMethod, "removeLastIndex", "");
							return true;
						}
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "removeLastIndex", "");
						return false;
					}

					virtual bool removePart(int a_index, int a_amount){
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "removePart", "");
						bool i_key_remove = this->m_keys.removePart(a_index, this->m_length, a_amount);
						bool i_value_remove = this->m_values.removePart(a_index, this->m_length, a_amount);
						if(i_key_remove && i_key_remove){
							MemberArrayMapCollectionLog(pankey_Log_Statement, "removePart", "i_key_remove && i_key_remove");
							this->m_keys.reorder(a_index, this->length(), a_amount);
							this->m_values.reorder(a_index, this->length(), a_amount);
							this->decrementPosition(a_amount);
							MemberArrayMapCollectionLog(pankey_Log_EndMethod, "removePart", "");
							return true;
						}
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "removePart", "");
						return false;
					}
					
					virtual bool removeFirst(){
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "removeFirst", "");
						if(this->isEmpty()){
							MemberArrayMapCollectionLog(pankey_Log_EndMethod, "removeFirst", "");
							return false;
						}
						bool i_key_remove = this->m_keys.removeFirst();
						bool i_value_remove = this->m_values.removeFirst();
						if(i_key_remove && i_key_remove){
							MemberArrayMapCollectionLog(pankey_Log_Statement, "removeFirst", "i_key_remove && i_key_remove");
							this->m_keys.reorder(0, this->length());
							this->m_values.reorder(0, this->length());
							this->decrementPosition();
							MemberArrayMapCollectionLog(pankey_Log_EndMethod, "removeFirst", "true");
							return true;
						}
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "removeFirst", "false");
						return false;
					}

					virtual bool removeLast(){
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "removeLast", "");
						if(this->isEmpty()){
							MemberArrayMapCollectionLog(pankey_Log_EndMethod, "removeLast", "");
							return false;
						}
						Member<H,M> i_key_pointer = this->m_keys.removeByIndex(this->length() - 1);
						Member<H,M> i_value_pointer = this->m_values.removeByIndex(this->length() - 1);
						this->m_keys.reorder(this->length() - 1, this->length());
						this->m_values.reorder(this->length() - 1, this->length());
						this->decrementPosition();
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "removeLast", "");
						return true;
					}
					
					virtual bool clear(){
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "clear", "");
						this->m_length = 0;
						bool i_key_clear = this->m_keys.clear();
						bool i_value_clear = this->m_values.clear();
						if(i_key_clear && i_value_clear){
							this->m_length = 0;
							MemberArrayMapCollectionLog(pankey_Log_EndMethod, "clear", "");
							return true;
						}
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "clear", "");
						return false;
					}

					virtual bool isInOrder()const{
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "isInOrder", "");
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "isInOrder", "");
						return this->m_reorder;
					}

					virtual void setReorder(bool a_reorder){
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "setReorder", "");
						if(a_reorder != this->m_reorder){
							MemberArrayMapCollectionLog(pankey_Log_EndMethod, "setReorder", "");
							return;
						}
						this->m_reorder = a_reorder;
						reorder();
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "setReorder", "");
					}
					
					virtual void reorder(){
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "reorder", "");
						if(!this->m_reorder){
							MemberArrayMapCollectionLog(pankey_Log_Statement, "reorder", "this->m_reorder || this->m_values == nullptr");
							return;
						}
						this->m_keys.reorder();
						this->m_values.reorder();
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "reorder", "");
					}
					
				protected:
					
					virtual void incrementPosition(){
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "incrementPosition", "");
						this->m_length++;
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "incrementPosition", "");
					}
					virtual void decrementPosition(){
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "decrementPosition", "");
						this->m_length--;
						if(this->m_length < 0){
							this->m_length = 0;
						}
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "decrementPosition", "");
					}
					
					virtual void incrementPosition(int a_size){
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "incrementPosition", "");
						this->m_length += a_size;
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "incrementPosition", "");
					}
					virtual void decrementPosition(int a_size){
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "decrementPosition", "");
						this->m_length -= a_size;
						if(this->m_length < 0){
							this->m_length = 0;
						}
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "decrementPosition", "");
					}

				public:
				
					virtual bool operator<(int x) const{
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "operator<", "");
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "operator<", "");
						return this->length() < x;
					}
					
					virtual bool operator>(int x) const{
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "operator>", "");
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "operator>", "");
						return this->length() > x;
					}
					
					virtual bool operator<=(int x) const{
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "operator<=", "");
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "operator<=", "");
						return this->length() <= x;
					}
					
					virtual bool operator>=(int x) const{
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "operator>=", "");
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "operator>=", "");
						return this->length() >= x;
					}
					
					virtual bool operator==(int x) const{
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "operator==", "");
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "operator==", "");
						return this->length() == x;
					}
					
					virtual bool operator!=(int x) const{
						MemberArrayMapCollectionLog(pankey_Log_StartMethod, "operator!=", "");
						MemberArrayMapCollectionLog(pankey_Log_EndMethod, "operator!=", "");
						return this->length() != x;
					}
				
				protected:
					MemberArrayStorage<H,M> m_keys;
					MemberArrayStorage<H,M> m_values;
					bool m_reorder = true;
			};

		}

	}

#endif