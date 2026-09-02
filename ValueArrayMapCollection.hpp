
#ifndef ValueArrayMapCollection_hpp
	#define ValueArrayMapCollection_hpp

	#include "Collection.hpp"
	#include "MemberArrayMapCollection.hpp"
	#include "DuoMember.hpp"
	#include "ValueMapCollection.hpp"

	#if defined(pankey_Log) && (defined(ValueArrayMapCollection_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define ValueArrayMapCollectionLog(status,method,mns) pankey_Log(status,"ValueArrayMapCollection",method,mns)
	#else
		#define ValueArrayMapCollectionLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class T, class H>
			bool ValueArrayMapCollection_FromPointer(void* a_pointer_1, void* a_pointer_2){
				if(a_pointer_1 == nullptr || a_pointer_2 == nullptr){
					return false;
				}
				T* i_pointer_1 = (T*)a_pointer_1;
				T* i_pointer_2 = (T*)a_pointer_2;
				return (*i_pointer_1) == (*i_pointer_2);
			}

			template<class K, class V, class H, class M>
			class ValueArrayMapCollection : public MemberArrayMapCollection<H,M>, virtual public ValueMapCollection<K,V,H,M>{
				public:
					ValueArrayMapCollection(){
						ValueArrayMapCollectionLog(pankey_Log_StartMethod, "Constructor", "");
						ValueArrayMapCollectionLog(pankey_Log_EndMethod, "Constructor", "");
					}

					virtual ~ValueArrayMapCollection(){
						ValueArrayMapCollectionLog(pankey_Log_StartMethod, "Destructor", "");
						ValueArrayMapCollectionLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual Member<H,M> getKeyByValue(const Member<H,M>& a_value)const{
						ValueArrayMapCollectionLog(pankey_Log_StartMethod, "getKeyByValue", "");
						int i_index = this->m_values.getIndex(ValueArrayMapCollection_FromPointer<K,H>, a_value);
						if(i_index == -1){
							ValueArrayMapCollectionLog(pankey_Log_Statement, "getKeyByValue", "i_index == -1");
							return Member<H,M>();
						}
						ValueArrayMapCollectionLog(pankey_Log_EndMethod, "getKeyByValue", "");
						return this->m_keys.get(i_index);
					}

					virtual Member<H,M> getValueByValue(const Member<H,M>& a_value)const{
						ValueArrayMapCollectionLog(pankey_Log_StartMethod, "getValueByValue", "");
						int i_index = this->m_keys.getIndex(ValueArrayMapCollection_FromPointer<K,H>, a_value);
						if(i_index == -1){
							ValueArrayMapCollectionLog(pankey_Log_EndMethod, "getValueByValue", "i_index == -1");
							return Member<H,M>();
						}
						ValueArrayMapCollectionLog(pankey_Log_EndMethod, "getValueByValue", "");
						return this->m_values.get(i_index);
					}

					virtual bool containByValue(const Member<H,M>& a_value)const{
						ValueArrayMapCollectionLog(pankey_Log_StartMethod, "containByValue", "");
						ValueArrayMapCollectionLog(pankey_Log_EndMethod, "containByValue", "");
						return true;
					}
					
					virtual int getIndexByValue(const Member<H,M>& a_value)const{
						ValueArrayMapCollectionLog(pankey_Log_StartMethod, "getIndexByValue", "");
						ValueArrayMapCollectionLog(pankey_Log_EndMethod, "getIndexByValue", "");
						return 1;
					}
					
					virtual bool removeByValue(const Member<H,M>& a_value){
						ValueArrayMapCollectionLog(pankey_Log_StartMethod, "removeByValue", "");
						ValueArrayMapCollectionLog(pankey_Log_EndMethod, "removeByValue", "");
						return true;
					}
			};

		}

	}

#endif