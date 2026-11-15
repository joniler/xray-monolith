#pragma once

#include "telekinetic_object.h"
#include "../../../xrphysics/PHUpdateObject.h"
#include "../../../xrphysics/IPhysicsShellHolder.h"

// Collision hit callback for an object a monster throws at the actor. The first real impact on the actor is
// credited to the monster and costs the actor at least min_damage health; a heavy, fast object can do more,
// as computed by the collision damage. A graze (or the object resting against the actor) does not use up the
// hit, and once the throw is over the object is an ordinary object again. The monster is kept by id because it
// can be destroyed while the object is still in the air.
class CTeleProjectileHitCallback : public ICollisionHitCallback
{
	u16 m_monster_id;
	float m_min_damage;
	u32 m_expire_time;
	bool m_done;

public:
	CTeleProjectileHitCallback(u16 monster_id, float min_damage, u32 lifetime_ms);
	void call(CObject*& obj, float min_cs, float max_cs, float& cs, float& hl, ICollisionDamageInfo* di) override;
};


class CTelekinesis : public CPHUpdateObject
{
protected:
	DEFINE_VECTOR(CTelekineticObject*, TELE_OBJECTS, TELE_OBJECTS_IT);
	TELE_OBJECTS objects;
	xr_vector<CObject*> m_nearest;
	bool active;

public:
	CTelekinesis();
	virtual ~CTelekinesis();

	// allocates relevant TelekineticObject


	// активировать объект
	virtual CTelekineticObject* activate(CPhysicsShellHolder* obj, float strength, float height, u32 max_time_keep,
	                                     bool rot = true);

	// деактивировать все объекты
	void deactivate();

    void remove_object_callbacks();

	//clear objects (does not call release, but call switch to TS_None)
	void clear_deactivate();
	// clear 
	virtual void clear();
	virtual void clear_notrelevant();
	// деактивировать объект
	void deactivate(CPhysicsShellHolder* obj);
	void remove_object(TELE_OBJECTS_IT it);
	void remove_object(CPhysicsShellHolder* obj);
	// бросить все объекты в позицию 'target'
	void fire_all(const Fvector& target);

	// бросить объект 'obj' в позицию 'target' с учетом коэф силы 
	void fire(CPhysicsShellHolder* obj, const Fvector& target, float power);

	// бросить объект 'obj' в позицию 'target' с учетом коэф силы 
	void fire_t(CPhysicsShellHolder* obj, const Fvector& target, float time);


	// вернуть активность телекинеза
	bool is_active() { return active; }

	// вернуть активность объекта		
	bool is_active_object(CPhysicsShellHolder* obj);

	// вернуть количество контролируемых объектов (в состоянии TS_Raise & TS_Keep)
	u32 get_objects_count();

	// вернуть количество контролируемых объектов (всех)
	u32 get_objects_total_count() { return objects.size(); }


	// вернуть объект по индексу в массиве
	// a	copy of the object!
	CTelekineticObject get_object_by_index(u32 index)
	{
		VERIFY(objects.size() > index);
		return *objects[index];
	}

	// обновить состоняие на shedule_Update			
	void schedule_update();

	// объект был удален - удалить все связи на объект
	void remove_links(CObject* O);

protected:
	virtual CTelekineticObject* alloc_tele_object() { return xr_new<CTelekineticObject>(); }
private:

	// обновление на шагах физики
	virtual void PhDataUpdate(float step);
	virtual void PhTune(float step);
};
