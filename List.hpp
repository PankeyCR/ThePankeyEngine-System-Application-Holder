
#ifndef List_hpp
	#define List_hpp

	#include "shared_ptr.hpp"

	#if defined(pankey_Log) && (defined(List_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define ListLog(status,method,mns) pankey_Log(status,"List",method,mns)
	#else
		#define ListLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template <class T, class M>
			class List{	
				public:
					virtual ~List(){}
                    
                    virtual bool isEmpty()const=0;
					
                    virtual int length()const=0;

                    virtual bool replace(int i, int j)=0;

                    virtual void add(const shared_ptr<T,M>& a_value)=0;
                    
                    // virtual shared_ptr<T,M> put(const shared_ptr<T,M>& a_value)=0;

                    // virtual shared_ptr<T,M> set(int a_index, const shared_ptr<T,M>& a_value)=0;

                    // virtual shared_ptr<T,M> insert(int a_index, const shared_ptr<T,M>& a_value)=0;

                    // virtual shared_ptr<T,M> get(const shared_ptr<T,M>& a_value)=0;
                    // virtual shared_ptr<T,M> getByIndex(int x)const=0;

                    // virtual bool contain(const shared_ptr<T,M>& a_value)=0;
                    
                    // virtual int getIndex(const shared_ptr<T,M>& a_value)=0;

                    // virtual void reset()=0;
                    // virtual void clear()=0;

                    // virtual shared_ptr<T,M> remove(const shared_ptr<T,M>& a_value)=0;

                    // virtual shared_ptr<T,M> removeByIndex(int a_index)=0;

                    // virtual bool destroy(const shared_ptr<T,M>& a_value){
                    //     ListLog(pankey_Log_StartMethod, "destroyBy", "");
                    //     shared_ptr<T,M> t = this->remove(a_value);
                    //     bool removed = t != nullptr;
                    //     if(removed && isOwner()){
                    //         delete t;
                    //     }
                    //     ListLog(pankey_Log_EndMethod, "destroyBy", "");
                    //     return removed;
                    // }

                    // virtual bool destroyByIndex(int a_index){
                    //     ListLog(pankey_Log_StartMethod, "destroyByIndex", "");
                    //     shared_ptr<T,M> t = this->removeByIndex(a_index);
                    //     bool removed = t != nullptr;
                    //     if(removed && isOwner()){
                    //         ListLog(pankey_Log_Statement, "destroyByIndex", "deleting ");
                    //         delete t;
                    //     }
                    //     ListLog(pankey_Log_EndMethod, "destroyByIndex", "");
                    //     return removed;
                    // }

                    // //special removes
                    // virtual bool destroyFirstIndex(int a_amount)=0;
                    // virtual bool destroyLastIndex(int a_amount)=0;
                    
                    // virtual shared_ptr<T,M> removeFirst(){
                    //     ListLog(pankey_Log_StartMethod, "removeFirst", "");
                    //     ListLog(pankey_Log_EndMethod, "removeFirst", "");
                    //     return this->removeByIndex(0);
                    // }
                    
                    // virtual bool destroyFirst(){
                    //     ListLog(pankey_Log_StartMethod, "destroyFirst", "");
                    //     if(this->isEmpty()){
                    //         ListLog(pankey_Log_EndMethod, "destroyFirst", "this->isEmpty()");
                    //         return false;
                    //     }
                    //     ListLog(pankey_Log_EndMethod, "destroyFirst", "");
                    //     return this->destroyByIndex(0);
                    // }

                    // virtual shared_ptr<T,M> removeLast(){
                    //     ListLog(pankey_Log_StartMethod, "removeLast", "");
                    //     ListLog(pankey_Log_EndMethod, "removeLast", "");
                    //     return this->removeByIndex(this->length() - 1);
                    // }

                    // virtual bool destroyLast(){
                    //     ListLog(pankey_Log_StartMethod, "destroyLast", "");
                    //     if(this->isEmpty()){
                    //         return false;
                    //     }
                    //     ListLog(pankey_Log_EndMethod, "destroyLast", "");
                    //     return this->destroyByIndex(this->length() - 1);
                    // }
                    
                    // virtual void destroyFromList(const RawList<T>& a_list){
                    //     ListLog(pankey_Log_StartMethod, "destroyFromList", "");
                    //     for(int x = 0; x < a_list.length(); x++){
                    //         shared_ptr<T,M> f_value = a_list.getByIndex(x);
                    //         this->destroy(f_value);
                    //     }
                    //     ListLog(pankey_Log_EndMethod, "destroyFromList", "");
                    // }

                    // virtual bool isInOrder(){return true;}
                    // virtual void setReorder(bool a_reorder){}
                    // virtual void reorder(){}

                    // virtual void expand(int a_size)=0;
				private:
			};

		}

	}

#endif