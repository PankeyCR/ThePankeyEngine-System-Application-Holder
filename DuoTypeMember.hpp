
#ifndef DuoTypeMember_hpp
	#define DuoTypeMember_hpp

	#include "Member.hpp"
	#include "ClassCount.hpp"

	#if defined(pankey_Log) && (defined(DuoTypeMember_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
	    #include "Logger_status.hpp"
		#define DuoTypeMemberLog(status,method,mns) pankey_Log(status,"DuoTypeMember",method,mns)
	#else
		#define DuoTypeMemberLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

            template <class K, class V, class H, class M>
            class DuoTypeMember : public Member<H,M>{
                public:

                    using MANAGER_TYPE = typename MemoryHolder<H>::MANAGER_TYPE;
                    using VOID_TYPE = typename MemoryHolder<H>::VOID_TYPE;
                    using HOLDER_TYPE = typename MemoryHolder<H>::HOLDER_TYPE;

                    DuoTypeMember(){
                        DuoTypeMemberLog(pankey_Log_StartMethod, "Constructor", "");
                        DuoTypeMemberLog(pankey_Log_EndMethod, "Constructor", "");
                    }
                    
                    DuoTypeMember(Member<H,M> c_holder_0, Member<H,M> c_holder_1){
                        DuoTypeMemberLog(pankey_Log_StartMethod, "Constructor", "");
                        if(c_holder_0.sameType(Base::ClassCount<K>::get()) || c_holder_0.sameBaseType(Base::ClassCount<K>::get())){
                            this->setHolder(c_holder_0.getHolder());
                        }
                        if(c_holder_1.sameType(Base::ClassCount<V>::get()) || c_holder_1.sameBaseType(Base::ClassCount<V>::get())){
                            this->setDuoTypeHolder(c_holder_1.getHolder());
                        }
                        DuoTypeMemberLog(pankey_Log_EndMethod, "Constructor", "");
                    }
                    
                    DuoTypeMember(const DuoTypeMember<K,V,H,M>& c_duo_holder){
                        DuoTypeMemberLog(pankey_Log_StartMethod, "Constructor", "");
                        this->setHolder(c_duo_holder.getHolder());
                        this->setDuoTypeHolder(c_duo_holder.getDuoTypeHolder());
                        DuoTypeMemberLog(pankey_Log_EndMethod, "Constructor", "");
                    }
                    
                    virtual ~DuoTypeMember(){
                        DuoTypeMemberLog(pankey_Log_StartMethod, "Destructor", "");
                        this->removeDuoType();
                        DuoTypeMemberLog(pankey_Log_EndMethod, "Destructor", "");
                    }

                    virtual void copyMemoryHolder(const MemoryHolder<H>& a_holder){
                        MemoryHolderLog(pankey_Log_StartMethod, "copyMemoryHolder", "");
                        if(a_holder.isMember(this->getManager(), Base::ClassCount<K>::get())){
                            this->setHolder(a_holder.getHolder());
                        }
                        MemoryHolderLog(pankey_Log_EndMethod, "copyMemoryHolder", "");
                    }

                    virtual void copyMember(const Member<H,M>& a_holder){
                        MemberLog(pankey_Log_StartMethod, "copyMember", "");
                        if(a_holder.sameType(Base::ClassCount<K>::get()) || a_holder.sameBaseType(Base::ClassCount<K>::get())){
                            this->setHolder(a_holder.getHolder());
                        }
                        MemberLog(pankey_Log_EndMethod, "copyMember", "");
                    }

                    virtual void copyDuoTypeMember(const Member<H,M>& a_holder){
                        DuoTypeMemberLog(pankey_Log_StartMethod, "copyDuoTypeMember", "");
                        if(a_holder.sameType(Base::ClassCount<V>::get()) || a_holder.sameBaseType(Base::ClassCount<V>::get())){
                            this->setDuoTypeHolder(a_holder.getHolder());
                        }
                        DuoTypeMemberLog(pankey_Log_EndMethod, "copyDuoTypeMember", "");
                    }

                    virtual Member<H,M> getDuoTypeMember(){
                        DuoTypeMemberLog(pankey_Log_StartMethod, "getDuoTypeMember", "");
                        Member<H,M> i_member;
                        i_member.setHolder(this->m_duo_holder);
                        DuoTypeMemberLog(pankey_Log_EndMethod, "getDuoTypeMember", "");
                        return i_member;
                    }

                    virtual void removeDuoType(){
                        DuoTypeMemberLog(pankey_Log_StartMethod, "removeDuoType", "");
                        MemoryHolderManager<H>::remove(this->getManager(), this->m_duo_holder);
                        DuoTypeMemberLog(pankey_Log_EndMethod, "removeDuoType", "");
                    }

                    virtual void destroyDuoType(){
                        DuoTypeMemberLog(pankey_Log_StartMethod, "destroyDuoType", "");
                        MemoryHolderManager<H>::destroy(this->getManager(), this->m_duo_holder);
                        DuoTypeMemberLog(pankey_Log_EndMethod, "destroyDuoType", "");
                    }
                        
                    //unsafe method
                    virtual void setDuoTypeHolder(HOLDER_TYPE a_holder){
                        DuoTypeMemberLog(pankey_Log_StartMethod, "setDuoTypeHolder", "");
                        MemoryHolderManager<H>::add(this->getManager(), a_holder);
                        MemoryHolderManager<H>::remove(this->getManager(), this->m_duo_holder);
                        this->m_duo_holder = a_holder;
                        DuoTypeMemberLog(pankey_Log_EndMethod, "setDuoTypeHolder", "");
                    }

                    //unsafe method
                    virtual HOLDER_TYPE getDuoTypeHolder()const{
                        return this->m_duo_holder;
                    }

                    virtual HOLDER_TYPE& getDuoTypeHolderReference(){
                        return this->m_duo_holder;
                    }

                    virtual bool isDuoTypeHolderNull()const{
                        return this->m_duo_holder == nullptr;
                    }

                    virtual void copyDuoTypeMemoryHolder(const MemoryHolder<H>& a_holder){
                        DuoTypeMemberLog(pankey_Log_StartMethod, "copyDuoTypeMemoryHolder", "");
                        if(a_holder.sameType(Base::ClassCount<V>::get()) || a_holder.sameBaseType(Base::ClassCount<V>::get())){
                            this->setDuoTypeHolder(a_holder.getHolder());
                        }
                        DuoTypeMemberLog(pankey_Log_EndMethod, "copyDuoTypeMemoryHolder", "");
                    }

                    virtual bool sameDuoType(long a_type)const{
                        DuoTypeMemberLog(pankey_Log_StartMethod, "sameDuoType", "");
                        if(a_type == -1){
                            DuoTypeMemberLog(pankey_Log_Error, "sameDuoType", "a_type == -1");
                            DuoTypeMemberLog(pankey_Log_EndMethod, "sameDuoType", "");
                            return false;
                        }
                        long i_type = this->getDuoType();
                        if(i_type == -1){
                            DuoTypeMemberLog(pankey_Log_Error, "sameDuoType", "i_type != -1");
                            DuoTypeMemberLog(pankey_Log_EndMethod, "sameDuoType", "");
                            return false;
                        }
                        DuoTypeMemberLog(pankey_Log_EndMethod, "sameDuoType", "");
                        return i_type == a_type;
                    }

                    virtual bool sameDuoBaseType(long a_type)const{
                        DuoTypeMemberLog(pankey_Log_StartMethod, "sameDuoBaseType", "");
                        if(a_type == -1){
                            DuoTypeMemberLog(pankey_Log_Error, "sameDuoBaseType", "a_type == -1");
                            DuoTypeMemberLog(pankey_Log_EndMethod, "sameDuoBaseType", "");
                            return false;
                        }
                        long i_type = this->getDuoBaseType();
                        if(i_type == -1){
                            DuoTypeMemberLog(pankey_Log_Error, "sameDuoBaseType", "i_type == -1");
                            DuoTypeMemberLog(pankey_Log_EndMethod, "sameDuoBaseType", "");
                            return false;
                        }
                        DuoTypeMemberLog(pankey_Log_EndMethod, "sameDuoBaseType", "");
                        return i_type == a_type;
                    }

                    virtual bool isDuoTypeMember(MANAGER_TYPE a_manager, long a_type)const{
                        DuoTypeMemberLog(pankey_Log_StartMethod, "isDuoTypeMember", "");
                        DuoTypeMemberLog(pankey_Log_EndMethod, "isDuoTypeMember", "");
                        return this->shareManager(a_manager) && (this->sameDuoType(a_type) || this->sameDuoBaseType(a_type));
                    }

                    virtual bool isDuoTypeMember(HOLDER_TYPE a_holder, MANAGER_TYPE a_manager)const{
                        DuoTypeMemberLog(pankey_Log_StartMethod, "isDuoTypeMember", "");
                        auto i_type = MemoryHolderManager<H>::getType(a_manager, a_holder);
                        DuoTypeMemberLog(pankey_Log_EndMethod, "isDuoTypeMember", "");
                        return this->isDuoTypeMember(a_manager, i_type);
                    }

                    virtual bool isDuoTypeMember(HOLDER_TYPE a_holder)const{
                        DuoTypeMemberLog(pankey_Log_StartMethod, "isDuoTypeMember", "");
                        DuoTypeMemberLog(pankey_Log_EndMethod, "isDuoTypeMember", "");
                        return this->isDuoTypeMember(a_holder, this->getManager());
                    }

                    virtual bool isDuoTypeMember(const MemoryHolder<H>& a_holder)const{
                        DuoTypeMemberLog(pankey_Log_StartMethod, "isDuoTypeMember", "");
                        auto i_manager = a_holder.getManager();
                        auto i_type = a_holder.getType();
                        DuoTypeMemberLog(pankey_Log_EndMethod, "isDuoTypeMember", "");
                        return this->isDuoTypeMember(i_manager, i_type);
                    }

                    virtual void setDuoType(long a_type){
                        DuoTypeMemberLog(pankey_Log_StartMethod, "setDuoType", "");
                        MemoryHolderManager<H>::setType(this->getManager(), this->m_duo_holder, a_type);
                        DuoTypeMemberLog(pankey_Log_EndMethod, "setDuoType", "");
                    }

                    virtual long getDuoType()const{
                        DuoTypeMemberLog(pankey_Log_StartMethod, "getDuoType", "");
                        DuoTypeMemberLog(pankey_Log_EndMethod, "getDuoType", "");
                        return MemoryHolderManager<H>::getType(this->getManager(), this->m_duo_holder);
                    }

                    virtual void setDuoBaseType(long a_type){
                        DuoTypeMemberLog(pankey_Log_StartMethod, "setDuoBaseType", "");
                        MemoryHolderManager<H>::setBaseType(this->getManager(), this->m_duo_holder, a_type);
                        DuoTypeMemberLog(pankey_Log_EndMethod, "setDuoBaseType", "");
                    }

                    virtual long getDuoBaseType()const{
                        DuoTypeMemberLog(pankey_Log_StartMethod, "getDuoBaseType", "");
                        DuoTypeMemberLog(pankey_Log_EndMethod, "getDuoBaseType", "");
                        return MemoryHolderManager<H>::getBaseType(this->getManager(), this->m_duo_holder);
                    }

                    virtual bool isDuoTypeMemoryNull()const{
                        DuoTypeMemberLog(pankey_Log_StartMethod, "isDuoTypeMemoryNull", "");
                        if(this->m_duo_holder == nullptr){
                            DuoTypeMemberLog(pankey_Log_EndMethod, "isDuoTypeMemoryNull", "this->m_duo_holder == nullptr");
                            return true;
                        }
                        VOID_TYPE i_pointer = MemoryHolderManager<H>::get(this->getManager(), this->m_duo_holder);
                        DuoTypeMemberLog(pankey_Log_Statement, "isDuoTypeMemoryNull", "isDuoNull: ");
                        DuoTypeMemberLog(pankey_Log_Statement, "isDuoTypeMemoryNull", i_pointer == nullptr);
                        DuoTypeMemberLog(pankey_Log_EndMethod, "isDuoTypeMemoryNull", "");
                        return i_pointer == nullptr;
                    }

                    //unsafe method
                    virtual VOID_TYPE getDuoTypeRawPointer()const{
                        DuoTypeMemberLog(pankey_Log_StartMethod, "getDuoTypeRawPointer", "");
                        VOID_TYPE i_pointer = MemoryHolderManager<H>::get(this->getManager(), this->m_duo_holder);
                        DuoTypeMemberLog(pankey_Log_Statement, "getDuoTypeRawPointer", "VOID_TYPE is null?");
                        DuoTypeMemberLog(pankey_Log_Statement, "getDuoTypeRawPointer", i_pointer == nullptr);
                        DuoTypeMemberLog(pankey_Log_EndMethod, "getDuoTypeRawPointer", "");
                        return i_pointer;
                    }
                    
                    virtual DuoTypeMember<K,V,H,M>& operator=(const DuoTypeMember<K,V,H,M>& a_duo_member){
                        DuoTypeMemberLog(pankey_Log_StartMethod, "operator=", "");
                        this->setHolder(a_duo_member.getHolder());
                        this->setDuoTypeHolder(a_duo_member.getDuoTypeHolder());
                        DuoTypeMemberLog(pankey_Log_EndMethod, "operator=", "");
                        return *this;
                    }
                    
                    virtual void operator=(const MemoryHolder<H>& a_holder){
                        DuoTypeMemberLog(pankey_Log_StartMethod, "operator=", "");
                        if(a_holder.sameType(Base::ClassCount<K>::get()) || a_holder.sameBaseType(Base::ClassCount<K>::get())){
                            this->setHolder(a_holder.getHolder());
                            DuoTypeMemberLog(pankey_Log_EndMethod, "Constructor", "");
                            return;
                        }
                        if(a_holder.sameType(Base::ClassCount<V>::get()) || a_holder.sameBaseType(Base::ClassCount<V>::get())){
                            this->setDuoTypeHolder(a_holder.getHolder());
                            DuoTypeMemberLog(pankey_Log_EndMethod, "Constructor", "");
                            return;
                        }
                        DuoTypeMemberLog(pankey_Log_EndMethod, "operator=", "");
                    }
                    
                    virtual void operator=(const Member<H,M>& a_holder){
                        DuoTypeMemberLog(pankey_Log_StartMethod, "operator=", "");
                        if(a_holder.sameType(Base::ClassCount<K>::get()) || a_holder.sameBaseType(Base::ClassCount<K>::get())){
                            this->setHolder(a_holder.getHolder());
                            DuoTypeMemberLog(pankey_Log_EndMethod, "Constructor", "");
                            return;
                        }
                        if(a_holder.sameType(Base::ClassCount<V>::get()) || a_holder.sameBaseType(Base::ClassCount<V>::get())){
                            this->setDuoTypeHolder(a_holder.getHolder());
                            DuoTypeMemberLog(pankey_Log_EndMethod, "Constructor", "");
                            return;
                        }
                        DuoTypeMemberLog(pankey_Log_EndMethod, "operator=", "");
                    }
                    
                    virtual bool operator!=(const DuoTypeMember<K,V,H,M>& a_duo_member){
                        DuoTypeMemberLog(pankey_Log_StartMethod, "operator!=", "");
                        DuoTypeMemberLog(pankey_Log_EndMethod, "operator!=", "");
                        return this->getHolder() == a_duo_member.getHolder() && this->getDuoTypeHolder() == a_duo_member.getDuoTypeHolder();
                    }
                    
                    virtual bool operator==(const DuoTypeMember<K,V,H,M>& a_duo_member){
                        DuoTypeMemberLog(pankey_Log_StartMethod, "operator==", "");
                        DuoTypeMemberLog(pankey_Log_EndMethod, "operator==", "");
                        return this->getHolder() != a_duo_member.getHolder() && this->getDuoTypeHolder() != a_duo_member.getDuoTypeHolder();
                    }
                    
                    virtual bool isNull()const{
                        DuoTypeMemberLog(pankey_Log_StartMethod, "isDuoTypeMemberNull", "");
                        DuoTypeMemberLog(pankey_Log_EndMethod, "isDuoTypeMemberNull", "");
                        return this->isMemoryNull() && this->isDuoTypeMemoryNull();
                    }
                
                protected:

                    HOLDER_TYPE m_duo_holder = nullptr;
            };

        }

	}

#endif