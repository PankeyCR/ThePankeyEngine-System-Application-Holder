
#ifndef TypeList_hpp
	#define TypeList_hpp
	
	#include "MemberArrayCollection.hpp"
	#include "ClassCount.hpp"

	#if defined(pankey_Log) && (defined(TypeList_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define TypeListLog(status,method,mns) pankey_Log(status,"TypeList",method,mns)
	#else
		#define TypeListLog(status,method,mns) 
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class P, class H, class A>
			class TypeList : public MemberArrayCollection<H,A>{
				public:
					TypeList(){
						TypeListLog(pankey_Log_StartMethod, "Constructor", "");
						TypeListLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~TypeList(){
						TypeListLog(pankey_Log_StartMethod, "Destructor", "");
						TypeListLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual long getType()const{
						TypeListLog(pankey_Log_StartMethod, "getType", "");
						TypeListLog(pankey_Log_Statement, "getType", Base::ClassCount<P>::get());
						TypeListLog(pankey_Log_EndMethod, "getType", "");
						return Base::ClassCount<P>::get();
					}

					virtual bool sameType(long a_type)const{
						TypeListLog(pankey_Log_StartMethod, "sameType", "");
						if(a_type == -1){
							TypeListLog(pankey_Log_Error, "sameType", "The variable cheching has no type");
							TypeListLog(pankey_Log_EndMethod, "sameType", "");
							return false;
						}
						long i_type = this->getType();
						if(i_type != a_type){
							TypeListLog(pankey_Log_Error, "sameType", "Not a memeber because it has diferent types");
							TypeListLog(pankey_Log_EndMethod, "sameType", "");
							return false;
						}
						TypeListLog(pankey_Log_EndMethod, "sameType", "");
						return true;
					}

					virtual Member<H,A> add(Member<H,A>& a_pointer){
						TypeListLog(pankey_Log_StartMethod, "add", "");
						if(!this->sameType(a_pointer.getType())){
							TypeListLog(pankey_Log_Error, "add", "Variable is not Member of Variable");
							TypeListLog(pankey_Log_EndMethod, "add", "");
							return a_pointer;
						}
						if(this->m_storage.add(this->m_length, a_pointer)){
							this->incrementPosition();
						}
						TypeListLog(pankey_Log_EndMethod, "add", "");
						return a_pointer;
					}

					virtual Pointer<P,H,A> add(Pointer<P,H,A>& a_pointer){
						TypeListLog(pankey_Log_StartMethod, "add", "");
						if(this->m_storage.add(this->m_length, a_pointer)){
							this->incrementPosition();
						}
						TypeListLog(pankey_Log_EndMethod, "add", "");
						return a_pointer;
					}
					
					virtual Member<H,A> put(Member<H,A>& a_pointer){
						TypeListLog(pankey_Log_StartMethod, "put", "");
						if(!this->sameType(a_pointer.getType())){
							TypeListLog(pankey_Log_Error, "put", "Variable is not Member of Variable");
							TypeListLog(pankey_Log_EndMethod, "put", "");
							return a_pointer;
						}
						if(this->m_storage.containByPointer(a_pointer)){
							return a_pointer;
						}
						TypeListLog(pankey_Log_EndMethod, "put", "");
						return this->add(a_pointer);
					}
					
					virtual Pointer<P,H,A> put(Pointer<P,H,A>& a_pointer){
						TypeListLog(pankey_Log_StartMethod, "put", "");
						if(this->m_storage.containByPointer(a_pointer)){
							return a_pointer;
						}
						TypeListLog(pankey_Log_EndMethod, "put", "");
						return this->add(a_pointer);
					}

					virtual Member<H,A> set(int a_position, Member<H,A>& a_pointer){
						TypeListLog(pankey_Log_StartMethod, "set", "");
						if(!this->sameType(a_pointer.getType())){
							TypeListLog(pankey_Log_Error, "set", "Variable is not Member of Variable");
							TypeListLog(pankey_Log_EndMethod, "set", "");
							return a_pointer;
						}
						if(a_position >= this->getSize()){
							return a_pointer;
						}
						TypeListLog(pankey_Log_EndMethod, "set", "");
						this->m_storage.set(a_position, a_pointer);
						return a_pointer;
					}

					virtual Pointer<P,H,A> set(int a_position, Pointer<P,H,A>& a_pointer){
						TypeListLog(pankey_Log_StartMethod, "set", "");
						if(a_position >= this->getSize()){
							return a_pointer;
						}
						this->m_storage.set(a_position, a_pointer);
						TypeListLog(pankey_Log_EndMethod, "set", "");
						return a_pointer;
					}

					virtual Member<H,A> insert(int a_position, Member<H,A>& a_pointer){
						TypeListLog(pankey_Log_StartMethod, "insert", "");
						if(!this->sameType(a_pointer.getType())){
							TypeListLog(pankey_Log_Error, "insert", "Variable is not Member of Variable");
							TypeListLog(pankey_Log_EndMethod, "insert", "");
							return a_pointer;
						}
						this->m_storage.insert(a_position, this->length(), 1);
						this->m_storage.set(a_position, a_pointer);
						this->incrementPosition();
						TypeListLog(pankey_Log_EndMethod, "insert", "");
						return a_pointer;
					}

					virtual Pointer<P,H,A> insert(int a_position, Pointer<P,H,A>& a_pointer){
						TypeListLog(pankey_Log_StartMethod, "insert", "");
						this->m_storage.insert(a_position, this->length(), 1);
						this->m_storage.set(a_position, a_pointer);
						this->incrementPosition();
						TypeListLog(pankey_Log_EndMethod, "insert", "");
						return a_pointer;
					}
					
					virtual void move(Collection<H,A>& a_collection){
						TypeListLog(pankey_Log_StartMethod, "move", "");
						for(int x = 0; x < a_collection.length(); x++){
							Member<H,A> f_value = a_collection.get(x);
							this->add(f_value);
						}
						a_collection.clear();
						TypeListLog(pankey_Log_EndMethod, "move", "");
					}
					
					virtual void duplicate(const Collection<H,A>& a_collection){
						TypeListLog(pankey_Log_StartMethod, "duplicate", "");
						for(int x = 0; x < a_collection.length(); x++){
							Member<H,A> f_value = a_collection.get(x);
							this->add(f_value);
						}
						TypeListLog(pankey_Log_EndMethod, "duplicate", "");
					}
			};

		}

	}

#endif