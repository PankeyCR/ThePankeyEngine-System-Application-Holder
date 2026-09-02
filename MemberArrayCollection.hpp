
#ifndef MemberArrayCollection_hpp
	#define MemberArrayCollection_hpp

	#include "Collection.hpp"
	#include "MemberArrayStorage.hpp"
	#include "Member.hpp"

	#if defined(pankey_Log) && (defined(MemberArrayCollection_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define MemberArrayCollectionLog(status,method,mns) pankey_Log(status,"MemberArrayCollection",method,mns)
	#else
		#define MemberArrayCollectionLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class H, class M>
			class MemberArrayCollection : public Collection<H,M>{
				public:
					MemberArrayCollection(){
						MemberArrayCollectionLog(pankey_Log_StartMethod, "Constructor", "");
						MemberArrayCollectionLog(pankey_Log_EndMethod, "Constructor", "");
					}

					virtual ~MemberArrayCollection(){
						MemberArrayCollectionLog(pankey_Log_StartMethod, "Destructor", "");
						MemberArrayCollectionLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					virtual bool isEmpty()const{
						MemberArrayCollectionLog(pankey_Log_StartMethod, "isEmpty", "");
						MemberArrayCollectionLog(pankey_Log_EndMethod, "isEmpty", "");
						return this->m_storage.isNull() || this->m_storage.getSize() <= 0 || this->m_length <= 0;
					}

					virtual int length()const{
						MemberArrayCollectionLog(pankey_Log_StartMethod, "length", "");
						MemberArrayCollectionLog(pankey_Log_EndMethod, "length", "");
						return this->m_length;
					}
					
					virtual int getSize()const{
						MemberArrayCollectionLog(pankey_Log_StartMethod, "getSize", "");
						MemberArrayCollectionLog(pankey_Log_EndMethod, "getSize", "");
						return this->m_storage.getSize();
					}

					virtual bool replace(int a_index_1, int a_index_2){
						MemberArrayCollectionLog(pankey_Log_StartMethod, "replace", "");
						MemberArrayCollectionLog(pankey_Log_EndMethod, "replace", "");
						return this->m_storage.replace(a_index_1, a_index_2);
					}

					virtual Member<H,M> getByPointer(const Member<H,M>& a_value)const{
						MemberArrayCollectionLog(pankey_Log_StartMethod, "getByPointer", "");
						if(!this->m_storage.containByPointer(a_value)){
							MemberArrayCollectionLog(pankey_Log_Statement, "getByPointer", "!this->m_storage.contain(a_value)");
							return Member<H,M>();
						}
						MemberArrayCollectionLog(pankey_Log_EndMethod, "getByPointer", "");
						return a_value;
					}

					virtual Member<H,M> get(int x)const{
						MemberArrayCollectionLog(pankey_Log_StartMethod, "get", "");
						MemberArrayCollectionLog(pankey_Log_EndMethod, "get", "");
						return this->m_storage.get(x);
					}

					virtual bool containByPointer(const Member<H,M>& a_value)const{
						MemberArrayCollectionLog(pankey_Log_StartMethod, "containByPointer", "");
						MemberArrayCollectionLog(pankey_Log_EndMethod, "containByPointer", "");
						return this->m_storage.containByPointer(a_value);
					}
					
					virtual int getIndexByPointer(const Member<H,M>& a_value)const{
						MemberArrayCollectionLog(pankey_Log_StartMethod, "getIndexByPointer", "");
						MemberArrayCollectionLog(pankey_Log_EndMethod, "getIndexByPointer", "");
						return this->m_storage.getIndexByPointer(a_value);
					}
					
					virtual bool removeByPointer(const Member<H,M>& a_value){
						MemberArrayCollectionLog(pankey_Log_StartMethod, "removeByPointer", "");
						int i_index = this->m_storage.getIndexByPointer(a_value);
						if(i_index == -1){
							MemberArrayCollectionLog(pankey_Log_EndMethod, "removeByPointer", "");
							return false;
						}
						MemberArrayCollectionLog(pankey_Log_Statement, "removeByPointer", "index that is been removed:");
						MemberArrayCollectionLog(pankey_Log_Statement, "removeByPointer", i_index);
						this->m_storage.removeByIndex(i_index);
						this->m_storage.reorder(i_index, this->length());
						MemberArrayCollectionLog(pankey_Log_EndMethod, "removeByPointer", "");
						return true;
					}
					
					virtual Member<H,M> remove(int a_index){
						MemberArrayCollectionLog(pankey_Log_StartMethod, "remove", "");
						if(a_index < 0 || this->isEmpty() || a_index >= this->length()){
							MemberArrayCollectionLog(pankey_Log_EndMethod, "remove", "");
							return Member<H,M>();
						}
						Member<H,M> i_pointer = this->m_storage.removeByIndex(a_index);
						this->m_storage.reorder(a_index, this->length());
						this->decrementPosition();
						MemberArrayCollectionLog(pankey_Log_EndMethod, "remove", "");
						return i_pointer;
					}
					
					virtual bool removeFirstIndex(int a_amount){
						MemberArrayCollectionLog(pankey_Log_StartMethod, "removeFirstIndex", "");
						if(this->m_storage.removeFirstIndex(this->m_length, a_amount)){
							this->m_storage.reorder(0, this->length(), a_amount);
							this->decrementPosition(a_amount);
							MemberArrayCollectionLog(pankey_Log_EndMethod, "removeFirstIndex", "");
							return true;
						}
						MemberArrayCollectionLog(pankey_Log_EndMethod, "removeFirstIndex", "");
						return false;
					}

					virtual bool removeLastIndex(int a_amount){
						MemberArrayCollectionLog(pankey_Log_StartMethod, "removeLastIndex", "");
						if(this->m_storage.removeLastIndex(this->m_length, a_amount)){
							this->decrementPosition(a_amount);
							MemberArrayCollectionLog(pankey_Log_EndMethod, "removeLastIndex", "");
							return true;
						}
						MemberArrayCollectionLog(pankey_Log_EndMethod, "removeLastIndex", "");
						return false;
					}

					virtual bool removePart(int a_index, int a_amount){
						MemberArrayCollectionLog(pankey_Log_StartMethod, "removePart", "");
						if(this->m_storage.removePart(a_index, this->m_length, a_amount)){
							this->m_storage.reorder(a_index, this->length(), a_amount);
							this->decrementPosition(a_amount);
							MemberArrayCollectionLog(pankey_Log_EndMethod, "removePart", "");
							return true;
						}
						MemberArrayCollectionLog(pankey_Log_EndMethod, "removePart", "");
						return false;
					}
					
					virtual bool removeFirst(){
						MemberArrayCollectionLog(pankey_Log_StartMethod, "removeFirst", "");
						if(this->m_storage.removeFirst()){
							this->m_storage.reorder(0, this->length());
							this->decrementPosition();
							MemberArrayCollectionLog(pankey_Log_EndMethod, "removeFirst", "true");
							return true;
						}
						MemberArrayCollectionLog(pankey_Log_EndMethod, "removeFirst", "false");
						return false;
					}

					virtual bool removeLast(){
						MemberArrayCollectionLog(pankey_Log_StartMethod, "removeLast", "");
						if(this->isEmpty()){
							MemberArrayCollectionLog(pankey_Log_EndMethod, "removeLast", "");
							return false;
						}
						Member<H,M> i_pointer = this->m_storage.removeByIndex(this->length() - 1);
						this->m_storage.reorder(this->length() - 1, this->length());
						this->decrementPosition();
						MemberArrayCollectionLog(pankey_Log_EndMethod, "removeLast", "");
						return true;
					}
					
					virtual bool clear(){
						MemberArrayCollectionLog(pankey_Log_StartMethod, "clear", "");
						this->m_length = 0;
						if(this->m_storage.clear()){
							this->m_length = 0;
							MemberArrayCollectionLog(pankey_Log_EndMethod, "clear", "");
							return true;
						}
						MemberArrayCollectionLog(pankey_Log_EndMethod, "clear", "");
						return false;
					}

					virtual bool isInOrder()const{
						MemberArrayCollectionLog(pankey_Log_StartMethod, "isInOrder", "");
						MemberArrayCollectionLog(pankey_Log_EndMethod, "isInOrder", "");
						return this->m_reorder;
					}

					virtual void setReorder(bool a_reorder){
						MemberArrayCollectionLog(pankey_Log_StartMethod, "setReorder", "");
						if(a_reorder != this->m_reorder){
							MemberArrayCollectionLog(pankey_Log_EndMethod, "setReorder", "");
							return;
						}
						this->m_reorder = a_reorder;
						reorder();
						MemberArrayCollectionLog(pankey_Log_EndMethod, "setReorder", "");
					}
					
					virtual void reorder(){
						MemberArrayCollectionLog(pankey_Log_StartMethod, "reorder", "");
						if(!this->m_reorder){
							MemberArrayCollectionLog(pankey_Log_Statement, "reorder", "this->m_reorder || this->m_storage == nullptr");
							return;
						}
						this->m_storage.reorder();
						MemberArrayCollectionLog(pankey_Log_EndMethod, "reorder", "");
					}
					
				protected:
					
					virtual void incrementPosition(){
						MemberArrayCollectionLog(pankey_Log_StartMethod, "incrementPosition", "");
						this->m_length++;
						MemberArrayCollectionLog(pankey_Log_EndMethod, "incrementPosition", "");
					}
					virtual void decrementPosition(){
						MemberArrayCollectionLog(pankey_Log_StartMethod, "decrementPosition", "");
						this->m_length--;
						if(this->m_length < 0){
							this->m_length = 0;
						}
						MemberArrayCollectionLog(pankey_Log_EndMethod, "decrementPosition", "");
					}
					
					virtual void incrementPosition(int a_size){
						MemberArrayCollectionLog(pankey_Log_StartMethod, "incrementPosition", "");
						this->m_length += a_size;
						MemberArrayCollectionLog(pankey_Log_EndMethod, "incrementPosition", "");
					}
					virtual void decrementPosition(int a_size){
						MemberArrayCollectionLog(pankey_Log_StartMethod, "decrementPosition", "");
						this->m_length -= a_size;
						if(this->m_length < 0){
							this->m_length = 0;
						}
						MemberArrayCollectionLog(pankey_Log_EndMethod, "decrementPosition", "");
					}

				public:
				
					virtual bool operator<(int x) const{
						MemberArrayCollectionLog(pankey_Log_StartMethod, "operator<", "");
						MemberArrayCollectionLog(pankey_Log_EndMethod, "operator<", "");
						return this->length() < x;
					}
					
					virtual bool operator>(int x) const{
						MemberArrayCollectionLog(pankey_Log_StartMethod, "operator>", "");
						MemberArrayCollectionLog(pankey_Log_EndMethod, "operator>", "");
						return this->length() > x;
					}
					
					virtual bool operator<=(int x) const{
						MemberArrayCollectionLog(pankey_Log_StartMethod, "operator<=", "");
						MemberArrayCollectionLog(pankey_Log_EndMethod, "operator<=", "");
						return this->length() <= x;
					}
					
					virtual bool operator>=(int x) const{
						MemberArrayCollectionLog(pankey_Log_StartMethod, "operator>=", "");
						MemberArrayCollectionLog(pankey_Log_EndMethod, "operator>=", "");
						return this->length() >= x;
					}
					
					virtual bool operator==(int x) const{
						MemberArrayCollectionLog(pankey_Log_StartMethod, "operator==", "");
						MemberArrayCollectionLog(pankey_Log_EndMethod, "operator==", "");
						return this->length() == x;
					}
					
					virtual bool operator!=(int x) const{
						MemberArrayCollectionLog(pankey_Log_StartMethod, "operator!=", "");
						MemberArrayCollectionLog(pankey_Log_EndMethod, "operator!=", "");
						return this->length() != x;
					}
				
				protected:
					MemberArrayStorage<H,M> m_storage;
					int m_length = 0;
					bool m_reorder = true;
			};

		}

	}

#endif