#pragma once
#include "MayhemObjects.h"

class MayhemObjectHandle
{
public:
	explicit MayhemObjectHandle(MayhemObjects* mayhemObjects, unsigned _int32 handleIndex);

	~MayhemObjectHandle();

	bool ObjectExists() const;

	void Update(double);

	// Setters
	bool SetEnabled(const bool);
	bool SetPosition(const glm::vec3);
	bool SetRotation(const glm::quat);

	bool SetDirection(const glm::vec3);
	bool SetAmbient(const glm::vec3);
	bool SetDiffuse(const glm::vec3);
	bool SetSpecular(const glm::vec3);

	bool SetConstant(const float);
	bool SetLinear(const float);
	bool SetQuadratic(const float);
	bool SetCutOff(const float);
	bool SetOuterCutOff(const float);


	// Getters
	bool IsEnabled() const;
	glm::vec3 GetPosition() const;
	glm::quat GetRotation() const;

	glm::vec3 GetDirection() const;
	glm::vec3 GetAmbient() const;
	glm::vec3 GetDiffuse() const;
	glm::vec3 GetSpecular() const;

	float GetConstant() const;
	float GetLinear() const;
	float GetQuadratic() const;
	float GetCutOff() const;
	float GetOuterCutOff() const;

	std::string GetDirectory() const;
	glm::mat4 GetTransform() const;
	Shader* GetShader() const;

private:
	unsigned _int32 m_uniqueId;
	unsigned _int32 m_handleIndex;
	MayhemObjects* m_mayhemObjects;
};

