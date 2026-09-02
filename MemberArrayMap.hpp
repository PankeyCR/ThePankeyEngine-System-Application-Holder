
#ifndef MemberArrayMap_hpp
	#define MemberArrayMap_hpp
	
	#include "MemberArrayMapCollection.hpp"
	#include "DuoMember.hpp"
	#include "ClassCount.hpp"

	#if defined(pankey_Log) && (defined(MemberArrayMap_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define MemberArrayMapLog(status,method,mns) pankey_Log(status,"MemberArrayMap",method,mns)
	#else
		#define MemberArrayMapLog(status,method,mns) 
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class H, class M>
			class MemberArrayMap : public MemberArrayMapCollection<H,M>{
				public:
					MemberArrayMap(){
						MemberArrayMapLog(pankey_Log_StartMethod, "Constructor", "");
						MemberArrayMapLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~MemberArrayMap(){
						MemberArrayMapLog(pankey_Log_StartMethod, "Destructor", "");
						MemberArrayMapLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual DuoMember<H,M> add(Member<H,M>& a_key, Member<H,M>& a_value){
						MemberArrayListLog(pankey_Log_StartMethod, "add", "");
						if(this->m_keys.add(this->m_length, a_key) && this->m_values.add(this->m_length, a_value)){
							this->incrementPosition();
						}
						MemberArrayListLog(pankey_Log_EndMethod, "add", "");
						return DuoMember<H,M>(a_key, a_value);
					}

					virtual DuoMember<H,M> add(DuoMember<H,M>& a_duo){
						MemberArrayListLog(pankey_Log_StartMethod, "add", "");
						Member<H,M> i_member = a_duo.getMember();
						Member<H,M> i_duo_member = a_duo.getDuoMember();
						if(this->m_keys.add(this->m_length, i_member) && this->m_values.add(this->m_length, i_duo_member)){
							this->incrementPosition();
						}
						MemberArrayListLog(pankey_Log_EndMethod, "add", "");
						return a_duo;
					}
					
					virtual DuoMember<H,M> put(DuoMember<H,M>& a_duo){
						MemberArrayMapLog(pankey_Log_StartMethod, "put", "");
						if(this->m_keys.containByPointer(a_duo.getMember())){
							return a_duo;
						}
						MemberArrayMapLog(pankey_Log_EndMethod, "put", "");
						return this->add(a_duo);
					}
					
					virtual DuoMember<H,M> put(Member<H,M>& a_key, Member<H,M>& a_value){
						MemberArrayMapLog(pankey_Log_StartMethod, "put", "");
						if(this->m_keys.containByPointer(a_key)){
							return DuoMember<H,M>(a_key, a_value);
						}
						MemberArrayMapLog(pankey_Log_EndMethod, "put", "");
						return this->add(a_key, a_value);
					}

					virtual DuoMember<H,M> getDuoMember(const Member<H,M>& a_value)const{
						MemberArrayMapLog(pankey_Log_StartMethod, "getDuoMember", "");
						int i_index = this->m_keys.getIndexByPointer(a_value);
						if(i_index == -1){
							MemberArrayMapLog(pankey_Log_EndMethod, "getDuoMember", "i_index == -1");
							return DuoMember<H,M>();
						}
						MemberArrayMapLog(pankey_Log_EndMethod, "getDuoMember", "");
						return DuoMember<H,M>(this->m_keys.get(i_index), this->m_values.get(i_index));
					}

					virtual DuoMember<H,M> getDuoMember(int a_index)const{
						MemberArrayMapLog(pankey_Log_StartMethod, "getDuoMember", "");
						if(a_index == -1){
							MemberArrayMapLog(pankey_Log_EndMethod, "getDuoMember", "i_index == -1");
							return DuoMember<H,M>();
						}
						MemberArrayMapLog(pankey_Log_EndMethod, "getDuoMember", "");
						return DuoMember<H,M>(this->m_keys.get(a_index), this->m_values.get(a_index));
					}

					virtual bool containByPointer(const Member<H,M>& a_value)const{
						MemberArrayMapLog(pankey_Log_StartMethod, "containByPointer", "");
						MemberArrayMapLog(pankey_Log_EndMethod, "containByPointer", "");
						return this->m_keys.containByPointer(a_value) || this->m_values.containByPointer(a_value);
					}

					virtual bool containByPointer(DuoMember<H,M>& a_duo)const{
						MemberArrayMapLog(pankey_Log_StartMethod, "contain", "");
						Member<H,M> i_member = a_duo.getMember();
						Member<H,M> i_duo_member = a_duo.getDuoMember();
						MemberArrayMapLog(pankey_Log_EndMethod, "contain", "");
						return this->m_keys.containByPointer(i_member) || this->m_values.containByPointer(i_duo_member);
					}
			};

		}

	}

#endif