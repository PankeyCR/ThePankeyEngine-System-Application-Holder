
#ifndef ValueMapCollection_hpp
	#define ValueMapCollection_hpp

	#include "MapCollection.hpp"

	#if defined(pankey_Log) && (defined(ValueMapCollection_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define ValueMapCollectionLog(status,method,mns) pankey_Log(status,"ValueMapCollection",method,mns)
	#else
		#define ValueMapCollectionLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class K, class V, class H, class M>
			class ValueMapCollection : virtual public MapCollection<H,M>{
				public:

					virtual ~ValueMapCollection(){
						ValueMapCollectionLog(pankey_Log_StartMethod, "Destructor", "");
						ValueMapCollectionLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual Member<H,M> getKeyByValue(const Member<H,M>& a_value)const=0;

					virtual Member<H,M> getValueByValue(const Member<H,M>& a_value)const=0;

					// virtual bool containByValue(const Member<H,M>& a_value)const=0;

					// virtual bool containKeyByValue(const Member<H,M>& a_value)const=0;

					// virtual bool containValueByValue(const Member<H,M>& a_value)const=0;
					
					// virtual int getKeyIndexByValue(const Member<H,M>& a_value)const=0;
					
					// virtual int getValueIndexByValue(const Member<H,M>& a_value)const=0;
					
					// virtual bool removeKeyByValue(const Member<H,M>& a_value)=0;
					
					// virtual bool removeValueByValue(const Member<H,M>& a_value)=0;
			};

		}

	}

#endif