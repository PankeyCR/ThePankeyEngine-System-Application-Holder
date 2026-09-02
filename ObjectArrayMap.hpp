
#ifndef ObjectArrayMap_hpp
	#define ObjectArrayMap_hpp
	
	#include "ValueArrayMapCollection.hpp"
	#include "DuoTypeMember.hpp"
	#include "Pointer.hpp"
	#include "ClassCount.hpp"

	#if defined(pankey_Log) && (defined(ObjectArrayMap_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define ObjectArrayMapLog(status,method,mns) pankey_Log(status,"ObjectArrayMap",method,mns)
	#else
		#define ObjectArrayMapLog(status,method,mns) 
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class K, class V, class H, class M>
			class ObjectArrayMap : public ValueArrayMapCollection<K,V,H,M>{
				public:
					ObjectArrayMap(){
						ObjectArrayMapLog(pankey_Log_StartMethod, "Constructor", "");
						ObjectArrayMapLog(pankey_Log_EndMethod, "Constructor", "");
					}
			
					ObjectArrayMap(const ObjectArrayMap<K,V,H,M>& a_map){
						ObjectArrayMapLog(pankey_Log_StartMethod, "Constructor", "const ObjectArrayMap<K,V,H,M>&");
						for(int x = 0; x < a_map.length(); x++){
							Object<K,H,M> f_key = a_map.getKey(x);
							Object<V,H,M> f_value = a_map.getValue(x);
							this->add(f_key, f_value);
						}
						ObjectArrayMapLog(pankey_Log_EndMethod, "Constructor", "");
					}

					virtual ~ObjectArrayMap(){
						ObjectArrayMapLog(pankey_Log_StartMethod, "Destructor", "");
						ObjectArrayMapLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual long getKeyBaseType()const{
						ObjectArrayMapLog(pankey_Log_StartMethod, "getKeyBaseType", "");
						ObjectArrayMapLog(pankey_Log_Statement, "getKeyBaseType", Base::ClassCount<K>::get());
						ObjectArrayMapLog(pankey_Log_EndMethod, "getKeyBaseType", "");
						return Base::ClassCount<K>::get();
					}

					virtual long getValueBaseType()const{
						ObjectArrayMapLog(pankey_Log_StartMethod, "getValueBaseType", "");
						ObjectArrayMapLog(pankey_Log_Statement, "getValueBaseType", Base::ClassCount<V>::get());
						ObjectArrayMapLog(pankey_Log_EndMethod, "getValueBaseType", "");
						return Base::ClassCount<V>::get();
					}

					virtual DuoTypeMember<K,V,H,M> add(Object<K,H,M>& a_key, Object<V,H,M>& a_value){
						ObjectArrayMapLog(pankey_Log_StartMethod, "add", "Object<K,H,M>& a_key, Object<V,H,M>& a_value");
						if(this->m_keys.add(this->m_length, a_key) && this->m_values.add(this->m_length, a_value)){
							ObjectArrayMapLog(pankey_Log_Statement, "add", "adding objects");
							this->incrementPosition();
						}
						ObjectArrayMapLog(pankey_Log_EndMethod, "add", "");
						return DuoTypeMember<K,V,H,M>(a_key, a_value);
					}

					virtual DuoTypeMember<K,V,H,M> add(DuoTypeMember<K,V,H,M>& a_duo){
						ObjectArrayMapLog(pankey_Log_StartMethod, "add", "");
						Member<H,M> i_member = a_duo.getMember();
						Member<H,M> i_duo_member = a_duo.getDuoTypeMember();
						if(i_member.getBaseType() != this->getKeyBaseType() || i_duo_member.getBaseType() != this->getValueBaseType()){
							return DuoTypeMember<K,V,H,M>();
						}
						if(this->m_keys.add(this->m_length, i_member) && this->m_values.add(this->m_length, i_duo_member)){
							this->incrementPosition();
						}
						ObjectArrayMapLog(pankey_Log_EndMethod, "add", "");
						return a_duo;
					}
					
					virtual DuoTypeMember<K,V,H,M> put(DuoTypeMember<K,V,H,M>& a_duo){
						ObjectArrayMapLog(pankey_Log_StartMethod, "put", "");
						if(this->m_keys.containByPointer(a_duo.getMember())){
							return a_duo;
						}
						ObjectArrayMapLog(pankey_Log_EndMethod, "put", "");
						return this->add(a_duo);
					}
			
					virtual ObjectArrayMap<K,V,H,M>& operator=(const ObjectArrayMap<K,V,H,M>& a_map){
						ObjectArrayMapLog(pankey_Log_StartMethod, "operator=", "const ObjectArrayMap<K,V,H,M>&");
						for(int x = 0; x < a_map.length(); x++){
							Object<K,H,M> f_key = a_map.getKey(x);
							Object<V,H,M> f_value = a_map.getValue(x);
							this->add(f_key, f_value);
						}
						ObjectArrayMapLog(pankey_Log_EndMethod, "operator=", "");
						return *this;
					}
			
					virtual bool operator==(const ObjectArrayMap<K,V,H,M>& a_map){
						ObjectArrayMapLog(pankey_Log_StartMethod, "operator=", "const ObjectArrayMap<K,V,H,M>&");
						if(this->length() != a_map.length()){
							return false;
						}
						for(int x = 0; x < a_map.length(); x++){
							auto f_key_1 = this->getKey(x);
							auto f_value_1 = this->getValue(x);
							auto f_key_2 = a_map.getKey(x);
							auto f_value_2 = a_map.getValue(x);
							if(f_key_1 != f_key_2 || f_value_1 != f_value_2){
								return false;
							}
						}
						ObjectArrayMapLog(pankey_Log_EndMethod, "operator=", "");
						return true;
					}
			
					virtual bool operator!=(const ObjectArrayMap<K,V,H,M>& a_map){
						ObjectArrayMapLog(pankey_Log_StartMethod, "operator=", "const ObjectArrayMap<K,V,H,M>&");
						if(this->length() != a_map.length()){
							return true;
						}
						for(int x = 0; x < a_map.length(); x++){
							auto f_key_1 = this->getKey(x);
							auto f_value_1 = this->getValue(x);
							auto f_key_2 = a_map.getKey(x);
							auto f_value_2 = a_map.getValue(x);
							if(f_key_1 != f_key_2 || f_value_1 != f_value_2){
								return true;
							}
						}
						ObjectArrayMapLog(pankey_Log_EndMethod, "operator=", "");
						return false;
					}
			};

		}

	}

#endif