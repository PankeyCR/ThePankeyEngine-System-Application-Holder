
#ifndef MapCollection_hpp
	#define MapCollection_hpp

	#include "Collection.hpp"

	#if defined(pankey_Log) && (defined(MapCollection_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define MapCollectionLog(status,method,mns) pankey_Log(status,"MapCollection",method,mns)
	#else
		#define MapCollectionLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class H, class M>
			class MapCollection : virtual public Collection<H,M>{
				public:

					virtual ~MapCollection(){
						MapCollectionLog(pankey_Log_StartMethod, "Destructor", "");
						MapCollectionLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual Member<H,M> getKeyByPointer(const Member<H,M>& a_value)const=0;

					virtual Member<H,M> getValueByPointer(const Member<H,M>& a_value)const=0;

					virtual Member<H,M> getKey(int x)const=0;

					virtual Member<H,M> getValue(int x)const=0;

					virtual bool containKeyByPointer(const Member<H,M>& a_value)const=0;

					virtual bool containValueByPointer(const Member<H,M>& a_value)const=0;
					
					virtual int getKeyIndexByPointer(const Member<H,M>& a_value)const=0;
					
					virtual int getValueIndexByPointer(const Member<H,M>& a_value)const=0;
					
					virtual bool removeKeyByPointer(const Member<H,M>& a_value)=0;
					
					virtual bool removeValueByPointer(const Member<H,M>& a_value)=0;
			};

		}

	}

#endif