
#ifndef MemberArrayList_hpp
	#define MemberArrayList_hpp
	
	#include "MemberArrayCollection.hpp"

	#if defined(pankey_Log) && (defined(MemberArrayList_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define MemberArrayListLog(status,method,mns) pankey_Log(status,"MemberArrayList",method,mns)
	#else
		#define MemberArrayListLog(status,method,mns) 
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class H, class A>
			class MemberArrayList : public MemberArrayCollection<H,A>{
				public:
					MemberArrayList(){
						MemberArrayListLog(pankey_Log_StartMethod, "Constructor", "");
						MemberArrayListLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~MemberArrayList(){
						MemberArrayListLog(pankey_Log_StartMethod, "Destructor", "");
						MemberArrayListLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual Member<H,A> add(Member<H,A>& a_pointer){
						MemberArrayListLog(pankey_Log_StartMethod, "add", "");
						if(this->m_storage.add(this->m_length, a_pointer)){
							this->incrementPosition();
						}
						MemberArrayListLog(pankey_Log_EndMethod, "add", "");
						return a_pointer;
					}
					
					virtual Member<H,A> put(Member<H,A>& a_pointer){
						MemberArrayListLog(pankey_Log_StartMethod, "put", "");
						if(this->m_storage.containByPointer(a_pointer)){
							return Member<H,A>();
						}
						MemberArrayListLog(pankey_Log_EndMethod, "put", "");
						return this->add(a_pointer);
					}

					virtual Member<H,A> set(int a_position, Member<H,A>& a_value){
						MemberArrayListLog(pankey_Log_StartMethod, "set", "");
						MemberArrayListLog(pankey_Log_EndMethod, "set", "");
						return this->set(a_position, a_value);
					}

					virtual Member<H,A> insert(int a_position, Member<H,A>& a_value){
						MemberArrayListLog(pankey_Log_StartMethod, "insert", "");
						MemberArrayListLog(pankey_Log_EndMethod, "insert", "");
						return this->insert(a_position, a_value);
					}
					
					virtual void move(Collection<H,A>& a_collection){
						CollectionLog(pankey_Log_StartMethod, "move", "");
						for(int x = 0; x < a_collection.length(); x++){
							Member<H,A> f_value = a_collection.get(x);
							this->add(f_value);
						}
						a_collection.clear();
						CollectionLog(pankey_Log_EndMethod, "move", "");
					}
					
					virtual void duplicate(const Collection<H,A>& a_collection){
						CollectionLog(pankey_Log_StartMethod, "duplicate", "");
						for(int x = 0; x < a_collection.length(); x++){
							Member<H,A> f_value = a_collection.get(x);
							this->add(f_value);
						}
						CollectionLog(pankey_Log_EndMethod, "duplicate", "");
					}
			};

		}

	}

#endif