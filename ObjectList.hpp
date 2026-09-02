
#ifndef ObjectList_hpp
	#define ObjectList_hpp
	
	#include "MemberArrayCollection.hpp"
	#include "ClassCount.hpp"
	#include "Object.hpp"

	#if defined(pankey_Log) && (defined(ObjectList_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define ObjectListLog(status,method,mns) pankey_Log(status,"ObjectList",method,mns)
	#else
		#define ObjectListLog(status,method,mns) 
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class O, class H, class M>
			class ObjectList : public MemberArrayCollection<H,M>{
				public:
					ObjectList(){
						ObjectListLog(pankey_Log_StartMethod, "Constructor", "");
						ObjectListLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~ObjectList(){
						ObjectListLog(pankey_Log_StartMethod, "Destructor", "");
						ObjectListLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual long getBaseType()const{
						ObjectListLog(pankey_Log_StartMethod, "getBaseType", "");
						ObjectListLog(pankey_Log_Statement, "getBaseType", Base::ClassCount<O>::get());
						ObjectListLog(pankey_Log_EndMethod, "getBaseType", "");
						return Base::ClassCount<O>::get();
					}

					virtual bool sameBaseType(long a_type)const{
						ObjectListLog(pankey_Log_StartMethod, "sameBaseType", "");
						if(a_type == -1){
							ObjectListLog(pankey_Log_Error, "sameBaseType", "The variable cheching has no type");
							ObjectListLog(pankey_Log_EndMethod, "sameBaseType", "");
							return false;
						}
						long i_type = this->getBaseType();
						if(i_type != a_type && i_type != -1){
							ObjectListLog(pankey_Log_Error, "sameBaseType", "Not a memeber because it has diferent types");
							ObjectListLog(pankey_Log_EndMethod, "sameBaseType", "");
							return false;
						}
						ObjectListLog(pankey_Log_EndMethod, "sameBaseType", "");
						return true;
					}

					virtual Member<H,M> add(Member<H,M>& a_pointer){
						ObjectListLog(pankey_Log_StartMethod, "add", "Member<H,M>");
						if(!this->sameBaseType(a_pointer.getBaseType())){
							ObjectListLog(pankey_Log_Error, "add", "Variable is not Member of Variable");
							ObjectListLog(pankey_Log_EndMethod, "add", "");
							return a_pointer;
						}
						if(this->m_storage.add(this->m_length, a_pointer)){
							ObjectListLog(pankey_Log_Statement, "add", "element added and know incrementing position");
							this->incrementPosition();
						}
						ObjectListLog(pankey_Log_EndMethod, "add", "");
						return a_pointer;
					}

					virtual Object<O,H,M> add(Object<O,H,M>& a_pointer){
						ObjectListLog(pankey_Log_StartMethod, "add", "Object<O,H,M>");
						ObjectListLog(pankey_Log_Statement, "add", "is the pointer null:");
						ObjectListLog(pankey_Log_Statement, "add", a_pointer.isNull());
						if(this->m_storage.add(this->m_length, a_pointer)){
							ObjectListLog(pankey_Log_Statement, "add", "element added and know incrementing position");
							this->incrementPosition();
						}
						ObjectListLog(pankey_Log_EndMethod, "add", "");
						return a_pointer;
					}
					
					virtual Member<H,M> put(Member<H,M>& a_pointer){
						ObjectListLog(pankey_Log_StartMethod, "put", "Member<H,M>");
						if(!this->sameBaseType(a_pointer.getBaseType())){
							ObjectListLog(pankey_Log_Error, "put", "Variable is not Member of Variable");
							ObjectListLog(pankey_Log_EndMethod, "put", "");
							return a_pointer;
						}
						if(this->m_storage.containByPointer(a_pointer)){
							return a_pointer;
						}
						ObjectListLog(pankey_Log_EndMethod, "put", "");
						return this->add(a_pointer);
					}
					
					virtual Object<O,H,M> put(Object<O,H,M>& a_pointer){
						ObjectListLog(pankey_Log_StartMethod, "put", "Object<O,H,M>");
						if(this->m_storage.containByPointer(a_pointer)){
							return a_pointer;
						}
						ObjectListLog(pankey_Log_EndMethod, "put", "");
						return this->add(a_pointer);
					}

					virtual Member<H,M> set(int a_position, Member<H,M>& a_pointer){
						ObjectListLog(pankey_Log_StartMethod, "set", "Member<H,M>");
						if(!this->sameBaseType(a_pointer.getBaseType())){
							ObjectListLog(pankey_Log_Error, "set", "Variable is not Member of Variable");
							ObjectListLog(pankey_Log_EndMethod, "set", "");
							return a_pointer;
						}
						if(a_position >= this->getSize()){
							return a_pointer;
						}
						ObjectListLog(pankey_Log_EndMethod, "set", "");
						this->m_storage.set(a_position, a_pointer);
						return a_pointer;
					}

					virtual Object<O,H,M> set(int a_position, Object<O,H,M>& a_pointer){
						ObjectListLog(pankey_Log_StartMethod, "set", "Object<O,H,M>");
						if(a_position >= this->getSize()){
							return a_pointer;
						}
						this->m_storage.set(a_position, a_pointer);
						ObjectListLog(pankey_Log_EndMethod, "set", "");
						return a_pointer;
					}

					virtual Member<H,M> insert(int a_position, Member<H,M>& a_pointer){
						ObjectListLog(pankey_Log_StartMethod, "insert", "Member<H,M>");
						if(!this->sameBaseType(a_pointer.getBaseType())){
							ObjectListLog(pankey_Log_Error, "insert", "Variable is not Member of Variable");
							ObjectListLog(pankey_Log_EndMethod, "insert", "");
							return a_pointer;
						}
						this->m_storage.insert(a_position, this->length(), 1);
						this->m_storage.set(a_position, a_pointer);
						this->incrementPosition();
						ObjectListLog(pankey_Log_EndMethod, "insert", "");
						return a_pointer;
					}

					virtual Object<O,H,M> insert(int a_position, Object<O,H,M>& a_pointer){
						ObjectListLog(pankey_Log_StartMethod, "insert", "Object<O,H,M>");
						this->m_storage.insert(a_position, this->length(), 1);
						this->m_storage.set(a_position, a_pointer);
						this->incrementPosition();
						ObjectListLog(pankey_Log_EndMethod, "insert", "");
						return a_pointer;
					}
			
					virtual ObjectList<O,H,M>& operator=(const ObjectList<O,H,M>& a_list){
						ObjectListLog(pankey_Log_StartMethod, "operator=", "");
						for(int x = 0; x < a_list.length(); x++){
							auto f_value = a_list.get(x);
							this->add(f_value);
						}
						ObjectListLog(pankey_Log_EndMethod, "operator=", "");
						return *this;
					}
			
					virtual bool operator==(const ObjectList<O,H,M>& a_list){
						ObjectListLog(pankey_Log_StartMethod, "operator=", "");
						if(this->length() != a_list.length()){
							return false;
						}
						for(int x = 0; x < a_list.length(); x++){
							auto f_value_1 = a_list.get(x);
							auto f_value_2 = this->get(x);
							if(f_value_1 != f_value_2){
								return false;
							}
						}
						ObjectListLog(pankey_Log_EndMethod, "operator=", "");
						return true;
					}
			
					virtual bool operator!=(const ObjectList<O,H,M>& a_list){
						ObjectListLog(pankey_Log_StartMethod, "operator=", "");
						if(this->length() != a_list.length()){
							return true;
						}
						for(int x = 0; x < a_list.length(); x++){
							auto f_value_1 = a_list.get(x);
							auto f_value_2 = this->get(x);
							if(f_value_1 == f_value_2){
								return false;
							}
						}
						ObjectListLog(pankey_Log_EndMethod, "operator=", "");
						return true;
					}
			};

		}

	}

#endif