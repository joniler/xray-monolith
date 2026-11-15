#ifndef I_COLLISION_DAMAGE_INFO_H
#define I_COLLISION_DAMAGE_INFO_H
//struct SCollisionHitCallback;
class ICollisionHitCallback;

// Breakdown of the contact that produced the current ContactVelocity(), for the
// ph_log_collision_damage console log. Velocities are along the contact normal.
struct SCollisionDamageDbgInfo
{
	bool from_object; // damage from a moving object; false for level geometry and for own motion into a fixed/frozen object
	u16 source_id; // contacted object, u16(-1) for level geometry
	bool source_fixed; // contacted object is fixed (frozen by script, fixed bone)
	float source_mass; // kg, 0 if not from_object
	float self_normal_vel; // m/s
	float source_normal_vel; // m/s, 0 if not from_object
	float accepted_energy; // J, kinetic energy converted to contact velocity (from_object only)
	float material_factor; // bounce_damage_factor of the contacted material
	LPCSTR material_name;

	SCollisionDamageDbgInfo() { reset(); }

	void reset()
	{
		from_object = false;
		source_id = u16(-1);
		source_fixed = false;
		source_mass = 0.f;
		self_normal_vel = 0.f;
		source_normal_vel = 0.f;
		accepted_energy = 0.f;
		material_factor = 0.f;
		material_name = "";
	}
};

class ICollisionDamageInfo
{
public:
	virtual float ContactVelocity() const =0;
	virtual void GetDbgInfo(SCollisionDamageDbgInfo& info) const =0;
	virtual void HitDir(Fvector& dir) const =0;
	virtual const Fvector& HitPos() const =0;
	virtual u16 DamageInitiatorID() const =0;
	virtual CObject* DamageInitiator() const =0;
	virtual ALife::EHitType HitType() const =0;
	virtual ICollisionHitCallback* HitCallback() const =0;
	virtual void Reinit() =0;
	virtual void SetInitiated() =0;
	virtual bool IsInitiated() const =0;
	virtual bool GetAndResetInitiated() =0;
protected:
	virtual ~ICollisionDamageInfo() = 0
	{
	}
};
#endif
